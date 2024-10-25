#include <math.h>
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