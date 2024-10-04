#ifndef chrono_H
#define chrono_H
#include <chrono>
#include <algs.h>
const bool plusDayAssumpsion = true;
const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
const std::chrono::duration C = duration_cast<std::chrono::seconds>(start.time_since_epoch());
// std::string generateTime();
// std::chrono::steady_clock::time_point& operator=(std::chrono::steady_clock::time_point&, std::string&);
// std::chrono::seconds operator -(std::chrono::steady_clock::time_point&, std::chrono::steady_clock::time_point&);
// std::chrono::steady_clock::time_point operator +(std::chrono::steady_clock::time_point&, std::chrono::seconds&);
// std::chrono::steady_clock::time_point operator -(std::chrono::steady_clock::time_point&, std::chrono::seconds&);
// std::chrono::steady_clock::time_point& operator +=(std::chrono::steady_clock::time_point&, std::chrono::seconds&);
// std::chrono::steady_clock::time_point& operator -=(std::chrono::steady_clock::time_point&, std::chrono::seconds&);
// std::ostream& operator << (std::ostream&,std::chrono::steady_clock::time_point&);
// std::ostream& operator << (std::ostream&,std::chrono::seconds&);
// int& operator=(int&, std::chrono::seconds&);
// std::chrono::seconds& operator=(std::chrono::seconds&, int&);
// std::chrono::seconds operator+(std::chrono::seconds&, int&);
// std::chrono::seconds& operator+=(std::chrono::seconds&, int&);
// std::chrono::seconds operator-(std::chrono::seconds&, int&);
// std::chrono::seconds& operator-=(std::chrono::seconds&, int&);
#endif