#include "kmeans.h"
#include <stdlib.h>
#include <limits.h>
#include <math.h>

Cluster::Cluster()
{

}

Cluster::Cluster(rgb col, int ux, int uy):
    color(col), x(ux), y(uy)
{

}

kmeans::kmeans(img *uimage, int uk):
    image(uimage), n(uk)
{
    means = new rgb[n];
    clusters = new std::vector<Cluster>[n];
}

void
kmeans::initialize()
{
    for (int i = 0; i < n; i++) {
        int tx = (rand() % image->width);
        int ty = (rand() % image->height);
        means[i] = image->data[ty][tx];
    }
}

void
kmeans::clusterize(int iter)
{ 
    for (int i = 0; i < n; i++) {
        clusters[i].clear();
    }

    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            int dist = INT_MAX;
            int mink = -1;
            for (int k = 0; k < n; k++) {
                int tdist = rgbdistance(means[k], image->data[i][j]);
                if (tdist < dist) {
                    dist = tdist;
                    mink = k;
                }
            }
            clusters[mink].push_back(Cluster(image->data[i][j], j, i));
        }
    }

    for (int i = 0; i < n; i++) {
        rgb mean;
        mean.r = mean.g = mean.b = 0;
        for (auto j: clusters[i]) {
            mean.r += j.color.r;
            mean.g += j.color.g;
            mean.b += j.color.b;
        }
        if (clusters->size() != 0) {
            means[i].r = mean.r / clusters[i].size();
            means[i].g = mean.g / clusters[i].size();
            means[i].b = mean.b / clusters[i].size();
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (auto j: clusters[i]) {
            image->data[j.y][j.x] = means[i];
        }
    }
}

int
rgbdistance(rgb a, rgb b)
{
    return sqrt(pow(a.r - b.r, 2) + pow(a.g - b.g, 2) + pow(a.b - b.b, 2));
}
