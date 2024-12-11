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
void createMakeFile (const std::string& mode, const std::string& extension, const std::string& outline,
	const std::vector<std::string>& headers, const std::vector<std::string>& source, const std::string& entryPoint){
	
	auto dirs = getDirs("./");
	bool newline = false;
	if (find (dirs,"./Makeline") == -1)
	{
		newline = true;
		system ("touch Makeline");
	}
	std::vector<std::string> lines;
	std::string l;
	if(!newline){
		std::ifstream in("./Makeline");
		while (std::getline(in, l))
			lines.push_back(l);
		in.close();
	}
	std::string incfolders = "";
	std::vector<std::string> sourcefolders;
	std::vector<std::string> sourcenames;
	for(int i = 0; i < headers.size(); ++i){
		for(int j = headers[i].size()-1; j >= 0; --j){
			if(headers[i][j] == '/'){
				std::string tmp(headers[i].begin(), headers[i].begin() + j);
				if(incfolders.size() == 0 || find(incfolders, tmp) == -1)
					incfolders += (tmp + " ");
				break;
			}
		}
	}
	for(int i = 0; i < source.size(); ++i){
		for(int j = source[i].size()-1; j >= 0; --j){
			if(source[i][j] == '/'){
				std::string tmp1(source[i].begin(), source[i].begin() + j);
				std::string tmp2(source[i].begin() + j + 1, source[i].end());
				if(find(sourcefolders,tmp1) == -1)
					sourcefolders.push_back(tmp1);
				if(find(sourcenames, tmp2) == -1)
					sourcenames.push_back(tmp2);	
				break;
			}
		}
	}
	std::ofstream out("./Makeline");
	out << "OUTPUT=" << outline << std::endl;
	out << "EXT=" << extension << std::endl;
	if(extension == "cpp")
		out << "CPPC=g++" << std::endl;
	else
		out << "CPPC=gcc" << std::endl;
	out << "INCDIR=" << incfolders << std::endl;
	out << objectsGen(sourcenames) << std::endl;
	if(mode == "stat"){
		out << std::string("STATICdepend=./lib" + STATICLIBGEN_name + ".a") << std::endl;
		out << "SHAREDdepend=" << std::endl;
		out << "SHAREDFLAG=" << std::endl;
	}
	else if(mode == "shar"){
		out << "STATICdepend=" << std::endl;
		out << std::string("SHAREDdepend=./lib" + SHAREDLIBGEN_name+".so") << std::endl;
		out << "SHAREDFLAG= -fPIC" << std::endl;
	}
	else{
		out << "STATICdepend=" << std::endl;
		out << "SHAREDdepend=" << std::endl;
		out << "SHAREDFLAG=" << std::endl;
	}
	out << std::string("ENTRY=" + entryPoint) << std::endl;
	out << std::string("DEPOBJDIR=./" + depFolder) << std::endl;
	out << std::string("ContFile=./" + contFile + "." + extension) << std::endl;
	out << std::string("TSTfile=./" + TSTfile) << std::endl;
	out << std::string("ANSfile=./" + ANSfile) << std::endl;
	out << std::string("TSTlogs=./" + TSTlogs) << std::endl;
	std::string testGarbage = "";
	std::string analGarbage = "";
	for(int i = 0; i < TSTgarbage.size(); ++i)
		testGarbage += ("./" + TSTgarbage[i] + " ");
	for(int i = 0; i < ANALgarbage.size(); ++i)
		analGarbage += ("./" + ANALgarbage[i] + " ");
	out << std::string("TSTgarbage=" + testGarbage) << std::endl;
	out << std::string("ANALgarbage=" + analGarbage) << std::endl;
	out << std::string("STLIBGEN=./lib" + STATICLIBGEN_name + ".a") << std::endl;
	out << std::string("SHLIBGEN=./lib" + SHAREDLIBGEN_name + ".so") << std::endl;
	std::vector<std::string> allstaticLibs;
	std::vector<std::string> allsharedLibs;
	getAllStaticLibs(allstaticLibs);
	getAllSharedLibs(allsharedLibs);
	std::vector<std::string> LibFldrs;
	std::vector<std::string> LibNames;
	getLibsFolders(LibFldrs, allsharedLibs);
	std::string libnamesline = "", libfoldersline = "";
	if(allsharedLibs.size() > 0){
		for(int i = 0; i < LibFldrs.size(); ++i)
			libfoldersline += (LibFldrs[i] + " ");
		out << std::string("SHAREDLIBCOMMAND=export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:" + libfoldersline) << std::endl;
	}
	else
		out << "SHAREDLIBCOMMAND=" << std::endl;
	getLibsFolders(LibFldrs, allstaticLibs);
	getLibNamesStatic(LibNames, allstaticLibs);
	getLibNamesShared(LibNames, allsharedLibs);
	for(int i = 0; i < LibFldrs.size(); ++i)
		libfoldersline += (LibFldrs[i] + " ");
	for(int i = 0; i < LibNames.size(); ++i)
		libnamesline += (LibNames[i] + " ");
	out << std::string("LIBNAMES=" + libnamesline) << std::endl;
	out << std::string("LIBFOLDERS=" + libfoldersline) << std::endl;
	if(newline){
		out << defaultMakefile << std::endl;
		out << rulesGen(sourcefolders) << std::endl;
		out << "-include $(DEPFILES)" << std::endl;
	}
	else{
		for(int i = 21; i < lines.size(); ++i)
			out << lines[i] << std::endl;
	}
	out.close();
}
void createEssentials(const std::string& mode, const std::string& extension, const std::string& outline){
	auto dirs = getDirs("./");
	if(find(dirs, "./depsAndObjects") == -1){
		std::string cmd = ("mkdir " + depFolder); 
		system(cmd.c_str());
	}
	if(mode == "oneline"){
		if(find(dirs, std::string("./code." + extension)) == -1){
			std::string cmd = ("touch " + contFile + "." + extension);
			system(cmd.c_str());
		}
	}
	else if(mode == "test"){
		if(find(dirs, "./testFile") == -1){
			std::string cmd = ("touch " + TSTfile); 
			system(cmd.c_str());
		}
		if(find(dirs, "./answerFile") == -1){
			std::string cmd = ("touch " + ANSfile); 
			system(cmd.c_str());
		}
		if(find(dirs, "./logs") == -1){
			std::string cmd = ("touch " + TSTlogs); 
			system(cmd.c_str());
		}
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
void includeFiles(std::vector<std::string>& includes,const std::vector<std::string>& allHeaders,const std::vector<std::string>& allSource,const std::string& line){
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
void sourceFiles(std::vector<std::string>& source,const std::vector<std::string>& allSource,const std::vector<std::string>& headers){
	std::string l;
    for(int i = 0; i < allSource.size(); ++i){
    	std::ifstream input(allSource[i]);
    	if (input.is_open()){
  			while (std::getline(input, l)){
        		if(l.find("#include") != std::string::npos){
        			std::string s;
        			for(int j = 10; j < l.size() && l[j+2] != '>' && l[j+2] != '"'; ++j)
        				s+=l[j];
        			if(find(allSource[i], s) != -1){
        				for(int k = 0; k < headers.size(); ++k){
        					if(find(headers[k], s) != -1){
        						if(find(source,allSource[i]) == -1)
        							source.push_back(allSource[i]);
        						break;
        					}
        				}
        			}
    			}
        	}
    	}
    	input.close();
    }
}
std::string rulesGen(const std::vector<std::string>& sourcefolders){
	std::string res = "";
	for(int i = 0; i < sourcefolders.size(); ++i){
		std::string s = "$(DEPOBJDIR)/%.o:" + sourcefolders[i] + "/%.$(EXT)\n";
		s += "	$(CPPC) $(CFLAGS) $(foreach D,$(INCDIR),-I$(D)) $(SHAREDFLAG) -c $< -o $@\n";
		res += s;
	}
	return res;
}
std::string objectsGen(const std::vector<std::string>& sourcenames){
	std::string s = "OBJECTS=";
	for(int i = 0; i < sourcenames.size(); ++i){
		std::string tmp;
		for(int j = sourcenames[i].size()-1; j >= 0; --j){
			if(sourcenames[i][j] == '.'){
				tmp = std::string(sourcenames[i].begin(), sourcenames[i].begin() + j) + ".o";
				break;
			}
		}
		s += ("./" + depFolder + "/" + tmp + " ");
	}
	return s;
}
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
void refreshObjects(const std::string& mode){
	std::ifstream make("./Makeline");
	bool wasShared = false;
	bool isShared = (mode == "shar");
	std::string l;
	int count = 0;
	if(make.is_open()){
		while (std::getline(make, l)){
			if(count == 7){
				if(l == "SHAREDFLAG= -fPIC")
					wasShared = true;
				break;
			}
			count++;
		}
		if(isShared != wasShared){
			auto dirs = getDirs("./");
			std::string depFldr = ("./" + depFolder);
  			if(find(dirs, depFldr) != -1){
  				std::string cmd = ("rm -rf " + depFldr);
  				system(cmd.c_str());
  			}
		}
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
void createOnefile(const std::string& mainFile,const std::vector<std::string>& headers,
 const std::vector<std::string>& source, const std::string& entryPoint, 
 const std::string& extension){
	std::vector<std::string> lines;
	std::vector<std::string> mainlines;
	std::string line;
	std::vector<std::string> existingIncNames;
	std::vector<std::string> IncNames;
	for(int i = 0; i < headers.size(); ++i){
		for(int j = headers[i].size()-1;j>=0;--j){
			if(headers[i][j] == '/'){
				existingIncNames.push_back(std::string(headers[i].begin() + j + 1, headers[i].end()));
				break;
			}
		}
	}
	for(int i = 0; i < headers.size(); ++i){
		std::ifstream in(headers[i]);
		while(std::getline(in,line)){
			if(line.find("#include") != std::string::npos){
				std::string s;
        		for(int j = 10; j < line.size() && line[j] != '>' && line[j] != '"'; ++j)
        			s+=line[j];
        		if(find(existingIncNames, s) == -1 && find(IncNames, s) == -1)
        			IncNames.push_back(s);
			}
		}
		in.close();	
	}
	std::ifstream main(mainFile);
	if(main.is_open()){
		while (std::getline(main, line))
			mainlines.push_back(line);
	}
	else{
		std::cout << "=================== ERROR ===================" << std::endl;
		std::cout << "createOneline: cannot open main line: " << mainFile << std::endl;
		std::cout << "=============================================" << std::endl;
	}
	main.close();
	writeIncludes(lines, IncNames);
	writeHeaderFiles(lines,headers);
	writeSourceFiles(lines,source);
	writeMainFile(lines,mainlines,entryPoint);
	std::string codeFile = ("./" + contFile + "." + extension);
	std::ofstream out(codeFile);
	if(out.is_open()){
		for(auto el : lines)
			out << el.c_str() << std::endl;
	}
	else{
		std::cout << "=================== ERROR ===================" << std::endl;
		std::cout << "createOneline: cannot open code line: " << codeFile << std::endl;
		std::cout << "=============================================" << std::endl;
	}
	out.close();
	std::string compileTest = "./compileTest";
	std::string compiler;
	if(extension == "cpp")
		compiler = "g++ ";
	else
		compiler = "gcc ";
    std::string cmd = compiler + codeFile + " -o " + compileTest;
    system(cmd.c_str());
    auto ls = getDirs("./");
    if(find(ls, compileTest) != -1){
    	std::cout << "================== SUCCES ==================" << std::endl;
    	std::string cmdrm = "rm " + compileTest;
        std::string opencmd = "sublime-text.subl " + codeFile;
        system(cmdrm.c_str());
        system(opencmd.c_str()); 
    }
    else
    	std::cout << "================== COMPILATION ERROR ==================" << std::endl;
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
void getAllStaticLibs(std::vector<std::string>& v, const std::string path){
	auto dirs = getDirs(path);
	for(int i = 1; i < dirs.size(); ++i){
		std::string tmp;
		for(int j = dirs[i].size() - 1; j >= 0; --j){
			if(dirs[i][j] == '/'){
				tmp = std::string(dirs[i].begin() + j + 1, dirs[i].end());
				break;
			}
		}
		if(std::filesystem::is_directory(dirs[i]))
			getAllStaticLibs(v, dirs[i]);
		else if(tmp.size() >= 6){
			if(tmp[0] == 'l' && tmp[1] == 'i' && tmp[2] == 'b' &&
				tmp[tmp.size()-1] == 'a' && tmp[tmp.size() - 2] == '.')
				v.push_back(dirs[i]);
		}
		
	}
}
void getAllSharedLibs(std::vector<std::string>& v, const std::string path){
	auto dirs = getDirs(path);
	for(int i = 1; i < dirs.size(); ++i){
		std::string tmp;
		for(int j = dirs[i].size() - 1; j >= 0; --j){
			if(dirs[i][j] == '/'){
				tmp = std::string(dirs[i].begin() + j + 1, dirs[i].end());
				break;
			}
		}
		if(std::filesystem::is_directory(dirs[i]))
			getAllSharedLibs(v, dirs[i]);
		else if(tmp.size() >= 7){
			if(tmp[0] == 'l' && tmp[1] == 'i' && tmp[2] == 'b' &&
				tmp[tmp.size()-1] == 'o' && tmp[tmp.size() - 2] == 's' && tmp[tmp.size() - 3] == '.')
				v.push_back(dirs[i]);
		}
		
	}
}
void getLibsFolders(std::vector<std::string>& v, const std::vector<std::string>& alllibs){
	for(int i = 0; i < alllibs.size(); ++i){
		std::string folder;
		for(int j = alllibs[i].size()-1; j >= 0; --j){
			if(alllibs[i][j] == '/'){
				folder = std::string(alllibs[i].begin(), alllibs[i].begin() + j + 1);
				break;
			}		
		}
		if(v.size() == 0 || find(v, folder) == -1)
			v.push_back(folder);
	}
}
void getLibNamesStatic(std::vector<std::string>& v, const std::vector<std::string>& alllibs){
	for(int i = 0; i < alllibs.size(); ++i){
		std::string name;
		for(int j = alllibs[i].size()-1; j >= 0; --j){
			if(alllibs[i][j] == '/'){
				name = std::string(alllibs[i].begin() + j + 4, alllibs[i].end() - 2);
				break;
			}		
		}
		if(v.size() == 0 || find(v, name) == -1)
			v.push_back(name);
	}
}
void getLibNamesShared(std::vector<std::string>& v, const std::vector<std::string>& alllibs){
	for(int i = 0; i < alllibs.size(); ++i){
		std::string name;
		for(int j = alllibs[i].size()-1; j >= 0; --j){
			if(alllibs[i][j] == '/'){
				name = std::string(alllibs[i].begin() + j + 4, alllibs[i].end() - 3);
				break;
			}		
		}
		if(v.size() == 0 || find(v, name) == -1)
			v.push_back(name);
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
void sourceFiles(std::vector<std::string>& source, const std::vector<std::string>& allSource,
	const std::vector<std::string>& headers,int x){

	std::vector<function> funcs;
	std::cout << headers << std::endl;
	for(int index = 0; index < headers.size(); ++index){
		std::cout << "====================================" << std::endl;
		std::cout << std::endl;
		std::ifstream in(headers[index]);
		std::string line, buffer = "";
		int coolBracesCount = 0, roundBracesCount = 0;
		while(std::getline(in,line)){
			bool allSpaces = true;
			bool comment = false;
			for(int j = 0; j < line.size(); ++j){
				if(allSpaces && j < (line.size() - 1) && line[j] == '/' && line[j+1] == '/'){
					comment = true;
					break;
				}
				if(line[j] != '\t' && line[j] != '\r' && line[j] != '\n' && line[j] != ' ')
					allSpaces = false;
			}
			if(allSpaces || comment || line.find('#') != std::string::npos)
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
				else if(line[i] == ';' && coolBracesCount == 0 && roundBracesCount == 0){
					std::cout << buffer << std::endl;
					i++;
					buffer.clear();
				}
				else
					buffer += line[i];
			}
			buffer += ' ';	
		}
	}
	
}