#include <problems.h>
#include <algs.h>
#include <filework.h>
#include <math.h>
extern "C" int mainfunc(int argc, char* argv[]){
	std::vector<std::vector<int>> input;
	std::vector<std::vector<int>> res;
	if(argc == 3)
		readVectors(input, argv[1]);
	std::cout << "A-Z: " << int('A') << " - " << int('Z') << std::endl;
	std::cout << "a-z: " << int('a') << " - " << int('z') << std::endl;
	std::cout << "0-9: " << int('0') << " - " << int('9') << std::endl;
	std::cout << "+ " << int('+') << std::endl;
	std::cout << "- " << int('-')<< std::endl;
	std::cout << "* " << int('*')<< std::endl;
	std::cout << "/ " << int('/')<< std::endl;
	std::cout << "= " << int('=')<< std::endl;
	std::cout << '\n' << std::endl;
	// std::string s;
	// std::getline(std::cin,s,'\n');
	// s = strip(s);
	// std::cout << s << std::endl;
	// auto r = split(s," +-=");
	// std::cout << r << std::endl;
 	//x_1 * 3 + x_2 * 2.543 - 89*y     + y_1*14.456  = 7896.2
	if(argc == 3)
		writeVectors(res,argv[2]);	
	return 0;
}