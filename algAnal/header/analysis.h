#include <iostream>
#include <ctime>
#include "algs.h"
#include "analmath.h"
const int n = 100;
const int N = 200;
const int defaultIterations = 5;
long double constAp(std::map<int,long double>&);
long double powerAp(std::map<int,long double>&, double, long double (*)(long double, int));