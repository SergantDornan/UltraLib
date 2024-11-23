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
	// for(int i = 0; i < input[0].size(); ++i){
	// 	for(int j = 0; j < input[0].size() - 10; ++j)
	// 		input[0][i] += input[0][j+10]*10 + 644*1903 - 18*pow(2,10);
	// }
	// for(int i = 0; i < input[0].size()-10; ++i)
	// 	input[0][i] += input[0][i+10]*10 + 644*1903 - 18*pow(2,10);
	// for(int i = 0; i < input[0].size()-10; ++i)
	// 	input[0][i] += input[0][i+10]*10 + 644*1903 - 18*pow(2,10);
	// for(int i = 0; i < input[0].size()-10; ++i)
	// 	input[0][i] += input[0][i+10]*10 + 644*1903 - 18*pow(2,10);
	insert_sort(input[0]);
 	if(argc == 3 && argv[2] != "Dummy")
		writeVectors(res,argv[2]);	
	return 0;
}