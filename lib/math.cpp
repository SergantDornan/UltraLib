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
Function::Function(std::function<long double(long double,std::vector<long double>, double)> func,
 std::vector<long double> solution, double p, Range<long double> r){
		power = p;
		f = func;
		k = solution;
		range = r;
		mode = "pow";
}
Function::Function(std::function<long double(long double)> func, Range<long double> r){
		power = 0;
		simpfunc = func;
		range = r;
		mode = "simp";
}
Function::Function(std::function<long double(long double,std::vector<long double>, double)> func,
 std::vector<long double> solution, double p){
		power = p;
		f = func;
		k = solution;
		Range<long double> tmp("-inf","inf");
		range = tmp;
		mode = "pow";
}
Function::Function(std::function<long double(long double)> func){
		power = 0;
		simpfunc = func;
		Range<long double> tmp("-inf","inf");
		range = tmp;
		mode = "simp";
}
Function::Function(Range<long double> r){
	power = 0;
	k = {};
	range = r;
}
long double Function::operator()(long double x){
		if(range(x)){
			if(mode == "pow")
				return f(x,k,power);
			else if(mode == "simp")
				return simpfunc(x);
		}
		else{
			std::cout << "======================== ERROR ========================" << std::endl;
			std::cout << "math.cpp: long double Function::operator()(long double x)" << std::endl;
			std::cout << "argument is out of range" << std::endl;
			return 0;
		}
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
long double lim(std::function<long double(long double)> f,Range<long double> range,
	std::string mode, long double start,long double e){
		long double prev = 1000;
		long double res = 0;
		int count = 0;
		if(mode == "inf" || mode == "+inf"){
			if(range.max() < pow(10,9)){
				std::cout << "====================================================== ERROR ======================================================" << std::endl;
				std::cout << "============== math.cpp::lim(std::function,Range<double>, std::string, long double, long double) ==============" << std::endl;
				std::cout << "============== Function right range is not +inf, but you trying to find lim x -> +inf ==============" <<std::endl;
				return 0;
			}
			if(start < 0)
				start*=-1;
		}
		else if(mode == "-inf"){
			if(range.min() > -pow(10,9)){
				std::cout << "====================================================== ERROR ======================================================" << std::endl;
				std::cout << "============== math.cpp::lim(std::function,Range<double>, std::string, long double, long double) ==============" << std::endl;
				std::cout << "============== Function left range is not -inf, but you trying to find lim x -> -inf ==============" <<std::endl;
				return 0;
			}
			if(start > 0)
				start *= -1;
		}
		else{
			std::cout << "====================================================== ERROR ======================================================" << std::endl;
			std::cout << "============== math.cpp::lim(std::function,Range<double>, std::string, long double, long double) ==============" << std::endl;
			std::cout << "============== Unknown mode: " << mode << " =============="<<std::endl;
			std::cout << "=================== Enter +inf or -inf ===================" << std::endl;
			return 0;
		}
		while(abs(prev - res) > e){
				prev = res;
				if(range(start))
					res = f(start);
				else{
					start*=2;
					continue;
				}
				
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
long double lim(std::function<long double(long double)> f,std::string mode,
	Range<long double> range,long double start,long double e){
		long double prev = 1000;
		long double res = 0;
		int count = 0;
		if(mode == "inf" || mode == "+inf"){
			if(range.max() < pow(10,9)){
				std::cout << "====================================================== ERROR ======================================================" << std::endl;
				std::cout << "============== math.cpp::lim(std::function,std::string, Range<double>, long double, long double) ==============" << std::endl;
				std::cout << "============== Function right range is not +inf, but you trying to find lim x -> +inf ==============" <<std::endl;
				return 0;
			}
			if(start < 0)
				start*=-1;
		}
		else if(mode == "-inf"){
			if(range.min() > -pow(10,9)){
				std::cout << "====================================================== ERROR ======================================================" << std::endl;
				std::cout << "============== math.cpp::lim(std::function,std::string, Range<double>, long double, long double) ==============" << std::endl;
				std::cout << "============== Function left range is not -inf, but you trying to find lim x -> -inf ==============" <<std::endl;
				return 0;
			}
			if(start > 0)
				start *= -1;
		}
		else{
			std::cout << "====================================================== ERROR ======================================================" << std::endl;
				std::cout << "============== math.cpp::lim(std::function,std::string, Range<double>, long double, long double) ==============" << std::endl;
			std::cout << "============== Unknown mode: " << mode << " =============="<<std::endl;
			std::cout << "=================== Enter +inf or -inf ===================" << std::endl;
			return 0;
		}
		while(abs(prev - res) > e){
				prev = res;
				if(range(start))
					res = f(start);
				else{
					start*=2;
					continue;
				}
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
long double lim(std::function<long double(long double)> f,long double x0, long double left, long double right,
	Range<long double> range, long double e){

	if(range.min() > -pow(10,9))
		left = range.min();
	else if(x0 != 0)
		left = (int(x0 < 0)*2 - 1) * x0 * 1000;


	if(range.max() < pow(10,9))
		right = range.max();
	else if(x0 != 0)
		right = (int(x0 > 0)*2 - 1)*x0*1000;


	long double prev1 = 1000, prev2 = 1000;
	long double res1 = 0, res2 = 0;
	int count = 0;
	while(abs(prev1 - res1) > e){
		prev1 = res1;
		if(range(left)){
			res1 = f(left);
		//	std::cout << left << ' ' << res1 << std::endl;
			left += ((x0 - left) / 2);
			
		}
		else{
			left += ((x0 - left) / 2);
			continue;
		}
		count++;
		if(count > 100000){
			std::cout << "=============================== ERROR ===============================" << std::endl;
			std::cout << "math.cpp: lim(std::function, long double, Range<double, long double>)" << std::endl;
			std::cout << "left lim error: while count > 100000, smth is wrong idk" << std::endl;
			return 0;
		}
	}
	while(abs(prev2 - res2) > e){
		prev2 = res2;
		if(range(right)){
			res2 = f(right);
		//	std::cout << "AAAAAAAAAAAAAAA " << right << ' '<< res2 << ' ' << x0 << std::endl;
			right -= ((right - x0) / 2);
		}
		else{
			right -= ((right - x0) / 2);
			continue;
		}
		count++;
		if(count > 100000){
			std::cout << "=============================== ERROR ===============================" << std::endl;
			std::cout << "math.cpp: lim(std::function, long double, Range<double, long double>)" << std::endl;
			std::cout << "right lim error: while count > 100000, smth is wrong idk" << std::endl;
			return 0;
		}
	}
	if(abs(res1 - res2) <= e){
		return ((res1 + res2) / 2);
	}
	else{
		std::cout << "=============================== ERROR ===============================" << std::endl;
		std::cout << "math.cpp: lim(std::function, long double, Range<double, long double>)" << std::endl;
		std::cout << "left lim if not equal right lim => lim is diverging, idk what to do" << std::endl;
		return 0;
	}
}
Function Function::der(std::string m){
	if(m == "pow"){ 
		std::vector<long double> newk;
		double newp = power - 1;
		for(int i = 0; i < k.size()-1;++i){
			newk.push_back(k[i]*(power-i));
		}
		return Function(f,newk, newp);
	}
	else{
		std::cout << "=============================== ERROR ===============================" << std::endl;
		std::cout << "math.cpp: Function Function::der(std::string mode)" << std::endl;
		std::cout << "Unknown mode: " << m << std::endl;
		return Function();
	}
}
long double Function::der(long double x){
	if(mode == "pow"){
		auto f = der(mode);
		return f(x);
	}
	else
		return defDer(x);
}
long double Function::defDer(long double x, long double left, long double right){
		if(mode == "pow"){
				auto F = [&](long double arg){
						return (f(x + arg,k,power) - f(x,k,power)) / arg;
				};
				return lim(F, 0,left,right);
		}
		else if(mode == "simp"){
				auto F = [&](long double arg){
						return (simpfunc(x + arg) - simpfunc(x)) / arg;
				};
				return lim(F, 0,left,right);
		}
		else{
			std::cout << "=============================== ERROR ===============================" << std::endl;
		std::cout << "math.cpp: Function Function::defDer(long double)" << std::endl;
		std::cout << "Unknown mode: " << mode << std::endl;
		return 0;
		}
}
Function& Function::operator=(std::function<long double(long double)> func){
	Range<long double> tmp("-inf", "inf");
	range = tmp;
	mode = "simp";
	simpfunc = func;
	return *this;
}
long double lim(Function& f, std::string mode,
	long double start, long double e){
	auto F = [&](long double xi){
		return f(xi);
	};
	return lim(F,mode,f.range,start,e);
}
long double lim(Function& f, long double x0, long double left, long double right, long double e){
	Range<long double> range = f.range;
	if(range(x0))
		return f(x0);
	else{
		auto F = [&](long double xi){
				return f(xi);
		};
		return lim(F,x0,left,right,range,e);
	}
}