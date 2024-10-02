#include <test.h>
extern "C" int TSTentry(int argc, char* argv[]){
	TEST<int> test(2);
	test.vectorTest();
	test.info();
	runAnal();
	std::cout << "================= SUCCES =================" << std::endl;
	return 0;
}