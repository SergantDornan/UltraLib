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
extern void yandexGen(std::vector<std::vector<std::string>>& v,std::string& path, 
	int minRand, int maxRand, int size){
	std::string cmd = "touch " + path;
	system(cmd.c_str());
	int N = rand() % 10000;
	std::vector<std::string> n;
	n.push_back(std::to_string(N));
	v.push_back(n);
	for(int i = 0; i < N; ++i){
		std::vector<std::string> j;
		fillVector(j,Range<int>({minRand,maxRand}),size);
		v.push_back(j);
	}
	writeVectors(v, path);
}


extern void yandexGenLine(std::vector<std::vector<std::string>>& v,std::string& path, 
	int minRand, int maxRand, int size){
	std::string cmd = "touch " + path;
	system(cmd.c_str());
	int N = rand() % 10000;
	std::vector<std::string> n;
	n.push_back(std::to_string(N));
	v.push_back(n);
	std::vector<std::string> j;
	fillVector(j,Range<int>({minRand,maxRand}),N);
	v.push_back(j);
	writeVectors(v, path);
}