#ifndef problems
#define problems
#include <algs.h>
#include <filework.h>
#include <math.h>
typedef long int i64;

//Дан массив целых чисел, назовем отрезов k-хорошим, если в нем не более k различных чисел
//Найти длину наиболее длинного k-хорошего отрезка
int MaxKgoodsize(std::vector<long>&, long unsigned int);

class alg{
public:
	const i64 c = pow(10,9) + 7;
	i64 x;
	alg(){x = 0;}
	alg(i64 n){x = n % c;}
	alg(alg& n){x = n.x;}
	alg& operator=(const alg& n){
		x = n.x;
		return *this;
	}
	alg& operator += (i64 n){
		x += n;
		x %= c;
		return *this;
	}
	alg& operator += (alg n){
		x += n.x;
		x %= c;
		return *this;
	}
	alg& operator *= (i64 n){
		x *= n;
		x %= c;
		return *this;
	}
	alg& operator *= (alg n){
		x *= n.x;
		x %= c;
		return *this;
	}
};
class Rect{
		public:
			int id;
			int lx,rx,ly,ry;
			Rect(int a,int b,int c,int d,int e){
			lx = a;
			rx = b;
			ly = c;
			ry = d;
			id = e;
	}
};
alg power(int n);
bool intersect(Rect& x, Rect& y);
void Atask(std::vector<std::vector<int>>&,std::vector<std::vector<int>>&);
void Btask(std::vector<std::vector<int>>&,std::vector<std::vector<int>>&);
void Ctask(std::vector<std::vector<int>>&,std::vector<std::vector<int>>&);
void Dtask(std::vector<std::vector<int>>&,std::vector<std::vector<int>>&);
void Etask(std::vector<std::vector<int>>&,std::vector<std::vector<int>>&);


//Дан массив из нулей и единиц, найти позицию 0 такого, что расстояние от него до 
//близжайшей единицы будет максимальным
void onesandzerosMaxMindistance(std::string,std::string);
#endif