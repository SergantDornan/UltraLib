#include <test.h>
template <class T>
void solution(std::string task, std::string answer,void (*cut)(vec&, vec&,int&),int& start)
{
	vec input;
	readVectors(input, task);
	vec res;
	//SOLUTION
	int n = input[0][0];
	int pr = 0,next = 1;
	for(int i = 0; i < n; ++i){
		next = pr + next;
		pr = next - pr;
	}
	res.push_back({pr});
	//ENDSOLUTION
	writeVectors(res,answer);
}

template <class T>
void solutionCut(vec& input, vec& output,int& start){
	
}

template <class T>
void generateFile(vec& output,std::string& path,int minRand,int maxRand,int size_of_generation_unit){
	std::string cmd = "touch " + path;
	system(cmd.c_str());

	for(int i = 0; i < 50; ++i){
		output.push_back({minRand + (rand() % (maxRand + 1))});
		output.push_back({});
	}

	writeVectors(output, path);
}

template <class T>
void inputCut(vec& input, vec& output,int& start){
	
}

// !!!! ARGUMENT ORDER : solution, solutionCut, generateFile, inputCut
extern "C" int TSTentry(int argc, char* argv[]){
	TEST<int> test({1,5});
	test.run(solution,generateFile, "yandex");
	test.info();
	std::cout << "================= SUCCES =================" << std::endl;
	return 0;
}