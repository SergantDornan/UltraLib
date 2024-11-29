#include <build.h>



// -ext
// -o
// --anal -anal
// -onefile -one
// -shared -sh
// -static -st
// --mrproper -mr
// --purge -pr
// -make --Makefile
// self
// (run)filename(run) (extension)
int main(int argc, char* argv[]){
	std::string extension = "cpp";
	std::string outfile = "out.a";
	std::string mode = "default";
  	std::vector<std::string> allHeaders;
  	std::vector<std::string> allSource;
  	getAllheaders(allHeaders);
  	getAllsource(allSource, extension);
  	bool remakeMakefile = false;
  	std::string arg;
  	if(argc >= 2 && argv[1][0] != '-')
  		arg = argv[1];
  	if(arg == "self"){
  		std::cout << "===================== SELF COMPILE =====================" << std::endl;
  		std::cout << std::endl;
  		auto dirs = getDirs("./lib");
  		std::string self_compile = "g++ -I./buildercode/header -I./include ./buildercode/source/build.cpp ./buildercode/source/buildFunc.cpp ";
  		for(int i = 1; i < dirs.size(); ++i)
  			self_compile += (dirs[i] + " ");
  		self_compile += " -o ./builder";
  		system(self_compile.c_str());
  		return 0;
  	}
  	for(int i = 1; i < argc; ++i){
  		if(std::string(argv[i]) == "-ext" || std::string(argv[i]) == "--extension"){
  			if(i + 1 >= argc || argv[i + 1][0] == '-'){
  				std::cout << "====================== ERROR ======================" << std::endl;
  	 			std::cout << "============  No extension after " << argv[i] << " flag ============" << std::endl;
  	 			std::cout << "===================================================" << std::endl;
  	 			return 0;
  			}
  			extension = std::string(argv[i+1]);
  		}
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
  			if(outfile == "out.a")
  				outfile = "test";
  		}
  		else if(std::string(argv[i]) == "--anal" || std::string(argv[i]) == "-anal"){
  			if(outfile == "out.a")
  				outfile = "analysis";
  			mode = "anal";
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
  	createEssentials(mode, extension,outfile);
  	std::string mainFile = "main." + extension;
  	bool run = (find(arg,"run") != -1 && arg != "");
  	if(!(arg == "" || arg == "run") && arg != "make" && arg != "Makefile"){
  		int index = find(arg,"run");
  		if(index != -1){
  			if(index == 0)
  				mainFile = std::string(arg.begin() + 3, arg.end()) + '.' + extension;
  			else
  				mainFile = std::string(arg.begin(), arg.end() - 3) + '.' + extension;
  		}
  		else
  			mainFile = arg + '.' + extension;
  	}
  	bool b = false;
  	for(int i = 0; i < allSource.size(); ++i){
  		for(int j = allSource[i].size()-1; j >=0; --j){
  			if(allSource[i][j] == '/'){
  				std::string tmp(allSource[i].begin() + j + 1, allSource[i].end());
  				if(tmp == mainFile){
  					b = true;
  					mainFile = allSource[i];
  					break;
  				}			
  			}
  		}
  	}
  	if(!b){
  		std::cout << "====================== ERROR ======================" << std::endl;
  		std::cout << "============  CANNOT FIND ENTRY POINT  ============" << std::endl;
  		std::cout << "====== create main." << extension << " or specify entry file ======" << std::endl;
  		std::cout << "===================================================" << std::endl;
  		return 0;
  	}
  	std::vector<std::string> source;
  	std::vector<std::string> headers;
  	source.push_back(mainFile);
  	includeFiles(headers,allHeaders,mainFile);
  	sourceFiles(source,allSource,headers);
  	if(remakeMakefile){
  		auto dirs = getDirs("./");
  		if(find(dirs,"./Makefile") != -1)
  			system("rm ./Makefile");
  	}
  	createMakeFile(mode,extension,outfile,headers,source);
  	if(mode == "mrproper")
  		system("make mrproper");
  	else if(mode == "purge")
  		system("make purge");
  	else if(mode == "stat")
  		system("make libstatic");
  	else if(mode == "shar")
  		system("make libshared");
  	else
  		system("make");
  	if(run){
  		std::string runcmd = "./" + outfile;
  		system(runcmd.c_str());
  	}
	return 0;
}