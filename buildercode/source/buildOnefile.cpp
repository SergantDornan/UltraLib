#include <build.h>

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