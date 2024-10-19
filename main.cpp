#include <algs.h>
#include <filework.h>
bool comp(std::pair<int,int>& x, std::pair<int,int>& y){
	return (x.second < y.first);
}
extern "C" int mainfunc(int argc, char* argv[]){
	std::vector<std::vector<int>> input;
	std::vector<std::vector<int>> res;
	if(argc == 3)
		readVectors(input, argv[1]);
	std::vector<std::pair<int,int>> v = {{46, 76},{5,10},{80,90},{1,4},{13, 24}};
	merge_sort(v, comp);
	std::cout << v;
	if(argc == 3 && argv[0] != "anal")
		writeVectors(res,argv[2]);	
	return 0;
}