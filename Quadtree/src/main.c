#include "quadtree.h"
#include <stdio.h>
#include <stdlib.h>

int 
main(int argc, char *argv[]) 
{
    if (argc == 3) {
        char* name = argv[1];
        img image = mainBMP(name);
        qtnode **node;
        /*
        for (int i = 0; i < 64; i++) {
            for (int j = 0; j < 64; j++) {
                image.data[i][j].r = 0;
                image.data[i][j].g = 0;
                image.data[i][j].b = 0;
            }
        }
        for (int i = 64; i < 128; i++) {
            for (int j = 0; j < 64; j++) {
                image.data[i][j].r = 10; 
                image.data[i][j].g = 10;
                image.data[i][j].b = 10;
            }
        }
        for (int i = 0; i < 64; i++) {
            for (int j = 64; j < 128; j++) {
                image.data[i][j].r = 40;
                image.data[i][j].g = 40;
                image.data[i][j].b = 40;
            }
        }
        for (int i = 64; i < 128; i++) {
            for (int j = 64; j < 128; j++) {
                image.data[i][j].r = 50;
                image.data[i][j].g = 50;
                image.data[i][j].b = 50;
            }
        }
        */
        compress(&image, node, atoi(argv[2]));
        write_modified(image);
    }
    return 0;
}
