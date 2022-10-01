#include <sys/types.h>

typedef struct rgb {
    int r, g, b;
} rgb;

typedef struct img {
    unsigned char header[54];
    rgb **data;
    int32_t height, width;
    int row_padded;
} img;

void write_modified(img image);
img mainBMP(char *filename);
