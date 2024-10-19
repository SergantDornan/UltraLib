#ifndef UBERMENSCHENAMOGUS228_HEADER_H
#define UBERMENSCHENAMOGUS228_HEADER_H
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
    bool operator ()(std::vector<T>& x){
        for(int i = 0; i < x.size(); ++i){
            for(int j = 0; j < v.size(); ++j){
                if(x[i] >= v[j].first && x[i] <= v[j].second)
                    return true;
            }
        }
        return false;
    }
    bool operator ()(T& x){
        for(int i = 0; i < v.size(); ++i){
            if(x >= v[i].first && x <= v[i].second)
                return true;
        }
        return false;
    }
    int size(){
        return v.size();
    }
    std::pair<T,T> operator ()(){
        return v[rand() % v.size()];
    }
    int max(){

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
std::ostream& operator <<(std::ostream& out, Range<T>& r){
    out << r.v;
    return out;
}


#endif //UBERMENSCHENAMOGUS228_HEADER_H
