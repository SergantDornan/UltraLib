#include <test.h>

template <class T>
void solution(std::string task, std::string answer,void (*cut)(vec&, vec&,int&),int& start)
{
	std::vector<std::vector<T>> input;
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

template <class T>
void solutionCut(vec& input, vec& output,int& start){

}

template <class T>
void generateFile(vec& output,int minRand,int maxRand,int size_of_generation_unit){
	//YANDEX generation

	int maxLines = 100;
	for(int i = 0; i < 1000; ++i){
		int N = 1+(rand() % maxLines);
		std::vector<T> num;
		num.push_back(N);
		output.push_back(num);
		for(int j = 0; j < N; ++j){
			std::vector<T> line;
			fillVector(line,minRand,maxRand,size_of_generation_unit);
			output.push_back(line);
		}
	}
	writeVectors(output, testFile);

	//END YANDEX generatio
}

template <class T>
void inputCut(vec& input, vec& output,int& start){

}

// !!!! ARGUMENT ORDER : solution, solutionCut, generateFile, inputCut
extern "C" int TSTentry(int argc, char* argv[]){
	TEST<int> test({0,1}, 100);
	test.run(solution, "vec");
	test.info();
	std::cout << "================= SUCCES =================" << std::endl;
	return 0;
}