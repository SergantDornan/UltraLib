#include <math.h>
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
std::ostream& operator <<(std::ostream& out, Function& f){
	out << f.k << std::endl;
	return out;
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
long double Function::operator[](int i){
	if(i >= k.size()){
		std::cout << "=========================== ERROR ===========================" << std::endl;
		std::cout << "= mathFunction.cpp: long double Function::operator[](int i) =" << std::endl;
		std::cout << "index is out of vector (k) range" << std::endl;
		std::cout << "k.size(): " << k.size() << " index: " << i << std::endl;
		std::cout << "also for this operation mode must be 'pow', now mode is: " << mode << std::endl;
		std::cout << "=============================================================" << std::endl;
		return 0;
	}
	else
		return k[i];
}
Function::Function(std::map<double,long double>& mp, double p){
	*this = powerAp(mp,p);
}