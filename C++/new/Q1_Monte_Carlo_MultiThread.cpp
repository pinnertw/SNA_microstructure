#include "ThreadPool.h"
#include <random>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <mutex>

using namespace std;
using namespace chrono;
#define vi vector<int>

struct Sum{
    int sum = 0;
    mutex mu;
    void incre(){
        mu.lock();
        sum++;
        mu.unlock();
    }
};

//static const int values [12] = {-1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1};
static const int values [12] = {-3, -2, -2, -1, -1, -1, 1, 1, 1, 2, 2, 3};

int inf_echantillon(mt19937& gen, poisson_distribution<int>& dist_poi, uniform_int_distribution<>& dist_uniform_int){
    int P0 = 35;
    int N = dist_poi(gen);
    for (int i = 0; i < N; i++){
        P0 += values[dist_uniform_int(gen)];
        //cout << P0 << ' ' << endl;
        if (P0 < 0) {
            return 1;
        }
    }
    return 0;
}

void trajectoire(int size, Sum& ruines){
    mt19937 gen = mt19937(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
    poisson_distribution<int> dist_poi = poisson_distribution<int> (14400. / 300.);
    uniform_int_distribution<> dist_uniform_int = uniform_int_distribution<>(0, 11);
    int ruine = 0;
    while (size--){
        ruine += inf_echantillon(gen, dist_poi, dist_uniform_int);
    }
    while (ruine--){
        ruines.incre();
    }
}

int trajectoire_multi(int size){
    Sum ruines;
    int threads_nb = 1;
    ctpl::thread_pool p(threads_nb);
    for (int i = 0; i < threads_nb; i++){
        auto task = bind(trajectoire, size / threads_nb, ref(ruines));
        p.push(task);
    }
    p.stop(true);

    return ruines.sum;
}


int main(){
    uint64_t t = -duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout<<trajectoire_multi(1000000)<<endl;

    t += duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout<<setw(10)<<t<<" ms\t"<<endl;
}
