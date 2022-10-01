#pragma once
#include "bmp.h"
#include <stdio.h>

typedef struct qtnode {
    int sx, sy, fx, fy;
    int area;
    rgb mean;
    struct qtnode *top_right, *top_left;
    struct qtnode *bottom_right, *bottom_left;
} qtnode;


void init(img*, qtnode**, int, int, int, int, int);
void compress(img*, qtnode**, int);
void reccompress(img*, qtnode**, FILE*);
