#include "math.h"
Matrix::Matrix(std::vector<std::vector<long double>>& v){
	m = v;}
Matrix::Matrix(){
	m = {};}
int Matrix::size(){
	return m.size();}
std::vector<long double>& Matrix::operator [] (int i){
	return m[i];}
long double Matrix::det(){
	long double sum = 0;
	std::vector<std::vector<long double>> v = {};
	std::vector<long double> row = {};
	if(m.size() == 2){
		sum = (m[0][0] * m[1][1] - m[0][1]*m[1][0]);
	}
	else{
		for(int i = 0; i < m.size(); ++i){
			for(int j = 1; j < m.size(); ++j){
				row.clear();
				for(int h = 0; h < m.size(); ++h){
					if(h != i)
						row.push_back(m[j][h]);
				}
				v.push_back(row);
			}
			Matrix m1(v);
			v.clear();
			sum += pow(-1,i)*m[0][i]*m1.det(); 
		}
	}
	return sum;}
SLAE::SLAE(std::vector<std::vector<long double>> V1, std::vector<long double> V2){
	A.m = V1;
	B = V2;}
SLAE::SLAE(Matrix& M, std::vector<long double> V){
	A = M;
	B = V;}
Matrix& Matrix::operator = (const Matrix& other){
	(this -> m) = (other.m);
	return *this;}
std::vector<long double> SLAE::solve(){
	std::vector<long double> solution;
	long double d0 = A.det();
	for(int i = 0; i < A.size();++i){
		Matrix tmp = A;
		for(int j = 0; j < A.size(); ++j)
			tmp[j][i] = B[j];
		long double d = tmp.det();
		solution.push_back(d / d0);
	}
	return solution;}

long double powerAp(std::map<double,long double>& mp, double power, int n, int N){
	if(power == 0)
		return constAp(mp,n,N);
	std::vector<long double> a, b;
	for(int i = 0; i < 2*power; ++i)
		a.push_back(0);
	for(int i = 0; i < power+1; ++i)
		b.push_back(0);
	for(double xi = n; xi <= N; ++xi){
		for(int i = 0; i < 2*power;++i)
			a[i] += pow(xi,i+1);
		for(int i = 0; i < power + 1; ++i)
			b[i] += mp[xi]*pow(xi,power - i);
	}
	Matrix M;
	for(int i = 0; i < power + 1; ++i){
		std::vector<long double> row = {};
		for(int j = 0; j < power + 1; ++j){
		//	std::cout << int(a.size() - 1 - i - j) << "  AAAAAAAAA" << std::endl;
			if(int(a.size() - 1 - i - j) < 0)
				row.push_back(N);
			else
				row.push_back(a[a.size() - 1 - i - j]);
		}
		M.m.push_back(row);
	}
	SLAE sl(M, b);
	std::vector<long double> solution = sl.solve();
	auto F = [&solution, &power](long double xi) -> long double{
		long double result = 0;
		for(int i = 0; i < power + 1; ++i){
			result += solution[i] * pow(xi, power - i);
		}
		return result;
	};
	long double result = 0;
	for(double xi = n; xi <= N; xi+=0.25){
		result += (F(xi) - mp[xi])*(F(xi) - mp[xi]);
	}
	return result;
}
long double constAp(std::map<double,long double>& mp,int n, int N){
	long double a = 0;
	for(double xi = n; xi <= N; ++xi){
		a += mp[xi];
	}
	long double c = a / N;
	long double res = 0;
	for(double xi = n; xi <= N; xi+=0.25){
		res += ((mp[xi] - c)*(mp[xi] - c));
	}
	return res;
}

bool is_prime(int n) {
  try{
  	if(n <= 0)
  		throw "bool is_prime: argument is less than 0 or is 0";
  }
  catch(const char* s){
  		std::cout << s << std::endl;
  		return false;
  }
  if(n == 1) 
  	return false; 
  if(n == 2 || n == 3) 
  	return true; 
  if(n % 2 == 0 || n % 3 == 0) return false; 
  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return false;
    }
  }
  return true;
}
std::vector<std::pair<int,int>> canon(int x){
	if(is_prime(x))
		return {{x,1}};
	std::vector<std::pair<int,int>> res;
	int i = 2;
	while(1){
		if(i > x)
			break;
		if(is_prime(i)){
			if(x % i == 0){
				res.push_back({i,0});
				while(x % i == 0){
					res[res.size()-1].second++;
					x = x / i;
				}
			}
			i++;
		}
		else
			i++;
	}
	return res;
}