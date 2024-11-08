#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <list>
#include <cmath>
#include <functional>
#include <fstream>
#include <typeinfo>
#include <sstream>
template <class T>
class heap{
public:
	std::vector<T> vector;
	int d;
	bool (*comparator)(T&,T&);

	heap(int x = 2, bool(*comp)(T&,T&) = [](T& x, T& y){return (x < y);}){
		d = x;
		comparator = comp;
	}
	heap(std::vector<T>& v, int x = 2, bool(*comp)(T&,T&) = [](T& x, T& y){return (x < y);}){
		d = x;
		vector = v;
		comparator = comp;
		buildHeap();
	}
	heap(heap<T>& h){
		vector = h.vector;
		d = h.d;
		comparator = h.comparator;
	}
	heap<T>& operator=(std::vector<T> v){
		vector = v;
		buildHeap();
		return *this;
	}
	T operator [](int i){
		return vector[i];
	}
	void heapify(int x){
		int i = x + 1;
		std::vector<int> childs;
		for(int j = 0; j < d && ischild(i,j); ++j)
			childs.push_back(child(i,j));
		int largest = i;
		for(int j = 0; j < childs.size(); ++j){
			if(childs[j] <= size() && !comparator(vector[childs[j]-1],vector[largest-1]))
				largest = childs[j];
		} 
		if(largest != i){
			swap(vector[i-1],vector[largest-1]);
			heapify(largest-1);
		}
	} // O(log_d(n))
	void buildHeap(){
		for(int i = size() / d; i >= 0; --i)
			heapify(i);
	}// O(n)
	int parent(int i){
		return i/d;
	}
	bool ischild(int i, int offset){
		return (offset < d && (d * i + offset - 1) < size());
	}
	int child(int i, int offset){
		int result =  d*i + offset;
		if(d*i + offset - 1 >= size()){
			std::cout << "=============================== ERROR ===============================" << std::endl;
			std::cout << "================ dHeap.h: int heap::child(int,int) ================" << std::endl;
			std::cout << "================ child index is out of vector range ================ " << std::endl;
			std::cout << "=====================================================================" << std::endl;
			result = -1;
		}
		if(offset >= d){
			std::cout << "=============================== ERROR ===============================" << std::endl;
			std::cout << "================ dHeap.h: int heap::child(int,int) ================" << std::endl;
			std::cout << "================ offset is bigger than base of the heap (d) ================ " << std::endl;
			std::cout << "================ there is up to "  << d << " childs, but you tying to get " << offset << " child ================ " << std::endl;
			std::cout << "=====================================================================" << std::endl;
			result = -1;
		}
		return result;
	}
	int size(){
		return vector.size();
	}
	std::string toString(int i = 1,const std::string prefix = ""){
		std::string s = "";
		if (i-1 >= size()){
   			return s;
		}
  		if (i == 1) {
    		s += "─────";
  		} else {
    		s+= (prefix +
     		 ((i % d == 0) ? "├────" : "└───"));
  		}
  		std::ostringstream stream;
  		stream << vector[i-1];
  		std::string subs = stream.str();
  		s += (subs + "\n");
  		for(int j = 0; j < d; ++j)
  			s += toString(d*i+j, prefix + ((i % d != (d-1) && i != 1) ? "│   " : "    "));
  		return s;
	}
	void print(){
		std::cout << vector << std::endl;
	}
	T extract(){
		if(vector.size() == 0){
			std::cout << "========================== ERROR ==========================" << std::endl;
			std::cout << "=========== dHeap.h: T binHeap::extract() ===========" << std::endl;
			std::cout << "========= heap size is 0, no max element ========" << std::endl;
			std::cout << "===========================================================" << std::endl;
			return T(0);
		}
		else{
			T m = vector[0];
			vector[0] = vector[vector.size()-1];
			vector.erase(vector.end()-1);
			heapify(0);
			return m;
		}
	} // O(log_d(n))


	T max(){
		if(vector.size() == 0){
			std::cout << "========================== ERROR ==========================" << std::endl;
			std::cout << "=========== dHeap.h: T binHeap::max() ===========" << std::endl;
			std::cout << "========= heap size is 0, no max element ========" << std::endl;
			std::cout << "===========================================================" << std::endl;
			return T(0);
		}
		else
			return vector[0];
	}
	void insert(T x){
		int i = size() + 1;
		vector.push_back(x);
		while(i > 1 && vector[parent(i) - 1] < x){
			vector[i-1]  = vector[parent(i)-1];
			i = parent(i);
		}
		vector[i-1] = x;
	} //O(log_d(n)) 
};
template <class T>
std::ostream& operator << (std::ostream& out, heap<T>& h){
	out << h.toString() << std::endl;
	return out;
}
template <class T>
class Range{
public:
    std::vector<std::pair<T,T>> v;
    Range(Range<T>& r){
        v = r.v;
    }
    Range(const std::pair<T,T> p){
        v.push_back(p);
    }
    Range(const std::vector<std::pair<T,T>> p){
        v = p;
        sortinput();
    }
    Range(const std::string s,const T x){
        if(s != "-inf"){
            std::cout << "======================================== ERROR ========================================" << std::endl;
            std::cout << "===================== header.h: Range(const std::string, const T) =====================" << std::endl;
            std::cout << "===================== first parameter is: " << s << " =====================" << std::endl;
            std::cout << "=========================== but first parameter must be -inf ===========================" << std::endl; 
        }
        else{
            v.push_back({T(-pow(10,9)), x});
        }
    }
    Range(const std::string s,const T x,const std::pair<T,T> p){
        if(s != "-inf"){
            std::cout << "======================================== ERROR ========================================" << std::endl;
            std::cout << "============ header.h: Range(const std::string, const T, std::pair<T,T>) ==============" << std::endl;
            std::cout << "===================== first parameter is: " << s << " =====================" << std::endl;
            std::cout << "=========================== but first parameter must be -inf ===========================" << std::endl; 
        }
        else{
            v.push_back({T(-pow(10,9)), x});
            v.push_back(p);
            sortinput();
        }
    }
    Range(const std::string s,const T x, const std::vector<std::pair<T,T>> p){
        if(s != "-inf"){
            std::cout << "======================================== ERROR ========================================" << std::endl;
            std::cout << "====== header.h: Range(const std::string, const T, std::vector<std::pair<T,T>>) =======" << std::endl;
            std::cout << "===================== first parameter is: " << s << " =====================" << std::endl;
            std::cout << "=========================== but first parameter must be -inf ===========================" << std::endl; 
        }
        else{
            v = p;
            v.push_back({T(-pow(10,9)), x});
            sortinput();
        }
    }
    Range(const T x, const std::string s){
        if(s != "inf" && s != "+inf"){
            std::cout << "======================================== ERROR ========================================" << std::endl;
            std::cout << "===================== header.h: Range(const T, const std::string) =====================" << std::endl;
            std::cout << "===================== second parameter is: " << s << " =====================" << std::endl;
            std::cout << "====================== but second parameter must be +inf or inf ======================" << std::endl; 
        }
        else{
            v.push_back({x, T(pow(10,9))});
        }
    }
    Range(const std::pair<T,T> p, const T x, const std::string s){
        if(s != "inf" && s != "+inf"){
            std::cout << "======================================== ERROR ========================================" << std::endl;
            std::cout << "============ header.h: Range(std::pair<T,T>, const T, const std::string) ==============" << std::endl;
            std::cout << "======================= last parameter is: " << s << " =======================" << std::endl;
            std::cout << "======================== but last parameter must be +inf or inf ========================" << std::endl; 
        }
        else{
            v.push_back(p);
            v.push_back({x, T(pow(10,9))});
            sortinput();
        }
    }
    Range(const std::vector<std::pair<T,T>> p, const T x, const std::string s){
        if(s != "inf" && s != "+inf"){
            std::cout << "======================================== ERROR ========================================" << std::endl;
            std::cout << "====== header.h: Range(std::vector<std::pair<T,T>>, const T, const std::string) =======" << std::endl;
            std::cout << "======================= last parameter is: " << s << " =======================" << std::endl;
            std::cout << "======================== but last parameter must be +inf or inf ========================" << std::endl; 
        }
        else{
            v = p;
            v.push_back({x, T(pow(10,9))});
            sortinput();
        }
    }
    Range(const std::string s1, const std::string s2){
        if(s1 != "-inf" || (s2 != "inf" && s2 != "+inf")){
            std::cout << "======================================== ERROR ========================================" << std::endl;
            std::cout << "=============== header.h : Range(const std::string, const std::string) ================" << std::endl;
            std::cout << "======================= parameters are: " << s1 << "  " << s2 << " =======================" << std::endl;
            std::cout << "===================== but parameters must be -inf and inf or +inf =====================" << std::endl; 
        }
        else{
            v.push_back({T(-pow(10,9)), T(pow(10,9))});
        }
    }
    Range(const std::string s1,const T x,const std::pair<T,T> p, const  T y, const std::string s2){
        if((s2 != "inf" && s2 != "+inf") || s1 != "-inf"){
            std::cout << "======================================== ERROR ========================================" << std::endl;
            std::cout << "===================== header.h: Range(string,T,pair,T,string) =====================" << std::endl;
            std::cout << "===================== string parameters are: " << s1 << ' ' << s2 << " =====================" << std::endl;
            std::cout << "====================== but they must be -inf and +inf ======================" << std::endl; 
        }
        else{
            v.push_back({T(-pow(10,9)), x});
            v.push_back(p);
            v.push_back({y, T(pow(10,9))});
            sortinput();
        }
    }
    Range(const std::string s1,const T x,const std::vector<std::pair<T,T>> p, const  T y, const std::string s2){
        if((s2 != "inf" && s2 != "+inf") || s1 != "-inf"){
            std::cout << "======================================== ERROR ========================================" << std::endl;
            std::cout << "===================== header.h: Range(string,T,vector<pair>,T,string) =====================" << std::endl;
            std::cout << "===================== string parameters are: " << s1 << ' ' << s2 << " =====================" << std::endl;
            std::cout << "====================== but they must be -inf and +inf ======================" << std::endl; 
        }
        else{
            v = p;
            v.push_back({T(-pow(10,9)), x});
            v.push_back({y, T(pow(10,9))});
            sortinput();
        }
    }
    Range(const std::string s1,const T x, const  T y, const std::string s2){
        if((s2 != "inf" && s2 != "+inf") || s1 != "-inf"){
            std::cout << "======================================== ERROR ========================================" << std::endl;
            std::cout << "===================== header.h: Range(string,T,T,string) =====================" << std::endl;
            std::cout << "===================== string parameters are: " << s1 << ' ' << s2 << " =====================" << std::endl;
            std::cout << "====================== but they must be -inf and +inf ======================" << std::endl; 
        }
        else{
            v.push_back({T(-pow(10,9)), x});
            v.push_back({y, T(pow(10,9))});
            sortinput();
        }
    }
    bool operator ()(std::vector<T>& x){
        for(int i = 0; i < x.size(); ++i){
            for(int j = 0; j < v.size(); ++j){
                if(x[i] >= v[j].first && x[i] <= v[j].second)
                    return true;
            }
        }
        return false;
    }
    Range(){
        
    }
    bool operator ()(T& x){
        for(int i = 0; i < v.size(); ++i){
            if(x >= v[i].first && x <= v[i].second)
                return true;
        }
        return false;
    }
    void sortinput(){
        std::sort(v.begin(), v.end(), [](std::pair<T,T>& x, std::pair<T,T>& y){
            if(x.first > x.second){
                T c = x.first;
                x.first = x.second;
                x.second = c;
            }
            if(y.first > y.second){
                T c = y.first;
                y.first = y.second;
                y.second = c;
            }
            if(x.first >= y.first && x.second <= y.second){
                return true;
            }
            else if(y.first >= x.first && y.second <= x.second){
                return false;
            }
            else if(x.first < y.first && x.second >= y.first){
                x.second = y.first;
                return true;
            }
            else if(x.first > y.first && y.second >= x.first){
                y.second = x.first;
                return false;
            }
            else
                return (x.first < y.first);

        });
        bool b = true;
        while(b){
            b = false;
            auto it = v.begin();
            while((it+1) != v.end() && it != v.end()){
            if((*it).first >= (*(it+1)).first && (*it).second <= (*(it+1)).second){
                v.erase(it);
                b = true;
            }
            else if((*it).second == (*(it + 1)).first){
                std::pair<T,T> p = {(*it).first, (*(it+1)).second};
                v.erase(it);
                v.erase(it);
                v.insert(it,p);
                it++;
                b = true;
            }
            else
                it++;
        }
        }
    }
    Range<T>& operator = (Range<T>& r){
        v = r.v;
        return *this;
    }
    int size(){
        return v.size();
    }
    std::pair<T,T> operator ()(){
        return v[rand() % v.size()];
    }
    T right(){
        return v[v.size() - 1].second;
    }
    T left(){
        return v[0].first;
    }
};

template <>
class Range<std::string>{
public:
    std::vector<std::pair<int,int>> v;
    Range(const std::pair<int,int> p){
        v.push_back(p);
    }
    Range(const std::vector<std::pair<int,int>> p){
        v = p;
    }
    bool operator ()(std::string& x){
        for(int i = 0; i < x.size(); ++i){
            for(int j = 0; j < v.size(); ++j){
                if(int(x[i]) >= v[j].first && int(x[i]) <= v[j].second)
                    return true;
            }
        }
        return false;
    }
    bool operator ()(int& x){
        for(int i = 0; i < v.size(); ++i){
            if(x >= v[i].first && x <= v[i].second)
                return true;
        }
        return false;
    }
    int size(){
        return v.size();
    }
    std::pair<int,int> operator ()(){
        return v[rand() % v.size()];
    }
};

template <class T>
std::ostream& operator <<(std::ostream& out, Range<T>& r){
    out << r.v;
    return out;
}

long double lim(std::function<long double(long double)> f,Range<long double> range = Range<long double>("-inf","+inf"),
	std::string mode = "inf", long double start = 10000,long double e = 0.001);
long double lim(std::function<long double(long double)> f,std::string mode = "inf",
	Range<long double> range = Range<long double>("-inf","+inf"),long double start = 10000,long double e = 0.001);
long double lim(std::function<long double(long double)> f,long double x0, long double left = -0.001, long double right = 0.001,
	Range<long double> range = Range<long double>("-inf", "+inf"), long double e = 0.001);
class Matrix{
public:
	std::vector<std::vector<long double>> m;
	Matrix();
	Matrix(const std::vector<std::vector<long double>>);
	long double det();
	int size();
	void set(const std::vector<std::vector<long double>>);
	std::vector<long double>& operator [] (int);
	Matrix& operator = (const Matrix&);
};
class SLAE{
public:
	Matrix A;
	std::vector<long double> B;
	SLAE();
	SLAE(const std::vector<std::vector<long double>>,const std::vector<long double>);
	SLAE(Matrix&,const std::vector<long double>);
	void set(const std::vector<std::vector<long double>>, const std::vector<long double>);
	void set(Matrix&, const std::vector<long double>);
	std::vector<long double> solve();
};
class EqSys{
public:
	std::vector<std::string> names;
	SLAE s;
	EqSys();
	EqSys(const std::vector<std::string>);
	void set(const std::vector<std::string>);
};

class Function{
public:
	Range<long double> range;
	std::string mode;
	std::function<long double(long double)>simpfunc;
	std::function<long double(long double,std::vector<long double>, double)>f;
	std::vector<long double> k;
	double power;
	Function(std::function<long double(long double,std::vector<long double>, double)> func, 
		std::vector<long double> solution, double p, Range<long double> r);
	Function(std::function<long double(long double,std::vector<long double>, double)> func, 
		std::vector<long double> solution, double p);
	Function(std::function<long double(long double)> func, Range<long double> r);
	Function(std::function<long double(long double)> func);
	Function(Range<long double> r = Range<long double>("-inf","inf"));
	Function(std::map<double,long double>&, double);
	long double operator()(long double x);
	Function der(std::string m = "simp");
	Function& operator = (std::function<long double(long double)>);
	long double der(long double);
	long double defDer(long double, long double left = -0.001, long double right = 0.001);
	long double operator [](int);
};
long double lim(Function& f,
	std::string mode = "inf", long double start = 10000, long double e = 0.001);
long double lim(Function& f, long double x0, long double left = -0.001, long double right = 0.001, 
	long double e = 0.001);
Function powerAp(std::map<double,long double>&, double);
bool is_prime(int);
int factorial(int);
std::istream& operator >> (std::istream&,EqSys&);
std::ostream& operator << (std::ostream&,EqSys&);
std::ostream& operator << (std::ostream&, Function&);
std::vector<std::pair<int,int>> canon(int);
long int C(int,int);
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
 std::vector<std::string> split(std::string s, std::string ch = " ", std::string except = "");
 std::string strip(std::string s, std::string ch = " ");


template <class T1, class T2>
std::istream& operator >> (std::istream& in, std::pair<T1,T2>& pair){
	std::string s;
    std::getline(in, s);
    if(s == "{}")
    	return in;
    std::string s1(s.begin()+1,s.end()-1);
    auto vals = split(s1, ",");
    std::stringstream st1, st2;
    st1 << vals[0];
    st2 << vals[1];
    T1 fir;
    T2 sec;
    st1 >> fir;
    st2 >> sec;
    pair.first = fir;
    pair.second = sec;
    return in;
}

template <class T>
std::istream& operator >> (std::istream& in, std::vector<T>& v){
    std::string inp;
    std::getline(in, inp);
    if(inp.size() == 0)
    	return in;
    auto vals = split(inp);
    for(int i = 0; i < vals.size(); ++i){
    	std::stringstream stream;
    	stream << vals[i];
    	T x;
    	stream >> x;
    	v.push_back(x);
    }
    return in;
}

template <class T>
void stringToVector(std::string& s, std::vector<T>& v){
	std::stringstream stream;
	stream << s;
	stream >> v;
}

template <class T>
void writeVectors(std::vector<std::vector<T>>& v, std::string path){
	std::ofstream out(path);
	if(!out.is_open()){
		std::string s = "filework.h : writeVector: Cannot open file " + path; 
		std::cout << s << std::endl; 
	}
	else{
		for(int i = 0; i < v.size(); ++i){
			for(int j = 0; j < v[i].size(); ++j)
				out << v[i][j] << ' ';
			out << '\n';
		}
	}
	out.close();
}

template <class T>
void writeVectors(std::vector<T>& v, std::string path){
	//std::cout << path << std::endl;
	std::ofstream out(path);
	if(!out.is_open()){
		std::string s = "filework.h : writeVector: Cannot open file " + path; 
		std::cout << s << std::endl; 
	}
	else{
		for(int i = 0; i < v.size(); ++i){
				out << v[i] << ' ';
		}
		out << '\n';
	}
	out.close();
}

template <class T>
void readVectors(std::vector<std::vector<T>>& v, std::string path){
	
	std::ifstream input(path);
	if(!input.is_open()){
		std::string s = "filework.h : readVectors: Cannot open file " + path; 
		std::cout << s << std::endl; 
	}
	else{
		std::string line;
		while (std::getline(input, line))
       	{
       		std::vector<T> curr;
       		stringToVector(line,curr);
       		v.push_back(curr);
       	}
	}
	input.close();
}
 void clear(std::string);

template <class T>
void swap(T& a, T& b){
    T c = a;
    a = b;
    b = c;
}
template <class T>
T max(T& a, T& b){
    if(a > b)
        return a;
    else
        return b;
}
template <class T>
T min(T& a, T& b){
    if(a < b)
        return a;
    else
        return b;
}
template <class T>
std::ostream& operator <<(std::ostream&,std::stack<T>);
template <class T>
std::ostream& operator <<(std::ostream&,std::deque<T>);

template <class T1, class T2>
std::ostream& operator <<(std::ostream&,std::pair<T1,T2>);
template <class T>
std::ostream& operator <<(std::ostream&,std::queue<T>);

template <class T>
std::ostream& operator << (std::ostream&, std::vector<T>&);

template <class T>
std::istream& operator >> (std::istream&, std::vector<T>&);

template <class T>
std::ostream& operator << (std::ostream& out, std::stack<T> s){
    for(auto el : s)
        out << el << ' ';
    out << '\n';
    return out;
}
template <class T>
std::ostream& operator << (std::ostream& out, std::set<T>& s){
    for(auto it = s.begin(); it != s.end(); ++it)
        out << *it << std::endl;
    return out;
}
template<class T>
void dynammassout(T* mass, int N){
    std::cout << "{";
    for(int i = 0; i < N; ++i)
        std::cout << mass[i] << ' ';
    std::cout << " }";
    std::cout << '\n';
}

template<class T>
void matrixoutput(T** matrix, int N, int M){
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
}


template <class T>
std::ostream& operator << (std::ostream& out, std::deque<T> q){
    for(auto el : q)
        out << q << ' ';
    out << '\n';
    return out;
}

template <class T1, class T2>
std::ostream& operator << (std::ostream& out, std::pair<T1,T2> pair){
    out << '{' << pair.first << "," << pair.second << "}";
    return out;
}

template <class T>
std::ostream& operator << (std::ostream& out, std::queue<T> q){
    for(auto el : q)
        out << q << ' ';
    out << '\n';
    return out;
}

template <class T>
std::ostream& operator << (std::ostream& out, std::vector<T>& v){
    out << "{";
    for(long unsigned int i = 0; i < v.size(); ++i){
        if(i != v.size()-1)
            out << v[i] << ' ';
        else
            out << v[i];
    }
    out << "}" << std::endl;
    return out;
}

template <class T1, class T2>
std::ostream& operator << (std::ostream& out, std::map<T1, T2>& mp){
    for(auto it = mp.begin(); it != mp.end(); ++it){
        out << (*it).first << " : " << std::endl;
        out << (*it).second << std::endl;
    }
    out << '\n';
    return out;
}

template <class T>
int find(std::vector<T>& v,const T s){
    for(int i = 0; i < v.size(); ++i){
        if(v[i] == s){
            return i;
        }
    }
    return -1;
}

template <class T>
int binarySearch(std::vector<T>& v,const T x, int leftoffset = 0, int rightoffset = 0) 
{
  int l = leftoffset;
  int r = v.size() - 1 - rightoffset;
  while (l <= r) {
    int mid = l + (r - l) / 2;
    if(v[mid] == x)
      return mid;
    else if(v[mid] < x)
      l = mid + 1;
    else
      r = mid - 1;
  }
  return -1;
}

template <class T>
void insert_sort(std::vector<T>& a, std::function<bool(T&, T&)> comp = [](T& x, T& y){return (x < y);}){    //insertion sort, O(n^2)
    for(long unsigned int i = 1; i < a.size(); ++i){
        for(int j = i-1; j >= 0 && !comp(a[j],a[j+1]); --j)
            swap(a[j],a[j+1]);
    }
}  //insertion sort, O(n^2), по возрастанию



template <class T>
void merge(std::vector<T>& v,std::vector<T>& v1, std::vector<T>& v2, std::function<bool(T&,T&)> comp){
    v.clear();
    long unsigned int i = 0, j = 0;
    while(i < v1.size() && j < v2.size()){
        if(comp(v1[i],v2[j])){
            v.push_back(v1[i]);
            i++;
        }
        else{
            v.push_back(v2[j]);
            j++;
        }
    }
    if(i < v1.size()){
        for(long unsigned int k = i; k < v1.size();++k)
            v.push_back(v1[k]);
    }
    else if(j < v2.size()){
        for(long unsigned int k = j; k < v2.size();++k)
            v.push_back(v2[k]);
    }
} // Вспомогательная функция merge sort
template <class T>
void merge_sort(std::vector<T>& v, std::function<bool(T&, T&)> comp = [](T& x, T& y){return (x < y);}){   // Merge Sort, O(n * log(n))
    if(v.size() == 2){
        if(!comp(v[0],v[1])){
            swap(v[0],v[1]);
        }
    }
    else if(v.size() > 2){
        std::vector<T> v1(v.begin(), v.begin() + (v.size() / 2));
        std::vector<T> v2(v.begin() + (v.size() / 2), v.end());
        merge_sort(v1,comp);
        merge_sort(v2,comp);
        merge(v,v1,v2,comp);
    }
} // Merge Sort, O(n * log(n)), по возрастанию, O(n) - память

template <class T>
int partition(std::vector<T>& v, int p, int r){
    int x = v[p];
    int i = p;
    int j = r;
    while(true){
        while(v[j] <= x && j >= 0)
            j--;
        while(v[i] >= x && i < v.size())
            i++;
        if(i < j)
            swap(v[i],v[j]);
        else
            return j;
    }
}
template <class T>
void quickSort(std::vector<T>& v, int p, int r){
    if(p < r){
        int q = partition(v,p,r);
        quickSort(v,p,q);
        quickSort(v,q+1,r);
    }
}
template <class T>
void quickSort(std::vector<T>& v){
    int p = 0, r = v.size()-1;
    quickSort(v,p,r);
}


 void clear(std::string path){
	std::ofstream out(path);
	if(!out.is_open()){
		std::string s = "filework.h : clear : Cannot open file " + path;
		std::cout << s << std::endl;
	}
	else{
		out << "";
	}
	out.close();
}
bool is_prime(int n) {
  try{
  	if(n <= 0)
  		throw "bool is_prime: argument is less than 0 or is 0";
  }
  catch(const char* s){
  		std::cout << s << std::endl;
  		return false;
  }
  if(n == 1) 
  	return false; 
  if(n == 2 || n == 3) 
  	return true; 
  if(n % 2 == 0 || n % 3 == 0) return false; 
  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return false;
    }
  }
  return true;
}
std::vector<std::pair<int,int>> canon(int x){
	if(is_prime(x))
		return {{x,1}};
	std::vector<std::pair<int,int>> res;
	int i = 2;
	while(1){
		if(i > x)
			break;
		if(is_prime(i)){
			if(x % i == 0){
				res.push_back({i,0});
				while(x % i == 0){
					res[res.size()-1].second++;
					x = x / i;
				}
			}
			i++;
		}
		else
			i++;
	}
	return res;
}
long int C(int n, int k){
  if (k == 0 || k == n) {
    return 1;
  } else if (k < 0 || k > n) {
  	std::cout << "======================= ERROR =======================" << std::endl;
  	std::cout << "======= mathFuncs.cpp: long int C(int n, int k) ========" << std::endl;
  	std::cout << " k < 0 or k > n" << std::endl;
  	std::cout << "=====================================================" << std::endl;
    return 0;
  }
  long long int dp[k + 1];
  dp[0] = 1;
  for (int i = 1; i <= k; i++) {
    dp[i] = 0;
    for (int j = 1; j <= i; j++) {
      dp[i] += dp[j - 1];
    }
  }
  return dp[k];
}
Function powerAp(std::map<double,long double>& mp, double power){
	if(power < 0){
		std::cout << "========================= ERROR =========================" << std::endl;
		std::cout << "============ mathFuncs.cpp: powerAp() ============" << std::endl;
		std::cout << "power must be non negative, now power is: " << power << std::endl;
		std::cout << "=========================================================" << std::endl;
		return Function();
	}
	else if(power != 0){
		std::vector<long double> a, b;
		for(int i = 0; i < 2*power; ++i)
			a.push_back(0);
		for(int i = 0; i < power+1; ++i)
			b.push_back(0);
		for(auto el : mp){
			for(int i = 0; i < 2*power;++i)
				a[i] += pow(el.first,i+1);
			for(int i = 0; i < power + 1; ++i)
				b[i] += el.second*pow(el.first,power - i);
		}
		Matrix M;
		for(int i = 0; i < power + 1; ++i){
			std::vector<long double> row = {};
			for(int j = 0; j < power + 1; ++j){
			//	std::cout << int(a.size() - 1 - i - j) << "  AAAAAAAAA" << std::endl;
				if(int(a.size() - 1 - i - j) < 0)
					row.push_back(mp.size());
				else
					row.push_back(a[a.size() - 1 - i - j]);
			}
			M.m.push_back(row);
		}
		SLAE sl(M, b);
		std::vector<long double> solution = sl.solve();
		auto F = [](long double xi, std::vector<long double> solution, double power) -> long double{
			long double result = 0;
			for(int i = 0; i < power + 1; ++i){
				result += solution[i] * pow(xi, power - i);
			}
			return result;
		};
		Function result(F,solution,power);
		return result;
		// long double result = 0;
		// for(double xi = n; xi <= N; xi+=0.25){
		// 	result += (F(xi) - mp[xi])*(F(xi) - mp[xi]);
		// }
	}
	else{
		std::vector<long double> solution;
		long double sum = 0;
		for(auto el : mp)
			sum += el.second;
		solution.push_back(sum / mp.size());
		auto F = [](long double xi, std::vector<long double> solution, double power) -> long double{
			return solution[0];
		};
		Function result(F,solution,power);
		return result;
	}
}
Matrix::Matrix(const std::vector<std::vector<long double>> v){
	m = v;}
void Matrix::set(const std::vector<std::vector<long double>> v){
	m = v;
}
Matrix::Matrix(){
	m = {};}
int Matrix::size(){
	return m.size();}
std::vector<long double>& Matrix::operator [] (int i){
	return m[i];}
long double Matrix::det(){
	long double sum = 0;
	std::vector<std::vector<long double>> v = {};
	std::vector<long double> row = {};
	if(m.size() == 2){
		sum = (m[0][0] * m[1][1] - m[0][1]*m[1][0]);
	}
	else{
		for(int i = 0; i < m.size(); ++i){
			for(int j = 1; j < m.size(); ++j){
				row.clear();
				for(int h = 0; h < m.size(); ++h){
					if(h != i)
						row.push_back(m[j][h]);
				}
				v.push_back(row);
			}
			Matrix m1(v);
			v.clear();
			sum += pow(-1,i)*m[0][i]*m1.det(); 
		}
	}
	return sum;}
Matrix& Matrix::operator = (const Matrix& other){
	(this -> m) = (other.m);
	return *this;}
 std::vector<std::string> split(std::string s, std::string ch, std::string except){
	std::vector<std::string> res;
	std::string curr;
	bool push = true;
	for(int i = 0; i < s.size(); ++i){
		if(ch.find(s[i]) != std::string::npos && i != (s.size() - 1) && push){
			if(i != 0)
				res.push_back(curr);
			curr.clear();
			if(except.find(s[i]) != std::string::npos){
				curr += s[i];
			}
			push = false;
		}
		else if(ch.find(s[i]) != std::string::npos && i != (s.size() - 1) && !push && except.find(s[i]) != std::string::npos){
			curr += s[i];
		}
		else if(i == (s.size() - 1)){
		//	std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
			if(ch.find(s[i]) == std::string::npos)
				curr+=s[i];
			res.push_back(curr);
		}
		else if(ch.find(s[i]) == std::string::npos){
			push = true;
			curr += s[i];
		}
	}
	return res;
}

 std::string strip(std::string s, std::string ch){
	std::string res;
	for(int i = 0; i < s.size(); ++i){
		if(ch.find(s[i]) == std::string::npos)
			res+=s[i];
	}
	return res;
}
EqSys::EqSys(){}
EqSys::EqSys(const std::vector<std::string> v){
		set(v);
}
void EqSys::set(const std::vector<std::string> v){
		std::vector<std::vector<long double>> tempA;
		std::vector<std::vector<long double>> A;
		std::vector<std::vector<std::string>> tempNames;
		std::vector<long double> B;
		for(int n = 0; n < v.size(); ++n){
			std::string s = v[n];
			auto line = split(s, "+-=", "-");
			Range<std::string> r({{'a','z'},{'A','Z'}});
			std::vector<long double> Drow;
			std::vector<std::string> Srow;
			for(int i = 0; i < line.size(); ++i){
				if(!r(line[i])){
					std::stringstream stream;
					stream << line[i];
					long double k;
					stream >> k;
					B.push_back(k);	
				}
				else{
					auto subline = split(line[i], "*");
					if(subline.size() == 1){
						if(subline[0][0] == '-'){
							Drow.push_back(-1);
							Srow.push_back(std::string(subline[0].begin() + 1, subline[0].end()));
						}
						else{
							Drow.push_back(1);
							Srow.push_back(subline[0]);
						}
					}
					else{
						for(int j = 0; j < subline.size(); ++j){
						if(r(subline[j])){
							Srow.push_back(subline[j]);
						}
						else{
							long double k;
							std::stringstream stream;
							stream << subline[j];
							stream >> k;
							Drow.push_back(k);
						}
					}
					}
				}
				for(int i = 0; i < Srow.size(); ++i){
					if(find(names, Srow[i]) == -1){
						names.push_back(Srow[i]);
					}
				}
			}
			tempA.push_back(Drow);
			tempNames.push_back(Srow); 
		}
		for(int i = 0; i < tempA.size(); ++i){
			std::vector<long double> row;
			for(int j = 0; j < names.size(); ++j)
				row.push_back(0);
			for(int j = 0; j < names.size(); ++j){
				int pos = find(tempNames[i], names[j]);
				if(pos != -1){
					row[j] = tempA[i][pos];
				}
			}
			A.push_back(row);
		}
 		s.set(A,B);
}
std::istream& operator >> (std::istream& in, EqSys& eq){	
		std::cout << "End system with //" << std::endl;
		std::vector<std::string> v;
		while(true){
			std::string s;
			std::getline(in,s,'\n');
			s = strip(s);
			if(s == "$" || s == "$$" || s == "|" || s == "||" || s == "/" || s == "//")
				break;
			v.push_back(s);
		}
		eq.set(v);
		return in;
}
std::ostream& operator << (std::ostream& out, EqSys& eq){
	auto solution = eq.s.solve();
	for(int i = 0; i < eq.names.size(); ++i){
		out << eq.names[i] << "  " << solution[i] << std::endl;
	}
	out << '\n';
	return out;
}
//Дан массив целых чисел, назовем отрезов k-хорошим, если в нем не более k различных чисел
//Найти длину наиболее длинного k-хорошего отрезка
alg power(int n){
	alg r(1);
	int i = 1;
	while(i <= n){
		if(n - i >= 1999000){
			r *= 247581393;
			i += 1999000;
		}
		else if(n - i >= 35){
			r *= 359738130;
			i+=35;
		}
		else if(n - i >= 16){
			r *= 65536;
			i += 16;
		}
		else{
			r *= 2;
			i++;
		}
	}
	return r;
}


bool intersect(Rect& x, Rect& y){
	if(x.rx <= y.lx || y.rx <= x.lx)
		return false;
	if(x.ry <= y.ly || y.ry <= x.ly)
		return false;
	return true;
}
int MaxKgoodsize(std::vector<long>& v, long unsigned int k){
	if(v.size() <= k)
		return v.size();
	std::map<long,long unsigned int> mp;
	int count = 0;
	int maxcount = 0;
	for(long unsigned int i = 0; i < v.size(); ++i){
		if(mp.find(v[i]) != mp.end()){
			mp[v[i]]++;
			count++;
		}
		else{
			mp.emplace(v[i],1);
			count++;
			if(mp.size() > k){
				while(mp.size() > k){
					mp[v[i-count+1]]--;
					if(mp[v[i-count+1]] == 0){
						mp.erase(v[i-count+1]);
					}
					count--;
				}
			}
		}
		maxcount = max(count,maxcount);
	}	
	return maxcount;
}


void Btask(std::vector<std::vector<int>>& input,std::vector<std::vector<int>>& res){
	std::vector<int> r(input.size()-2,0);
	int T = input[input.size()-1][0];
	auto increaseNum = [](std::vector<int>& v, int c) -> int{
		int r = 0;
		int k = v.size()-1;
		for(int i = 1; i < v.size()-1; ++i){
			if(c < v[i]){
				k = i;
				break;
			}
		}
		r += (k-1);
		r -= (v.size()-1-k);
		return r;
	}; 
	for(int i = 1; i < input.size()-1; ++i){
		input[i].push_back(i-1);
		std::sort(input[i].begin()+1,input[i].end()-1);
		int inc = increaseNum(input[i],0); 
		input[i][0] = inc;
	} 
	input.erase(input.begin());
	input.erase(input.end()-1); 
	heap<std::vector<int>> h(input,2,
		[](std::vector<int>& x, std::vector<int>& y){return (x[0] > y[0]);}); 
	while(T > 0){
		int point = h.vector[0][h.vector[0].size()-1];
		r[point]++;
		T--;
		int inc = increaseNum(h.vector[0], r[point]); 
		h.vector[0][0] = inc;
		h.heapify(0);
	} 
	res.push_back(r);
}
void Ctask(std::vector<std::vector<int>>& input,std::vector<std::vector<int>>& res){
	int n = input[0][0];
	alg g(0);
	int n0 = n-1;
	std::vector<i64> cv = {1};
	for(int i = 0; i <= n0; ++i){
		std::vector<i64> tmp;
		for(int j = 0; j <= i; ++j){
			if(j == 0 || j == i)
				tmp.push_back(1);
			else{
				tmp.push_back(alg(cv[j-1]+cv[j]).x);
			}
		}
		cv = tmp;
	}
	for(int k = 0; k <= n0;++k){
		alg tmp(1);
		tmp *= ((n0 - k) % 2 == 0 ? 1 : -1);
		tmp *= power(k*(k-1)/2);
		tmp *= cv[k];
		g += tmp;
	}
	g*=n;
	res.push_back(std::vector<int>{g.x});
}
void Dtask(std::vector<std::vector<int>>& input,std::vector<std::vector<int>>& res){
	for(int i = 1; i < input.size(); ++i){
		int r = 1;
		int a = input[i][0];
		int b = input[i][1];
		std::vector<std::pair<int,int>> va = canon(a);
		std::vector<std::pair<int,int>>	vb = canon(b);
		for(int j = 0; j < va.size(); ++j){
			int ind = -1;
			for(int k = 0; k < vb.size(); ++k){
				if(vb[k].first == va[j].first){
					ind = k;
					break; 
				}
			}
			if(ind != -1){
				int power = min(va[j].second, vb[ind].second);
				r *= pow(va[j].first, power);
				va[j].second -= power;
				vb[ind].second -= power;
			}
		}
		int m = 1;
		for(int j = 0; j < va.size(); ++j){
			if(va[j].second > 0)
				m = max(m,va[j].first);
		}
		for(int j = 0; j < vb.size(); ++j){
			if(vb[j].second > 0)
				m = max(m,vb[j].first);
		}
		r *= m;
		res.push_back(std::vector<int>({r}));
	}
}
void Etask(std::vector<std::vector<int>>& input,std::vector<std::vector<int>>& res){
	class Vert{
	public:
		int x, ly, ry, type, id;
		Vert(int a, int b, int c, int d, int e){
			x = a;
			ly = b;
			ry = c;
			type = d;
			id = e;
		}
	};
	std::vector<Rect> rects;
	std::vector<Vert> verts;
	std::vector<int> intersections(input[0][0],0);
	std::vector<Rect> active;
	for(int i = 1; i < input.size(); ++i){
		int lx = input[i][0];
		int ly = input[i][1];
		int rx = input[i][2];
		int ry = input[i][3];
		Rect r(lx,rx,ly,ry,i-1);
		Vert v1(lx,ly,ry,0,i-1);
		Vert v2(rx,ly,ry,1,i-1);
		rects.push_back(r);
		verts.push_back(v1);
		verts.push_back(v2);
	}
	std::function<bool(Vert&,Vert&)> comp = [](Vert& x, Vert& y){
		return x.x < y.x;
	};
	merge_sort(verts,comp);
	for(int i = 0; i < verts.size(); ++i){
		if(verts[i].type == 0){
			Rect tmp = rects[verts[i].id];
			for(int j = 0; j < active.size(); ++j){
				if(intersect(tmp, active[j])){
					intersections[tmp.id]++;
					intersections[active[j].id]++;
				}
			}
			active.push_back(tmp);
		}
		else{
			Rect tmp = rects[verts[i].id];
			auto it = active.begin();
			while(it != active.end()){
				if(tmp.rx == (*it).rx)
					active.erase(it);
				else
					it++;
			}
		}
		// for(auto el : active)
		// 	std::cout << el.id << ' ';
		// std::cout << std::endl;
		// std::cout << intersections << std::endl;
	}
	res.push_back(intersections);
}


void onesandzerosMaxMindistance(std::string inp, std::string output){
	std::vector<std::vector<int>> input;
	readVectors(input, inp);
	std::vector<int> res;
	std::vector<int> v = input[0];
	int m = -1;
	int currk = 0;
	int curr = 0;
	int pos = 0;
	int start = 0;
	for(int i = 0; i < v.size(); ++i){
		if(v[i] == 1)
		{
			start = i;
			break;
		}
	}
	if(start > 0)
		res.push_back(0);
	m = start;
	for(int i = start; i < v.size(); ++i){
		if(v[i] == 1){
			curr = (curr / 2) + (curr % 2);
			if(curr >= m){
				if(curr > m){
					m = curr;
					res.clear();
				}
				pos = ((currk+i)/2);
				res.push_back(pos);
				if((i + currk) % 2 == 1){
					pos = ((currk+i)/2)+1;
					res.push_back(pos);	
				}
			}
			curr = 0;
			currk = i;
		}
		else if(i == v.size() - 1){
			curr++;
			if(curr >= m){
				pos = i;
				if(curr > m){
					m = curr;
					res.clear();
				}
				res.push_back(pos);
			}
		}
		else{
			curr++;
		}
	}
	writeVectors(res,output);
}
SLAE::SLAE(){

}
SLAE::SLAE(const std::vector<std::vector<long double>> V1,const std::vector<long double> V2){
	A.m = V1;
	B = V2;}
SLAE::SLAE(Matrix& M,const std::vector<long double> V){
	A = M;
	B = V;}
void SLAE::set(const std::vector<std::vector<long double>> V1, const std::vector<long double> V2){
	A.m = V1;
	B = V2;
}
void SLAE::set(Matrix& M, const std::vector<long double> V){
	A = M;
	B = V;
}
std::vector<long double> SLAE::solve(){
	std::vector<long double> solution;
	if(A.size() < A[0].size()){
		std::cout << "===================================== SLAE solution, number of rows less than nunber of variables =====================================" << std::endl;
		return solution;
	}
	else if(A.size() > A[0].size()){
		std::cout << "===================================== SLAE solution, number of rows bigger than nunber of variables =====================================" << std::endl;
		std::cout << "========================================================== Undefined behaviour ==========================================================" << std::endl;
		return solution;
	}
	long double d0 = A.det();
	for(int i = 0; i < A.size();++i){
		Matrix tmp = A;
		for(int j = 0; j < A.size(); ++j)
			tmp[j][i] = B[j];
		long double d = tmp.det();
		solution.push_back(d / d0);
	}
	return solution;}
long double lim(std::function<long double(long double)> f,Range<long double> range,
	std::string mode, long double start,long double e){
		long double prev = 1000;
		long double res = 0;
		int count = 0;
		if(mode == "inf" || mode == "+inf"){
			if(range.right() < pow(10,9)){
				std::cout << "====================================================== ERROR ======================================================" << std::endl;
				std::cout << "============== math.cpp::lim(std::function,Range<double>, std::string, long double, long double) ==============" << std::endl;
				std::cout << "============== Function right range is not +inf, but you trying to find lim x -> +inf ==============" <<std::endl;
				return 0;
			}
			if(start < 0)
				start*=-1;
		}
		else if(mode == "-inf"){
			if(range.left() > -pow(10,9)){
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
			if(range.right() < pow(10,9)){
				std::cout << "====================================================== ERROR ======================================================" << std::endl;
				std::cout << "============== math.cpp::lim(std::function,std::string, Range<double>, long double, long double) ==============" << std::endl;
				std::cout << "============== Function right range is not +inf, but you trying to find lim x -> +inf ==============" <<std::endl;
				return 0;
			}
			if(start < 0)
				start*=-1;
		}
		else if(mode == "-inf"){
			if(range.left() > -pow(10,9)){
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

	if(range.left() > -pow(10,9))
		left = range.left();
	else if(x0 != 0)
		left = (int(x0 < 0)*2 - 1) * x0 * 1000;


	if(range.right() < pow(10,9))
		right = range.right();
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
Function::Function(std::function<long double(long double,std::vector<long double>, double)> func,
 std::vector<long double> solution, double p, Range<long double> r){
		power = p;
		f = func;
		k = solution;
		range = r;
		mode = "pow";
}
Function::Function(std::function<long double(long double)> func, Range<long double> r){
		power = 0;
		simpfunc = func;
		range = r;
		mode = "simp";
}
Function::Function(std::function<long double(long double,std::vector<long double>, double)> func,
 std::vector<long double> solution, double p){
		power = p;
		f = func;
		k = solution;
		Range<long double> tmp("-inf","inf");
		range = tmp;
		mode = "pow";
}
Function::Function(std::function<long double(long double)> func){
		power = 0;
		simpfunc = func;
		Range<long double> tmp("-inf","inf");
		range = tmp;
		mode = "simp";
}
Function::Function(Range<long double> r){
	power = 0;
	k = {};
	range = r;
}
long double Function::operator()(long double x){
		if(range(x)){
			if(mode == "pow")
				return f(x,k,power);
			else if(mode == "simp")
				return simpfunc(x);
		}
		else{
			std::cout << "======================== ERROR ========================" << std::endl;
			std::cout << "math.cpp: long double Function::operator()(long double x)" << std::endl;
			std::cout << "argument is out of range" << std::endl;
			return 0;
		}
}
std::ostream& operator <<(std::ostream& out, Function& f){
	out << f.k << std::endl;
	return out;
}
Function Function::der(std::string m){
	if(m == "pow"){ 
		std::vector<long double> newk;
		double newp = power - 1;
		for(int i = 0; i < k.size()-1;++i){
			newk.push_back(k[i]*(power-i));
		}
		return Function(f,newk, newp);
	}
	else{
		std::cout << "=============================== ERROR ===============================" << std::endl;
		std::cout << "math.cpp: Function Function::der(std::string mode)" << std::endl;
		std::cout << "Unknown mode: " << m << std::endl;
		return Function();
	}
}
long double Function::der(long double x){
	if(mode == "pow"){
		auto f = der(mode);
		return f(x);
	}
	else
		return defDer(x);
}
long double Function::defDer(long double x, long double left, long double right){
		if(mode == "pow"){
				auto F = [&](long double arg){
						return (f(x + arg,k,power) - f(x,k,power)) / arg;
				};
				return lim(F, 0,left,right);
		}
		else if(mode == "simp"){
				auto F = [&](long double arg){
						return (simpfunc(x + arg) - simpfunc(x)) / arg;
				};
				return lim(F, 0,left,right);
		}
		else{
			std::cout << "=============================== ERROR ===============================" << std::endl;
		std::cout << "math.cpp: Function Function::defDer(long double)" << std::endl;
		std::cout << "Unknown mode: " << mode << std::endl;
		return 0;
		}
}
Function& Function::operator=(std::function<long double(long double)> func){
	Range<long double> tmp("-inf", "inf");
	range = tmp;
	mode = "simp";
	simpfunc = func;
	return *this;
}
long double Function::operator[](int i){
	if(i >= k.size()){
		std::cout << "=========================== ERROR ===========================" << std::endl;
		std::cout << "= mathFunction.cpp: long double Function::operator[](int i) =" << std::endl;
		std::cout << "index is out of vector (k) range" << std::endl;
		std::cout << "k.size(): " << k.size() << " index: " << i << std::endl;
		std::cout << "also for this operation mode must be 'pow', now mode is: " << mode << std::endl;
		std::cout << "=============================================================" << std::endl;
		return 0;
	}
	else
		return k[i];
}
Function::Function(std::map<double,long double>& mp, double p){
	*this = powerAp(mp,p);
}
// typedef unsigned short u16;
// typedef short int i16;
typedef int i32;
// typedef unsigned int u32;
typedef unsigned long int u64;
typedef long int i64;
// typedef char u8;
// typedef void u0;

int main(int argc, char* argv[]){
	std::vector<std::vector<int>> input;
	std::vector<std::vector<int>> res;
	 	readVectors(input, "input.txt");
	// int k = 3000;
	// int p = k*(k-1)/2;
	// alg r = power(p);
	// std::cout << p << std::endl;
	// std::cout << r.x << std::endl;
	Ctask(input,res);
		writeVectors(res,"output.txt");	
	return 0;
}
