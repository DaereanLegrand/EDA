#include <stdio.h>
#include "quadtree.hpp"

void
init(qtnode **node, int **data, int ssx, int ssy, int ffx, int ffy)
{
    (*node) = new qtnode;
    (*node)->data = data;

    (*node)->sx = ssx;
    (*node)->sy = ssy;
    (*node)->fx = ffx;
    (*node)->fy = ffy;

    if ((ffx - ssx <= 1 || ffy - ssy <= 1)) {
        (*node)->top_left = NULL;
        (*node)->top_right = NULL;
        (*node)->bottom_left = NULL;
        (*node)->bottom_right = NULL;
    } else {
        int tx = (ssx + ffx) / 2;
        int ty = (ssy + ffy) / 2;
        init(&((*node)->top_left), data, ssx, ssy, tx, ty);
        init(&((*node)->top_right), data, tx, ssy, ffx, ty);
        init(&((*node)->bottom_left), data, ssx, ty, tx, ffy);
        init(&((*node)->bottom_right), data, tx, ty, ffx, ffy);
    }
}

void
find(qtnode** node, int l, int r)
{
    if ((*node)->data[(*node)->sy][(*node)->sx] >= l && (*node)->data[(*node)->fy - 1][(*node)->fx - 1] <= r) {
        for (int i = (*node)->sy; i < (*node)->fy; i++) {
            for (int j = (*node)->sx; j < (*node)->fx; j++) {
                printf("%d ", (*node)->data[i][j]);
            }
            printf("\n");
        }
    } else if ((*node)->top_left != NULL) {
        find(&((*node)->top_left), l , r);
        find(&((*node)->top_right), l, r);
        find(&((*node)->bottom_left), l, r);
        find(&((*node)->bottom_right), l, r);
    }
}
