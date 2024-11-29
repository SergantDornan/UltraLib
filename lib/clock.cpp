#include <clock.h>
using std::chrono::duration_cast;
timePoint::timePoint(const timePoint& p){
	point = p.point;
}
duration::duration(const duration& d){
	dur = d.dur;
}
timePoint generateTime(){
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
	timePoint p(res);
	return p;
}
timePoint::timePoint(const std::string s){
	set(s);
}
timePoint::timePoint(const std::chrono::steady_clock::time_point& p){
	point = p;
	point += std::chrono::seconds(1);
} 
void timePoint::set(const std::string& time){
	std::chrono::steady_clock::time_point p;
	std::chrono::seconds dur;
	std::stringstream stream;
	if(time.size() == 8){
		int h,min,sec;
		stream << std::string(time.begin(), time.begin() + 2);
		stream >> h;
		stream.clear();
		stream << std::string(time.begin() + 3, time.begin() + 5);
		stream >> min;
		stream.clear();
		stream << std::string(time.begin() + 6, time.begin() + 8);
		stream >> sec;
		int Idur = h * 3600 + min*60 + sec;	
		dur = std::chrono::seconds(Idur);
		p = start.point + dur;
	}
	else{
		int d,h,min,sec;
		stream << std::string(time.begin(), time.begin() + 2);
		stream >> d;
		stream.clear();
		stream << std::string(time.begin() + 3, time.begin() + 5);
		stream >> h;
		stream.clear();
		stream << std::string(time.begin() + 6, time.begin() + 8);
		stream >> min;
		stream.clear();
		stream << std::string(time.begin() + 9, time.begin() + 11);
		stream >> sec;
		int Idur = d* 24* 3600 + h * 3600 + min*60 + sec;	
		dur = std::chrono::seconds(Idur);
		p = start.point + dur;
	}
	point = p;
}
timePoint& timePoint::operator = (const std::string& s){
	this -> set(s);
	return *this;
}
duration::duration(const std::chrono::seconds& x){
	dur = x;
}
duration::duration(const int x){
	dur =  std::chrono::seconds(x);
}
int duration::toInt(){
	int x = dur.count();
	return x;
}
duration& duration::operator=(const int x){
	this -> dur = std::chrono::seconds(x);
	return *this;
}
duration operator-(const timePoint& p2,const  timePoint& p1){
	timePoint pastp = p2;
	if(duration_cast<std::chrono::seconds>(pastp.point.time_since_epoch()).count() < 
		duration_cast<std::chrono::seconds>(p1.point.time_since_epoch()).count()){
		if(plusDayAssumpsion){
			auto dur2 = duration_cast<std::chrono::seconds>(p2.point - start.point);
			auto dur1 = duration_cast<std::chrono::seconds>(p1.point - start.point);
			int Idur2 = dur2.count();
			int Idur1 = dur1.count();
			if((Idur1 / 86400) == (Idur2 / 86400)){
				std::chrono::seconds day = std::chrono::seconds(86400);
				pastp.point = p2.point + day;
			}
			else{
				std::cout << "====================================== ERROR ======================================" << std::endl;
				std::cout << "clock.cpp: duration operator-(timePoint&, timePoint&) : " << std::endl;
				std::cout << "!!!! plusDayAssumption = TRUE (in clock.h)" << std::endl;
				std::cout << "Substraction from MUCH less time point bigger time point" << std::endl;
				std::cout << "Cannot do a plus one day assumption" << std::endl;
				std::cout << "===================================================================================" << std::endl;
				return duration(0);
			}
		}
		else{
			std::cout << "====================================== ERROR ======================================\n" << std::endl;
			std::cout << "clock.cpp : duration operator-(timePoint&, timePoint&) : " << std::endl;
			std::cout << "!!!! plusDayAssumption = FALSE (in clock.h)" << std::endl;
			std::cout << "Substraction from less time point bigger time point" << std::endl;
			std::cout << "No negative time points" << std::endl;
			std::cout << "===================================================================================" << std::endl;
			return duration(0);
		}
	}
	return duration(duration_cast<std::chrono::seconds>(pastp.point - p1.point));
}
timePoint operator+(const timePoint& p,const  duration& d){
	timePoint p1(p.point + d.dur);
	return p1;
}
timePoint operator-(const timePoint& p,const  duration& d){
	if(duration_cast<std::chrono::seconds>(p.point - start.point).count() - d.dur.count() < 0){
		std::cout << "====================================== ERROR ======================================" << std::endl;
		std::cout << "clock.cpp : timePoint operator-(timePoint&, duration&) : " << std::endl;
		std::cout << "No negative time points" << std::endl;
		std::cout << "===================================================================================" << std::endl;
		return timePoint(startPointnow);
	}
	else
		return timePoint(p.point - d.dur);
}
timePoint& timePoint::operator += (const duration& d){
	(this -> point) = (this -> point) + d.dur;
	return *this;
}
timePoint& timePoint::operator -= (const duration& d){
	std::chrono::steady_clock::time_point p1 = (this -> point - d.dur);
	if(duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count() < duration_cast<std::chrono::seconds>(start.point.time_since_epoch()).count()){
		std::cout << "====================================== ERROR ======================================" << std::endl;
		std::cout << "clock.cpp : timePoint& timePoint::operator-=(duration&) : " << std::endl;
		std::cout << "No negative time points" << std::endl;
		std::cout << "===================================================================================" << std::endl;
	}
	else
		this -> point = p1;
	return *this;
}
duration operator+(const duration& d,const int x){
	duration d1(d.dur + std::chrono::seconds(x));
	return d1;
}
duration operator-(const duration& d,const  int x){
	if(d.dur.count() < x){
		std::cout << "====================================== ERROR ======================================" << std::endl;
		std::cout << "clock.cpp : duration operator-(duration&, int) : " << std::endl;
		std::cout << "No negative durations" << std::endl;
		std::cout << "===================================================================================" << std::endl;
		return duration(0);
	}
	else{
		duration d1(d.dur - std::chrono::seconds(x));
		return d1;
	}
}
duration& duration::operator+=(const int x){
	dur = dur + std::chrono::seconds(x);
	return *this;
}
duration& duration::operator-=(const int x){
	if(dur.count() < x){
		std::cout << "====================================== ERROR ======================================" << std::endl;
		std::cout << "clock.cpp : duration& duration::operator-=(int) : " << std::endl;
		std::cout << "No negative durations" << std::endl;
		std::cout << "===================================================================================" << std::endl;
	}
	else
		dur = dur - std::chrono::seconds(x);
	return *this;
}
std::string timePoint::toString(){
	int x = duration_cast<std::chrono::seconds>(point - start.point).count();
	int d = x / 86400;
	int h = (x % 86400) / 3600;
	int min = (x % 3600) / 60;
	int sec = x % 60;
	auto f = [](int x){
		std::string s;
		if(x / 10 == 0){
			s = "0" + std::to_string(x);
		}
		else{
			s = std::to_string(x);
		}
		return s;
	};
	std::string s;
	if(d != 0)
		s = f(d) + ":" + f(h) + ":" + f(min) + ":" + f(sec);
	else
		s = f(h) + ":" + f(min) + ":" + f(sec);
	return s;
}
std::ostream& operator << (std::ostream& out,timePoint& p){
	std::string s = p.toString();
	out << s;
	return out;
}
std::ostream& operator << (std::ostream& out,duration& d){
	int x = d.toInt();
	out << x;
	return out;
}
timePoint operator+(timePoint& p,const  int x){
	duration d(x);
	return (p + d);
}
timePoint operator-(timePoint& p,const  int x){
	duration d(x);
	return (p - d);
}
timePoint& timePoint::operator+=(const int x){
	duration d(x);
	this -> point  = this -> point + d.dur;
	return *this;
}
timePoint& timePoint::operator-=(const int x){
	duration d(x);
	if(duration_cast<std::chrono::seconds>(point - start.point).count() - d.dur.count() < 0){
		std::cout << "====================================== ERROR ======================================" << std::endl;
		std::cout << "clock.cpp : timePoint& timePoint::operator-(int x) : " << std::endl;
		std::cout << "No negative time points" << std::endl;
		std::cout << "===================================================================================" << std::endl;
	}
	else
		point = point - d.dur;
	return *this;
}
std::istream& operator >>(std::istream& in,timePoint& p){
	std::string s;
	in >> s;
	p = s;
	return in;
}
std::istream& operator >>(std::istream& in, duration& d){
	int x;
	in >> x;
	d = x;
	return in;
}