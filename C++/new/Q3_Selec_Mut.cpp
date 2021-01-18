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
#define M 10000000
#define N 100
#define P0 35
#define mu 0.008

//static const int values [12] = {-1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1};
static const int values [6] = {1, 1, 1, 2, 2, 3};

double trajectoire(){
    mt19937 gen = mt19937(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
    uniform_int_distribution<> dist_uniform_int = uniform_int_distribution<>(0, 5);
    bernoulli_distribution distribution_(0.5);
    bernoulli_distribution distribution(0.125 / 2.);
    //int prix[M][N];
    vector<vi> prix(M, vi(N));

    vector<vector<bool> > sign (M, vector<bool> (N));
    vector<bool> sign_act(M);

    // Init sauts et les signes
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            prix[i][j] = 0;
            sign[i][j] = distribution(gen);
        }
    }
    for (int i = 0; i < M; i++){
        sign_act[i] = distribution_(gen);
        if (sign_act[i]) prix[i][0] = (P0 + values[dist_uniform_int(gen)]);
        else prix[i][0] = (P0 - values[dist_uniform_int(gen)]);
    }
    // Selection-mutation
    double facteurDroite = 1.;
    for (int i = 0; i < N - 1; i++){
        vector<double> weights(M);
        double sum = 0.;
        for (int j = 0; j < M; j++){
            weights[j] = exp(-mu * prix[j][i]);
            sum += weights[j];
        }
        facteurDroite *= sum / (double) M;
        discrete_distribution<int> distribution(weights.begin(), weights.end());
        // np.random.choice
        vector<int> indices(M);
        generate(indices.begin(), indices.end(), [&gen, &distribution]() {return distribution(gen);});
        
        // selection - mutation
        vector<vi> new_prix(M, vi(N));
        vector<bool> new_sign (M);

        for (int j = 0; j < M; j++){
            for (int k = 0; k <= i; k++){
                new_prix[j][k] = prix[j][k];
            }
            new_sign[j] = sign_act[j];
        }
        for (int j = 0; j < M; j++){
            int indice_loc = indices[j];
            sign_act[j] = (new_sign[indice_loc] && (sign[j][i])) || (!new_sign[indice_loc] && !sign[j][i]);
            for (int k = 0; k <= i; k++){
                prix[j][k] = new_prix[indice_loc][k];
            }
            if (sign_act[j]) prix[j][i + 1] = (prix[j][i] + values[dist_uniform_int(gen)]);
            else prix[j][i + 1] = (prix[j][i] - values[dist_uniform_int(gen)]);
        }
    }
    double res = 0.;
    for (int j = 0; j < M; j++){
        double facteurGauche;
        double sum = 0.;
        bool inferieur_0 = false;
        for (int i = 0; i < N - 1; i++){
            sum += prix[j][i];
            if (prix[j][i] < 0) inferieur_0 = true;
        }
        facteurGauche = exp(mu * sum);
        res += inferieur_0 * facteurGauche;
    }
    res *= facteurDroite / (double) M;
    return res;
}

int main(){
    uint64_t t = -duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout<<trajectoire()<<endl;

    t += duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout<<setw(10)<<t<<" ms\t"<<endl;
}
