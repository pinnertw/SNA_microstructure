#include "ThreadPool.h"
#include "Q1.hpp"
#include <vector>
#include <algorithm>

using namespace std;

#define vi vector<int>
#define pi pair<int, int>
//    Q1

Q1::Q1(int P0_, int T_, double lamb_, int m_){
    P0 = P0_;
    T = T_;
    lamb = lamb_;
    m = m_;
}

Q1::~Q1(){}

void Q1::ruines_once(Sum& sum){
    // Random init
    using namespace chrono;
    mt19937_64 gen = mt19937_64(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
    int N = poisson_distribution<int> (T * lamb)(gen);
    uniform_int_distribution<> dist_uniform_int (0, 11);

    int somme = P0;
    for (int i = 0; i < N; i++){
        somme += (m == 1)? (dist_uniform_int(gen) % 2) * 2 - 1 : values[dist_uniform_int(gen)];
        if (somme < 0){
            sum.incre();
            return;
        }
    }
    return;
}


long double Q1::ruines(int size){
    Sum ruine;
    ctpl::thread_pool p(thread_max_1);
    int i = 0;
    while(i < size){
        auto task =  bind(&Q1::ruines_once, this, ref(ruine));
        p.push(task);
        i++;
    }
    p.stop(true);
    return (long double) ruine.sum / (long double) size;
}

int Q1::quantiles_once(){
    // init random
    using namespace chrono;
    mt19937_64 gen = mt19937_64(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
    int N = poisson_distribution<int> (T * lamb)(gen);
    uniform_int_distribution<> dist_uniform_int (0, 11);

    int somme = P0;
    for (int i = 0; i < N; i++){
        somme += (m == 1)? (dist_uniform_int(gen) % 2) * 2 - 1 : values[dist_uniform_int(gen)];
    }
    return somme;
}

pi Q1::quantiles(int size, double quantile){
    vi echant (size, 0);
    // (size) echantillionages.
    for (int i = 0; i < size; i++){
        echant[i] = quantiles_once();
    }
    int index_bot = int(ceil(size * quantile));
    nth_element(echant.begin(), echant.begin() + index_bot, echant.end());
    int bot = echant[index_bot];
 
    int index_top = int(ceil(size * (1. - quantile)));
    if (index_top == size) index_top--;
    nth_element(echant.begin(), echant.begin() + index_top, echant.end());
    int top = echant[index_top];
 
    return pi(bot, top);
}
