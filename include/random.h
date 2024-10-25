#include <inputs.h>
#include <header.h>
template <class T1, class T2>
void fillVector(std::vector<T1>& v,Range<T2> range,int N){
    for(int i = 0; i < N; ++i){
        std::pair<int,int> p = range();
        v.push_back(p.first + (rand() % (p.second - p.first +1)));
    }          
}
template <class T>
void fillVector(std::vector<char>& v,Range<T> range, int N){
    for(int i = 0; i < N; ++i){
        std::pair<int,int> p = range();
        v.push_back(char(p.first + (rand() % (p.second - p.first +1))));
    }       
}
template <class T>
std::string randomString(Range<T> range, int n, int N){
    int len = n + (rand() % (N-n+1));
    std::string s = "";
    for(int i = 0; i < len; ++i){
        std::pair<int, int> p = range();
        char ch = char(p.first + (rand() % (p.second - p.first + 1)));
        s+=ch;
    }
    return s;
}
template <class T>
void fillVector(std::vector<std::string>& v,Range<T> range, int minStringSize, int maxStringSize,int size){
    for(int i = 0; i < size; ++i){
        v.push_back(randomString(range, minStringSize, maxStringSize));
    }
}