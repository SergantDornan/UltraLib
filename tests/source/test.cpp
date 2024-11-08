#include <test.h>
#include <problems.h> 
template <class T>
void solution(std::string task, std::string answer,void (*cut)(vec&, vec&,int&),int& start)
{
	vec input;
	readVectors(input, task);
	vec res;
	//SOLUTION
	Dtask(input,res);
	//ENDSOLUTION
	writeVectors(res,answer);
}

template <class T>
void solutionCut(vec& input, vec& output,int& start){
	output.clear();
	//CUT
}

template <class T>
void generateFile(vec& output,std::string& path,int minRand,int maxRand,int size_of_generation_unit){
	std::string cmd = "touch " + path;
	system(cmd.c_str());
	//Generation
	output.clear();
	output.push_back(std::vector<int>{20});
	for(int i = 0; i < 20; ++i){
		output.push_back(std::vector<int>{pow(10,12),pow(10,12)});
	}
	//EndGeneration
	writeVectors(output, path);
}

template <class T>
void inputCut(vec& input, vec& output,int& start){
	output.clear();
	//CUT
}


//simpleCut - по строчкам

//yandexCut - блоки, разделенные /n

//generateVectors - генерация 1000 случайных векторов по строчкам

//yandexGen - генерация блокa, в начале блока - количество строк,
//дальше - некоторое количество случайных векторов

//yandexGenLine - генерация блока, в начале блока - количество элементов
//в сгенерированном векторе, следующая строка - вектор с этим количеством элементов

//конструктор TEST: (std::pair<int,int>{minRand, maxRand},int size,int reqTime)
// или TEST(int reqTime)

// !!!! ARGUMENT ORDER : solution, solutionCut, generateFile, inputCut
extern "C" int TSTentry(int argc, char* argv[]){
	TEST<int> test(2);
	test.run(solution,generateFile,"yan");
	test.info();
	std::cout << "================= SUCCES =================" << std::endl;
	return 0;
}