#include <cmath>
#include "algs.h"
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
