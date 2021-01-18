#include "ThreadPool.h"
#include <random>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <mutex>
#include <cmath>

using namespace std;
using namespace chrono;
#define vi vector<int>

//static const int values [12] = {-1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1};
static const int values [12] = {-3, -2, -2, -1, -1, -1, 1, 1, 1, 2, 2, 3};

void IC_quantile(vi& quantiles, double niveau){
    int n = quantiles.size();
    int index_ = (int) ceil(n * niveau) - 1;
    int niveau_inf = (int) ceil(n * (niveau - 1.96 * sqrt(niveau * (1-niveau) / n))) - 1;
    int niveau_sup = (int) ceil(n * (niveau + 1.96 * sqrt(niveau * (1-niveau) / n))) - 1;
    cout<<"Quantile au niveau "<<niveau<<" = "<<quantiles[index_]<<", avec intervalle de confiance = "<<quantiles[niveau_inf]<<", "<<quantiles[niveau_sup]<<endl;
}

int echantillon(mt19937& gen, uniform_int_distribution<>& dist, int N){
    int P0 = 35;
    for (int i = 0; i < N; i++){
        P0 += values[dist(gen)];
        //cout << P0 << ' ' << endl;
    }
    return P0;
}

void quantile(int size){
    mt19937 gen = mt19937(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
    poisson_distribution<int> dist_poi = poisson_distribution<int> (14400. / 300.);
    uniform_int_distribution<> dist_uniform_int = uniform_int_distribution<>(0, 11);
    int ruines = 0;
    vi results(size);
    while (size--){
        int n = dist_poi(gen);
        results[size] = echantillon(gen, dist_uniform_int, n);
    }
    sort(results.begin(), results.end());
    vector<double> niveaus = {0.000001, 0.00001, 0.0001, 1 - 0.0001, 1 - 0.00001, 1 - 0.000001};
    for (auto i: niveaus) IC_quantile(results, i);
}

int main(){
    uint64_t t = -duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    quantile(10000000);

    t += duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout<<setw(10)<<t<<" ms\t"<<endl;
}
