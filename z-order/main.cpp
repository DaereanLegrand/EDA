#include <iostream>
#include <math.h>
#include "quadtree.hpp"

using namespace std;

static const unsigned int B[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF};
static const unsigned int S[] = {1, 2, 4, 8};

int 
zorder(int x,int y)
{
    x = (x | (x << S[3])) & B[3];
    x = (x | (x << S[2])) & B[2];
    x = (x | (x << S[1])) & B[1];
    x = (x | (x << S[0])) & B[0];

    y = (y | (y << S[3])) & B[3];
    y = (y | (y << S[2])) & B[2];
    y = (y | (y << S[1])) & B[1];
    y = (y | (y << S[0])) & B[0];
    return x | (y << 1);
}

int cantbits, maxn;

int
main()
{
    cout << "Enter a number of bits: ";
    cin >> cantbits;
    maxn = pow(2, cantbits);
    int _x = maxn, _y = maxn;

    int **data = new int*[maxn];
    for (int i = 0; i < maxn; i++) {
        if (i == 0) data[0] = new int[maxn * maxn];
        else data[i] = data[i - 1] + maxn;
    }

    for (int i = 0; i < _x; i++) {
        for(int j = 0; j < _y; j++) {
            data[i][j] = zorder(j, i);
            cout << data[i][j] << " ";
        }
        cout << endl;
    }

    qtnode **z;
    z = new qtnode*;
    cout << "Initializing data...\n";
    init(z, data, 0, 0, _x, _y);

    int l = 0;
    int r = 0;
    cout << "Enter inferior range: ";
    cin >> l;
    cout << "Enter superior range: ";
    cin >> r;
    cout << "Finding data in given range...\n";
    find(z, l, r);
    // find(z, 3, 10);

    return 0;
}
