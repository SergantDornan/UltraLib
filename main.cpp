#include <algs.h>
#include <filework.h>
#include <clock.h>
// typedef unsigned short u16;
// typedef short int i16;
typedef int i32;
// typedef unsigned int u32;
typedef unsigned long int u64;
typedef long int i64;
// typedef char u8;
// typedef void u0;


int main(int argc, char* argv[]){
	std::vector<std::vector<int>> input;
	std::vector<std::vector<int>> res;
	if(argc == 3)
	 	readVectors(input, argv[1]);
	std::cout << "ABOBA" << std::endl;
 	if(argc == 3 && argv[2] != "Dummy")
		writeVectors(res,argv[2]);	
	return 0;
}