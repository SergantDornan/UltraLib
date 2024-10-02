#include <analysis.h>
#include <math.h>
void points(std::map<double,long double>& mp, int left, int right){
	for(double xi = left; xi <= right; ++xi){
		auto old = std::chrono::steady_clock::now();
		char** str = new char*[2];
		
		str[0] = const_cast<char*>("anal");
		str[1] = const_cast<char*>(analFile.c_str());
		mainfunc(2, str);
		delete[] str;
		auto dur = std::chrono::steady_clock::now() - old;
		long double elapsed_time = double(duration_cast<std::chrono::microseconds>(dur).count()) / 1000;
		mp.emplace(xi,elapsed_time);
	}
}

std::mutex mtx;

void Iteration(std::map<int,int>& counts, bool output){
	std::map<double,long double> mp;
	points(mp,n,N);
	for(double xi = n+1; xi <= N; ++xi){
		double mid = xi-0.5;
		mp.emplace(mid, (mp[xi-1] + mp[xi]) / 2);
		mp.emplace(mid - 0.25, (mp[mid] + mp[xi-1]) / 2);
		mp.emplace(mid + 0.25, (mp[mid] + mp[xi]) / 2);
	}
	std::vector<long double> res, frac, fracfinal;
	int k = -1;
	for(int i = 0; i <= 4; ++i)
		res.push_back(powerAp(mp,i,n,N));
	long double maximal = -10000;
	for(size_t i = 0; i < res.size()-1; ++i)
		frac.push_back((res[i] - res[i+1]) / res[i]);
	for(size_t i = 0; i < frac.size()-1; ++i)
		fracfinal.push_back((frac[i] - frac[i+1]) / frac[i]);
	for(size_t i = 0; i < fracfinal.size(); ++i){
			if(fracfinal[i] > maximal){
				maximal = fracfinal[i];
				k = i + 1;
			}
		}
	if(output){
		mtx.lock();
		std::cout << "============== THREAD: " << std::this_thread::get_id() << "   =====================" << std::endl;
		std::cout << '\n';
		std::cout << res << std::endl;
		std::cout << frac << std::endl;
		std::cout << fracfinal << std::endl;
		std::cout << '\n';
		mtx.unlock();
	}
	if(counts.find(k) != counts.end()){
		counts[k]++;
	}
	else{
		counts.emplace(k,1);
	}
}

void time_control(){
	auto old = std::chrono::steady_clock::now();
	int message = 0;
	bool control = true;
	while(control){
		if(int(duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - old).count()) > 90 && message == 0){
			std::cout << "============================== It is too long =============================" << std::endl;
			std::cout << '\n';
			message++;
		}
		else if(int(duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - old).count()) > 120 && message == 1){
			std::cout << "================ Complexity is probably higher than O(n^2) ================" << std::endl;
			std::cout << "================ Abort analysis and go write better code ==================" << std::endl;
			std::cout << '\n';
			message++;
		}
		else if(int(duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - old).count()) > 150 && message == 2){
			std::cout << "================ Definitely abort analysis and go write better code =======" << std::endl;
			std::cout << "================ Complexity is probably higher than O(n^2) ================" << std::endl;
			std::cout << '\n';
			control = false;
		}
	}
}

extern "C" int entry(int argc, char* argv[]){
	bool output = false;
	auto old = std::chrono::steady_clock::now();
	double iterations = defaultIterations-1;
	
	if(argc >= 2){
		std::string s = "output";
		if(argv[1] == s){
			output = true;
		}
	}
	if(output){
		std::cout << '\n';
		std::cout << '\n';
		std::cout << "====== Number of threads: " << iterations << " =========" << std::endl;
		std::cout << '\n';
		std::cout << '\n';
	}
	std::map<int,int> counts;
	std::vector<std::thread> threads;
	std::thread time_controller(time_control);
	time_controller.detach();
	for(int i = 0; i < iterations; ++i)
		threads.push_back(std::thread(Iteration, std::ref(counts),output));
	for(int i = 0; i < threads.size(); ++i)
		threads[i].join();
	if(output)
		std::cout << counts << std::endl;
	double maximal = -1;
	int answer = -1;
	for(auto el : counts){
		if(el.second > maximal){
			maximal = el.second;
			answer = el.first;
		}
	}
	
	auto dur = std::chrono::steady_clock::now() - old;
	long double time = double(duration_cast<std::chrono::milliseconds>(dur).count()) / 1000;
	if(output){
		std::cout << '\n';
		std::cout << "=========== Analysis time: " << time << " seconds ===============" << std::endl; 
		std::cout << '\n';
		std::cout << "================ Accuracy: " << (maximal / iterations) << " =====================" << std::endl;
	}
	std::cout << '\n';
	std::cout << "================== COMPLEXITY: O(n^" <<  answer << ") =====================" << std::endl;
	std::cout << '\n';
	return 0;
}