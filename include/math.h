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
class EqSys{
public:
	std::vector<std::string> names;
	SLAE s;
};

class Function{
public:
	long double(*f)(long double x, std::vector<long double> k, double power);
	std::vector<long double> k;
	double power;
	Function(long double(*func)(long double, std::vector<long double>, double), std::vector<long double> solution, double p);
	long double operator()(long double x);
};

Function powerAp(std::map<double,long double>&, double);
long double constAp(std::map<double,long double>& mp);
bool is_prime(int);
std::istream& operator >> (std::istream&,EqSys&);
std::vector<std::pair<int,int>> canon(int);
#endif