#include "algAnal.h"
void startCount(){
	clock_t start = clock(); // Запись времени начала
	
	clock_t end = clock(); // Запись времени окончания
	double elapsed_time = double(end - start) / CLOCKS_PER_SEC; // Вычисление времени в секундах
}
void BigO(){
	
}