#ifndef rangeh
#define rangeh
#include <header.h>
template <class T>
class Range{
public:
    int func();
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
                if(x[i] < v[j].first || x[i] > v[j].second)
                    return false;
            }
        }
        return true;
    }
    Range(){
        
    }
    bool operator ()(const T x){
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
    Range<T>& operator = (const Range<T>& r){
        v = r.v;
        return *this;
    }
    int size(){
        return v.size();
    }
    std::pair<T,T> operator ()(){
        return v[rand() % v.size()];
    }
    T max(){
        return v[v.size() - 1].second;
    }
    T min(){
        return v[0].first;
    }
};

template <>
class Range<std::string>{
public:
    std::vector<std::pair<int,int>> v;
    Range(Range<std::string>& r){
        v = r.v;
    }
    Range(const std::string s){
        int min = 1000, max = -1;
        for(int i = 0; i < s.size(); ++i){
            if(int(s[i]) < min)
                min = int(s[i]);
            if(int(s[i]) > max)
                max = int(s[i]);
        }
        v.push_back({min,max});
        sortinput();
    }
    Range(const std::pair<int,int> p){
        v.push_back(p);
    }
    Range(const std::vector<std::pair<int,int>> p){
        v = p;
        sortinput();
    }
    Range(const std::string s,const int x){
        if(s != "-inf"){
            std::cout << "======================================== ERROR ========================================" << std::endl;
            std::cout << "===================== header.h: Range(const std::string, const int) =====================" << std::endl;
            std::cout << "===================== first parameter is: " << s << " =====================" << std::endl;
            std::cout << "=========================== but first parameter must be -inf ===========================" << std::endl; 
        }
        else{
            v.push_back({int(-pow(10,9)), x});
        }
    }
    Range(const std::string s,const int x,const std::pair<int,int> p){
        if(s != "-inf"){
            std::cout << "======================================== ERROR ========================================" << std::endl;
            std::cout << "============ header.h: Range(const std::string, const int, std::pair<int,int>) ==============" << std::endl;
            std::cout << "===================== first parameter is: " << s << " =====================" << std::endl;
            std::cout << "=========================== but first parameter must be -inf ===========================" << std::endl; 
        }
        else{
            v.push_back({int(-pow(10,9)), x});
            v.push_back(p);
            sortinput();
        }
    }
    Range(const std::string s,const int x, const std::vector<std::pair<int,int>> p){
        if(s != "-inf"){
            std::cout << "======================================== ERROR ========================================" << std::endl;
            std::cout << "====== header.h: Range(const std::string, const int, std::vector<std::pair<int,int>>) =======" << std::endl;
            std::cout << "===================== first parameter is: " << s << " =====================" << std::endl;
            std::cout << "=========================== but first parameter must be -inf ===========================" << std::endl; 
        }
        else{
            v = p;
            v.push_back({int(-pow(10,9)), x});
            sortinput();
        }
    }
    Range(const int x, const std::string s){
        if(s != "inf" && s != "+inf"){
            std::cout << "======================================== ERROR ========================================" << std::endl;
            std::cout << "===================== header.h: Range(const int, const std::string) =====================" << std::endl;
            std::cout << "===================== second parameter is: " << s << " =====================" << std::endl;
            std::cout << "====================== but second parameter must be +inf or inf ======================" << std::endl; 
        }
        else{
            v.push_back({x, int(pow(10,9))});
        }
    }
    Range(const std::pair<int,int> p, const int x, const std::string s){
        if(s != "inf" && s != "+inf"){
            std::cout << "======================================== ERROR ========================================" << std::endl;
            std::cout << "============ header.h: Range(std::pair<int,int>, const int, const std::string) ==============" << std::endl;
            std::cout << "======================= last parameter is: " << s << " =======================" << std::endl;
            std::cout << "======================== but last parameter must be +inf or inf ========================" << std::endl; 
        }
        else{
            v.push_back(p);
            v.push_back({x, int(pow(10,9))});
            sortinput();
        }
    }
    Range(const std::vector<std::pair<int,int>> p, const int x, const std::string s){
        if(s != "inf" && s != "+inf"){
            std::cout << "======================================== ERROR ========================================" << std::endl;
            std::cout << "====== header.h: Range(std::vector<std::pair<int,int>>, const int, const std::string) =======" << std::endl;
            std::cout << "======================= last parameter is: " << s << " =======================" << std::endl;
            std::cout << "======================== but last parameter must be +inf or inf ========================" << std::endl; 
        }
        else{
            v = p;
            v.push_back({x, int(pow(10,9))});
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
            v.push_back({int(-pow(10,9)), int(pow(10,9))});
        }
    }
    Range(const std::string s1,const int x,const std::pair<int,int> p, const  int y, const std::string s2){
        if((s2 != "inf" && s2 != "+inf") || s1 != "-inf"){
            std::cout << "======================================== ERROR ========================================" << std::endl;
            std::cout << "===================== header.h: Range(string,int,pair,int,string) =====================" << std::endl;
            std::cout << "===================== string parameters are: " << s1 << ' ' << s2 << " =====================" << std::endl;
            std::cout << "====================== but they must be -inf and +inf ======================" << std::endl; 
        }
        else{
            v.push_back({int(-pow(10,9)), x});
            v.push_back(p);
            v.push_back({y, int(pow(10,9))});
            sortinput();
        }
    }
    Range(const std::string s1,const int x,const std::vector<std::pair<int,int>> p, const  int y, const std::string s2){
        if((s2 != "inf" && s2 != "+inf") || s1 != "-inf"){
            std::cout << "======================================== ERROR ========================================" << std::endl;
            std::cout << "===================== header.h: Range(string,int,vector<pair>,int,string) =====================" << std::endl;
            std::cout << "===================== string parameters are: " << s1 << ' ' << s2 << " =====================" << std::endl;
            std::cout << "====================== but they must be -inf and +inf ======================" << std::endl; 
        }
        else{
            v = p;
            v.push_back({int(-pow(10,9)), x});
            v.push_back({y, int(pow(10,9))});
            sortinput();
        }
    }
    Range(const std::string s1,const int x, const  int y, const std::string s2){
        if((s2 != "inf" && s2 != "+inf") || s1 != "-inf"){
            std::cout << "======================================== ERROR ========================================" << std::endl;
            std::cout << "===================== header.h: Range(string,int,int,string) =====================" << std::endl;
            std::cout << "===================== string parameters are: " << s1 << ' ' << s2 << " =====================" << std::endl;
            std::cout << "====================== but they must be -inf and +inf ======================" << std::endl; 
        }
        else{
            v.push_back({int(-pow(10,9)), x});
            v.push_back({y, int(pow(10,9))});
            sortinput();
        }
    }
    bool operator ()(std::string& x){
        for(int i = 0; i < x.size(); ++i){
            for(int j = 0; j < v.size(); ++j){
                if(int(x[i]) < v[j].first || int(x[i]) > v[j].second)
                    return false;
            }
        }
        return true;
    }
    Range(){
        
    }
    bool operator ()(char& x){
        for(int i = 0; i < v.size(); ++i){
            if(int(x) >= v[i].first && int(x) <= v[i].second)
                return true;
        }
        return false;
    }
    void sortinput(){
        std::sort(v.begin(), v.end(), [](std::pair<int,int>& x, std::pair<int,int>& y){
            if(x.first > x.second){
                int c = x.first;
                x.first = x.second;
                x.second = c;
            }
            if(y.first > y.second){
                int c = y.first;
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
                std::pair<int,int> p = {(*it).first, (*(it+1)).second};
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
    Range<std::string>& operator = (Range<std::string>& r){
        v = r.v;
        return *this;
    }
    int size(){
        return v.size();
    }
    std::pair<int,int> operator ()(){
        return v[rand() % v.size()];
    }
    int max(){
        return v[v.size() - 1].second;
    }
    int min(){
        return v[0].first;
    }
};

template <class T>
std::ostream& operator <<(std::ostream& out, Range<int>& r){
    out << r.v;
    return out;
}
#endif