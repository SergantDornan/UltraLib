#include <problems.h>
#include <inputs.h>

extern std::vector<std::string> split(std::string s, std::string ch, std::string except){
	std::vector<std::string> res;
	std::string curr;
	bool push = true;
	for(int i = 0; i < s.size(); ++i){
		if(ch.find(s[i]) != std::string::npos && i != (s.size() - 1) && push){
			if(i != 0)
				res.push_back(curr);
			curr.clear();
			if(except.find(s[i]) != std::string::npos){
				curr += s[i];
			}
			push = false;
		}
		else if(ch.find(s[i]) != std::string::npos && i != (s.size() - 1) && !push && except.find(s[i]) != std::string::npos){
			curr += s[i];
		}
		else if(i == (s.size() - 1)){
		//	std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
			if(ch.find(s[i]) == std::string::npos)
				curr+=s[i];
			res.push_back(curr);
		}
		else if(ch.find(s[i]) == std::string::npos){
			push = true;
			curr += s[i];
		}
	}
	return res;
}

extern std::string strip(std::string s, std::string ch){
	std::string res;
	for(int i = 0; i < s.size(); ++i){
		if(ch.find(s[i]) == std::string::npos)
			res+=s[i];
	}
	return res;
}
extern void clear(std::string path){
	std::ofstream out(path);
	if(!out.is_open()){
		std::string s = "filework.h : clear : Cannot open file " + path;
		std::cout << s << std::endl;
	}
	else{
		out << "";
	}
	out.close();
}


//Дан массив целых чисел, назовем отрезов k-хорошим, если в нем не более k различных чисел
//Найти длину наиболее длинного k-хорошего отрезка
int MaxKgoodsize(std::vector<long>& v, long unsigned int k){
	if(v.size() <= k)
		return v.size();
	std::map<long,long unsigned int> mp;
	int count = 0;
	int maxcount = 0;
	for(long unsigned int i = 0; i < v.size(); ++i){
		if(mp.find(v[i]) != mp.end()){
			mp[v[i]]++;
			count++;
		}
		else{
			mp.emplace(v[i],1);
			count++;
			if(mp.size() > k){
				while(mp.size() > k){
					mp[v[i-count+1]]--;
					if(mp[v[i-count+1]] == 0){
						mp.erase(v[i-count+1]);
					}
					count--;
				}
			}
		}
		maxcount = max(count,maxcount);
	}	
	return maxcount;
}



//дан отсортированный массив, найти количество пар чисел, у которых среднее арифметическое тоже в массиве
std::vector<std::pair<int,int>> sortVmiddleNumber(std::vector<int>& v){

}

void onesandzerosMaxMindistance(std::string inp, std::string output){
	std::vector<std::vector<int>> input;
	readVectors(input, inp);
	std::vector<int> res;
	std::vector<int> v = input[0];
	int m = -1;
	int currk = 0;
	int curr = 0;
	int pos = 0;
	int start = 0;
	for(int i = 0; i < v.size(); ++i){
		if(v[i] == 1)
		{
			start = i;
			break;
		}
	}
	if(start > 0)
		res.push_back(0);
	m = start;
	for(int i = start; i < v.size(); ++i){
		if(v[i] == 1){
			curr = (curr / 2) + (curr % 2);
			if(curr >= m){
				if(curr > m){
					m = curr;
					res.clear();
				}
				pos = ((currk+i)/2);
				res.push_back(pos);
				if((i + currk) % 2 == 1){
					pos = ((currk+i)/2)+1;
					res.push_back(pos);	
				}
			}
			curr = 0;
			currk = i;
		}
		else if(i == v.size() - 1){
			curr++;
			if(curr >= m){
				pos = i;
				if(curr > m){
					m = curr;
					res.clear();
				}
				res.push_back(pos);
			}
		}
		else{
			curr++;
		}
	}
	writeVectors(res,output);
}

void HackatonTime(){

}