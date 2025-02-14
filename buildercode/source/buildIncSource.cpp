#include <build.h>
std::string getFolder(const std::string& s){
	for(int i = s.size() - 1; i >= 0; --i){
		if(s[i] == '/')
			return std::string(s.begin(), s.begin() + i);
	}
	return "";
}
void getAllheaders(std::vector<std::string>& headers,const std::string path){
	auto dirs = getDirs(path);
	for(int i = 1; i < dirs.size(); ++i){
		if(dirs[i][dirs[i].size()-2] == '.' && dirs[i][dirs[i].size()-1] == 'h' && find(headers, dirs[i]) == -1)
			headers.push_back(dirs[i]);
		if(std::filesystem::is_directory(dirs[i]))
			getAllheaders(headers, dirs[i]);
	}
}
void getAllsource(std::vector<std::string>& source, const std::string path){
	auto dirs = getDirs(path);
	for(int i = 1; i < dirs.size(); ++i){
		int index = -1;
		for(int j = dirs[i].size()-1; j>=0; --j){
			if(dirs[i][j] == '.' && j != 0){
				index = j;
				break;
			}
		}
		if(index != -1){
			std::string ext(dirs[i].begin() + index + 1,dirs[i].end());
			if(find(source, dirs[i]) == -1 && (ext == "cpp" || ext == "c"))
				source.push_back(dirs[i]);
		}
		if(std::filesystem::is_directory(dirs[i]))
			getAllsource(source, dirs[i]);
	}
}
std::string defineEntryPoint(const std::string& mainFile){
	std::ifstream main(mainFile);
	std::string line;
	while(std::getline(main,line)){
		if(line.find("int argc") != std::string::npos){
			int index1 = find(line,"int") + 3;
			int index2 = find(line, '(');
			std::string entryPoint(line.begin() + index1, line.begin() + index2);
			entryPoint = strip(entryPoint);
			return entryPoint;
		}
	}
	return "";
}
void includeFiles(std::vector<std::string>& includes,
	const std::vector<std::string>& allHeaders,
	const std::vector<std::string>& allSource,
	const std::string& line)
{
    std::string l;
    std::ifstream input(line);
    if (input.is_open()){
  		while (std::getline(input, l)){
        	if(l.find("#include") != std::string::npos){
        		std::string s;
        		
        		for(int j = 10; j < l.size() && l[j] != '>' && l[j] != '"'; ++j)
        			s+=l[j];
        		std::string newline;
        		bool b = false;
        		for(int j = 0; j < allHeaders.size(); ++j){
        			if(find(allHeaders[j], s) != -1){
        				b = true;
        				newline = allHeaders[j];
        				break;
        			}
        		}
        		for(int j = 0; j < allSource.size(); ++j){
        			if(find(allSource[j], s) != -1){
        				b = true;
        				newline = allSource[j];
        				break;
        			}
        		}
        		if(b && find(includes, newline) == -1){
        			includes.push_back(newline);
        			includeFiles(includes,allHeaders,allSource,newline);
        		}
    		}
        }
    }
    input.close();
}
// void sourceFiles(std::vector<std::string>& source,const std::vector<std::string>& allSource,const std::vector<std::string>& headers){
// 	std::string l;
//     for(int i = 0; i < allSource.size(); ++i){
//     	std::ifstream input(allSource[i]);
//     	if (input.is_open()){
//   			while (std::getline(input, l)){
//         		if(l.find("#include") != std::string::npos){
//         			std::string s;
//         			for(int j = 10; j < l.size() && l[j+2] != '>' && l[j+2] != '"'; ++j)
//         				s+=l[j];
//         			if(find(allSource[i], s) != -1){
//         				for(int k = 0; k < headers.size(); ++k){
//         					if(find(headers[k], s) != -1){
//         						if(find(source,allSource[i]) == -1)
//         							source.push_back(allSource[i]);
//         						break;
//         					}
//         				}
//         			}
//     			}
//         	}
//     	}
//     	input.close();
//     }
// }
void stripExt(std::vector<std::string>& allSource, const std::string& extension){
	auto it = allSource.begin();
	while (it != allSource.end()){
		int index = -1;
		for(int j = (*it).size()-1; j >= 0; --j){
			if((*it)[j] == '.'){
				index = j;
				break;
			}
		}
		std::string ext((*it).begin() + index +1,(*it).end());
		if(ext != extension){
			allSource.erase(it);
		}
		else
			it++;
	}
}
void push_line(std::vector<std::string>& v,const std::string& line){
	if(line.find("#include") == std::string::npos && 
		line.find("#ifdef") == std::string::npos &&
      	line.find("#ifndef") == std::string::npos &&
      	line.find("#define") == std::string::npos &&
      	line.find("endif") == std::string::npos)
	{
      	if(line.find("extern") != std::string::npos){
      		std::regex reg("extern");
            std::string newstr = std::regex_replace(line,reg,"");
            v.push_back(newstr);
        }
        else
        	v.push_back(line);
    }
}
void writeIncludes(std::vector<std::string>& lines,const std::vector<std::string>& IncNames){
	for(int i = 0; i < IncNames.size(); ++i)
		lines.push_back(std::string("#include <" + IncNames[i] + ">"));
}
void writeHeaderFiles(std::vector<std::string>& lines,const std::vector<std::string>& headers){
	for(int i = 0; i < headers.size(); ++i){
		std::string l;
   		std::ifstream input(headers[i]);
    	if (input.is_open()){
         	while (std::getline(input, l))
       			push_line(lines,l);
    	}
    	input.close();
	}
}
void writeSourceFiles(std::vector<std::string>& lines, const std::vector<std::string>& source){
	std::string line;
	for(int i = 1; i < source.size(); ++i){
		std::ifstream input(source[i]);
		while(std::getline(input,line))
			push_line(lines,line);
		input.close();
	}
}
void writeMainFile(std::vector<std::string>& lines, const std::vector<std::string>& linesmain,
 	const std::string& entryPoint){
	for(int i = 0; i < linesmain.size(); ++i){
		if(linesmain[i].find(entryPoint) !=  std::string::npos &&
			linesmain[i].find("int argc") != std::string::npos){
        	if(linesmain[i].find("{") != std::string::npos)
          		lines.push_back("int main(int argc, char* argv[]){");
        	else
          		lines.push_back("int main(int argc, char* argv[])");
      	}
      	else if(linesmain[i].find("argv[1]") != std::string::npos){
        	std::regex reg("argv[^ ]{3}");
        	std::string newstr = std::regex_replace(linesmain[i],reg,"\"input.txt\"");
        	lines.push_back(newstr);
      	}
      	else if(linesmain[i].find("argv[2]") != std::string::npos){
        	std::regex reg("argv[^ ]{3}");
        	std::string newstr = std::regex_replace(linesmain[i],reg,"\"output.txt\"");
        	lines.push_back(newstr);
      	}
      	else if(linesmain[i].find("argc") == std::string::npos)
        	push_line(lines,linesmain[i]);
	}
}
void MrProperSourceFiles(std::vector<std::string>& source, const std::vector<std::string>& headers){
	auto it = source.begin();
	while(it != source.end()){
		if(find(headers, *it) != -1)
			source.erase(it);
		else
			it++;
	}
}
void sourceFiles(std::vector<std::string>& source, 
	const std::vector<std::string>& allSource,
	const std::vector<std::string>& headers){

	std::vector<function> funcsDeclarations;
	findFunctionsDeclarations(funcsDeclarations,headers);
	std::cout << funcsDeclarations << std::endl;
	for(int index = 0; index < allSource.size(); ++index){
		std::cout << "=============================" << std::endl;
		std::cout << allSource[index] << std::endl;
		std::cout << std::endl;
		std::ifstream in(allSource[index]);
		std::vector<function> funcs;
		std::string line, buffer = "";
		int coolBracesCount = 0, roundBracesCount = 0;
		std::string currClass = "";
		while(std::getline(in,line)){
			bool allSpaces = true;
			bool comment = false;
			for(int j = 0; j < line.size(); ++j){
				if(allSpaces && j < (line.size() - 1) && line[j] == '/' && line[j+1] == '/'){
					comment = true;
					break;
				}
				if(find(spaces, line[j]) == -1)
					allSpaces = false;
			}
			if(allSpaces || comment)
				continue;
			auto it = line.begin();
			while(it != line.end()){
				if(find(spaces,*it) != -1)
					line.erase(it);
				else
					break;
			}
			if(find(line,"#include") == 0)
				continue;
			for(int i = 0; i < line.size(); ++i){
				if(line[i] == '\r')
					continue;
				if(line[i] == '(')
					roundBracesCount++;
				if(line[i] == ')')
					roundBracesCount--;
				if(line[i] == ';' && roundBracesCount == 0 && coolBracesCount == 0){
					buffer.clear();
					i++;
				}
				if(line[i] == '}'){
					coolBracesCount--;
					if(roundBracesCount == 0 && coolBracesCount == 0)
						buffer.clear();
				}
				else if(line[i] == '{'){
					if(coolBracesCount == 0 && roundBracesCount == 0){
						functionParsing(funcs, buffer);
						i++;
						buffer.clear();
					}
					coolBracesCount++;
				}
				else
					buffer += line[i];
			}
			buffer += ' ';	
		}
		in.close();
		std::cout << funcs << std::endl;
		for(int i = 0; i < funcs.size(); ++i){
			if(find(funcsDeclarations, funcs[i]) != -1){
				source.push_back(allSource[index]);
				break;
			}
		}
	}
}
void findFunctionsDeclarations(std::vector<function>& funcs,const std::vector<std::string>& headers){

	for(int index = 0; index < headers.size(); ++index){
		std::ifstream in(headers[index]);
		std::string line, buffer = "";
		int coolBracesCount = 0, roundBracesCount = 0;
		std::string currClass = "";
		while(std::getline(in,line)){
			bool allSpaces = true;
			bool comment = false;
			for(int j = 0; j < line.size(); ++j){
				if(allSpaces && j < (line.size() - 1) && line[j] == '/' && line[j+1] == '/'){
					comment = true;
					break;
				}
				if(find(spaces, line[j]) == -1)
					allSpaces = false;
			}
			if(allSpaces || comment)
				continue;
			auto it = line.begin();
			while(it != line.end()){
				if(find(spaces,*it) != -1)
					line.erase(it);
				else
					break;
			}
			if(find(line,"#include") == 0)
				continue;
			for(int i = 0; i < line.size(); ++i){
				if(line[i] == '\r')
					continue;
				if(line[i] == '(')
					roundBracesCount++;
				if(line[i] == '{')
					coolBracesCount++;
				if(line[i] == ')')
					roundBracesCount--;
				if(line[i] == '}'){
					coolBracesCount--;
					if(roundBracesCount == 0 && coolBracesCount == 0)
						buffer.clear();
				}
				else if(roundBracesCount == 0 && line[i] == ';'){
					if(line[i] == ';' && find(buffer,"//") == -1 &&
						find(buffer,"template") == -1){
						if(coolBracesCount == 0)
							functionParsing(funcs,buffer);
						else if(coolBracesCount == 1){
							if(find(buffer, "class") != -1){
								int ind = find(buffer,"class");
								ind += 5;
								for(int k = ind; k < buffer.size(); ++k){
									if(find(spaces,buffer[k]) == -1){
										ind = k;
										break;
									}
								}
								std::string name = "";
								for(int k = ind; k < buffer.size(); ++k){
									if(buffer[k] == '{')
										break;
									else
										name += buffer[k];
								}
								currClass = name;
							}
							methodParsing(funcs,buffer,currClass);
						}
						++i;
						buffer.clear();
					}
				}
				else
					buffer += line[i];
			}
			buffer += ' ';	
		}
		in.close();
	}	
}
void methodParsing(std::vector<function>& funcs, const std::string& buffer,
	const std::string& currClass){
	
	std::string s;
	if(find(buffer, currClass) != -1 && find(buffer, "class") != -1){
		int ind = find(buffer, '{') + 1;
		s = std::string(buffer.begin() + ind, buffer.end());
		auto it = s.begin();
		while(it != s.end()){
			if(find(spaces, *it) == -1)
				break;
			else
				s.erase(it);
		}
		if(find(s,"public") == 0 || find(s,"private") == 0 || 
			find(s, "protected") == 0)
			s = std::string(s.begin() + find(s, ':') + 1, s.end());
	}
	else
		s = buffer;
	functionParsing(funcs,s,currClass);
}
void functionParsing(std::vector<function>& funcs,const std::string& buffer,
	const std::string& className){
	std::string tail = "";
	std::string type = findType(buffer, tail);
	if(type == "class" || tail.find('(') == std::string::npos)
		return;
	auto it = tail.begin();
	while(it != tail.end()){
		if((*it) == '(')
			break;
		if(find(spaces, *it) != -1)
			tail.erase(it);
		else
			++it;
	}
	it = tail.end()-1;
	while(it != tail.begin()){
		if((*it) == ')')
			break;
		if(find(spaces, *it) != -1)
			tail.erase(it);
		else
			--it;
	}
	int index = find(tail,'(');
	std::string name(tail.begin(), tail.begin() + index);
	if(className != "")
		name = (className + "::" + name);
	tail = std::string(tail.begin() + index + 1, tail.end());
	auto v = split(tail, ",");	
	for(int i = 0; i < v.size(); ++i){
		auto iter = v[i].begin();
		while(iter != v[i].end()){
			if(find(spaces, *iter) != -1)
				v[i].erase(iter);
			else
				break;
		}
		iter = v[i].end()-1;
		while(iter != v[i].begin()){
			if(find(spaces, *iter) != -1)
				v[i].erase(iter);
			else
				break;
		}
	}
	std::vector<std::string> args;
	for(int i = 0; i < v.size(); ++i)
		args.push_back(findType(v[i], tail));
	funcs.push_back({type,name,args});
}
std::string findType(const std::string& buffer, std::string& tail){
	std::string type = "";
	std::string tmp = "";
	int ind = 0;
	for(int i = 0; i < buffer.size();++i){
		if(find(spaces,buffer[i]) == -1){
			ind = i;
			break;
		}
	}
	for(int i = ind; i < buffer.size();++i){
		if(find(spaces,buffer[i]) != -1)
			break;
		else if(buffer[i] == '('){
			tail = buffer;
			return type;
		}
	}
	ind = find(buffer,'(');
	if(ind < 0)
		return "";
	for(int i = ind - 1; i >= 0; --i){
		if(find(spaces,buffer[i]) == -1){
			ind = i;
			break;
		}
	}
	int stop = ind;
	for(int i = ind; i >= 0; --i){
		if(find(spaces,buffer[i]) != -1)
			break;
		else
			stop = i;
	}
	type = std::string(buffer.begin(), buffer.begin() + stop);
	tail = std::string(buffer.begin() + stop, buffer.end());
	if(find(type, "extern") != -1)
		type = std::string(type.begin() + find(type,"extern") + 6, type.end());
	return type;
}
bool operator==(function f1,function f2){
	return (f1.type == f2.type) && (f1.name == f2.name) && (f1.args == f2.args);
}
std::ostream& operator << (std::ostream& out, function f){
	out << f.type << ", " << f.name << ", " << f.args << std::endl;
	return out;
}