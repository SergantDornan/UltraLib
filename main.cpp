#include <algs.h>
#include <math.h>
#include <problems.h>
#include <filework.h>
const std::string testFile = "/home/andrew/MasterFolder/UBERMENSCHENAMOGUS228/tests/testFile";
const std::string mainFile = "/home/andrew/MasterFolder/UBERMENSCHENAMOGUS228/tests/mainFile";
extern "C" int mainfunc(int argc, char* argv[]){
	std::vector<std::vector<int>> input;
	readVectors(input, testFile);
	std::vector<int> res;

	int m = -1;
	int pos = 0;
	std::vector<int> v = input[0];
	
	res.push_back(pos);
	
	writeVectors(res,mainFile);
	return 0;
}