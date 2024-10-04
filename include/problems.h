#ifndef problems
#define problems
#include <algs.h>
#include <filework.h>
#include <math.h>


//Дан массив целых чисел, назовем отрезов k-хорошим, если в нем не более k различных чисел
//Найти длину наиболее длинного k-хорошего отрезка
int MaxKgoodsize(std::vector<long>&, long unsigned int);

 
/*Хакатон идет 24 часа. Если он начинается в 18:00:00, то последняя секунда, в
   которую можно отправить решение это 17:59:59 следуюшего дня
   Цель - взломать наибольшее количество серверов 
 За каждый взломанный сервер начисляется 1 балл, и также штрафное время в минутах,
 округленное в меньшую сторону, прошедшее с начала хакатона

 Если было несколько попыток взломать сервер, то за каждую неудчаную попытку
 начисляется 20 минут штрафного времени

 Если было несколько попыток, но сервер так и не взломали, то штрафное время не начисляется

 в ходе соревнований команды могут отправлять PING запросы к серверу, которые никак не учитываются

 Побеждает команда, которая взломала наибольшее количество серверов, если таких несколько, то побеждает с наименьшим
 штрафным временем

 Написать программу, которая выводит результаты хакатона
 В первой строке дано время начала хакатона hh::mm::ss, во второй строке число N - количество запросов
 далее n строк:
 в начале строки - название команды в двойных кавычках
 через пробел дано время запроса в том же формате
 далее - заглавная латинская буква - идентификатор сервера
 далее - результат - ACCESSED - взломан, DENIED, FORBIDDEN - не взломан, PONG- ответ на PING


 Вывод:
 вывести на каждую команду по строке, строки отсортированы по результату, 
 если у кого то результат одинаковый - то в алфавитном порядке
 В начале строки - место команды, затем - название команды в двойных кавычках, через пробел два числа - количество
 взломаных серверов и штрафное время

  */ 

void HackatonTime();



//дан отсортированный массив, найти количество пар чисел, у которых среднее арифметическое тоже в массиве
std::vector<std::pair<int,int>> sortVmiddleNumber(std::vector<int>&);


//Дан массив из нулей и единиц, найти позицию 0 такого, что расстояние от него до близжайшей единицы будет максимальным
void onesandzerosMaxMindistance(std::string,std::string);
#endif