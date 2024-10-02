#include <typeinfo>
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
#include <sstream>
#include <cmath>
#include <fstream>


template <class T>
void stringToVector(std::string& s, std::vector<T>& v){
	std::stringstream stream;
	stream << s;
	stream >> v;
}

template <class T>
void writeVectors(std::vector<T>& v, std::string path){
	std::ofstream out(path);
	if(!out.is_open()){
		std::string s = "filework.h : writeVector: Cannot open file " + path; 
		std::cout << s << std::endl; 
	}
	else
		out << v;
	out.close();
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
			out << v[i] << std::endl;
		}
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


//Дан массив целых чисел, назовем отрезов k-хорошим, если в нем не более k различных чисел
//Найти длину наиболее длинного k-хорошего отрезка
int MaxKgoodsize(std::vector<long>&, long unsigned int);

//{ 
//Хакатон идет 24 часа. Если он начинается в 18:00:00, то последняя секунда, в
// которую можно отправить решение это 17:59:59 следуюшего дня
// Цель - взломать наибольшее количество серверов
// За каждый взломанный сервер начисляется 1 балл, и также штрафное время в минутах,
// округленное в меньшую сторону, прошедшее с начала хакатона

// Если было несколько попыток взломать сервер, то за каждую неудчаную попытку
// начисляется 20 минут штрафного времени

// Если было несколько попыток, но сервер так и не взломали, то штрафное время не начисляется

// в ходе соревнований команды могут отправлять PING запросы к серверу, которые никак не учитываются

// Побеждает команда, которая взломала наибольшее количество серверов, если таких несколько, то побеждает с наименьшим
// штрафным временем

// Написать программу, которая выводит результаты хакатона


//В первой строке дано время начала хакатона hh::mm::ss, во второй строке число N - количество 
//}// Условие


//дан отсортированный массив, найти количество пар чисел, у которых среднее арифметическое тоже в массиве
std::vector<std::pair<int,int>> problem1(std::vector<int>&);


class Matrix{
public:
	std::vector<std::vector<long double>> m;
	Matrix();
	Matrix(std::vector<std::vector<long double>>&);
	long double det();
	int size();
	std::vector<long double>& operator [] (int);
	Matrix& operator = (const Matrix&);
};
class SLAE{
public:
	Matrix A;
	std::vector<long double> B;
	SLAE(std::vector<std::vector<long double>>, std::vector<long double>);
	SLAE(Matrix&, std::vector<long double>);
	std::vector<long double> solve();
};
long double powerAp(std::map<double,long double>&, double, int, int);
long double constAp(std::map<double,long double>& mp, int, int);


bool is_prime(int);
std::vector<std::pair<int,int>> canon(int);
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



extern std::vector<std::string> split(std::string s, char ch = ' ');



template <class T1, class T2>
std::istream& operator >> (std::istream& in, std::pair<T1,T2>& pair){
	std::string s;
    std::getline(in, s);
    if(s == "{}")
    	return in;
    std::string s1(s.begin()+1,s.end()-1);
    auto vals = split(s1, ',');
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
    if(inp == "{}")
    	return in;
    std::string s(inp.begin()+1, inp.end()-1);
    auto vals = split(s);
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
bool find(std::vector<T>& v, T s){
    bool b = false;
    for(int i = 0; i < v.size(); ++i){
        if(v[i] == s){
            b = true;
            break;
        }
    }
    return b;
}

template <class T>
int binarySearch(std::vector<T>& v, T x) {
  int l = 0;
  int r = v.size() - 1;
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
T max(T& a, T& b){
    if(a > b)
        return a;
    else
        return b;
}

template <class T>
void swap(T& a, T& b){
    T c = a;
    a = b;
    b = c;
}


template <class T>
void insert_sort(std::vector<T>& a){    //insertion sort, O(n^2)
    for(long unsigned int i = 1; i < a.size(); ++i){
        for(int j = i-1; j >= 0 && a[j] > a[j+1]; --j)
            swap(a[j],a[j+1]);
    }
}  //insertion sort, O(n^2), по возрастанию



template <class T>
void merge(std::vector<T>& v,std::vector<T>& v1, std::vector<T>& v2){
    v.clear();
    long unsigned int i = 0, j = 0;
    while(i < v1.size() && j < v2.size()){
        if(v1[i] < v2[j]){
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
void merge_sort(std::vector<T>& v){   // Merge Sort, O(n * log(n))
    if(v.size() == 2){
        if(v[0] > v[1])
            swap(v[0],v[1]);
    }
    else if(v.size() > 2){
        std::vector<T> v1(v.begin(), v.begin() + (v.size() / 2));
        std::vector<T> v2(v.begin() + (v.size() / 2), v.end());
        merge_sort(v1);
        merge_sort(v2);
        merge(v,v1,v2);
    }
} // Merge Sort, O(n * log(n)), по возрастанию




Matrix::Matrix(std::vector<std::vector<long double>>& v){
	m = v;}
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
SLAE::SLAE(std::vector<std::vector<long double>> V1, std::vector<long double> V2){
	A.m = V1;
	B = V2;}
SLAE::SLAE(Matrix& M, std::vector<long double> V){
	A = M;
	B = V;}
Matrix& Matrix::operator = (const Matrix& other){
	(this -> m) = (other.m);
	return *this;}
std::vector<long double> SLAE::solve(){
	std::vector<long double> solution;
	long double d0 = A.det();
	for(int i = 0; i < A.size();++i){
		Matrix tmp = A;
		for(int j = 0; j < A.size(); ++j)
			tmp[j][i] = B[j];
		long double d = tmp.det();
		solution.push_back(d / d0);
	}
	return solution;}

long double powerAp(std::map<double,long double>& mp, double power, int n, int N){
	if(power == 0)
		return constAp(mp,n,N);
	std::vector<long double> a, b;
	for(int i = 0; i < 2*power; ++i)
		a.push_back(0);
	for(int i = 0; i < power+1; ++i)
		b.push_back(0);
	for(double xi = n; xi <= N; ++xi){
		for(int i = 0; i < 2*power;++i)
			a[i] += pow(xi,i+1);
		for(int i = 0; i < power + 1; ++i)
			b[i] += mp[xi]*pow(xi,power - i);
	}
	Matrix M;
	for(int i = 0; i < power + 1; ++i){
		std::vector<long double> row = {};
		for(int j = 0; j < power + 1; ++j){
		//	std::cout << int(a.size() - 1 - i - j) << "  AAAAAAAAA" << std::endl;
			if(int(a.size() - 1 - i - j) < 0)
				row.push_back(N);
			else
				row.push_back(a[a.size() - 1 - i - j]);
		}
		M.m.push_back(row);
	}
	SLAE sl(M, b);
	std::vector<long double> solution = sl.solve();
	auto F = [&solution, &power](long double xi) -> long double{
		long double result = 0;
		for(int i = 0; i < power + 1; ++i){
			result += solution[i] * pow(xi, power - i);
		}
		return result;
	};
	long double result = 0;
	for(double xi = n; xi <= N; xi+=0.25){
		result += (F(xi) - mp[xi])*(F(xi) - mp[xi]);
	}
	return result;
}
long double constAp(std::map<double,long double>& mp,int n, int N){
	long double a = 0;
	for(double xi = n; xi <= N; ++xi){
		a += mp[xi];
	}
	long double c = a / N;
	long double res = 0;
	for(double xi = n; xi <= N; xi+=0.25){
		res += ((mp[xi] - c)*(mp[xi] - c));
	}
	return res;
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

extern std::vector<std::string> split(std::string s, char ch){
	std::vector<std::string> res;
	std::string curr;
	for(int i = 0; i < s.size(); ++i){
		if(s[i] == ch || i == s.size() - 1){
			if(i == s.size() - 1 && s[i] != ch)
				curr += s[i];
			res.push_back(curr);
			curr.clear();
		}
		else
			curr += s[i];
	}
	return res;
}

//Дан массив целых чисел, назовем отрезов k-хорошим, если в нем не более k различных чисел
//Найти длину наиболее длинного k-хорошего отрезка
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



//дан отсортированный массив, найти количество пар чисел, у которых среднее арифметическое тоже в массиве
std::vector<std::pair<int,int>> problem1(std::vector<int>& v){
	std::set<int> set;
	std::vector<std::pair<int,int>> res;
	std::vector<int>::iterator it = v.begin();
	while(it != v.end()){
		if(set.find(*it) == set.end()){
			set.insert(*it);
			it++;
		}
		else
		{
			if(!find(res,{*it,*it}))
				res.push_back({*it,*it});
			v.erase(it);
		}
	}
	std::cout << v << std::endl;
	std::vector<int> sums;

    merge_sort(sums);
  	std::cout << sums << std::endl;
	return res;
}

const std::string testFile = "/home/andrew/MasterFolder/UBERMENSCHENAMOGUS228/tests/testFile";
const std::string answerFile = "/home/andrew/MasterFolder/UBERMENSCHENAMOGUS228/tests/answerFile";
auto compfunca(std::vector<int>& v){
	merge_sort(v);
	std::vector<std::pair<int,int>> res;
	for(int i = 0; i < v.size()-1; ++i){
		for(int j = i+1; j < v.size(); ++j){
			int sum = v[i] + v[j];
			if(sum % 2 == 0){
				sum = sum / 2;
				if(find(v,sum) && !find(res,{v[i],v[j]}))
					res.push_back({v[i],v[j]});
			}
		}
	}
	return res;
}
int main(int argc, char* argv[]){
	// std::vector<std::vector<int>> input;
	// readVectors(input,testFile);
	// auto v = input[0];
	// merge_sort(v);
	// //std::cout << v << std::endl;
	// auto res = compfunca(v);
	// //std::cout << res << std::endl;
	// writeVectors(res, answerFile);
	SLAE s({{-10,5,0,0},{10,0,5,0},{0,0,-5,3},{0,5,0,3}},{0,0,25,25});
	auto solution = s.solve();
	std::cout << solution << std::endl;
	return 0;
}
