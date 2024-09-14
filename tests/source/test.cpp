#include "test.h"
#include "analysis.h"
extern "C" int mainfunc(int argc, char* argv[]);
extern "C" int entry(int argc, char* argv[]);

extern "C" int TSTentry(int argc, char* argv[]){
	const int N = 100;
	std::cout << '\n';
	for(int i = 0; i < N;++i){
		char** str = new char*[2];
		str[0] = const_cast<char*>("tests");
		str[1] = const_cast<char*>(std::to_string(i).c_str());
		mainfunc(2, str);
		delete[] str;
	}


	char y;
	std::cout << "Run analysis? [y/n]: ";
	std::cin >> y;
	while(y != 'y' && y != 'n'){
		std::cout << '\n';
		std::cout << "Enter [y/n]: ";
		std::cin >> y;
	}
	if(y == 'y'){
		std::cout << '\n';
		std::cout << "Running analysis: " << std::endl;
		entry(0,{}); 
	}
	return 0;
}