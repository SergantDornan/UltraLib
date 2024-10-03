#include <test.h>

template <class T>
void solution(std::string task, std::string answer,void (*cut)(vec&, vec&,int&),int& start)
{
	vec input;
	readVectors(input, task);
	std::vector<T> res;
	//SOLUTION
	
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

	//END YANDEX generation
}

template <class T>
void inputCut(vec& input, vec& output,int& start){

}

// !!!! ARGUMENT ORDER : solution, solutionCut, generateFile, inputCut
extern "C" int TSTentry(int argc, char* argv[]){
	TEST<int> test({0,1}, 100);
	test.run(solution, "vector");
	test.info();
	std::cout << "================= SUCCES =================" << std::endl;
	return 0;
}