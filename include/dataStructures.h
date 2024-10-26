#ifndef dataStructuresH
#define dataStructuresH
#include <header.h>
template <class T>
class binHeap{
public:
	std::vector<T> vector;
	binHeap(std::vector<T> v){
		vector = v;
		buildHeap();
	}
	binHeap(binHeap<T>& bh){
		vector = bh.vector;
	}
	binHeap<T>& operator=(std::vector<T> v){
		vector = v;
		buildHeap();
		return *this;
	}
	T operator [](int i){
		return vector[i];
	}
	void heapify(int x){
		int i = x + 1;
		int l = left(i);
		int r = right(i);
		int largest = 0;
		if(l <= size() && vector[l-1] > vector[i-1])
			largest = l;
		else
			largest = i;
		if(r <= size() && vector[r-1] > vector[largest-1])
			largest = r;
		if(largest != i){
			swap(vector[i-1],vector[largest-1]);
			heapify(largest-1);
		}
	} // O(lgn)
	void buildHeap(){
		for(int i = size() / 2; i >= 0; --i)
			heapify(i);
	}// O(n)
	int parent(int i){
		return i/2;
	}
	int left(int i){
		return 2*i;
	}
	int right(int i){
		return 2*i + 1;
	}
	int size(){
		return vector.size();
	}
	std::string toString(int i = 1,const std::string prefix = ""){
		std::string s = "";
		if (i-1 >= size()){
   			return s;
		}
  		if (i == 1) {
    		s += "─────";
  		} else {
    		s+= (prefix +
     		 ((i % 2 == 0) ? "L├────" : "R└───"));
  		}
  		s += (std::to_string(vector[i-1]) + "\n");
  		s += toString(2*i, prefix + ((i % 2 == 0) ? " │   " : "    "));
  		s += toString(2*i+1,prefix + ((i % 2 == 0) ? " │   " : "    "));
  		return s;
	}
	void print(){
		std::cout << vector << std::endl;
	}
};  //Структура данных, представляющая собой бинарное дерево, но внутри хранится вектор.
// Первый элемент ветора возьмем под индексом 1, у i элемента вектора есть левый и правый
// элемент (как в дереве) под индексами 2i(л) и 2i+1(п)
// основное свойство - родительский элемент >= каждому из дочерних элементов
template<class T>
std::ostream& operator << (std::ostream& out, binHeap<T> bh){
	out << bh.toString() << std::endl;
	return out;
}

#endif