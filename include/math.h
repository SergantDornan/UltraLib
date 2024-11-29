#ifndef math_h
#define math_h
#include <cmath>
#include <algs.h>
#include <range.h>
#include <inputs.h>
template <class T>
long double lim(const T f,Range<long double> range = Range<long double>("-inf","+inf"),
	std::string mode = "inf", long double start = 10000,long double e = 0.001){
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
template <class T>
long double lim(const T f,std::string mode = "inf",
	Range<long double> range = Range<long double>("-inf","+inf"),long double start = 10000,long double e = 0.001){
	return lim(f,range,mode,start,e);
}
template <class T>
long double lim(const T f,long double x0, long double left = -0.001, long double right = 0.001,
	Range<long double> range = Range<long double>("-inf", "+inf"), long double e = 0.001){
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
class Matrix{
public:
	std::vector<std::vector<long double>> m;
	Matrix();
	Matrix(const std::vector<std::vector<long double>>);
	long double det();
	int size();
	void set(const std::vector<std::vector<long double>>);
	std::vector<long double>& operator [] (int);
	void push_back(const std::vector<long double>);
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
template <class T>
class Function{
public:
	Range<long double> range;
	std::string mode;
	T f;
	std::vector<long double> k;
	double power;
	Function(Function<T>& func){
		range = func.range;
		mode = func.mode;
		f = func.f;
		k = func.k;
		power = func.power;
	}
	Function(const T func,const std::vector<long double> solution,const double p,const Range<long double> r = Range<long double>("-inf","+inf")){
		power = p;
		f = func;
		k = solution;
		range = r;
		mode = "pow";
	}
	Function(const T func, const Range<long double> r = Range<long double>("-inf","+inf")){
		f = func;
		range = r;
		mode = "simp";
		power = 0;
		k = {};
	}
	Function(const Range<long double> r = Range<long double>("-inf","inf")){
		range = r;
		power = 0;
		k = {};
	}
	long double operator()(const long double x){
		if(range(x)){
			if(mode == "pow")
				return f(x,k,power);
			else if(mode == "simp")
				return f(x);
		}
		else{
			std::cout << "======================== ERROR ========================" << std::endl;
			std::cout << "math.h: long double Function::operator()(long double x)" << std::endl;
			std::cout << "argument is out of range" << std::endl;
			return 0;
		}
	}
	Function der(){
		if(mode == "pow"){ 
			std::vector<long double> newk;
			double newp = power - 1;
			for(int i = 0; i < k.size()-1;++i){
				newk.push_back(k[i]*(power-i));
			}
			return Function(f,newk, newp);
		}
		else{
			std::cout << "=============================== ERROR ===============================" << std::endl;
			std::cout << "math.h: Function Function::der(std::string mode)" << std::endl;
			std::cout << "Unknown mode: " << mode << std::endl;
			return Function();
		}
	}
	Function& operator = (const T func){
		f = func;
		return *this;
	}
	Function& operator = (Function& func){
		range = func.range;
		mode = func.mode;
		f = func.f;
		k = func.k;
		power = func.power;
		return *this;
	}
	long double der(long double x){
		if(mode == "pow"){
			auto F = der(mode);
			return F(x);
		}
		else
			return defDer(x);
	}
	long double defDer(long double x, long double left = -0.001, long double right = 0.001){
		if(mode == "pow"){
			auto F = [&](long double arg){
					return (f(x + arg,k,power) - f(x,k,power)) / arg;
			};
			return lim(F, 0,left,right);
		}
		else if(mode == "simp"){
			auto F = [&](long double arg){
					return (f(x + arg) - f(x)) / arg;
			};
			return lim(F, 0,left,right);
		}
		else{
			std::cout << "=============================== ERROR ===============================" << std::endl;
			std::cout << "math.h: Function Function::defDer(long double)" << std::endl;
			std::cout << "Unknown mode: " << mode << std::endl;
			return 0;
		}
	}
	long double operator [](int i){
		if(i >= k.size()){
			std::cout << "=========================== ERROR ===========================" << std::endl;
			std::cout << "= math.h: long double Function::operator[](int i) =" << std::endl;
			std::cout << "index is out of vector (k) range" << std::endl;
			std::cout << "k.size(): " << k.size() << " index: " << i << std::endl;
			std::cout << "also for this operation mode must be 'pow', now mode is: " << mode << std::endl;
			std::cout << "=============================================================" << std::endl;
			return 0;
		}
		else
			return k[i];
	}
};
bool is_prime(int);
int factorial(int);
template <class T1, class T2>
Function<std::function<long double(long double, std::vector<long double>, double)>> powerAp(std::map<T1,T2>& mp,const double power){
	if(power < 0){
		std::cout << "========================= ERROR =========================" << std::endl;
		std::cout << "============ math.h: powerAp() ============" << std::endl;
		std::cout << "power must be non negative, now power is: " << power << std::endl;
		std::cout << "=========================================================" << std::endl;
		return Function<std::function<long double(long double, std::vector<long double>, double)>>();
	}
	else if(power != 0){
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
				if(int(a.size() - 1 - i - j) < 0)
					row.push_back(mp.size());
				else
					row.push_back(a[a.size() - 1 - i - j]);
			}
			M.push_back(row);
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

		return Function<std::function<long double(long double, std::vector<long double>, double)>>(F,solution,power);
	}
	else{
		std::vector<long double> solution;
		long double sum = 0;
		for(auto el : mp)
			sum += el.second;
		solution.push_back(sum / mp.size());
		auto F = [](long double xi, std::vector<long double> solution, double power) -> long double{
			return solution[0];
		};
		return Function<std::function<long double(long double, std::vector<long double>, double)>>(F,solution,power);
	}
}
std::istream& operator >> (std::istream&,EqSys&);
std::ostream& operator << (std::ostream&,EqSys&);
template <class T>
std::ostream& operator <<(std::ostream& out, Function<T>& f){
	out << f.k << std::endl;
	return out;
}
std::vector<std::pair<int,int>> canon(int);
long int C(int,int);
#endif