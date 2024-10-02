#include <test.h>
template <class T>
void standartCut(std::vector<std::vector<T>>& input, std::vector<std::vector<T>>& output, int& start){
	if(start < input.size()){
		int size = input[start][0];
		output.clear();
		for(int i = 0; i < size; ++i)
			output.push_back(input[i]);
		start += (size+1);
	}
}

void generateFile(int minRand, int maxRand, int size){
	std::vector<std::vector<int>> v;
	for(int i = 0; i < 1000; ++i){
		std::vector<int> j;
		fillVector(j,minRand,maxRand,size);
		v.push_back(j);
	}
	writeVectors(v, testFile);
}
void solution(std::string task, std::string answer){
	std::vector<std::vector<int>> input;
	readVectors(input, task);
	//SOLUTION
	std::vector<int> v = input[0];
	std::vector<int> res;
	int m = -1;
	int pos = 0;
	for(int i = 0; i < v.size(); ++i){
		if(v[i] == 0){
			int r1 = 10000000;
			int r2 = 10000000;
			for(int j = i; j >= 0; --j){
				if(v[j] == 1){
					r1 = abs(i - j);
					break;
				}
			}
			for(int j = i; j < v.size(); ++j){
				if(v[j] == 1){
					r2 = abs(i - j);
					break;
				}
			}
			int r = 0;
			if(r1 < r2)
				r = r1;
			else
				r = r2;
			if(r >= m){
				pos = i;
				if(r > m){
					m = r;
					res.clear();
				}
				res.push_back(pos);
			}
		}
	}
	//ENDSOLUTION


	writeVectors(res,answer);
}


extern "C" int TSTentry(int argc, char* argv[]){
	TEST<int> test({0,1}, 10);
	test.run(solution, [](int a,int b, int c){});
	test.info();
	std::cout << "================= SUCCES =================" << std::endl;
	return 0;
}