#include "math.h"
Matrix::Matrix(const std::vector<std::vector<long double>> v){
	m = v;}
void Matrix::set(const std::vector<std::vector<long double>> v){
	m = v;
}
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
SLAE::SLAE(){

}
SLAE::SLAE(const std::vector<std::vector<long double>> V1,const std::vector<long double> V2){
	A.m = V1;
	B = V2;}
SLAE::SLAE(Matrix& M,const std::vector<long double> V){
	A = M;
	B = V;}
void SLAE::set(const std::vector<std::vector<long double>> V1, const std::vector<long double> V2){
	A.m = V1;
	B = V2;
}
void SLAE::set(Matrix& M, const std::vector<long double> V){
	A = M;
	B = V;
}
Matrix& Matrix::operator = (const Matrix& other){
	(this -> m) = (other.m);
	return *this;}
std::vector<long double> SLAE::solve(){
	std::vector<long double> solution;
	if(A.size() < A[0].size()){
		std::cout << "===================================== SLAE solution, number of rows less than nunber of variables =====================================" << std::endl;
		return solution;
	}
	else if(A.size() > A[0].size()){
		std::cout << "===================================== SLAE solution, number of rows bigger than nunber of variables =====================================" << std::endl;
		std::cout << "========================================================== Undefined behaviour ==========================================================" << std::endl;
		return solution;
	}
	long double d0 = A.det();
	for(int i = 0; i < A.size();++i){
		Matrix tmp = A;
		for(int j = 0; j < A.size(); ++j)
			tmp[j][i] = B[j];
		long double d = tmp.det();
		solution.push_back(d / d0);
	}
	return solution;}
Function::Function(long double(*func)(long double, std::vector<long double>, double), std::vector<long double> solution, double p){
		power = p;
		f = func;
		k = solution;
}
long double Function::operator()(long double x){
		return f(x,k,power);
}

Function powerAp(std::map<double,long double>& mp, double power){
	std::vector<long double> a, b;
	for(int i = 0; i < 2*power; ++i)
		a.push_back(0);
	for(int i = 0; i < power+1; ++i)
		b.push_back(0);
	for(auto el : mp){
		for(int i = 0; i < 2*power;++i)
			a[i] += pow(el.first,i+1);
		for(int i = 0; i < power + 1; ++i)
			b[i] += el.second*pow(el.first,power - i);
	}
	Matrix M;
	for(int i = 0; i < power + 1; ++i){
		std::vector<long double> row = {};
		for(int j = 0; j < power + 1; ++j){
		//	std::cout << int(a.size() - 1 - i - j) << "  AAAAAAAAA" << std::endl;
			if(int(a.size() - 1 - i - j) < 0)
				row.push_back(mp.size());
			else
				row.push_back(a[a.size() - 1 - i - j]);
		}
		M.m.push_back(row);
	}
	SLAE sl(M, b);
	std::vector<long double> solution = sl.solve();
	auto F = [](long double xi, std::vector<long double> solution, double power) -> long double{
		long double result = 0;
		for(int i = 0; i < power + 1; ++i){
			result += solution[i] * pow(xi, power - i);
		}
		return result;
	};
	Function result(F,solution,power);
	return result;
	// long double result = 0;
	// for(double xi = n; xi <= N; xi+=0.25){
	// 	result += (F(xi) - mp[xi])*(F(xi) - mp[xi]);
	// }
}
long double constAp(std::map<double,long double>& mp){
	long double a = 0;
	for(auto el : mp){
		a += el.second;
	}
	long double c = a / mp.size();
	long double res = 0;
	for(auto el : mp){
		res += ((el.second - c)*(el.second - c));
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
EqSys::EqSys(){}
EqSys::EqSys(const std::vector<std::string> v){
		set(v);
}
void EqSys::set(const std::vector<std::string> v){
		std::vector<std::vector<long double>> tempA;
		std::vector<std::vector<long double>> A;
		std::vector<std::vector<std::string>> tempNames;
		std::vector<long double> B;
		for(int n = 0; n < v.size(); ++n){
			std::string s = v[n];
			auto line = split(s, "+-=", "-");
			Range<std::string> r({{'a','z'},{'A','Z'}});
			std::vector<long double> Drow;
			std::vector<std::string> Srow;
			for(int i = 0; i < line.size(); ++i){
				if(!r(line[i])){
					std::stringstream stream;
					stream << line[i];
					long double k;
					stream >> k;
					B.push_back(k);	
				}
				else{
					auto subline = split(line[i], "*");
					if(subline.size() == 1){
						if(subline[0][0] == '-'){
							Drow.push_back(-1);
							Srow.push_back(std::string(subline[0].begin() + 1, subline[0].end()));
						}
						else{
							Drow.push_back(1);
							Srow.push_back(subline[0]);
						}
					}
					else{
						for(int j = 0; j < subline.size(); ++j){
						if(r(subline[j])){
							Srow.push_back(subline[j]);
						}
						else{
							long double k;
							std::stringstream stream;
							stream << subline[j];
							stream >> k;
							Drow.push_back(k);
						}
					}
					}
				}
				for(int i = 0; i < Srow.size(); ++i){
					if(find(names, Srow[i]) == -1){
						names.push_back(Srow[i]);
					}
				}
			}
			tempA.push_back(Drow);
			tempNames.push_back(Srow); 
		}
		for(int i = 0; i < tempA.size(); ++i){
			std::vector<long double> row;
			for(int j = 0; j < names.size(); ++j)
				row.push_back(0);
			for(int j = 0; j < names.size(); ++j){
				int pos = find(tempNames[i], names[j]);
				if(pos != -1){
					row[j] = tempA[i][pos];
				}
			}
			A.push_back(row);
		}
 		s.set(A,B);
}
std::istream& operator >> (std::istream& in, EqSys& eq){	
		std::cout << "End system with //" << std::endl;
		std::vector<std::string> v;
		while(true){
			std::string s;
			std::getline(in,s,'\n');
			s = strip(s);
			if(s == "$" || s == "$$" || s == "|" || s == "||" || s == "/" || s == "//")
				break;
			v.push_back(s);
		}
		eq.set(v);
		return in;
}
std::ostream& operator << (std::ostream& out, EqSys& eq){
	auto solution = eq.s.solve();
	for(int i = 0; i < eq.names.size(); ++i){
		out << eq.names[i] << "  " << solution[i] << std::endl;
	}
	out << '\n';
	return out;
}
std::ostream& operator <<(std::ostream& out, Function& f){
	out << f.k << std::endl;
	return out;
}
long double lim(long double(*f)(long double x),Range<double> range,std::string mode, long double start,long double e){
		long double prev = 1000;
		long double res = 0;
		int count = 0;
		if(mode == "inf" || mode == "+inf"){
			if(start < 0)
				start*=-1;
		}
		else if(mode == "-inf"){
			if(start > 0)
				start *= -1;
		}
		else{
			std::cout << "====================================================== ERROR ======================================================" << std::endl;
			std::cout << "============== math.cpp::lim(f, std::string, long double, long double) ==============" << std::endl;
			std::cout << "============== Unknown mode: " << mode << " =============="<<std::endl;
			std::cout << "=================== Enter +inf or -inf ===================" << std::endl;
			return 0;
		}
		while(abs(prev - res) > e){
				prev = res;
				res = f(start);
				start*=2;
				count++;
				if(count > 100000){
					if(mode == "-inf")
						return -1000000;
					else
						return 1000000;
				}
		}
		return res;
}
long double lim(long double(*f)(long double),long double x0, long double e){
	long double left, right;
	if(x0 < 0){
		left = x0*1000;
		right = -x0*1000;
	}
	else if(x0 > 0){
		left = -x0*1000;
		right = x0*1000;
	}
	else{
		left = -1000;
		right = 1000;
	}
	long double prev1 = 1000, prev2 = 1000;
	long double res1 = 0, res2 = 0;
	while(abs(prev1 - res1) > e){
		
	}
}