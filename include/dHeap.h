#ifndef dHeapH
#define dHeapH
template <class T>
class heap{
public:
	std::vector<T> vector;
	int d;
	heap(int x = 2){
		d = x;
	}
	heap(std::vector<T>& v, int x = 2){
		d = x;
		vector = v;
		buildHeap();
	}
	heap(heap<T>& h){
		vector = h.vector;
		d = h.d;
	}
	heap<T>& operator=(std::vector<T> v){
		vector = v;
		buildHeap();
		return *this;
	}
	T operator [](int i){
		return vector[i];
	}
	void heapify(int x){
		int i = x + 1;
		std::vector<int> childs;
		for(int j = 0; j < d; ++j)
			childs.push_back(child(i,j));
		int largest = i;
		for(int j = 0; j < childs.size(); ++j){
			if(childs[j] <= size() && vector[childs[j]-1] > vector[largest-1])
				largest = childs[j];
		}
		if(largest != i){
			swap(vector[i-1],vector[largest-1]);
			heapify(largest-1);
		}
	} // O(lgn)
	void buildHeap(){
		for(int i = size() / d; i >= 0; --i)
			heapify(i);
	}// O(n)
	int parent(int i){
		return i/d;
	}
	int child(int i, int offset){
		return d*i + offset;
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
     		 ((i % d == 0) ? "├────" : "└───"));
  		}
  		s += (std::to_string(vector[i-1]) + "\n");
  		for(int j = 0; j < d; ++j)
  			s += toString(d*i+j, prefix + ((i % d != (d-1) && i != 1) ? "│   " : "    "));
  		return s;
	}
	void print(){
		std::cout << vector << std::endl;
	}
	T extract(){
		if(vector.size() == 0){
			std::cout << "========================== ERROR ==========================" << std::endl;
			std::cout << "=========== dHeap.h: T binHeap::extract() ===========" << std::endl;
			std::cout << "========= heap size is 0, no max element ========" << std::endl;
			std::cout << "===========================================================" << std::endl;
			return T(0);
		}
		else{
			T m = vector[0];
			vector[0] = vector[vector.size()-1];
			vector.erase(vector.end()-1);
			heapify(0);
			return m;
		}
	} // O(lgn)


	T max(){
		if(vector.size() == 0){
			std::cout << "========================== ERROR ==========================" << std::endl;
			std::cout << "=========== dHeap.h: T binHeap::max() ===========" << std::endl;
			std::cout << "========= heap size is 0, no max element ========" << std::endl;
			std::cout << "===========================================================" << std::endl;
			return T(0);
		}
		else
			return vector[0];
	}
	void insert(T x){
		int i = size() + 1;
		vector.push_back(x);
		while(i > 1 && vector[parent(i) - 1] < x){
			vector[i-1]  = vector[parent(i)-1];
			i = parent(i);
		}
		vector[i-1] = x;
	} //O(lgn) 
};
template <class T>
std::ostream& operator << (std::ostream& out, heap<T> h){
	out << h.toString() << std::endl;
	return out;
}
#endif