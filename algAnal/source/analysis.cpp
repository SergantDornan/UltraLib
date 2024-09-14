#include "analysis.h"
extern "C" int mainfunc(int argc, char* argv[]);
void points(std::map<int,long double>& mp){
	for(int xi = 1; xi <= N; ++xi){
		clock_t start = clock();
		char** str = new char*[2];
		str[0] = const_cast<char*>("anal");
		str[1] = const_cast<char*>(std::to_string(xi).c_str());
		mainfunc(2, str);
		delete[] str;
		clock_t end = clock();
		long double elapsed_time = (long double)(end - start) / CLOCKS_PER_SEC;
		mp.emplace(xi,elapsed_time*100000);
	}}


void foo(){
	std::cout << boost::stacktrace::stacktrace();
}



extern "C" int entry(int argc, char* argv[]){
	std::map<int,long double> mp;
	for(int i = 200; i < 300; ++i){
		char** str = new char*[2];
		str[0] = const_cast<char*>("anal");
		str[1] = const_cast<char*>(std::to_string(i).c_str());
		mainfunc(2, str);
		delete[] str;
	}
	//points(mp);
	return 0;
}