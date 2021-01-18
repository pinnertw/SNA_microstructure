#pragma once
#include "preambule.hpp"
using namespace std;

#define pi pair<int, int>
//    Q2
class Q2{
    private:
        int P0;
        int T;
        double lamb1;
        double lamb2;
        int m;
    public:
        Q2(int, int, double, double, int);
        ~Q2();
        void ruines_once(Sum&);
        long double ruines(int);
};
