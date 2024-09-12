#include "algs.h"
int mainfunc(int param){
	for(int i = 0; i < param; ++i){
		for(int j = 0; j < param; ++j){
			int x = 1;
			x++;
			int y = 20;
			int c = (x+y)*(x+y)*(x+y)*(x+y)*(x+y)*(x+y)*(x+y)*(x+y)*(x+y);
		}
	}
	return 0;
}
int main(int argc, char* argv[]){
	return mainfunc(atoi(argv[1]));
}