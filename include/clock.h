#ifndef chrono_H
#define chrono_H
#include <chrono>
#include <algs.h>
#include <sstream>
const bool plusDayAssumpsion = true;
const std::chrono::steady_clock::time_point startPointnow = std::chrono::steady_clock::now();
class duration;
class timePoint{
public:
	std::chrono::steady_clock::time_point point;
	timePoint(std::string s = "00:00:00");
	timePoint(std::chrono::steady_clock::time_point p);
	timePoint(timePoint&);
	void set(const std::string);
	timePoint& operator=(const std::string);
	timePoint& operator+=(duration&);
	timePoint& operator-=(duration&);
	timePoint& operator+=(int);
	timePoint& operator-=(int);
	std::string operator()();
};
timePoint generateTime();
const timePoint start(startPointnow);
class duration{
public:
	std::chrono::seconds dur;
	duration(int x = 0);
	int operator()();
	duration& operator=(int x);
	duration(duration&);
	duration(std::chrono::seconds);
	duration& operator+=(int);
	duration& operator-=(int);
};
duration operator-(timePoint&, timePoint&);
timePoint operator +(timePoint&, duration&);
timePoint operator+(timePoint&, int);
timePoint operator-(timePoint&, duration&);
timePoint operator-(timePoint&, int);
duration operator+(duration&, int);
duration operator-(duration&, int);
std::ostream& operator << (std::ostream&,timePoint&);
std::ostream& operator << (std::ostream&,duration&);
std::istream& operator >> (std::istream&,timePoint&);
std::istream& operator >> (std::istream&,duration&);
#endif