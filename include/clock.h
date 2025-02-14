#ifndef chrono_H
#define chrono_H
#include <chrono>
#include <algs.h>
#include <sstream>
const bool plusDayAssumpsion = true;
const std::chrono::steady_clock::time_point startPointnow=std::chrono::steady_clock::now();
class duration;
class timePoint{
public:
	std::chrono::steady_clock::time_point point;
	timePoint(const std::string s = "00:00:00");
	timePoint(const std::chrono::steady_clock::time_point&);
	timePoint(const timePoint&);
	void set(const std::string&);
	timePoint& operator=(const std::string&);
	timePoint& operator+=(const duration&);
	timePoint& operator-=(const duration&);
	timePoint& operator+=(const int);
	timePoint& operator-=(const int);
	std::string toString();
};
timePoint generateTime();
const timePoint start(startPointnow);
class duration{
public:
	std::chrono::seconds dur;
	duration(const int x = 0);
	duration(const duration&);
	int toInt();
	duration& operator=(const int);
	duration(const std::chrono::seconds&);
	duration& operator += (const int);
	duration& operator-=(const int);
};
duration operator-(const timePoint&,const timePoint&);
timePoint operator+(const timePoint&,const duration&);
timePoint operator+(const timePoint&,const int);
timePoint operator-(const timePoint&,const duration&);
timePoint operator-(const timePoint&,const int);
duration operator+(const duration&,const int);
duration operator-(const duration&,const int);
std::ostream& operator << (std::ostream&,timePoint&);
std::ostream& operator << (std::ostream&,duration&);
std::istream& operator >> (std::istream&,timePoint&);
std::istream& operator >> (std::istream&,duration&);
#endif