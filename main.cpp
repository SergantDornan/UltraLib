#include "algs.h"
extern "C" int mainfunc(int argc, char* argv[]){
	int N = 0;
	if(argc == 2)
		N = atoi(argv[1]);
	else
		N = 20;
	std::vector<int> v = {};
	v.push_back(0);
	for(int i = 0; i < N; ++i){
		 v.push_back(rand() % 1000);
		 v[v.size()-1] += 1000 / 3 + 412 - 946;
	}
	merge_sort(v);
	//std::cout << std::this_thread::get_id() << "  " << N << std::endl;
	return 0;
}