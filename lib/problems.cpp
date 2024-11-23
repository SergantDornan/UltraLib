#include <problems.h>
#include <dHeap.h>
//Дан массив целых чисел, назовем отрезов k-хорошим, если в нем не более k различных чисел
//Найти длину наиболее длинного k-хорошего отрезка
// alg power(int n){
// 	alg r(1);
// 	int i = 1;
// 	while(i <= n){
// 		if(n - i >= 1999000){
// 			r *= 247581393;
// 			i += 1999000;
// 		}
// 		else if(n - i >= 35){
// 			r *= 359738130;
// 			i+=35;
// 		}
// 		else if(n - i >= 16){
// 			r *= 65536;
// 			i += 16;
// 		}
// 		else{
// 			r *= 2;
// 			i++;
// 		}
// 	}
// 	return r;
// }


bool intersect(Rect& x, Rect& y){
	if(x.rx <= y.lx || y.rx <= x.lx)
		return false;
	if(x.ry <= y.ly || y.ry <= x.ly)
		return false;
	return true;
}
int MaxKgoodsize(std::vector<long>& v, long unsigned int k){
	if(v.size() <= k)
		return v.size();
	std::map<long,long unsigned int> mp;
	int count = 0;
	int maxcount = 0;
	for(long unsigned int i = 0; i < v.size(); ++i){
		if(mp.find(v[i]) != mp.end()){
			mp[v[i]]++;
			count++;
		}
		else{
			mp.emplace(v[i],1);
			count++;
			if(mp.size() > k){
				while(mp.size() > k){
					mp[v[i-count+1]]--;
					if(mp[v[i-count+1]] == 0){
						mp.erase(v[i-count+1]);
					}
					count--;
				}
			}
		}
		maxcount = max(count,maxcount);
	}	
	return maxcount;
}


void Btask(std::vector<std::vector<int>>& input,std::vector<std::vector<int>>& res){
	std::vector<int> r(input.size()-2,0);
	int T = input[input.size()-1][0];
	auto increaseNum = [](std::vector<int>& v, int c) -> int{
		int r = 0;
		int k = v.size()-1;
		for(int i = 1; i < v.size()-1; ++i){
			if(c < v[i]){
				k = i;
				break;
			}
		}
		r += (k-1);
		r -= (v.size()-1-k);
		return r;
	}; 
	for(int i = 1; i < input.size()-1; ++i){
		input[i].push_back(i-1);
		std::sort(input[i].begin()+1,input[i].end()-1);
		int inc = increaseNum(input[i],0); 
		input[i][0] = inc;
	} 
	input.erase(input.begin());
	input.erase(input.end()-1); 
	heap<std::vector<int>> h(input,2,
		[](std::vector<int>& x, std::vector<int>& y){return (x[0] > y[0]);}); 
	while(T > 0){
		int point = h.vector[0][h.vector[0].size()-1];
		r[point]++;
		T--;
		int inc = increaseNum(h.vector[0], r[point]); 
		h.vector[0][0] = inc;
		h.heapify(0);
	} 
	res.push_back(r);
}
// void Ctask(std::vector<std::vector<int>>& input,std::vector<std::vector<int>>& res){
// 	int n = input[0][0];
// 	alg g(0);
// 	int n0 = n-1;
// 	std::vector<i64> cv = {1};
// 	for(int i = 0; i <= n0; ++i){
// 		std::vector<i64> tmp;
// 		for(int j = 0; j <= i; ++j){
// 			if(j == 0 || j == i)
// 				tmp.push_back(1);
// 			else{
// 				tmp.push_back(alg(cv[j-1]+cv[j]).x);
// 			}
// 		}
// 		cv = tmp;
// 	}
// 	for(int k = 0; k <= n0;++k){
// 		alg tmp(1);
// 		tmp *= ((n0 - k) % 2 == 0 ? 1 : -1);
// 		tmp *= power(k*(k-1)/2);
// 		tmp *= cv[k];
// 		g += tmp;
// 	}
// 	g*=n;
// 	res.push_back(std::vector<int>{g.x});
// }
void Dtask(std::vector<std::vector<int>>& input,std::vector<std::vector<int>>& res){
	for(int i = 1; i < input.size(); ++i){
		int r = 1;
		int a = input[i][0];
		int b = input[i][1];
		std::vector<std::pair<int,int>> va = canon(a);
		std::vector<std::pair<int,int>>	vb = canon(b);
		for(int j = 0; j < va.size(); ++j){
			int ind = -1;
			for(int k = 0; k < vb.size(); ++k){
				if(vb[k].first == va[j].first){
					ind = k;
					break; 
				}
			}
			if(ind != -1){
				int power = min(va[j].second, vb[ind].second);
				r *= pow(va[j].first, power);
				va[j].second -= power;
				vb[ind].second -= power;
			}
		}
		int m = 1;
		for(int j = 0; j < va.size(); ++j){
			if(va[j].second > 0)
				m = max(m,va[j].first);
		}
		for(int j = 0; j < vb.size(); ++j){
			if(vb[j].second > 0)
				m = max(m,vb[j].first);
		}
		r *= m;
		res.push_back(std::vector<int>({r}));
	}
}
void Etask(std::vector<std::vector<int>>& input,std::vector<std::vector<int>>& res){
	class Vert{
	public:
		int x, ly, ry, type, id;
		Vert(int a, int b, int c, int d, int e){
			x = a;
			ly = b;
			ry = c;
			type = d;
			id = e;
		}
	};
	std::vector<Rect> rects;
	std::vector<Vert> verts;
	std::vector<int> intersections(input[0][0],0);
	std::vector<Rect> active;
	for(int i = 1; i < input.size(); ++i){
		int lx = input[i][0];
		int ly = input[i][1];
		int rx = input[i][2];
		int ry = input[i][3];
		Rect r(lx,rx,ly,ry,i-1);
		Vert v1(lx,ly,ry,0,i-1);
		Vert v2(rx,ly,ry,1,i-1);
		rects.push_back(r);
		verts.push_back(v1);
		verts.push_back(v2);
	}
	std::function<bool(Vert&,Vert&)> comp = [](Vert& x, Vert& y){
		return x.x < y.x;
	};
	merge_sort(verts,comp);
	for(int i = 0; i < verts.size(); ++i){
		if(verts[i].type == 0){
			Rect tmp = rects[verts[i].id];
			for(int j = 0; j < active.size(); ++j){
				if(intersect(tmp, active[j])){
					intersections[tmp.id]++;
					intersections[active[j].id]++;
				}
			}
			active.push_back(tmp);
		}
		else{
			Rect tmp = rects[verts[i].id];
			auto it = active.begin();
			while(it != active.end()){
				if(tmp.rx == (*it).rx)
					active.erase(it);
				else
					it++;
			}
		}
		// for(auto el : active)
		// 	std::cout << el.id << ' ';
		// std::cout << std::endl;
		// std::cout << intersections << std::endl;
	}
	res.push_back(intersections);
}


void onesandzerosMaxMindistance(std::string inp, std::string output){
	std::vector<std::vector<int>> input;
	readVectors(input, inp);
	std::vector<int> res;
	std::vector<int> v = input[0];
	int m = -1;
	int currk = 0;
	int curr = 0;
	int pos = 0;
	int start = 0;
	for(int i = 0; i < v.size(); ++i){
		if(v[i] == 1)
		{
			start = i;
			break;
		}
	}
	if(start > 0)
		res.push_back(0);
	m = start;
	for(int i = start; i < v.size(); ++i){
		if(v[i] == 1){
			curr = (curr / 2) + (curr % 2);
			if(curr >= m){
				if(curr > m){
					m = curr;
					res.clear();
				}
				pos = ((currk+i)/2);
				res.push_back(pos);
				if((i + currk) % 2 == 1){
					pos = ((currk+i)/2)+1;
					res.push_back(pos);	
				}
			}
			curr = 0;
			currk = i;
		}
		else if(i == v.size() - 1){
			curr++;
			if(curr >= m){
				pos = i;
				if(curr > m){
					m = curr;
					res.clear();
				}
				res.push_back(pos);
			}
		}
		else{
			curr++;
		}
	}
	writeVectors(res,output);
}