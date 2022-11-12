#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kmeans.h"

int 
main(int argc, char *argv[]) 
{
    if (argc == 3) {
        char* name = argv[1];
        img image = mainBMP(name);
        kmeans mk(&image, atoi(argv[2]));
        mk.initialize();
        mk.clusterize(10);
        write_modified(image, argv[1], argv[2]);
    }
    return 0;
}
