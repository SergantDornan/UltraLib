#include "problems.h"

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