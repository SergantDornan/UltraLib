#include <test.h>
extern void checkMode(std::string& mode){
	if(mode != "simple" && mode != "vector" && mode != "vec" && mode != "yandex" && mode != "yan"){
		std::cout << "==================================== ERROR ====================================" << std::endl;
		std::cout << "test.h : TEST : run" << std::endl;
		std::cout << "You entering unknown testing mode (last argument of run): " << mode << std::endl;
		std::cout << "Test aborted" << std::endl;
		std::cout << "===============================================================================" << std::endl;
	}
}