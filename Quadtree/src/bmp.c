#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "bmp.h"

/*
struct RGB {
    int r, g, b;
} RGB;

typedef struct RGB rgb;

struct IMG {
    unsigned char header[54];
    rgb **data;
    int32_t height, width;
    int row_padded;
} IMG;

typedef struct IMG img;
*/

void
write_modified(img image)
{
    char *fname = "adultered.bmp";
    FILE *res = fopen(fname, "w");
    unsigned char *data;
    printf("Name of wrote file: %s\nWidth: %d\nHeight: %d\n", fname, image.width, image.height);
    fwrite(image.header, sizeof(unsigned char), 54, res);
    for (int i = 0; i < image.height; i++) {
        data = (unsigned char *)malloc(sizeof(char) * image.row_padded);
        for (int j = 0; j < image.width * 3; j+=3) {
            data[j] = image.data[i][j / 3].b;
            data[j + 1] = image.data[i][j / 3].g;
            data[j + 2] = image.data[i][j / 3].r;
            //data[j] = image.data[i][j / 3].b + 20;
            //data[j + 1] = 0; //image.data[i][j / 3].g - 5;
            //data[j + 2] = image.data[i][j / 3].r + 20;
        }
        fwrite(data, sizeof(unsigned char), image.row_padded, res);
        free(data);
    }
    fclose(res);
    system("sxiv adultered.bmp");
}

img
mainBMP(char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");
    img original;

    if(f == NULL)
        printf("Argument exception\n");

    fread(original.header, sizeof(unsigned char), 54, f); // lee la cabecera

    original.width = 0;
    original.height = 0;
    for (int i = 0; i < 4; i++) {
        original.width += (int)original.header[i + 18] * pow(16, i * 2);
        original.height += (int)original.header[i + 22] * pow(16, i * 2);
    }

    printf("Name of read file: %s\nWidth: %d\nHeight: %d\n", filename, original.width, original.height);

    original.row_padded = (original.width * 3 + 3) & (~3);
    unsigned char* data = (unsigned char*)malloc(sizeof(char) * original.row_padded);
    char tmp;

    rgb **rgbtabledata = (rgb**)malloc(sizeof(rgb*) * original.height);
    for(int i = 0; i < original.height; i++) {
        rgbtabledata[i] = (rgb*)malloc(sizeof(rgb) * original.width);
        fread(data, sizeof(unsigned char), original.row_padded, f);
        for(int j = 0; j < original.width*3; j += 3) {
            rgbtabledata[i][j / 3].r = (int)data[j + 2];
            rgbtabledata[i][j / 3].g = (int)data[j + 1];
            rgbtabledata[i][j / 3].b = (int)data[j];
            //printf("r: %d, g: %d, b: %d\n", rgbtabledata[i][j / 3].r, rgbtabledata[i][j / 3].g, rgbtabledata[i][j / 3].b);
        }
    }
    original.data = rgbtabledata;
    fclose(f);
    //write_modified(original);
    return original;
}
