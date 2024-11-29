#include <math.h>
SLAE::SLAE(){

}
SLAE::SLAE(const std::vector<std::vector<long double>> V1,const std::vector<long double> V2){
	A.m = V1;
	B = V2;}
SLAE::SLAE(Matrix& M,const std::vector<long double> V){
	A = M;
	B = V;}
void SLAE::set(const std::vector<std::vector<long double>> V1, const std::vector<long double> V2){
	A.m = V1;
	B = V2;
}
void SLAE::set(Matrix& M, const std::vector<long double> V){
	A = M;
	B = V;
}
std::vector<long double> SLAE::solve(){
	std::vector<long double> solution;
	if(A.size() < A[0].size()){
		std::cout << "===================================== SLAE solution, number of rows is less than nunber of variables =====================================" << std::endl;
		return solution;
	}
	else if(A.size() > A[0].size()){
		std::cout << "===================================== SLAE solution, number of rows is bigger than nunber of variables =====================================" << std::endl;
		std::cout << "========================================================== Undefined behaviour ==========================================================" << std::endl;
		return solution;
	}
	long double d0 = A.det();
	for(int i = 0; i < A.size();++i){
		Matrix tmp = A;
		for(int j = 0; j < A.size(); ++j)
			tmp[j][i] = B[j];
		long double d = tmp.det();
		solution.push_back(d / d0);
	}
	return solution;}