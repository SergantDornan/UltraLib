#include <numSys.h>
Num::Num(int x, int b){
	base = b;
	sign = (x >= 0 ? 1 : -1);
	setv(abs(x));
}
void Num::setv(int x){
	if(x == 0)
		v.push_back(0);
	while(x > 0){
		v.push_back(x % base);
		x /= base;
	}
}
void Num::sort(){
	auto it = v.end()-1;
	while((*it) == 0 && v.size() > 1)
		v.erase(it);
}
int Num::toInt(){
	int res = 0;
	auto pw = [](int x, int p){
		int r = 1;
		while(p > 0){
			r *= x;
			p--;
		}
		return r;
	};
	for(int i = 0; i < v.size(); ++i){
		res += sign*v[i]*pw(base,i);
	}
	return res;
}
Num::Num(const Num& n){
	base = n.base;
	v = n.v;
	sign = n.sign;
}
Num& Num::operator = (const int x){
	sign = (x >= 0 ? 1 : -1);
	setv(abs(x));
}
Num& Num::operator = (const Num& n){
	base = n.base;
	v = n.v;
	sign = n.sign;
}
Num& Num::operator += (const Num& n){
	if(base != n.base){
		std::cout << "=========================== ERROR ===========================" << std::endl;
		std::cout << "numSys.cpp: Num::operator += (const Num&)" << std::endl;
		std::cout << "bases must be equal" << std::endl;
		std::cout << "this base is: " << base << " adding number base is: " << n.base << std::endl;
		std::cout << "=============================================================" << std::endl;
		return *this;
	}
	if(sign = 1 && n.sign == 1){
		std::vector<int> bg,sml;
		if(v.size() > n.v.size()){
			bg = v;
			sml = n.v;
		}
		else{
			bg = n.v;
			sml = v;
		}
		v.clear();
		int inmind = 0;
		for(int i = 0; i < bg.size(); ++i){
			if(i < sml.size()){
				int tmp = bg[i] + sml[i] + inmind;
				v.push_back(tmp % base);
				inmind = tmp / base;
			}
			else{
				int tmp = bg[i] + inmind;
				v.push_back(tmp % base);
				inmind = tmp / base;
			}
		}
		sort();
	}
	else if(sign == -1 && n.sign == -1){
		Num tmp(n);
		tmp.sign = 1;
		sign = 1;
		(*this) += tmp;
		sign = -1; 
	}
	else if(sign == -1 && n.sign == 1){
		sign = 1;
		Num tmp(n);
		tmp -= (*this);
		(*this) = tmp;
	}
	else if(sign == 1 && n.sign == -1){
		Num tmp(n);
		tmp.sign = 1;
		(*this) -= tmp;
	}
	return *this;
}
Num& Num::operator -= (const Num& n){
	if(base != n.base){
		std::cout << "=========================== ERROR ===========================" << std::endl;
		std::cout << "numSys.cpp: Num::operator -= (const Num&)" << std::endl;
		std::cout << "bases must be equal" << std::endl;
		std::cout << "this base is: " << base << " substracting number base is: " << n.base << std::endl;
		std::cout << "=============================================================" << std::endl;
		return *this;
	}
	if(sign == 1 && n.sign == 1){
		if(*this == n){
			sign = 1;
			setv(0);
			sort();
			return *this;
		}
		else if((*this) > n)
			sign = 1;
		else
			sign = -1;
		std::vector<int> bg,sml;
		if(v.size() > n.v.size()){
			bg = v;
			sml = n.v;
		}
		else{
			bg = n.v;
			sml = v;
		}
		v.clear();
		int inmind = 0;
		for(int i = 0; i < bg.size(); ++i){
			if(i < sml.size()){
				int tmp = bg[i] - sml[i] - inmind;
				if(tmp < 0){
					inmind = 1;
					tmp += base;
				}
				else
					inmind = 0;
				v.push_back(tmp);
			}
			else{

				int tmp = bg[i] - inmind;
				if(tmp < 0){
					inmind = 1;
					tmp += base;
				}
				else
					inmind = 0;
				v.push_back(tmp);
			}
		}
	}
	else if(sign == -1 && n.sign == -1){
		Num tmp(n);
		tmp.sign = 1;
		sign = 1;
		tmp -= (*this);
		(*this) = tmp;
	}
	else if(sign == 1 && n.sign == -1){
		Num tmp(n);
		tmp.sign = 1;
		(*this) += tmp;
	}
	else if(sign == -1 && n.sign == 1){
		sign = 1;
		(*this) += n;
		sign = -1;
	}
	return *this;
}
Num& Num::operator *= (const Num& n){
	if(base != n.base){
		std::cout << "=========================== ERROR ===========================" << std::endl;
		std::cout << "numSys.cpp: Num::operator *= (const Num&)" << std::endl;
		std::cout << "bases must be equal" << std::endl;
		std::cout << "this base is: " << base << " multipliyng number base is: " << n.base << std::endl;
		std::cout << "=============================================================" << std::endl;
		return *this;
	}
}
Num& Num::operator /= (const Num& n){
	if(base != n.base){
		std::cout << "=========================== ERROR ===========================" << std::endl;
		std::cout << "numSys.cpp: Num::operator /= (const Num&)" << std::endl;
		std::cout << "bases must be equal" << std::endl;
		std::cout << "this base is: " << base << " dividing number base is: " << n.base << std::endl;
		std::cout << "=============================================================" << std::endl;
		return *this;
	}
}
bool operator < (const Num& x, const Num& y){
	if(x.base != y.base){
		std::cout << "=========================== ERROR ===========================" << std::endl;
		std::cout << "numSys.cpp: Num::operator < (const Num&, const Num&)" << std::endl;
		std::cout << "bases must be equal" << std::endl;
		std::cout << "x base is: " << x.base << " y base is: " << y.base << std::endl;
		std::cout << "=============================================================" << std::endl;
		return false;
	}
	if(x.sign < y.sign)
		return true;
	if(x.sign > y.sign)
		return false;
	if(x.v.size() < y.v.size())
		return (x.sign == 1);
	if(x.v.size() > y.v.size())
		return (x.sign == -1);
	for(int i = x.v.size()-1; i >= 0; --i){
		if(x.v[i] < y.v[i])
			return (x.sign == 1);
		else if(x.v[i] > y.v[i])
			return (x.sign == -1);
	}
	return false;
}
bool operator < (const Num& x, int y){
	Num tmp(y,x.base);
	return x < tmp;
}
bool operator < (int x,const Num& y){
	Num tmp(x, y.base);
	return tmp < y;
}
bool operator > (const Num& x, const Num& y){
	if(x.base != y.base){
		std::cout << "=========================== ERROR ===========================" << std::endl;
		std::cout << "numSys.cpp: Num::operator > (const Num&, const Num&)" << std::endl;
		std::cout << "bases must be equal" << std::endl;
		std::cout << "x base is: " << x.base << " y base is: " << y.base << std::endl;
		std::cout << "=============================================================" << std::endl;
		return false;
	}
	return y < x;
}
bool operator > (const Num& x, int y){
	return y < x;
}
bool operator > (int x, const Num& y){
	return y < x;
}
bool operator == (const Num& x, const Num& y){
	return (x.v == y.v) && (x.sign == y.sign) && (x.base == y.base);
}
bool operator == (const Num& x, int y){
	Num tmp(y,x.base);
	return x == tmp;
}
bool operator == (int x, const Num& y){
	Num tmp(x,y.base);
	return y == tmp;
}
bool operator <= (const Num& x, const Num& y){
	return (x < y) || (x == y);
}
bool operator <= (int x, const Num& y){
	return (x < y) || (x == y);
}
bool operator <= (const Num& x, int y){
	return (x < y) || (x == y);
}
bool operator >= (const Num& x, const Num& y){
	return (x > y) || (x == y);
}
bool operator >= (int x, const Num& y){
	return (x > y) || (x == y);
}
bool operator >= (const Num& x, int y){
	return (x > y) || (x == y);
}
std::ostream& operator << (std::ostream& out, Num& n){
	for(int i = n.v.size()-1; i >= 0; --i){
		if(i < 10)
			out << i;
		else{
			char ch = char(int('A') + i - 10);
			out << ch;
		}
	}
	return out;
}