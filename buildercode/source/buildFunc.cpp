#include <build.h>
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
void createMakeFile(const std::string& mode, const std::string& extension, const std::string& outfile,
	const std::vector<std::string>& headers, const std::vector<std::string>& source, const std::string& entryPoint){
	
	auto dirs = getDirs("./");
	bool newfile = false;
	if(find(dirs,"./Makefile") == -1){
		newfile = true;
		system("touch Makefile");
	}
	std::vector<std::string> lines;
	std::string l;
	if(!newfile){
		std::ifstream in("./Makefile");
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
	std::ofstream out("./Makefile");
	out << "OUTPUT=" << outfile << std::endl;
	out << "EXT=" << extension << std::endl;
	if(extension == "cpp")
		out << "CPPC=g++" << std::endl;
	else
		out << "CPPC=gcc" << std::endl;
	out << "INCDIR=" << incfolders << std::endl;
	out << objectsGen(sourcenames) << std::endl;
	if(mode == "stat"){
		out << "STATICdepend=./staticLibs/libstatic.a" << std::endl;
		out << "SHAREDdepend=" << std::endl;
		out << "SHAREDFLAG=" << std::endl;
	}
	else if(mode == "shar"){
		out << "STATICdepend=" << std::endl;
		out << "SHAREDdepend=./sharedLibs/libshared.so" << std::endl;
		out << "SHAREDFLAG= -fPIC" << std::endl;
	}
	else{
		out << "STATICdepend=" << std::endl;
		out << "SHAREDdepend=" << std::endl;
		out << "SHAREDFLAG=" << std::endl;
	}
	out << std::string("ENTRY=" + entryPoint) << std::endl;
	out << std::string("DEPOBJDIR=./" + depFolder) << std::endl;
	out << std::string("STATLIBS=./" + staticLibsFolder) << std::endl;
	out << std::string("SHLIBS=./" + sharedLibsFolder) << std::endl;
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
	out << std::string("STATICLIBGEN_name=" + STATICLIBGEN_name) << std::endl;
	out << std::string("SHAREDLIBGEN_name=" + SHAREDLIBGEN_name) << std::endl;
	if(newfile){
		out << defaultMakefile << std::endl;
		out << rulesGen(sourcefolders) << std::endl;
		out << "-include $(DEPFILES)" << std::endl;
	}
	else{
		for(int i = 20; i < lines.size(); ++i)
			out << lines[i] << std::endl;
	}
	out.close();
}
void createEssentials(const std::string& mode, const std::string& extension, const std::string& outfile){
	auto dirs = getDirs("./");
	if(find(dirs, "./depsAndObjects") == -1){
		std::string cmd = ("mkdir " + depFolder); 
		system(cmd.c_str());
	}
	if(mode == "stat"){
		if(find(dirs, "./staticLibs") == -1){
			std::string cmd = ("mkdir " + staticLibsFolder); 
			system(cmd.c_str());
		}
	}
	else if(mode == "shar"){
		if(find(dirs, "./sharedLibs") == -1){
			std::string cmd = ("mkdir " + sharedLibsFolder); 
			system(cmd.c_str());
		}
	}
	else if(mode == "onefile"){
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
void includeFiles(std::vector<std::string>& includes,const std::vector<std::string>& allHeaders,const std::string& file){
    std::string l;
    std::ifstream input(file);
    if (input.is_open()){
  		while (std::getline(input, l)){
        	if(l.find("#include") != std::string::npos){
        		std::string s;
        		for(int j = 10; j < l.size() && l[j] != '>' && l[j] != '"'; ++j)
        			s+=l[j];
        		std::string newfile;
        		bool b = false;
        		for(int j = 0; j < allHeaders.size(); ++j){
        			if(find(allHeaders[j], s) != -1){
        				b = true;
        				newfile = allHeaders[j];
        				break;
        			}
        		}
        		if(b){
        			includeFiles(includes,allHeaders,newfile);	
        			if(find(includes, newfile) == -1)
						includes.push_back(newfile);
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
	std::ifstream make("./Makefile");
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
		std::cout << "createOnefile: cannot open main file: " << mainFile << std::endl;
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
		std::cout << "createOnefile: cannot open code file: " << codeFile << std::endl;
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