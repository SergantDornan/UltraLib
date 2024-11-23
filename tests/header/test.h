#ifndef test_H
#define test_H

#include <algs.h>
#include <filework.h>
#include <chrono>
#include <range.h>
#include <random.h>
const bool analysis = false;
const std::string workingFolder = "/home/andrew/MasterFolder/UBERMENSCHENAMOGUS228/tests/";
const std::string testFile = workingFolder + "testFile";
const std::string answerFile = workingFolder + "answerFile";
const std::string logs = workingFolder + "logs";
const std::string prog = "outprog";
#define vec std::vector<std::vector<T>>
extern void checkMode(std::string&);

template <class T>
void yandexCut(vec& input, vec& output, int& start){
	output.clear();
	while(input[start].size() != 0 && start < input.size()){
		output.push_back(input[start]);
		start++;
	}
	start++;
}
template <class T>
void simpleCut(vec& input, vec& output, int& start){
	if(start < input.size()){
		output.clear();
		output.push_back(input[start]);
		start++;
	}
}

template <class T>
void yandexGen(vec& v,std::string& path, int minRand, int maxRand, int size){
	std::string cmd = "touch " + path;
	system(cmd.c_str());
	int N = rand() % 10000;
	std::vector<T> n;
	n.push_back(N);
	v.push_back(n);
	for(int i = 0; i < N; ++i){
		std::vector<T> j;
		fillVector(j,Range<int>({minRand,maxRand}),size);
		v.push_back(j);
	}
	writeVectors(v, path);
}

template <class T>
void yandexGenLine(vec& v,std::string& path, int minRand, int maxRand, int size){
	std::string cmd = "touch " + path;
	system(cmd.c_str());
	int N = rand() % 10000;
	std::vector<T> n;
	n.push_back(N);
	v.push_back(n);
	std::vector<T> j;
	fillVector(j,Range<int>({minRand,maxRand}),N);
	v.push_back(j);
	writeVectors(v, path);
}

extern void yandexGen(std::vector<std::vector<std::string>>& v,std::string& path, 
	int minRand, int maxRand, int size);


extern void yandexGenLine(std::vector<std::vector<std::string>>& v,std::string& path, 
	int minRand, int maxRand, int size);


template <class T>
void generateVectors(vec& v,std::string& path, int minRand, int maxRand, int size){
	std::string cmd = "touch " + path;
	system(cmd.c_str());
	for(int i = 0; i < 1000; ++i){
		std::vector<T> j;
		fillVector(j,Range<int>({minRand,maxRand}),size);
		v.push_back(j);
	}
	writeVectors(v, path);
}


template <class T>
void answers(std::string task, std::string answer,void (*cut)(vec&, vec&,int&),int& start){
	vec input;
	readVectors(input, task);
	vec res;
	cut(input, res, start);
	writeVectors(res,answer);
}

template <class T>
class error{
public:
	vec testInput;
	vec answerInput;
	vec mainInput;
	double reqTime,actualTime;
	error(std::string testPath, std::string mainPath, std::string answerPath, double req, double act){
		readVectors(testInput, testPath);
		readVectors(mainInput, mainPath);
		readVectors(answerInput, answerPath);
		reqTime = req;
		actualTime = act;
	}
};

template <class T>
std::ostream& operator <<(std::ostream& out,error<T>& er){
	out << "====================== TESTCASE ======================" << std::endl;
	out << er.testInput << std::endl;
	if(er.mainInput != er.answerInput){
		out << "====================== RIGHT_ANSWER ======================" << std::endl;
		out << er.answerInput << std::endl;
		out << "====================== MAIN_ANSWER ======================" << std::endl;
		out << er.mainInput << std::endl;
	}
	if(er.actualTime > er.reqTime){
		std::cout << "============ !!!!!! TIME LIMIT !!!!! ============" << std::endl;
		std::cout << "required time: " << er.reqTime << std::endl;
		std::cout << "run time: " << er.actualTime << std::endl;
	}
	return out;
}

template <class T>
class errorInfo{
public:
	std::vector<error<T>> errors;
	void push_back(error<T>& err){
		errors.push_back(err);
	}
	void info(){
		if(errors.size() == 0){
			std::cout << "NO ERRORS" << std::endl;
		}
		else
		{
			for(int i = 0; i < errors.size(); ++i){
			std::cout << errors[i] << std::endl;
			std::cout << '\n';
			if(i != errors.size() - 1){
				std::cout << " == NEXT ERROR? [y/n]" << std::endl;
				char ch = 'a';
				std::cin >> ch;
				while(ch != 'y' && ch != 'n'){
					std::cout << "Write y or n" << std::endl;
					std::cin >> ch; 
				}
				if(ch == 'n')
					break;
			}
		}
		std::cout << '\n';
		std::cout << "===================== END OF ERRORS INFO =====================" << std::endl;
		}
	}
	void clear(){
		errors.clear();
	}
};


template <class T>
class TEST{
public:
	errorInfo<T> errors;
	int maxRand;
	int minRand;
	int N;
	int reqTime;
	TEST(std::pair<int,int> p = {0,10}, int n = 50, int time = 2){
		maxRand = p.second;
		minRand = p.first;
		N = n;
		reqTime = time;
	}
	TEST(int time = 2){
		maxRand = 10;
		minRand = 0;
		N = 50;
		reqTime = time;
	}
	void run(void (*generateFile)(vec&,std::string&,int,int,int), std::string mode = "simple")
	{
		checkMode(mode);
		if(mode == "yandex" || mode == "yan")
			actual_run(answers, yandexCut, generateFile,yandexCut);
		else
			actual_run(answers, simpleCut, generateFile, simpleCut);
	}
	void run(std::string mode = "simple"){
		checkMode(mode);
		if(mode == "simple")
			actual_run(answers,simpleCut, [](vec&,std::string&,int,int,int){}, simpleCut);
		else if(mode == "vector" || mode == "vec")
			actual_run(answers,simpleCut, generateVectors, simpleCut);
		else if(mode == "yandex" || mode == "yan")
			actual_run(answers,yandexCut, [](vec&,std::string&,int,int,int){},yandexCut);
	}
	void run(void (*solution)(std::string,std::string,void (*cut)(vec&, vec&,int&),int&),std::string mode = "simple")
	{
		checkMode(mode);
		if(mode == "simple")
			actual_run(solution,[](vec&, vec&,int&){}, [](vec&,std::string&,int,int,int){}, simpleCut);
		else if(mode == "vector" || mode == "vec")
			actual_run(solution,[](vec&, vec&,int&){}, generateVectors, simpleCut);
		else if(mode == "yandex" || mode == "yan")
			actual_run(solution,[](vec&, vec&,int&){}, [](vec&,std::string&,int,int,int){},yandexCut);
	}
	void run(void (*someCut)(vec&, vec&,int&),std::string cutmode = "aboba", std::string mode = "simple")
	{
		checkMode(mode);
		if(cutmode != "inp" && cutmode != "sol" && cutmode != "solution" && cutmode != "input"){
			std::cout << "==================================== ERROR ====================================" << std::endl;
			std::cout << "test.h : TEST : void run(void (*someCut)(vec&, vec&,int&),std::string cutmode, std::string mode)" << std::endl;
			std::cout << "Unknown cutting mode (cutmode): " << cutmode << std::endl;
			std::cout << "Perhaps you missed an argument, enter cutmode, only then mode" << std::endl;
			std::cout << "Test aborted" << std::endl;
			std::cout << "===============================================================================" << std::endl;
		}
		if(cutmode == "inp" || cutmode == "input"){
			if(mode == "vector" || mode == "vec")
				actual_run(answers, simpleCut, generateVectors, someCut);
			else if(mode == "yandex" || mode == "yan")
				actual_run(answers, yandexCut, [](vec&,std::string&,int,int,int){},someCut);
			else
				actual_run(answers, simpleCut, [](vec&,std::string&,int,int,int){},someCut);
		}
		else if(cutmode == "sol" || cutmode == "solution"){
			if(mode == "simple")
				actual_run(answers, someCut, [](vec&,std::string&,int,int,int){}, simpleCut);
			else if(mode == "vector" || mode == "vec")
				actual_run(answers, someCut, generateVectors, simpleCut);
			else if(mode == "yandex" || mode == "yan")
				actual_run(answers, someCut, [](vec&,std::string&,int,int,int){},yandexCut);
		}
	}
	void run(void (*solution)(std::string,std::string,void (*cut)(vec&, vec&,int&),int&), void (*generateFile)(vec&,std::string&,int,int,int),
	 std::string mode = "simple")
	{
		checkMode(mode);
		if(mode == "yandex" || mode == "yan")
			actual_run(solution, yandexCut, generateFile,yandexCut);
		else
			actual_run(solution, simpleCut, generateFile, simpleCut);
	}
	void run(void (*solution)(std::string,std::string,void (*cut)(vec&, vec&,int&),int&),void (*cut)(vec&, vec&,int&),
		std::string mode = "simple")
	{
		checkMode(mode);
		if(mode == "vector" || mode == "vec")
			actual_run(solution,[](vec&, vec&,int&){}, generateVectors, cut);
		else
			actual_run(solution,[](vec&, vec&,int&){}, [](vec&,std::string&,int,int,int){},cut);
	}
	void run(void (*solutionCut)(vec&, vec&,int&), void (*generateFile)(vec&,std::string&,int,int,int), std::string mode = "simple")
	{
		checkMode(mode);
		if(mode == "yandex" || mode == "yan")
			actual_run(answers, solutionCut, generateFile,yandexCut);
		else
			actual_run(answers, solutionCut, generateFile, simpleCut);
	}
	void run(void (*solutionCut)(vec&, vec&,int&),void (*cut)(vec&, vec&,int&), std::string mode = "simple")
	{
		checkMode(mode);
		if(mode == "vector" || mode == "vec")
			actual_run(answers, solutionCut, generateVectors, cut);
		else
			actual_run(answers, solutionCut, [](vec&,std::string&,int,int,int){},cut);
	}
	void run(void (*generateFile)(vec&,std::string&,int,int,int),void (*cut)(vec&, vec&,int&), std::string mode = "simple")
	{
		checkMode(mode);
		if(mode == "yandex" || mode == "yan")
			actual_run(answers,yandexCut, generateFile, cut);
		else
			actual_run(answers,simpleCut, generateFile, cut);
	}

	void run(void (*solution)(std::string,std::string,void (*cut)(vec&, vec&,int&),int&),
		void (*generateFile)(vec&,std::string&,int,int,int),
		void (*cut)(vec&, vec&,int&),
		std::string mode = "simple")
	{
		checkMode(mode);
		actual_run(solution, [](vec&, vec&, int&){},generateFile,cut);
	}
	void run(void (*solutionCut)(vec&, vec&,int&),
		void (*generateFile)(vec&,std::string&,int,int,int),
		void (*cut)(vec&, vec&,int&),
		std::string mode = "simple")
	{
		checkMode(mode);
		actual_run(answers, solutionCut,generateFile,cut);
	}
	void segf(){
		vec input;
		readVectors(input, logs);
		std::string testf = workingFolder + "tstFile";
		std::string ansf = workingFolder + "ansFile";
		std::string mainf = workingFolder + "mainFile"; 
		std::string generationFile = workingFolder + "genTest";
		std::string cmd4 = "rm " + ansf + ' ' + mainf + ' ' + testf + ' ' + generationFile;
		if(input.size() != 0)
			system(cmd4.c_str());
		if(input.size() != 0){
			std::cout << '\n';
			std::cout << '\n';
			std::cout << "====================== SEGFAULT TESTCASE ======================" << std::endl;
			for(int i = 0; i < input.size(); ++i)
				std::cout << input[i] << std::endl;
			clear(logs);
			char ch = 'a';
			std::cout << "===== Run the tests? [y/n]: ";
			std::cin >> ch;
			while(ch != 'n' && ch != 'y'){
				std::cout << "Enter 'y' or 'n': ";
				std::cin >> ch;
			}
			if(ch == 'n'){
				exit(0);
			}
		}
	}
	void actual_run(void (*solution)(std::string,std::string,void(*cut)(vec&, vec&,int&),int&),
		void (*solutionCut)(vec&, vec&,int&),
		void (*generateFile)(vec&,std::string&,int,int,int),
		void (*cut)(vec&, vec&,int&))
	{
		segf();
		errors.clear();
		vec generationVector;
		std::string generationFile = workingFolder + "genTest";
		generateFile(generationVector,generationFile,minRand, maxRand, N);
		int start = 0;
		int solutionStart = 0;
		vec input;
		vec currInput;
		std::string workingFile;
		std::ifstream check(generationFile);
		if(check.is_open())
			workingFile = generationFile;
		else
			workingFile = testFile;
		check.close();
		readVectors(input, workingFile);
		std::string testf = workingFolder + "tstFile";
		std::string ansf = workingFolder + "ansFile";
		std::string mainf = workingFolder + "mainFile"; 
		std::string cmd1 = "touch " + ansf + ' ' + mainf + ' ' + testf;
		system(cmd1.c_str());
		while(start < input.size()){
			cut(input,currInput,start);
			writeVectors(currInput, testf);
			if(answers<T> == solution)
				solution(answerFile, ansf, solutionCut, solutionStart);
			else
				solution(testf, ansf, solutionCut, solutionStart);
			std::string runcmd = "./" + prog + " " + testf + " " + mainf;
			writeVectors(currInput, logs);
			auto old = std::chrono::steady_clock::now();
			int code = system(runcmd.c_str());
			auto dur = std::chrono::steady_clock::now() - old;
			if(code != 0){
				std::cout << "==================== ERROR ====================" << std::endl;
				std::cout << "main returned code is " << code << std::endl;
			}
			long double elapsed_time = double(duration_cast<std::chrono::microseconds>(dur).count())/1000000;
			clear(logs);
			vec mainInput;
			vec answerInput;
			readVectors(mainInput, mainf);
			readVectors(answerInput, ansf);
			if(mainInput != answerInput || elapsed_time > reqTime){
			//	std::cout << "============== WRONG ==============" << std::endl;
				error<T> newerr(testf, mainf,ansf,reqTime,elapsed_time);
				errors.push_back(newerr);
			}
		}
		std::string cmd4 = "rm " + ansf + ' ' + mainf + ' ' + testf;
		if(workingFile == generationFile)
			cmd4 += (' ' + generationFile);
		system(cmd4.c_str());
	}
	void info(){
		errors.info();
	}

};


#endif