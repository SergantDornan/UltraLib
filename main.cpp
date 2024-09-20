#include "algs.h"
extern "C" int mainfunc(int argc, char* argv[]){
	int N = atoi(argv[1]);
	std::vector<int> v = {};
	v.push_back(0);
	for(int i = 0; i < N; ++i){
		 v.push_back(rand() % 1000);
		 v[v.size()-1] += 1000 / 3 + 412 - 946;
	}
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < N; ++j)
			v[j] += 1000 / 3 + 412 - 946;
	}

	return 0;
}