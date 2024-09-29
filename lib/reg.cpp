#include <reg.h>
std::vector<std::string> find(std::string str, std::regex reg){
	std::sregex_iterator it(str.begin(), str.end(), reg);
	std::sregex_iterator lst;
	std::vector<std::string> res;
	while(it != lst){
		std::smatch match = *it;
		res.push_back(match.str());
		it++;
	}
	return res;
}