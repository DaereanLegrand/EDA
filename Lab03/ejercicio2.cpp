#include <bits/stdc++.h>
#include <chrono>

typedef long long ll;

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::milliseconds;


void 
calc(ll dim, ll s1)
{
    auto t1 = high_resolution_clock::now();

    ll **vv = new ll*[s1];
    auto start = chrono::system_clock::now();
    for (ll i = 0; i < s1; i++) {
        ll temp = 0;
        vv[i] = new ll[dim];
        for (ll j = 0; j < dim; j++) {
            vv[i][j] = rand() % 1000; 
        }
    }

    for (ll i = 1; i < s1; i++) {
        ll temp = 0;
        for (ll j = 0; j < dim; j++) {
            temp += pow(vv[0][j] - vv[i][j], 2);
        }
        ll res = sqrt(temp);
    }
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    cout << "Con " << dim << " dimensiones y " << s1 << " puntos " << ms_double.count() << " milisegundos." << endl;
}

int
main()
{
    calc(1000, 100);    
    calc(10000, 100);    
    calc(50000, 100);    
}
