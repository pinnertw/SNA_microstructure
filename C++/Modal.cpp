#include "preambule.hpp"
#include "Q1.hpp"
#include "Q2.hpp"

#include<ctime>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

#define vi vector<int>
#define pi pair<int, int>

string questions []= {"  ", "Q1-1", "Q1-2", "Q2-1"};
string methods []= {"  ", "Méthode de Monte-Carlo naïf", "Méthode de Monte-Carlo naïf", "Méthode de Monte-Carlo naïf"};

//       PRINT
void print_Q(int Q, int size, int P0, int T, int m, double quant){
    if (abs(quant - 0) < 0.0000000001) cout<<setw(8)<<questions[Q]<<"\t"<<setw(13)<<size<<"\t"<<setw(5)<<P0<<"\t"<<setw(13)<<T<<"\t"<<m<<"\t"<<setw(10)<<"-\t";
    else cout<<setw(8)<<questions[Q]<<"\t"<<setw(13)<<size<<"\t"<<setw(5)<<P0<<"\t"<<setw(13)<<T<<"\t"<<m<<"\t"<<setw(10)<<quant<<"\t";
}

void print_ruines(long double ruines, int size){
    cout<<setw(9)<<ruines<<"+/-" << setw(9)<<setprecision(6)<<1.96 * sqrt(ruines * (1 - ruines)) / (long double) sqrt(size)<<"\t";
}

void print_quant(pi quants){
    cout<<setw(10)<<quants.first<<' '<<setw(10)<<quants.second<<"\t";
}

//        TEST
void Q1_1_MC_naif(int size, int P0, int T, double lamb, int m){
    Q1 inst = Q1(P0, T, lamb, m);
    print_ruines(inst.ruines(size), size);
}

void Q1_2_MC_naif(int size, int P0, int T, double lamb, int m, double quantile){
    Q1 inst = Q1(P0, T, lamb, m);
    print_quant(inst.quantiles(size, quantile));
}

void Q2_1_MC_naif(int size, int P0, int T, double lamb1, double lamb2, int m){
    Q2 inst = Q2(P0, T, lamb1, lamb2, m);
    print_ruines(inst.ruines(size), size);
}

int main(){
    int t, Q, size, P0, T, m;
    double quant;
    string temp;
    getline(cin, temp);
    getline(cin, temp);
    cin>>t;
    int index = 1;
    while (t--){
        cerr<<"Processing the "<<index++<<" test"<<endl;
        using namespace std::chrono;
        uint64_t t = -duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

        cin>>Q>>size>>P0>>T>>m>>quant;
        print_Q(Q, size, P0, T, m, quant);

        if (Q == 1){
            Q1_1_MC_naif(size, P0, T, 1. / 300., m);
        }
        else if (Q == 2){
            Q1_2_MC_naif(size, P0, T, 1. / 300., m, quant);
        }
        else if (Q == 3){
            Q2_1_MC_naif(size, P0, T, 1. / 660., 1. / 110., m);
        }
        t += duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        cout<<setw(10)<<t<<" ms\t"<<methods[Q]<<"\n"<<endl;
    }
  //Q1_1_MC_naif(size, P0, T, lamb, m);
  //Q1_2_MC_naif(size, P0, T, lamb, m, quant);
  //Q2_1_MC_naif(size, P0, T, lamb1, lamb2, m);
  return 0;
}
