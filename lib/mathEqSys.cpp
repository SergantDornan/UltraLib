#include <math.h>
EqSys::EqSys(){}
EqSys::EqSys(const std::vector<std::string> v){
		set(v);
}
void EqSys::set(const std::vector<std::string> v){
		std::vector<std::vector<long double>> tempA;
		std::vector<std::vector<long double>> A;
		std::vector<std::vector<std::string>> tempNames;
		std::vector<long double> B;
		for(int n = 0; n < v.size(); ++n){
			std::string s = v[n];
			auto line = split(s, "+-=", "-");
			Range<std::string> r({{'a','z'},{'A','Z'}});
			std::vector<long double> Drow;
			std::vector<std::string> Srow;
			for(int i = 0; i < line.size(); ++i){
				if(!r(line[i])){
					std::stringstream stream;
					stream << line[i];
					long double k;
					stream >> k;
					B.push_back(k);	
				}
				else{
					auto subline = split(line[i], "*");
					if(subline.size() == 1){
						if(subline[0][0] == '-'){
							Drow.push_back(-1);
							Srow.push_back(std::string(subline[0].begin() + 1, subline[0].end()));
						}
						else{
							Drow.push_back(1);
							Srow.push_back(subline[0]);
						}
					}
					else{
						for(int j = 0; j < subline.size(); ++j){
						if(r(subline[j])){
							Srow.push_back(subline[j]);
						}
						else{
							long double k;
							std::stringstream stream;
							stream << subline[j];
							stream >> k;
							Drow.push_back(k);
						}
					}
					}
				}
				for(int i = 0; i < Srow.size(); ++i){
					if(find(names, Srow[i]) == -1){
						names.push_back(Srow[i]);
					}
				}
			}
			tempA.push_back(Drow);
			tempNames.push_back(Srow); 
		}
		for(int i = 0; i < tempA.size(); ++i){
			std::vector<long double> row;
			for(int j = 0; j < names.size(); ++j)
				row.push_back(0);
			for(int j = 0; j < names.size(); ++j){
				int pos = find(tempNames[i], names[j]);
				if(pos != -1){
					row[j] = tempA[i][pos];
				}
			}
			A.push_back(row);
		}
 		s.set(A,B);
}
std::istream& operator >> (std::istream& in, EqSys& eq){	
		std::cout << "End system with //" << std::endl;
		std::vector<std::string> v;
		while(true){
			std::string s;
			std::getline(in,s,'\n');
			s = strip(s);
			if(s == "$" || s == "$$" || s == "|" || s == "||" || s == "/" || s == "//")
				break;
			v.push_back(s);
		}
		eq.set(v);
		return in;
}
std::ostream& operator << (std::ostream& out, EqSys& eq){
	auto solution = eq.s.solve();
	for(int i = 0; i < eq.names.size(); ++i){
		out << eq.names[i] << "  " << solution[i] << std::endl;
	}
	out << '\n';
	return out;
}