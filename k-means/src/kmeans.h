#include "bmp.h"
#include <vector>

class Cluster {
    public:
    rgb color;
    int x, y;
    Cluster();
    Cluster(rgb, int, int);
};

class kmeans {
    public:
    int n;
    img *image;
    rgb *means;
    std::vector<Cluster> *clusters;
    kmeans(img*, int);
    void initialize();
    void clusterize(int);
};

int rgbdistance(rgb, rgb);
