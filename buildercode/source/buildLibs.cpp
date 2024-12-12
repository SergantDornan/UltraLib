#include <build.h>
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