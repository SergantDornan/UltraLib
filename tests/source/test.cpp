#include "test.h"
extern "C" int TSTentry(int argc, char* argv[]){
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