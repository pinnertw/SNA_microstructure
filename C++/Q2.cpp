#include "Q2.hpp"
#include"ThreadPool.h"
using namespace std;

#define vi vector<int>
#define pi pair<int, int>

//    Q2
Q2::Q2(int P0_, int T_, double lamb1_, double lamb2_, int m_){
    P0 = P0_;
    T = T_;
    lamb1 = lamb1_;
    lamb2 = lamb2_;
    m = m_;
}

Q2::~Q2(){}

void Q2::ruines_once(Sum& sum){
    using namespace chrono;
    mt19937_64 gen = mt19937_64(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
    uniform_int_distribution<> dist_uniform_int(0, 11);
    exponential_distribution<> dist_exp_1(lamb1);
    exponential_distribution<> dist_exp_2(lamb2);

    int J2 = (dist_uniform_int(gen) % 2) * 2 - 1;
    int somme = P0;
    double T1 = dist_exp_1(gen);
    double T2 = dist_exp_2(gen);
    while (T1 <= T){
        while ((T2 < T) && T2 < T1){
            somme += J2;
            if (somme < 0) {
                sum.incre();
                return;
            }
            J2 *= -1;
            T2 += dist_exp_2(gen);
        }
        somme += (m == 1)? (dist_uniform_int(gen) % 2) * 2 - 1 : values[dist_uniform_int(gen)];
        if (somme < 0) {
            sum.incre();
            return;
        }
        T1 += dist_exp_1(gen);
    }
    return;
}


long double Q2::ruines(int size){
    Sum ruine;
    ctpl::thread_pool p(thread_max_2);
    int i = 0;
    while(i < size){
        auto task = bind(&Q2::ruines_once, this, ref(ruine));
        p.push(task);
        i++;
    }
    p.stop();
    return (long double) ruine.sum / (long double) size;
}
