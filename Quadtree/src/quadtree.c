#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quadtree.h"

void
init(img *image, qtnode **node, int sx, int sy, int fx, int fy, int fact)
{
    (*node) = malloc(sizeof(qtnode));
    printf("sx: %d, sy: %d, fx: %d, fy: %d\n", sx, sy, fx, fy);
    printf("Allocated memory.\n");
    (*node)->mean.r = 0;
    (*node)->mean.g = 0;
    (*node)->mean.b = 0;
    (*node)->area = (fy - sy) * (fx - sx);
    for (int i = sy; i < fy; i++) {
        for (int j = sx; j < fx; j++) {
            printf("r: %d, g: %d, b: %d\n", image->data[i][j].r, image->data[i][j].g, image->data[i][j].b);
            (*node)->mean.r += image->data[i][j].r;
            (*node)->mean.g += image->data[i][j].g;
            (*node)->mean.b += image->data[i][j].b;
        }
    }
    //printf("Precalc mean: r: %d, g: %d, b: %d\n", (*node)->mean.r, (*node)->mean.g, (*node)->mean.b);
    (*node)->mean.r = (*node)->mean.r / (*node)->area;
    (*node)->mean.g = (*node)->mean.g / (*node)->area;
    (*node)->mean.b = (*node)->mean.b / (*node)->area;
    //printf("Postcalc mean: r: %d, g: %d, b: %d\n", (*node)->mean.r, (*node)->mean.g, (*node)->mean.b);

    rgb de;
    de.r = 0;
    de.g = 0;
    de.b = 0;
    int cont = 0;
    for (int i = sy; i < fy; i++) {
        for (int j = sx; j < fx; j++) {
            cont++;
            de.r += pow((image->data[i][j].r - (*node)->mean.r), 2);
            de.g += pow((image->data[i][j].g - (*node)->mean.g), 2);
            de.b += pow((image->data[i][j].b - (*node)->mean.b), 2);
            //de.r += pow((image->data[i][j].r - (*node)->mean.r), 2) / (*node)->area;
            //de.g += pow((image->data[i][j].g - (*node)->mean.g), 2) / (*node)->area;
            //de.b += pow((image->data[i][j].b - (*node)->mean.b), 2) / (*node)->area;
        }
    }
    de.r = sqrt((double)de.r / (*node)->area);
    de.g = sqrt((double)de.g / (*node)->area);
    de.b = sqrt((double)de.b / (*node)->area);

    printf("cont: %d, area: %d\n", cont, (*node)->area);
    printf("mean: r: %d, g: %d, b: %d\n", (*node)->mean.r, (*node)->mean.g, (*node)->mean.b);
    printf("de.r = %d, de.g = %d, de.b = %d\n", de.r, de.g, de.b);
    //if (de.r < fact && de.g < fact && de.b < fact) {
    if ((fx - sx <= 1 || fy - sy <= 1) || (de.r < fact && de.g < fact && de.b < fact)) {
         for (int i = sy; i < fy; i++) {
            for (int j = sx; j < fx; j++) {
                image->data[i][j].r = (*node)->mean.r;
                image->data[i][j].g = (*node)->mean.g;
                image->data[i][j].b = (*node)->mean.b;
            }
        }
        (*node)->top_left = NULL;
        (*node)->top_right = NULL;
        (*node)->bottom_left = NULL;
        (*node)->bottom_right = NULL;
    } else {
        int tx = (sx + fx) / 2;
        int ty = (sy + fy) / 2;
        init(image, &((*node)->top_left), sx, sy, tx, ty, fact);
        init(image, &((*node)->top_right), tx, sy, fx, ty, fact);
        init(image, &((*node)->bottom_left), sx, ty, tx, fy, fact);
        init(image, &((*node)->bottom_right), tx, ty, fx, fy, fact);
    }

}

void
compress(img *image, qtnode **node, int factor)
{
    node = malloc(sizeof(qtnode*));
    init(image, node, 0, 0, image->width, image->height, factor);
    char *cname = "compressed.image";
    FILE *res = fopen(cname, "w");
    //fwrite(image->header, sizeof(unsigned char), 54, res);
    reccompress(image, node, res);
    fclose(res);
}

void
reccompress(img *image, qtnode **node, FILE *res)
{
    //printf("reccompress %d\n", (*node)->area);
    if ((*node)->top_left != NULL && (*node)->top_right != NULL && (*node)->bottom_left != NULL && (*node)->bottom_right != NULL) {
        //printf("if\n");
        reccompress(image, &(*node)->top_left, res);
        reccompress(image, &(*node)->top_right, res);
        reccompress(image, &(*node)->bottom_left, res);
        reccompress(image, &(*node)->bottom_right, res);
    } else {
        //printf("else\n");
        char data[10];
        snprintf(data, 10, "%d,%d,%d", (*node)->mean.r, (*node)->mean.g, (*node)->mean.b);
        fwrite(data, sizeof(char), 54, res);
    }
}
