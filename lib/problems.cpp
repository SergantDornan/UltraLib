#include <problems.h>
#include <inputs.h>

extern std::vector<std::string> split(std::string s, char ch){
	std::vector<std::string> res;
	std::string curr;
	for(int i = 0; i < s.size(); ++i){
		if(s[i] == ch || i == s.size() - 1){
			if(i == s.size() - 1 && s[i] != ch)
				curr += s[i];
			res.push_back(curr);
			curr.clear();
		}
		else
			curr += s[i];
	}
	return res;
}

extern void fillVector(std::vector<int>& v,int minRand, int maxRand, int N){
    for(int i = 0; i < N; ++i)
            v.push_back(minRand + (rand() % (maxRand+1)));
}
extern void fillVector(std::vector<double>& v,int minRand, int maxRand, int N){
    for(int i = 0; i < N; ++i)
            v.push_back(minRand + (rand() % (maxRand+1)));
}
extern void fillVector(std::vector<char>& v,int minRand, int maxRand, int N){
    for(int i = 0; i < N; ++i)
            v.push_back(char(minRand + (rand() % (maxRand+1))));
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
std::vector<std::pair<int,int>> problem1(std::vector<int>& v){
	std::set<int> set;
	std::vector<std::pair<int,int>> res;
	std::vector<int>::iterator it = v.begin();
	while(it != v.end()){
		if(set.find(*it) == set.end()){
			set.insert(*it);
			it++;
		}
		else
		{
			if(!find(res,{*it,*it}))
				res.push_back({*it,*it});
			v.erase(it);
		}
	}
	std::cout << v << std::endl;
	std::vector<int> sums;

    merge_sort(sums);
  	std::cout << sums << std::endl;
	return res;
}

