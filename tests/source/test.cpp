#include <test.h>


std::vector<std::pair<int,int>> compfunc(std::vector<int>& v){
	merge_sort(v);
	std::vector<std::pair<int,int>> res;
	for(int i = 0; i < v.size()-1; ++i){
		for(int j = i+1; j < v.size(); ++j){
			int sum = v[i] + v[j];
			if(sum % 2 == 0){
				sum = sum / 2;
				if(find(v,sum) && !find(res,{v[i],v[j]}))
					res.push_back({v[i],v[j]});
			}
		}
	}
	return res;
}

void vectorTest(){

	for(int n = 1; n < 1000; ++n){
		std::vector<int> v;
		for(int i = 0; i < 50; ++i)
			v.push_back(rand() % 10);
		writeVectors(v, testFile);
		char** str = new char*[2];
		str[0] = const_cast<char*>("test");
		str[1] = const_cast<char*>("arg");
		mainfunc(2, str);
		delete[] str;
		std::vector<std::vector<std::pair<int,int>>> input;
		readVectors(input, answerFile);
		if(compfunc(v) != input[0]){
			std::cout << "============== WRONG ==============" << std::endl;
		}
	}
}



extern "C" int TSTentry(int argc, char* argv[]){
	vectorTest();



	if(analysis){
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
	}
	std::cout << "================= SUCCES =================" << std::endl;
	return 0;
}