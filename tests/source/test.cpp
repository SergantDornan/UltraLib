#include "test.h"
void uberfunc();
void hhh(){
	std::cout << "TEST" << std::endl;
}
extern "C" int entry(){
	uberfunc();
	hhh();
	return 0;
}