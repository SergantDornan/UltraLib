#include <algs.h>
#include <filework.h>
#include <dHeap.h>
typedef unsigned short u16;
typedef short int i16;
typedef int i32;
typedef unsigned int u32;
typedef unsigned long int u64;
typedef long int i64;
typedef char u8;

extern "C" int mainfunc(int argc, char* argv[]){
	std::vector<std::vector<int>> input;
	std::vector<std::vector<int>> res;
	if(argc == 3)
	 	readVectors(input, argv[1]);
	if(argc == 3 && argv[0] != "anal")
		writeVectors(res,argv[2]);	
	return 0;
}

//Cormen 151 надо сделать упражнения