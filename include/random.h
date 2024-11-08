#ifndef randomH
#define randomH
#include <inputs.h>
#include <header.h>
#include <range.h>

template <class T1, class T2>
void fillVector(std::vector<T1>& v,Range<T2> range,int N){
    for(int i = 0; i < N; ++i){
        std::pair<int,int> p = range();
        v.push_back(p.first + (rand() % (p.second - p.first +1)));
    }          
}

extern void fillVector(std::vector<char>& v,Range<int> range, int N);
extern std::string randomString(Range<int> range, int n, int N);
extern void fillVector(std::vector<std::string>& v,Range<int> range, 
    int size,int minStringSize = -1, int maxStringSize = -1);

#endif