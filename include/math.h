#ifndef math_h
#define math_h
#include <cmath>
#include <algs.h>
class Matrix{
public:
	std::vector<std::vector<long double>> m;
	Matrix();
	Matrix(std::vector<std::vector<long double>>&);
	long double det();
	int size();
	std::vector<long double>& operator [] (int);
	Matrix& operator = (const Matrix&);
};
class SLAE{
public:
	Matrix A;
	std::vector<long double> B;
	SLAE(std::vector<std::vector<long double>>, std::vector<long double>);
	SLAE(Matrix&, std::vector<long double>);
	std::vector<long double> solve();
};
long double powerAp(std::map<double,long double>&, double, int, int);
long double constAp(std::map<double,long double>& mp, int, int);


bool is_prime(int);
std::vector<std::pair<int,int>> canon(int);
#endif