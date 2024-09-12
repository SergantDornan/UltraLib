#include "analysis.h"
int mainfunc(int);
void points(std::map<int,double>& mp){
	for(int i = 1; i <= N; ++i){
		clock_t start = clock();
		mainfunc(i);
		clock_t end = clock();
		double elapsed_time = double(end - start) / CLOCKS_PER_SEC;
		mp.emplace(i,elapsed_time);
	}
}
std::pair<double,std::string> Oconst(std::map<int,double>& mp){
	double c = 0;
	for(int i = 1; i <= N; ++i)
		c+=mp[i];
	c = c/N;
	double d = 0;
	for(int i = 1; i <= N; ++i)
		d += pow((mp[i]-c),2);
	return {d,"O(1)"};
}
std::pair<double,std::string> Olinear(std::map<int,double>& mp){
	double k = 0;
	double b = 0;
	double a1 = 0, b1 = 0, c1 = 0, a2 = 0, b2 = 0, c2 = 0;
	for(int i = 1; i <= N; ++i){
		a1 += mp[i] * i;
		a2 += mp[i];
		b1 += i*i;
		b2 += i;
	}
	c2 = N;
	c1 = b2;
	k = (a2 - (a1*c2)/c1)/(b2 - (b1*c2)/c1);
	b = (a1 - k*b1) / c1;
	double d = 0;
	for(int i = 1; i <= N; ++i)
		d += pow((mp[i] - k*i - b),2);
	return {d,"O(n)"};
}
std::pair<double,std::string> Osquare(std::map<int,double>& mp){
	double a0 = 0, a1 = 0, a2 = 0;
	double s1 =0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0, s7 = 0;
	for(int i = 1; i <= N; ++i){
		s1 += i;
		s2 += i*i;
		s3 += i*i*i;
		s4 += i*i*i*i;
		s5 += mp[i];
		s6 += i*mp[i];
		s7 += i*i*mp[i];
	}
	double k1 = s2 - (s1*s1)/N;
	double k2 = s3 - (s1*s2)/N;
	double k3 = s6 - (s1*s5)/N;
	double k4 = s3 - (s1*s2)/N;
	double k5 = s4 - (s2*s2)/N;
	double k6 = s7 - (s2*s5)/N;
	a2 = (k6 - (k3*k4)/k1)/(k5 - (k2*k4)/k1);
	a1 = (k3 - (k2*a2))/k1;
	a0 = (s5 - s1*a1 - s2*a2)/N;
	double d = 0;
	for(int i = 1; i <= N; ++i)
		d += pow((mp[i] - a2*i*i - a1*i - a0),2);
	return {d, "O(n^2)"};
}
extern "C" int entry(){
	std::map<int,double> mp;
	points(mp);
	std::map<double, std::string> res = {Oconst(mp),Olinear(mp),Osquare(mp)};
	std::cout << res;
	return 0;
}