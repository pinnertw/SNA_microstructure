#pragma once
#include "preambule.hpp"
using namespace std;

#define vi vector<int>
#define pi pair<int, int>

//    Q1
class Q1{
    private:
        int P0;
        int T;
        double lamb;
        int m;

    public:
        Q1(int, int, double, int);
        ~Q1();
        void ruines_once(Sum&);
        long double ruines(int);
        int quantiles_once();
        pi quantiles(int, double);
};
