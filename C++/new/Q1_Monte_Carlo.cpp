#include "ThreadPool.h"
#include <random>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <mutex>

using namespace std;
using namespace chrono;
#define vi vector<int>

//static const int values [12] = {-1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1};
static const int values [12] = {-3, -2, -2, -1, -1, -1, 1, 1, 1, 2, 2, 3};

void inf_echantillon(mt19937& gen, uniform_int_distribution<>& dist, int N, int& ruines){
    int P0 = 35;
    for (int i = 0; i < N; i++){
        P0 += values[dist(gen)];
        //cout << P0 << ' ' << endl;
        if (P0 < 0) {
            ruines++;
            break;
        }
    }
}

int trajectoire(int size){
    mt19937 gen = mt19937(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
    poisson_distribution<int> dist_poi = poisson_distribution<int> (14400. / 300.);
    uniform_int_distribution<> dist_uniform_int = uniform_int_distribution<>(0, 11);
    int ruines = 0;
    while (size--){
        int n = dist_poi(gen);
        inf_echantillon(gen, dist_uniform_int, n, ruines);
    }
    return ruines;
}

int main(){
    uint64_t t = -duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout<<trajectoire(1000000)<<endl;

    t += duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout<<setw(10)<<t<<" ms\t"<<endl;
}
