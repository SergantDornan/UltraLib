#include <math.h>
bool is_prime(int n) {
  try{
  	if(n <= 0)
  		throw "bool is_prime: argument is less than 0 or is 0";
  }
  catch(const char* s){
  		std::cout << s << std::endl;
  		return false;
  }
  if(n == 1) 
  	return false; 
  if(n == 2 || n == 3) 
  	return true; 
  if(n % 2 == 0 || n % 3 == 0) return false; 
  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return false;
    }
  }
  return true;
}
std::vector<std::pair<int,int>> canon(int x){
	if(is_prime(x))
		return {{x,1}};
	std::vector<std::pair<int,int>> res;
	int i = 2;
	while(1){
		if(i > x)
			break;
		if(is_prime(i)){
			if(x % i == 0){
				res.push_back({i,0});
				while(x % i == 0){
					res[res.size()-1].second++;
					x = x / i;
				}
			}
			i++;
		}
		else
			i++;
	}
	return res;
}
long int C(int n, int k){
  if (k == 0 || k == n) {
    return 1;
  } else if (k < 0 || k > n) {
  	std::cout << "======================= ERROR =======================" << std::endl;
  	std::cout << "======= mathFuncs.cpp: long int C(int n, int k) ========" << std::endl;
  	std::cout << " k < 0 or k > n" << std::endl;
  	std::cout << "=====================================================" << std::endl;
    return 0;
  }
  long long int dp[k + 1];
  dp[0] = 1;
  for (int i = 1; i <= k; i++) {
    dp[i] = 0;
    for (int j = 1; j <= i; j++) {
      dp[i] += dp[j - 1];
    }
  }
  return dp[k];
}
Function powerAp(std::map<double,long double>& mp, double power){
	if(power < 0){
		std::cout << "========================= ERROR =========================" << std::endl;
		std::cout << "============ mathFuncs.cpp: powerAp() ============" << std::endl;
		std::cout << "power must be non negative, now power is: " << power << std::endl;
		std::cout << "=========================================================" << std::endl;
		return Function();
	}
	else if(power != 0){
		std::vector<long double> a, b;
		for(int i = 0; i < 2*power; ++i)
			a.push_back(0);
		for(int i = 0; i < power+1; ++i)
			b.push_back(0);
		for(auto el : mp){
			for(int i = 0; i < 2*power;++i)
				a[i] += pow(el.first,i+1);
			for(int i = 0; i < power + 1; ++i)
				b[i] += el.second*pow(el.first,power - i);
		}
		Matrix M;
		for(int i = 0; i < power + 1; ++i){
			std::vector<long double> row = {};
			for(int j = 0; j < power + 1; ++j){
			//	std::cout << int(a.size() - 1 - i - j) << "  AAAAAAAAA" << std::endl;
				if(int(a.size() - 1 - i - j) < 0)
					row.push_back(mp.size());
				else
					row.push_back(a[a.size() - 1 - i - j]);
			}
			M.m.push_back(row);
		}
		SLAE sl(M, b);
		std::vector<long double> solution = sl.solve();
		auto F = [](long double xi, std::vector<long double> solution, double power) -> long double{
			long double result = 0;
			for(int i = 0; i < power + 1; ++i){
				result += solution[i] * pow(xi, power - i);
			}
			return result;
		};
		Function result(F,solution,power);
		return result;
		// long double result = 0;
		// for(double xi = n; xi <= N; xi+=0.25){
		// 	result += (F(xi) - mp[xi])*(F(xi) - mp[xi]);
		// }
	}
	else{
		std::vector<long double> solution;
		long double sum = 0;
		for(auto el : mp)
			sum += el.second;
		solution.push_back(sum / mp.size());
		auto F = [](long double xi, std::vector<long double> solution, double power) -> long double{
			return solution[0];
		};
		Function result(F,solution,power);
		return result;
	}
}