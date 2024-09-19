#include "analysis.h"
extern "C" int mainfunc(int argc, char* argv[]);


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

long double constAp(std::map<double,long double>& mp){
	long double a = 0;
	for(double xi = n; xi <= N; ++xi){
		a += mp[xi];
	}
	long double c = a / N;
	long double res = 0;
	for(double xi = n; xi <= N; xi+=0.25){
		res += ((mp[xi] - c)*(mp[xi] - c));
	}
	return res;
}
long double powerAp(std::map<double,long double>& mp, double power, long double (*f)(long double)){
	std::vector<long double> a, b;
	for(int i = 0; i < 2*power; ++i)
		a.push_back(0);
	for(int i = 0; i < power+1; ++i)
		b.push_back(0);
	for(double xi = n; xi <= N; ++xi){
		for(int i = 0; i < 2*power;++i)
			a[i] += pow(f(xi),i+1);
		for(int i = 0; i < power + 1; ++i)
			b[i] += mp[xi]*pow(f(xi),power - i);
	}
	Matrix M;
	for(int i = 0; i < power + 1; ++i){
		std::vector<long double> row = {};
		for(int j = 0; j < power + 1; ++j){
		//	std::cout << int(a.size() - 1 - i - j) << "  AAAAAAAAA" << std::endl;
			if(int(a.size() - 1 - i - j) < 0)
				row.push_back(N);
			else
				row.push_back(a[a.size() - 1 - i - j]);
		}
		M.m.push_back(row);
	}
	//std::cout << b << std::endl;
	SLAE sl(M, b);
	std::vector<long double> solution = sl.solve();
	//long double minfc = minf / pow(10,power);	
	// if(solution[0] < minfc && solution[0] > 0)
	// 	solution[0] = minfc;
	// if(solution[0] > -minfc && solution[0] < 0)
	// 	solution[0] = -minfc;
	//std::cout << solution << std::endl;	
	auto F = [&solution, &power,f](long double xi) -> long double{
		long double result = 0;
		for(int i = 0; i < power + 1; ++i){
			result += solution[i] * pow(f(xi), power - i);
		}
		return result;
	};
	long double result = 0;
	for(double xi = n; xi <= N; xi+=0.25){
		result += (F(xi) - mp[xi])*(F(xi) - mp[xi]);
	}
	return result;
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
		std::vector<long double> res, reslog, frac, fracfinal;
		int k = -1;
		long double c = constAp(mp);
		res.push_back(c);
		reslog.push_back(c);
		for(int i = 1; i <= 4; ++i){
			res.push_back(powerAp(mp,i,classiqueFunc));
			reslog.push_back(powerAp(mp,i,logFunc));
		}
		if(h == 3){
			std::cout << res << std::endl;
			std::cout << reslog << std::endl;
			// long double hui = 0;
			// for(int i = 0; i < res.size();++i)
			// 	hui += res[i];
			// std::cout << hui << std::endl;
			// hui = 0;
			// for(int i = 0; i < reslog.size();++i)
			// 	hui += reslog[i];
			// std::cout << hui << std::endl;
		}
		long double maximal = -10000;
		for(size_t i = 0; i < res.size()-1; ++i)
			frac.push_back((res[i] - res[i+1]) / res[i]);
		for(size_t i = 0; i < frac.size()-1; ++i)
			fracfinal.push_back((frac[i] - frac[i+1]) / frac[i]);
		if(frac[0] < 0.1){
			k = 0;
		}
		else{
			for(size_t i = 0; i < fracfinal.size(); ++i){
				if(fracfinal[i] > maximal){
					maximal = fracfinal[i];
					k = i + 1;
				}
			}
		}
		if(counts.find(k) != counts.end()){
			counts[k]++;
		}
		else{
			counts.emplace(k,1);
		}
	}
	std::cout << counts << std::endl;
	int maximal = -1;
	int answer = -1;
	for(auto el : counts){
		if(el.second > maximal){
			maximal = el.second;
			answer = el.first;
		}
	}
	std::cout << answer << std::endl;
	return 0;
}