#ifndef math_h
#define math_h
#include <cmath>
#include <algs.h>
long double lim(std::function<long double(long double)> f,Range<long double> range = Range<long double>("-inf","+inf"),
	std::string mode = "inf", long double start = 10000,long double e = 0.001);
long double lim(std::function<long double(long double)> f,std::string mode = "inf",
	Range<long double> range = Range<long double>("-inf","+inf"),long double start = 10000,long double e = 0.001);
long double lim(std::function<long double(long double)> f,long double x0, long double left = -0.001, long double right = 0.001,
	Range<long double> range = Range<long double>("-inf", "+inf"), long double e = 0.001);
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
	Range<long double> range;
	std::string mode;
	std::function<long double(long double)>simpfunc;
	std::function<long double(long double,std::vector<long double>, double)>f;
	std::vector<long double> k;
	double power;
	Function(std::function<long double(long double,std::vector<long double>, double)> func, 
		std::vector<long double> solution, double p, Range<long double> r);
	Function(std::function<long double(long double,std::vector<long double>, double)> func, 
		std::vector<long double> solution, double p);
	Function(std::function<long double(long double)> func, Range<long double> r);
	Function(std::function<long double(long double)> func);
	Function(Range<long double> r = Range<long double>("-inf","inf"));
	long double operator()(long double x);
	Function der(std::string m = "simp");
	Function& operator = (std::function<long double(long double)>);
	long double der(long double);
	long double defDer(long double, long double left = -0.001, long double right = 0.001);
};
long double lim(Function& f,
	std::string mode = "inf", long double start = 10000, long double e = 0.001);
long double lim(Function& f, long double x0, long double left = -0.001, long double right = 0.001, 
	long double e = 0.001);
Function powerAp(std::map<double,long double>&, double);
bool is_prime(int);
std::istream& operator >> (std::istream&,EqSys&);
std::ostream& operator << (std::ostream&,EqSys&);
std::ostream& operator << (std::ostream&, Function&);
std::vector<std::pair<int,int>> canon(int);
#endif