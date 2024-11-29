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
void getAllsource(std::vector<std::string>& source,const std::string extension, const std::string path){
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
			if(find(source, dirs[i]) == -1 && ext == extension)
				source.push_back(dirs[i]);
		}
		if(std::filesystem::is_directory(dirs[i]))
			getAllsource(source,extension, dirs[i]);
	}
}
void createMakeFile(const std::string& mode, const std::string extension, const std::string& outfile,
	const std::vector<std::string>& headers, const std::vector<std::string>& source){
	
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
				if(find(incfolders, tmp) == -1 || incfolders.size() == 0)
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
	if(mode == "static"){
		out << "STATICdepend=./staticLibs/libstatic.a" << std::endl;
		out << "SHAREDdepend=" << std::endl;
		out << "SHAREDFLAG=" << std::endl;
	}
	else if(mode == "shared"){
		out << "STATICdepend=" << std::endl;
		out << "SHAREDdepend=./sharedLibs/libshared.so" << std::endl;
		out << "SHAREDFLAG= -fPIC" << std::endl;
	}
	else{
		out << "STATICdepend=" << std::endl;
		out << "SHAREDdepend=" << std::endl;
		out << "SHAREDFLAG=" << std::endl;
	}
	if(newfile){
		out << defaultMakefile << std::endl;
		out << rulesGen(sourcefolders) << std::endl;
		out << "-include $(DEPFILES)" << std::endl;
	}
	else{
		for(int i = 8; i < lines.size(); ++i)
			out << lines[i] << std::endl;
	}
	
	out.close();
}
void createEssentials(const std::string& mode, const std::string& extension, const std::string& outfile){
	auto dirs = getDirs("./");
	if(find(dirs, "./depsAndObjects") == -1)
		system("mkdir depsAndObjects");
	if(mode == "stat"){
		if(find(dirs, "./staticLibs") == -1)
			system("mkdir staticLibs");
	}
	else if(mode == "shared"){
		if(find(dirs, "./sharedLibs") == -1)
			system("mkdir sharedLibs");
	}
	else if(mode == "onefile"){
		if(find(dirs, std::string("./code." + extension)) == -1){
			std::string cmd = "touch code." + extension;
			system(cmd.c_str());
		}
	}
	else if(mode == "test"){
		if(find(dirs, "./testFile") == -1)
			system("touch testFile");
		if(find(dirs, "./answerFile") == -1)
			system("touch answerFile");
		if(find(dirs, "./logs") == -1)
			system("touch logs");
	}
}
void includeFiles(std::vector<std::string>& includes,const std::vector<std::string>& allHeaders, std::string file){
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
        			if(find(includes, newfile) == -1)
						includes.push_back(newfile);
    				includeFiles(includes,allHeaders,newfile);	
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