#include <algs.h>
#include <filework.h>
#include <problems.h>
#include <math.h>
#include <numSys.h>
// typedef unsigned short u16;
// typedef short int i16;
typedef int i32;
// typedef unsigned int u32;
typedef unsigned long int u64;
typedef long int i64;
// typedef char u8;
// typedef void u0;
extern "C" int mainfunc(int argc, char* argv[]){
	std::vector<std::vector<int>> input;
	std::vector<std::vector<int>> res;
	if(argc == 3)
	 	readVectors(input, argv[1]);
	Num a(-10,2);
	Num b(-4,2);
	a -= b;
	std::cout << a.toInt() << std::endl;
 	if(argc == 3 && argv[0] != "anal")
		writeVectors(res,argv[2]);	
	return 0;
}