#include "codemaker.h"
#include "algs.h"
void push_line(std::vector<std::string>& v, std::string line){
  if(line.find("#include") == std::string::npos && 
      line.find("#ifdef") == std::string::npos &&
      line.find("#ifndef") == std::string::npos &&
      line.find("#define") == std::string::npos &&
      line.find("endif") == std::string::npos){
             if(line.find("extern") != std::string::npos){
                std::regex reg("extern");
                std::string newstr = std::regex_replace(line,reg,"");
                v.push_back(newstr);
             }
             else
               v.push_back(line);
  }
}
std::vector<std::string> getDirs(const std::string &path)
{
  std::string back = path;

  while (back.back() != '/')
    {
      back.pop_back();
    }

  back.pop_back();
  std::vector<std::string> dirs = {back};

  for (const std::filesystem::directory_entry &dir : std::filesystem::directory_iterator(path))
    {
      dirs.push_back(dir.path().string());
    }

  return dirs;
}

void includeList(std::vector<std::string>& includes, std::string file){
	std::string path = headers + file;
	if(find(includes, file) == -1)
		includes.push_back(file);
    std::string l;
    std::ifstream input(path);
 // std::cout << std::filesystem::current_path() << std::endl;
    if (input.is_open())
  	{
     // std::cout << "FILE " << file << std::endl;
    //	std::cout << "AAAAAAAAAAA  " << file << std::endl;
        while (std::getline(input, l))
        {
        	if(l.find("#include") != std::string::npos){

        		std::string s;
        		for(int j = 10; j < l.size() && l[j] != '>' && l[j] != '"'; ++j)
        			s+=l[j];
        //		std::cout << s << std::endl;
    			includeList(includes, s);	
    		  }
        }
    }
    input.close();
}
void include(std::vector<std::string>& includes, std::vector<std::string>& lines){
	std::vector<std::string> existingfiles = getDirs(headers);
	for(int i = 0; i < includes.size(); ++i){
		bool exists = false;
		for(int j = 0; j < existingfiles.size(); ++j){
			if(existingfiles[j] == (headers + includes[i])){
				exists = true;
				break;
			}
		}
		if(!exists){
			std::string s = "#include <" + includes[i] + ">";
			lines.push_back(s);
		}
	}
	for(int i = includes.size()-1; i >= 0; --i){
		std::string l;
   		std::ifstream input(headers + includes[i]);
 //   	std::cout << std::filesystem::current_path() << std::endl;
    	if (input.is_open())
    	{
         	while (std::getline(input, l))
       		{
       			push_line(lines,l);
       		}
    	}
    	input.close();
	}
}


int main(){
	std::string line;
    std::ifstream in(mainfile);
 //   std::cout << std::filesystem::current_path() << std::endl;
    std::vector<std::string> lines;
    std::vector<std::string> linesmain;
    if (in.is_open())
    {
        while (std::getline(in, line))
        {
        	//std::cout << line << std::endl;
        	linesmain.push_back(line);
        }
    }
    else{
      std::cout << "Cannot open main.cpp" << std::endl;
      return 0;
    }
    int k = 0;
    std::vector<std::string> includes;
    for(int i = 0; i < linesmain.size(); ++i){
    	if(linesmain[i].find("#include") != std::string::npos){
    		std::string s;
    		for(int j = 10; j < linesmain[i].size() && linesmain[i][j] != '>' && linesmain[i][j] != '"'; ++j)
        			s+=linesmain[i][j];
      //  std::cout << s << std::endl;
    		includeList(includes, s);	
    	}
    	else{
    		k = i;
    		break;
    	}
    }
    std::cout << includes << std::endl;
    include(includes, lines);
    std::vector<std::string> sourceCode = getDirs(source);
    std::vector<std::string> files;
    for(int i = 0; i < sourceCode.size(); ++i){
    	std::string l;
    	std::ifstream input(sourceCode[i]);
    	if (input.is_open())
  		{
        	while (std::getline(input, l))
        	{
        		if(l.find("#include") != std::string::npos){
        			std::string s;
        			for(int j = 10; j < l.size() && l[j] != '>' && l[j] != '"'; ++j)
        				s+=l[j];
        			if(find(includes, s) && find(files, sourceCode[i]) == -1){
        				files.push_back(sourceCode[i]);
        			}
    			 }
        	}
    	}
    	input.close();
    }
    for(int i = 0; i < files.size(); ++i)
      std::cout << files[i] << std::endl;
    std::cout << '\n';
    std::cout << '\n';
    for(int i = 0; i < files.size(); ++i){
    	std::string l;
    	std::ifstream input(files[i]);
 //   	std::cout << std::filesystem::current_path() << std::endl;
    	if (input.is_open())
    	{
        	while (std::getline(input, l))
        	{
        		push_line(lines,l);
        	}
    	}
      else{
        std::cout << "Cannot open " << files[i] << std::endl;
        return 0;
      }
    	input.close();
    }
    for(int i = k; i  <linesmain.size(); ++i){
    	if(linesmain[i].find("mainfunc") !=  std::string::npos){
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
        lines.push_back(linesmain[i]);
    }
    std::ofstream out;
    out.open(output);
    if (out.is_open())
    {
    	for(auto el: lines){
    		 out << el.c_str() << std::endl;
    	}
    }
    else{
      std::cout << "Cannot open file" << std::endl;
      return 0;
    }
    out.close(); 
    // for(auto el: lines){
    // 	std::cout << el << std::endl;
    // }
    in.close();
    std::string compileTest = codeFolder + "compileTest";
    std::string cmd = "g++ " + output + " -o " + compileTest;
    system(cmd.c_str());
    std::vector<std::string> ls = getDirs(codeFolder);
    if(find(ls, compileTest) != -1){
      std::string cmdrm = "rm " + compileTest;
      system(cmdrm.c_str());
      std::cout << "================== SUCCES ==================" << std::endl;
      std::string opencmd = "sublime-text.subl " + output;
      system(opencmd.c_str()); 
    }
    else{
      std::cout << "================== COMPILATION ERROR ==================" << std::endl;
    }
    return 0;
}