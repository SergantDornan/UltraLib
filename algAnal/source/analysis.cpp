#include <analysis.h>
#include <math.h>
std::mutex mtx;
void points(std::map<double,long double>& mp, int left, int right, long double(*f)(long double) = [](long double x) -> long double{return x;}){
	std::stringstream stream;
	std::string s;
	stream << std::this_thread::get_id();
	stream >> s;
	std::string file = workingFolder + "analFile" + s;
	std::string cmd1 = "touch " + file;
	system(cmd1.c_str());
	for(long double xi = left; xi <= right; ++xi){
		std::vector<int> v;
		fillVector(v,Range<int>({0,10}),xi);
		writeVectors(v,file);
		char** str = new char*[3];
		str[0] = const_cast<char*>("anal");
		str[1] = const_cast<char*>(file.c_str());
		str[2] = const_cast<char*>("Dummy");
		auto old = std::chrono::steady_clock::now();
		mainfunc(3, str);
		auto dur = std::chrono::steady_clock::now() - old;
		delete[] str;
		long double elapsed_time = double(duration_cast<std::chrono::microseconds>(dur).count());
		old = std::chrono::steady_clock::now();
		std::vector<std::vector<int>> input;
		readVectors(input, file);
		dur = std::chrono::steady_clock::now() - old;
		long double Delta_time = double(duration_cast<std::chrono::microseconds>(dur).count());
		elapsed_time -= Delta_time;
		if(elapsed_time > 0)
			mp.emplace(f(xi),f(elapsed_time));
	}
	std::string cmd2 = "rm " + file;
	system(cmd2.c_str());
	// mtx.lock();
	// std::cout << "============== THREAD: " << std::this_thread::get_id() << " ==============" << std::endl;
	// std::cout << "============== THREAD finished ==============" << std::endl;
	// std::cout << "============== File " << file << " deleted ==============" << std::endl;
	// std::cout << '\n' << '\n' << std::endl;
	// mtx.unlock();
}
void foo(std::map<double,long double>& mp, int start,long double e, long double(*f)(long double) = [](long double x) -> long double{return x;}){
	std::stringstream stream;
	std::string s;
	stream << std::this_thread::get_id();
	stream >> s;
	std::string file = workingFolder + "analFile" + s;
	std::string cmd1 = "touch " + file;
	system(cmd1.c_str());
	long double prev = 100000;
	long double res = 0;
	while(abs(prev - res) > e){
		prev = res;
		std::vector<int> v;
		fillVector(v,Range<int>({0,1000}),start);
		writeVectors(v,file);
		char** str = new char*[3];
		str[0] = const_cast<char*>("anal");
		str[1] = const_cast<char*>(file.c_str());
		str[2] = const_cast<char*>("Dummy");
		auto old = std::chrono::steady_clock::now();
		mainfunc(3, str);
		auto dur = std::chrono::steady_clock::now() - old;
		delete[] str;
		long double elapsed_time = double(duration_cast<std::chrono::microseconds>(dur).count()) / 1000;
		res = log(elapsed_time) / log(start);
		std::cout << res << ' ' << prev << std::endl;
		start+=pow(10,6);
	}
	std::cout << '\n' << "=====================================================================" << std::endl;
	std::cout << res << std::endl;
	std::string cmd2 = "rm " + file;
	system(cmd2.c_str());
	
}

void Iteration(std::map<int,int>& counts, bool output){
	std::map<double,long double> mp;
	int iter;
	//iter = (defaultIterations - 1);
	iter = 1;
	int diff = (N - n)/iter;
	int start = n;
	// int startingPoint = pow(10,3);
	// long double e = pow(10,-3);
	std::vector<std::thread> threads;
	for(int i = 0; i < iter; ++i){
		//threads.push_back(std::thread(points,std::ref(mp), start, start + diff,[](long double x) -> long double{return log(x);}));
		threads.push_back(std::thread(points,std::ref(mp), start, start + diff,[](long double x) -> long double{return log(x);}));
		start+=diff;
	}
	for(int i = 0; i < threads.size(); ++i)
		threads[i].join();

	auto func = powerAp(mp, 1);
	std::cout << func << std::endl;
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
	std::thread time_controller(time_control);
	time_controller.detach();
	Iteration(counts,output);
	//threads.push_back(std::thread(Iteration, std::ref(counts),output));
	//threads[0].join();
	double maximal = -1;
	int answer = -1;
	
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