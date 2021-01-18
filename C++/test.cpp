#include"preambule.hpp"
#include<iostream>
#include<cmath>
#include<chrono>
using namespace std;


static mt19937_64 gen = mt19937_64(1);

int main(){
    poisson_distribution<int> dist_poisson(363.);
    cout<<dist_poisson(gen)<<' '<<dist_poisson(gen)<<' '<<dist_poisson(gen)<<' '<<dist_poisson(gen)<<' '<<endl;
    cout<<dist_poisson(gen)<<' '<<dist_poisson(gen)<<' '<<dist_poisson(gen)<<' '<<dist_poisson(gen)<<' '<<endl;
    cout<<dist_poisson(gen)<<' '<<dist_poisson(gen)<<' '<<dist_poisson(gen)<<' '<<dist_poisson(gen)<<' '<<endl;
    cout<<dist_poisson(gen)<<' '<<dist_poisson(gen)<<' '<<dist_poisson(gen)<<' '<<dist_poisson(gen)<<' '<<endl;
    /*

    using namespace chrono;
    cout<< duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count()<<endl;
    int i = 2, t0 = 3, t = 5;
    cout<<"Processing..."<<i<<"/"<<10000<<", ETA : "<<t0 + (t - t0) * 10000 / i<<"s";
    int ruine = 5;
    int size = 100000;
    cout<<(long double) ruine / (long double) size;
    cout<<endl;
    double sum = 0.;
    for (int i = 0; i < size; i++){
        sum += preambule(1, 14400, 1./300.).exponential_time();
    }
    cout<<sum / (double) size<<endl;
    */

}
