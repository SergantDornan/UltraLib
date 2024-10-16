#include <problems.h>
#include <algs.h>
#include <filework.h>
#include <math.h>
extern "C" int mainfunc(int argc, char* argv[]){
	std::vector<std::vector<int>> input;
	std::vector<std::vector<int>> res;
	if(argc == 3)
		readVectors(input, argv[1]);
	EqSys eq;
	std::cin >> eq;
	std::cout << eq << std::endl;
	if(argc == 3)
		writeVectors(res,argv[2]);	
	return 0;
}