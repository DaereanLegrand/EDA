#include <bits/stdc++.h>
#include <chrono>

typedef long long ll;

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::milliseconds;


struct triplet {
    int x, y, z;
    triplet(int rx, int ry, int rz) : x(rx), y(ry), z(rz) {  }
};

triplet*
initializa(ll n)
{
    triplet *t = (triplet*)malloc(sizeof(triplet) * n);
    for (ll i = 0; i < n; i++) {
        t[i] = triplet(rand() % 1000, rand() % 1000, rand() % 1000);
    }
    return t;
}

typedef triplet tp;

void 
calc(ll s1)
{
    auto t1 = high_resolution_clock::now();

    tp *n1 = initializa(s1);    
    auto start = chrono::system_clock::now();
    for (ll i = 1; i < s1; i++) {
        ll temp = sqrt(pow(n1[0].x - n1[i].x, 2) + pow(n1[0].y - n1[i].y, 2) + pow(n1[0].z - n1[i].z, 2));
    }
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    cout << "Con " << s1 << " puntos " << ms_double.count() << " milisegundos." << endl;
}

int
main()
{
    calc(1000);    
    calc(10000);    
    calc(50000);    
}
