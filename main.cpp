#include <reg.h>
extern "C" int mainfunc(int argc, char* argv[]){
	std::string str = "The ape 1234 12345 1234567 12345678 123456 ape)..xnak apeaboba";
	std::regex reg("(\\w*)");
	auto lines = find(str,reg);
	std::cout << lines << std::endl;
	return 0;
}