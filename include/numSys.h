#ifndef numsysh
#define numsysh
#include <algs.h>
class Num{
public:
	std::vector<int> v;
	int base;
	int sign;
	Num(int x = 0, int base = 2);
	Num(const Num&);
	Num& operator = (const int);
	Num& operator = (const Num&);
	Num& operator += (const int);
	Num& operator += (const Num&);
	Num& operator -= (const Num&);
	Num& operator -= (const int);
	Num& operator *= (const int);
	Num& operator *= (const Num&);
	Num& operator /= (const int);
	Num& operator /= (const Num&);
	void setv(int);
	void sort();
	int toInt();
};
Num operator + (const Num&,const Num&);
Num operator + (const Num&,const int);
Num operator + (const int,const Num&);
Num operator - (const int,const Num&);
Num operator - (const Num&,const int);
Num operator - (const Num&,const Num&);
Num operator * (const Num&,const Num&);
Num operator * (const Num&,const int);
Num operator * (const int,const Num&);
Num operator / (const Num&,const Num&);
Num operator / (const int, const Num&);
Num operator / (const Num&, const int);
bool operator < (const Num&, const Num&);
bool operator < (const Num&, int);
bool operator < (int, const Num&);
bool operator > (const Num&, const Num&);
bool operator > (int, const Num&);
bool operator > (const Num&, int);
bool operator == (const Num&, const Num&);
bool operator == (const Num&,int);
bool operator == (int,const Num&);
bool operator < (const Num&, const Num&);
bool operator < (int,const Num&);
bool operator < (const Num&,int);
bool operator > (const Num&, const Num&);
bool operator > (int,const Num&);
bool operator > (const Num&,int);
bool operator <= (const Num&, const Num&);
bool operator <= (int,const Num&);
bool operator <= (const Num&,int);
bool operator >= (const Num&, const Num&);
bool operator >= (int,const Num&);
bool operator >= (const Num&,int);
std::ostream& operator << (std::ostream&, Num&);
#endif