#pragma once
#include <random>
#include <mutex>
#include <iostream>
#include <chrono>
using namespace std;;

struct Sum{
    int sum = 0;
    mutex mu;
    void incre(){
        mu.lock();
        sum++;
        mu.unlock();
    }
};

static const int thread_max_1 = 5;
static const int thread_max_2 = 4;
static const int values [12]= {-3, -2, -2, -1, -1, -1, 1, 1, 1, 2, 2, 3};
