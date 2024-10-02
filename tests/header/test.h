#ifndef test_H
#define test_H

#include <algs.h>
#include <filework.h>
const bool analysis = false;
extern "C" int mainfunc(int argc, char* argv[]);
const std::string workingFolder = "/home/andrew/MasterFolder/UBERMENSCHENAMOGUS228/tests/";
const std::string testFile = workingFolder + "testFile";






template <class T>
class error{
public:
	std::vector<std::vector<T>> testInput;
	std::vector<std::vector<T>> answerInput;
	std::vector<std::vector<T>> mainInput;
	error(std::string testPath, std::string mainPath, std::string answerPath){
		readVectors(testInput, testPath);
		readVectors(mainInput, mainPath);
		readVectors(answerInput, answerPath);
	}
};

template <class T>
std::ostream& operator <<(std::ostream& out,error<T>& er){
	out << "====================== TESTCASE ======================" << std::endl;
	out << er.testInput << std::endl;
	out << "====================== RIGHT_ANSWER ======================" << std::endl;
	out << er.answerInput << std::endl;
	out << "====================== MAIN_ANSWER ======================" << std::endl;
	out << er.mainInput << std::endl;
	return out;
}

template <class T>
class errorInfo{
public:
	std::vector<error<T>> errors;
	errorInfo(){

	}
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
	TEST(std::pair<int,int> p = {0,10}, int n = 50){
		maxRand = p.second;
		minRand = p.first;
		N = n;
	}
	void run(void (*solution)(std::string,std::string) = [](std::string,std::string){},  
		void (*generateFile)(int,int,int) = [](int,int,int){},
		void (*cut)(std::vector<std::vector<T>>&, std::vector<std::vector<T>>&,int&) 
		= [](std::vector<std::vector<T>>& input, std::vector<std::vector<T>>& output, int& start){
			if(start < input.size()){
				output.clear();
				output.push_back(input[start]);
				start++;
			}
		} )
	{
		errors.clear();
		generateFile(minRand, maxRand, N);
		int start = 0;
		std::vector<std::vector<T>> input;
		std::vector<std::vector<T>> currInput;
		readVectors(input, testFile);
		std::string testf = workingFolder + "tstFile";
		std::string ansf = workingFolder + "ansFile";
		std::string mainf = workingFolder + "mainFile"; 
		std::string cmd1 = "touch " + ansf;
		std::string cmd2 = "touch " + mainf;
		std::string cmd3 = "touch " + testf;
		system(cmd1.c_str());
		system(cmd2.c_str());
		system(cmd3.c_str());
		while(start < input.size()){
			cut(input,currInput,start);
			writeVectors(currInput, testf);
			solution(testf, ansf);
			char** str = new char*[3];
			str[0] = const_cast<char*>("test");
			str[1] = const_cast<char*>(testf.c_str());
			str[2] = const_cast<char*>(mainf.c_str());
			mainfunc(3, str);
			delete[] str;
			std::vector<std::vector<T>> mainInput;
			std::vector<std::vector<T>> answerInput;
			readVectors(mainInput, mainf);
			readVectors(answerInput, ansf);
			if(mainInput != answerInput){
			//	std::cout << "============== WRONG ==============" << std::endl;
				error<T> newerr(testf, mainf,ansf);
				errors.push_back(newerr);
			}
		}
		std::string cmd4 = "rm " + ansf;
		std::string cmd5 = "rm " + mainf;
		std::string cmd6 = "rm " + testf;
		system(cmd4.c_str());
		system(cmd5.c_str());
		system(cmd6.c_str());
	}
	void info(){
		errors.info();
	}

};


#endif