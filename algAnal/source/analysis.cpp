#include "analysis.h"
#include "math.h"
extern "C" int mainfunc(int argc, char* argv[]);
const bool output = false;

void points(std::map<double,long double>& mp){
	for(double xi = n; xi <= N; ++xi){
		clock_t start = clock();
		char** str = new char*[2];
		str[0] = const_cast<char*>("anal");
		str[1] = const_cast<char*>(std::to_string(xi).c_str());
		mainfunc(2, str);
		delete[] str;
		clock_t end = clock();
		long double elapsed_time = (long double)(end - start) / CLOCKS_PER_SEC;
		mp.emplace(xi,elapsed_time*1000);
	}
	for(double xi = n+1; xi <= N; ++xi){
		double mid = xi-0.5;
		mp.emplace(mid, (mp[xi-1] + mp[xi]) / 2);
		mp.emplace(mid - 0.25, (mp[mid] + mp[xi-1]) / 2);
		mp.emplace(mid + 0.25, (mp[mid] + mp[xi]) / 2);
	}
}

extern "C" int entry(int argc, char* argv[]){
	int iterations = 0;
	if(argc < 2)
		iterations = defaultIterations;
	else
		iterations = atoi(argv[1]);
	std::map<int,int> counts;
	for(int h = 0; h < iterations; ++h){
		std::map<double,long double> mp;
		points(mp);
		std::vector<long double> res, frac, fracfinal;
		int k = -1;
		for(int i = 0; i <= 4; ++i)
			res.push_back(powerAp(mp,i,n,N));
		long double maximal = -10000;
		for(size_t i = 0; i < res.size()-1; ++i)
			frac.push_back((res[i] - res[i+1]) / res[i]);
		for(size_t i = 0; i < frac.size()-1; ++i)
			fracfinal.push_back((frac[i] - frac[i+1]) / frac[i]);
		for(size_t i = 0; i < fracfinal.size(); ++i){
				if(fracfinal[i] > maximal){
					maximal = fracfinal[i];
					k = i + 1;
				}
			}
		if(output){
			std::cout << res << std::endl;
			std::cout << frac << std::endl;
			std::cout << fracfinal << std::endl;
		}
		if(counts.find(k) != counts.end()){
			counts[k]++;
		}
		else{
			counts.emplace(k,1);
		}
	}
	if(output)
		std::cout << counts << std::endl;
	int maximal = -1;
	int answer = -1;
	for(auto el : counts){
		if(el.second > maximal){
			maximal = el.second;
			answer = el.first;
		}
	}
	std::cout << "O(n^" <<  answer << ")" << std::endl;
	return 0;
}