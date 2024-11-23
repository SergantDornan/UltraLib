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