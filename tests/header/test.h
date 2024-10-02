#ifndef test_H
#define test_H

#include <algs.h>
#include <analysis.h>
#include <filework.h>
const bool analysis = false;
extern "C" int mainfunc(int argc, char* argv[]);
const std::string testFile = "/home/andrew/MasterFolder/UBERMENSCHENAMOGUS228/tests/testFile";
const std::string answerFile = "/home/andrew/MasterFolder/UBERMENSCHENAMOGUS228/tests/answerFile";
const std::string mainFile = "/home/andrew/MasterFolder/UBERMENSCHENAMOGUS228/tests/mainFile";



void runAnal(){
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
}

template <class T>
class error{
public:
	std::vector<std::vector<T>> testInput;
	std::vector<std::vector<T>> answerInput;
	std::vector<std::vector<T>> mainInput;
	error(std::string testPath = testFile, std::string mainPath = mainFile, std::string answerPath = answerFile){
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
	TEST(int x = 10){
		maxRand = x;

	}
	void compfunc(std::vector<T>& v){ // UNIT TEST
		std::vector<T> res;


		int m = -1;
		int pos = 0;
		for(int i = 0; i < v.size(); ++i){
			if(v[i] == 0){
				for(int j = i; j < v.size(); ++j){
					if(v[j] == 1){
						if(abs(i - j) > m){
						m = abs(i - j);
						pos = i;
						}
						break;
					}
				}
				for(int j = i; j >= 0; --j){
					if(v[j] == 1){
						if(abs(i - j) > m){
						m = abs(i - j);
						pos = i;
						}
						break;
					}
				}
			}
		}
		res.push_back(pos);




		writeVectors(res,answerFile);
	}

	void vectorTest(){
		errors.clear();
	for(int n = 0; n < 1000; ++n){
		std::vector<T> v;
		fillVector(v,maxRand,50);
		writeVectors(v, testFile);
		char** str = new char*[2];
		str[0] = const_cast<char*>("test");
		str[1] = const_cast<char*>("arg");
		mainfunc(2, str);
		delete[] str;
		compfunc(v);
		std::vector<std::vector<T>> mainInput;
		std::vector<std::vector<T>> answerInput;
		readVectors(mainInput, mainFile);
		readVectors(answerInput, answerFile);
		if(mainInput != answerInput){
			std::cout << "============== WRONG ==============" << std::endl;
			error<T> newerr;
			errors.push_back(newerr);
		}
	}
	
	}
	void info(){
		errors.info();
	}

};


#endif