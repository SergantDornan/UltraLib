#include <problems.h>
#include <algs.h>
#include <filework.h>
#include <math.h>
extern "C" int mainfunc(int argc, char* argv[]){
	std::vector<std::vector<int>> input;
	std::vector<std::vector<int>> res;
	if(argc == 3)
		readVectors(input, argv[1]);
	int n = input[0][0];
	int y = (pow(((1 + sqrt(5)) / 2), n) - pow(((1 - sqrt(5)) / 2), n)) / sqrt(5);
	res.push_back({y});
	if(argc == 3)
		writeVectors(res,argv[2]);
	return 0;
}