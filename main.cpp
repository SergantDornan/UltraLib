#include <algs.h>
#include <filework.h>
#include <math.h>
extern "C" int mainfunc(int argc, char* argv[]){
	std::vector<std::vector<int>> input;
	std::vector<std::vector<int>> res;
	if(argc == 3)
	 	readVectors(input, argv[1]);
	
	if(argc == 3 && argv[0] != "anal")
		writeVectors(res,argv[2]);	
	return 0;
}