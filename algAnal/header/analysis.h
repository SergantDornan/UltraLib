#include <chrono>
#include <thread>
#include <mutex>
#include "algs.h"
const int n = 1000;
const int N = 5000;
extern "C" int mainfunc(int args, char* argv[]);
extern "C" int entry(int argc, char* argv[]);
void points(std::map<double,long double>& , int , int);
void Iteration(std::map<int,int>&,bool);
void time_control();
const int defaultIterations = std::thread::hardware_concurrency();