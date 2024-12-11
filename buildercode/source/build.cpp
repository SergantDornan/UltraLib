#include <build.h>

// -o
// -onefile -one
// -shared -sh
// -static -st
// --mrproper -mr
// --purge -pr
// --test -tst
// -make --Makefile
// self
// (run)filename(run) (extension)
int main(int argc, char* argv[]){
	auto dirs = getDirs("./");
	std::string extension = "default";
	std::string outfile = "default";
	std::string mode = "default";
	std::string entryPoint = "main";
  	std::vector<std::string> allHeaders;
  	std::vector<std::string> allSource;
  	std::vector<std::string> statlibs;
  	std::vector<std::string> sharlibs;
  	bool remakeMakefile = false;
  	std::string arg;
  	if(argc >= 2 && argv[1][0] != '-')
  		arg = argv[1];
  	if(arg == "self"){
  		std::cout << "===================== SELF COMPILE =====================" << std::endl;
  		std::vector<std::string> source;
  		std::vector<std::string> headers;
  		getAllheaders(allHeaders, sourceCodeFolder);
  		getAllsource(allSource, sourceCodeFolder);
  		stripExt(allSource, "cpp");
  		includeFiles(headers,allHeaders,allSource,mainSourceFileName);
  		sourceFiles(source,allSource,headers);
  		std::vector<std::string> headerfoldesrs;
  		for(int i = 0; i < headers.size(); ++i){
  			int index = -1;
  			for(int j = headers[i].size()-1;j >= 0; --j){
  				if(headers[i][j] == '/'){
  					index = j;
  					break;
  				}
  			}
  			std::string tmp(headers[i].begin(), headers[i].begin() + index);
  			if(find(headerfoldesrs, tmp) == -1)
  				headerfoldesrs.push_back(tmp);
  		}
  		std::string self_compile = "g++ -g3";
  		for(int i = 0; i < headerfoldesrs.size(); ++i)
  			self_compile += (" -I" + headerfoldesrs[i] + " ");
  		for(int i = 0; i < source.size(); ++i)
  			self_compile += (" " + source[i] + " ");
  		self_compile += (" -o ./" + builderOutfile);
  		system(self_compile.c_str());
  		return 0;
  	}
  	getAllheaders(allHeaders);
  	getAllsource(allSource);
  	for(int i = 1; i < argc; ++i){
  		if(std::string(argv[i]) == "-make" || std::string(argv[i]) == "--Makefile"){
  			remakeMakefile = true;
  		}
  		else if(std::string(argv[i]) == "-o"){
  			if(i + 1 >= argc || argv[i + 1][0] == '-'){
  				std::cout << "====================== ERROR ======================" << std::endl;
  	 			std::cout << "============  No file name after " << argv[i] << " flag ============" << std::endl;
  	 			std::cout << "===================================================" << std::endl;
  	 			return 0;
  			}
  			outfile = std::string(argv[i+1]);
  		}
  		else if(std::string(argv[i]) == "--onefile" || std::string(argv[i]) == "-one"){
  			mode = "onefile";
  		}
  		else if(std::string(argv[i]) == "--shared" || std::string(argv[i]) == "-sh")
  			mode = "shar";
  		else if(std::string(argv[i]) == "--static" || std::string(argv[i]) == "-st")
  			mode = "stat";
  		else if(std::string(argv[i]) == "--test" || std::string(argv[i]) == "-tst"){
  			mode = "test";
  		}
  		else if(std::string(argv[i]) == "--mrproper" || std::string(argv[i]) == "-mr"){
  			mode = "mrproper";
  			break;
  		}
  		else if(std::string(argv[i]) == "--purge" || std::string(argv[i]) == "-pr"){
  			mode = "purge";
  			break;
  		}
  	}

  	std::string mainFile = "main";
  	bool run = (find(arg,"run") != -1 && arg != "");
  	if(!(arg == "" || arg == "run")){
  		int index = find(arg,"run");
  		if(index == 0)
  			mainFile = std::string(arg.begin() + 3, arg.end());
  		else if(index == arg.size() - 3)
  			mainFile = std::string(arg.begin(), arg.end() - 3);
  		else
  			mainFile = arg;
  	}
  	if(outfile == "default")
  		outfile = mainFile;
  	std::ifstream makefile("./Makefile");
  	if(makefile.is_open()){
  		std::string l;
  		std::getline(makefile, l);
  		std::string name(l.begin() + 7, l.end());
  		if(name != outfile)
  			remakeMakefile = true;
  	}
  	bool b = false;
  	for(int i = 0; i < allSource.size(); ++i){
  		for(int j = allSource[i].size()-1; j >=0; --j){
  			if(allSource[i][j] == '/'){
  				std::string tmp(allSource[i].begin() + j + 1, allSource[i].end());
  				int f = find(tmp,'.');
  				std::string tmp1(tmp.begin(), tmp.begin() + f);
  				if(tmp1 == mainFile){
  					b = true;
  					extension = std::string(tmp.begin() + f + 1, tmp.end());
  					mainFile = allSource[i];
  					break;
  				}			
  			}
  		}
  	}
  	if(!b){
  		std::cout << "====================== ERROR ======================" << std::endl;
  		std::cout << "============  CANNOT FIND ENTRY POINT  ============" << std::endl;
  		std::cout << "====== create main file or specify entry file ======" << std::endl;
  		std::cout << "===================================================" << std::endl;
  		return 0;
  	}
  	entryPoint = defineEntryPoint(mainFile);
  	refreshObjects(mode);
  	createEssentials(mode,extension,outfile);
  	std::vector<std::string> source;
  	std::vector<std::string> headers;
  	source.push_back(mainFile);
  	stripExt(allSource, extension);
  	includeFiles(headers,allHeaders,allSource,mainFile);
  	sourceFiles(source,allSource,headers,0);
  	MrProperSourceFiles(source,headers);
  	if(remakeMakefile){
  		if(find(dirs,"./Makefile") != -1)
  			system("rm ./Makefile");
  	}
  	createMakeFile(mode,extension,outfile,headers,source,entryPoint);
  	if(mode == "mrproper" || mode == "purge"){
  		if(mode == "mrproper")
  			system("make mrproper");
  		else
  			system("make purge");
  		if(find(dirs, "./Makefile") != -1)
  			system("rm ./Makefile");
  		std::string codeFile = ("./" + contFile + "." + extension);
  		if(find(dirs, codeFile) != -1){
  			std::string cmd = ("rm " + codeFile);
  			system(cmd.c_str());
  		}
  		std::string depFldr = ("./" + depFolder);
  		if(find(dirs, depFldr) != -1){
  			std::string cmd = ("rm -rf " + depFldr);
  			system(cmd.c_str());
  		}
  	}
  	else if(mode == "onefile")
  		createOnefile(mainFile,headers, source, entryPoint,extension);
  	else if(mode == "stat")
  		system("make libstatic -j 20");
  	else if(mode == "shar")
  		system("make libshared -j 20");
  	else
  		system("make -j 20");
  	if(run){
  		std::string runcmd = "./" + outfile;
  		system(runcmd.c_str());
  	}
	return 0;}