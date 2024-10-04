#include <clock.h>
std::string generateTime(){
	std::string res = "";
	for(int i = 0; i < 3; ++i){
		int x = 0;
		if(i == 0)
			x = rand() % 24;
		else
			x = rand() % 60;
		if(x < 10)
			res += "0" + std::to_string(x);
		else
			res += std::to_string(x);
		if(i != 2)
			res += ":";
	}	
	return res;
}
// std::chrono::steady_clock::time_point& operator=(std::chrono::steady_clock::time_point& p, std::string& time){
// 	std::chrono::seconds dur;
// 	std::stringstream stream;
// 	if(time.size() == 8){
// 		int h,min,sec;
// 		stream << std::string(time.begin(), time.begin() + 2);
// 		stream >> h;
// 		stream.clear();
// 		stream << std::string(time.begin() + 3, time.begin() + 5);
// 		stream >> min;
// 		stream.clear();
// 		stream << std::string(time.begin() + 6, time.begin() + 8);
// 		stream >> sec;
// 		int Idur = h * 3600 + min*60 + sec;	
// 		dur = std::chrono::seconds(Idur);
// 		p = start + dur;
// 	}
// 	else{
// 		int d,h,min,sec;
// 		stream << std::string(time.begin(), time.begin() + 2);
// 		stream >> d;
// 		stream.clear();
// 		stream << std::string(time.begin() + 3, time.begin() + 5);
// 		stream >> h;
// 		stream.clear();
// 		stream << std::string(time.begin() + 6, time.begin() + 8);
// 		stream >> min;
// 		stream.clear();
// 		stream << std::string(time.begin() + 9, time.begin() + 11);
// 		stream >> sec;
// 		int Idur = d* 24* 3600 + h * 3600 + min*60 + sec;	
// 		dur = std::chrono::seconds(Idur);
// 		p = start + dur;
// 	}
// 	return p;	
// }
// std::chrono::seconds operator-(std::chrono::steady_clock::time_point& p2, std::chrono::steady_clock::time_point& p1){
// 	if(duration_cast<std::chrono::seconds>(p2.time_since_epoch()).count() < duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count()){
// 		if(plusDayAssumption){
// 			auto dur2 = duration_cast<std::chrono::seconds>(p2 - start);
// 			auto dur1 = duration_cast<std::chrono::seconds>(p1 - start);
// 			int Idur2 = dur2;
// 			int Idur1 = dur1;
// 			if((Idur1 / 86400) == (Idur2 / 86400)){
// 				auto day = 86400s;
// 				p2 += day;
// 			}
// 			else{
// 				std::cout << "====================================== ERROR ======================================" << std::endl;
// 				std::cout << "clock.cpp : std::chrono::seconds operator-(std::chrono::steady_clock::time_point&, std::chrono::steady_clock::time_point&) : " << std::endl;
// 				std::cout << "!!!! plusDayAssumption = TRUE (in clock.h)" << std::endl;
// 				std::cout << "Substraction from MUCH less time point bigger time point" << std::endl;
// 				std::cout << "Cannot do a plus one day assumption" << std::endl;
// 				std::cout << "===================================================================================" << std::endl;
// 				return 0s;
// 			}
// 		}
// 		else{
// 			std::cout << "====================================== ERROR ======================================" << std::endl;
// 			std::cout << "clock.cpp : std::chrono::seconds operator-(std::chrono::steady_clock::time_point&, std::chrono::steady_clock::time_point&) : " << std::endl;
// 			std::cout << "!!!! plusDayAssumption = FALSE (in clock.h)" << std::endl;
// 			std::cout << "Substraction from less time point bigger time point" << std::endl;
// 			std::cout << "No negative time points" << std::endl;
// 			std::cout << "===================================================================================" << std::endl;
// 			return 0s;
// 		}
// 	}
// 	return duration_cast<std::chrono::seconds>(p2 - p1);
// }
// std::chrono::steady_clock::time_point operator +(std::chrono::steady_clock::time_point& p, std::chrono::seconds& d){
// 	return (p + s);
// }
// std::chrono::steady_clock::time_point operator -(std::chrono::steady_clock::time_point& p, std::chrono::seconds& d){
// 	auto p1 = p - d;
// 	if(duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count() < duration_cast<std::chrono::seconds>(start.time_since_epoch()).count()){
// 		std::cout << "====================================== ERROR ======================================" << std::endl;
// 		std::cout << "clock.cpp : std::chrono::seconds operator-(std::chrono::steady_clock::time_point&, std::chrono::seconds&) : " << std::endl;
// 		std::cout << "No negative time points" << std::endl;
// 		std::cout << "===================================================================================" << std::endl;
// 		return start;
// 	}
// 	else
// 		return p1;
// }
// std::chrono::steady_clock::time_point& operator +=(std::chrono::steady_clock::time_point& p, std::chrono::seconds& d){
// 	p = p + d;
// 	return p;
// }
// std::chrono::steady_clock::time_point& operator -=(std::chrono::steady_clock::time_point& p, std::chrono::seconds& d){
// 	p = p - d;
// 	return p;
// }
// std::ostream& operator << (std::ostream& out, std::chrono::steady_clock::time_point& p){
// 	int x = duration_cast<std::chrono::seconds>(p - start);
// 	int d = x / 86400;
// 	int h = (x % 86400) / 3600;
// 	int min = (x % 3600) / 60;
// 	int sec = x % 60;
// 	std::string s = std::to_string(d) + ":" + std::to_string(h) + ":" + std::to_string(min) + ":" + std::to_string(sec);
// 	out << s;
// 	return out;
// }
// std::ostream& operator << (std::ostream& out,std::chrono::seconds& d){
// 	int x = d;
// 	out << x;
// 	return out;
// }
// int& operator=(int& x, std::chrono::seconds& d){
// 	x = d.count();
// 	return x;
// }
// std::chrono::seconds& operator=(std::chrono::seconds& d, int& x){
// 	d = std::chrono::seconds(x);
// 	return d;
// }
// std::chrono::seconds operator+(std::chrono::seconds& d, int& x){
// 	return (d + std::chrono::seconds(x));
// }
// std::chrono::seconds& operator+=(std::chrono::seconds& d, int& x){
// 	d = d + x;
// 	return d;
// }
// std::chrono::seconds operator-(std::chrono::seconds& d, int& x){
// 	return (d - std::chrono::seconds(x));
// }
// std::chrono::seconds& operator-=(std::chrono::seconds& d, int& x){
// 	d = d - x;
// 	return d;
// }