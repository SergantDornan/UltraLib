#ifndef math_h
#define math_h
#include <cmath>
#include <algs.h>
class Matrix{
public:
	std::vector<std::vector<long double>> m;
	Matrix();
	Matrix(const std::vector<std::vector<long double>>);
	long double det();
	int size();
	void set(const std::vector<std::vector<long double>>);
	std::vector<long double>& operator [] (int);
	Matrix& operator = (const Matrix&);
};
class SLAE{
public:
	Matrix A;
	std::vector<long double> B;
	SLAE();
	SLAE(const std::vector<std::vector<long double>>,const std::vector<long double>);
	SLAE(Matrix&,const std::vector<long double>);
	void set(const std::vector<std::vector<long double>>, const std::vector<long double>);
	void set(Matrix&, const std::vector<long double>);
	std::vector<long double> solve();
};
class EqSys{
public:
	std::vector<std::string> names;
	SLAE s;
	EqSys();
	EqSys(const std::vector<std::string>);
	void set(const std::vector<std::string>);
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
std::ostream& operator << (std::ostream&,EqSys&);
std::vector<std::pair<int,int>> canon(int);
#endif