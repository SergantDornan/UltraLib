#include <analysis.h>
#include <math.h>
void points(std::map<double,long double>& mp, int left, int right, std::string file){
	for(double xi = left; xi <= right; ++xi){
		std::vector<int> v;
		fillVector(v,0,1,xi);
		writeVectors(v,file);
		char** str = new char*[3];
		str[0] = const_cast<char*>("anal");
		str[1] = const_cast<char*>(file.c_str());
		str[2] = const_cast<char*>(file.c_str());
		auto old = std::chrono::steady_clock::now();
		mainfunc(3, str);
		auto dur = std::chrono::steady_clock::now() - old;
		delete[] str;
		long double elapsed_time = double(duration_cast<std::chrono::microseconds>(dur).count()) / 1000;
		mp.emplace(xi,elapsed_time);
	}
}

std::mutex mtx;

void Iteration(std::map<int,int>& counts, bool output){
	std::map<double,long double> mp;
	std::stringstream stream;
	std::string s;
	stream << std::this_thread::get_id();
	stream >> s;
	std::string file = workingFolder + "analFile" + s;
	std::string cmd1 = "touch " + file;
	system(cmd1.c_str());
	points(mp,n,N,file);
	std::string cmd2 = "rm " + file;
	system(cmd2.c_str());
	// for(double xi = n+1; xi <= N; ++xi){
	// 	double mid = xi-0.5;
	// 	mp.emplace(mid, (mp[xi-1] + mp[xi]) / 2);
	// 	mp.emplace(mid - 0.25, (mp[mid] + mp[xi-1]) / 2);
	// 	mp.emplace(mid + 0.25, (mp[mid] + mp[xi]) / 2);
	// }
	std::vector<long double> res, frac, fracfinal;
	int k = -1;
	
	long double maximal = -10000;
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
	// bool output = false;
	// auto old = std::chrono::steady_clock::now();
	// double iterations = defaultIterations-1;
	
	// if(argc >= 2){
	// 	std::string s = "output";
	// 	if(argv[1] == s){
	// 		output = true;
	// 	}
	// }
	// if(output){
	// 	std::cout << '\n';
	// 	std::cout << '\n';
	// 	std::cout << "====== Number of threads: " << iterations << " =========" << std::endl;
	// 	std::cout << '\n';
	// 	std::cout << '\n';
	// }
	// std::map<int,int> counts;
	// std::vector<std::thread> threads;
	// std::thread time_controller(time_control);
	// time_controller.detach();
	// for(int i = 0; i < iterations; ++i)
	// 	threads.push_back(std::thread(Iteration, std::ref(counts),output));
	// for(int i = 0; i < threads.size(); ++i)
	// 	threads[i].join();
	// if(output)
	// 	std::cout << counts << std::endl;
	// double maximal = -1;
	// int answer = -1;
	// for(auto el : counts){
	// 	if(el.second > maximal){
	// 		maximal = el.second;
	// 		answer = el.first;
	// 	}
	// }
	
	// auto dur = std::chrono::steady_clock::now() - old;
	// long double time = double(duration_cast<std::chrono::milliseconds>(dur).count()) / 1000;
	// if(output){
	// 	std::cout << '\n';
	// 	std::cout << "=========== Analysis time: " << time << " seconds ===============" << std::endl; 
	// 	std::cout << '\n';
	// 	std::cout << "================ Accuracy: " << (maximal / iterations) << " =====================" << std::endl;
	// }
	// std::cout << '\n';
	// std::cout << "================== COMPLEXITY: O(n^" <<  answer << ") =====================" << std::endl;
	// std::cout << '\n';
	return 0;
}