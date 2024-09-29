#include <algs.h>
#include <math.h>
#include <problems.h>
#include <filework.h>
const std::string testFile = "/home/andrew/MasterFolder/UBERMENSCHENAMOGUS228/tests/testFile";
const std::string answerFile = "/home/andrew/MasterFolder/UBERMENSCHENAMOGUS228/tests/answerFile";
auto compfunca(std::vector<int>& v){
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
extern "C" int mainfunc(int argc, char* argv[]){
	std::vector<std::vector<int>> input;
	readVectors(input,testFile);
	auto v = input[0];
	merge_sort(v);
	//std::cout << v << std::endl;
	auto res = compfunca(v);
	//std::cout << res << std::endl;
	writeVectors(res, answerFile);
	return 0;
}