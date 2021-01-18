#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

#define vi vector<int>

// Print quantiles
void IC_quantile(vi& quantiles, double niveau){
    int n = quantiles.size();
    int index_ = (int) ceil(n * niveau) - 1;
    int niveau_inf = (int) ceil(n * (niveau - 1.96 * sqrt(niveau * (1-niveau) / n))) - 1;
    int niveau_sup = (int) ceil(n * (niveau + 1.96 * sqrt(niveau * (1-niveau) / n))) - 1;
    cout<<"Quantile au niveau "<<niveau<<" = "<<quantiles[index_]<<", avec intervalle de confiance = "<<quantiles[niveau_inf]<<", "<<quantiles[niveau_sup]<<endl;
}


