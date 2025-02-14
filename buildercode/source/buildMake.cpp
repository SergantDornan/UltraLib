#include <build.h>
void createMakeFile (const std::string& mode, const std::string& extension, const std::string& outline,
	const std::vector<std::string>& headers, const std::vector<std::string>& source, const std::string& entryPoint){
	
	auto dirs = getDirs("./");
	bool newline = false;
	if (find (dirs,"./Makefile") == -1)
	{
		newline = true;
		system ("touch Makefile");
	}
	std::vector<std::string> lines;
	std::string l;
	if(!newline){
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