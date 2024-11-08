#include <random.h>
extern void fillVector(std::vector<char>& v,Range<int> range, int N){
    for(int i = 0; i < N; ++i){
        std::pair<int,int> p = range();
        v.push_back(char(p.first + (rand() % (p.second - p.first +1))));
    }       
}

extern std::string randomString(Range<int> range, int n, int N){
    int len = n + (rand() % (N-n+1));
    std::string s = "";
    for(int i = 0; i < len; ++i){
        std::pair<int, int> p = range();
        char ch = char(p.first + (rand() % (p.second - p.first + 1)));
        s+=ch;
    }
    return s;
}

extern void fillVector(std::vector<std::string>& v,Range<int> range, 
    int size,int minStringSize, int maxStringSize){
    if(minStringSize == -1)
        minStringSize = range.left();
    if(maxStringSize == -1)
        maxStringSize = range.right();
    for(int i = 0; i < size; ++i){
        v.push_back(randomString(range, minStringSize, maxStringSize));
    }
}