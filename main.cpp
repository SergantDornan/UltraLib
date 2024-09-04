#include <iostream>
#include "algs.h"
#include "a.h"
#include "b.h"
#include "c.h"
extern void staticfunc0(int);
extern void sharedfunc0(int);
extern void staticfunc1(int);
extern void staticfunc2(int);
extern void sharedfunc1(int);
extern void sharedfunc2(int);
int main(){
	std::vector<int> v = {3,2,1};
	insert_sort(v);
	std::cout << v;
	afunc();
	bfunc();
	cfunc();
	staticfunc0(1);
	sharedfunc0(2);
	staticfunc1(3);
	staticfunc2(4);
	sharedfunc1(5);
	sharedfunc2(6);
	std::cout << "MAIN" << std::endl;
	return 0;
}
