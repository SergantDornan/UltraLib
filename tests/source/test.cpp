#include "test.h"
extern "C" int mainfunc(int argc, char* argv[]);
extern "C" int TSTentry(int argc, char* argv[]){
	char** str = new char*[2];
	str[0] = const_cast<char*>("anal");
	str[1] = const_cast<char*>(std::to_string(1).c_str());
	mainfunc(2, str);
	delete[] str[0];
	delete[] str[1];
	delete[] str;
	return 0;
}