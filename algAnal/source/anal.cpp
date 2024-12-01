#include <anal.h>
#include <math.h>
void points(){
	std::map<long double,long double> mp;
	std::string file = workingFolder + "analFile";
	std::string cmd1 = "touch " + file;
	system(cmd1.c_str());
	std::string cmd = "./" + prog + " " + file;
	std::vector<int> testV;
	fillVector(testV,Range<int>({0,1000}),10000);
	writeVectors(testV,file);
	auto testOld = std::chrono::steady_clock::now();
	system(cmd.c_str());
	auto testDur = std::chrono::steady_clock::now() - testOld;
	double testTime = double(duration_cast<std::chrono::microseconds>(testDur).count())/100;
	// 1000 - (10000,20000)
	// 100 - (40000,50000)
	int n;
	int delta;
	if(testTime < 1000){
		delta = 20000;
		n = 50000;
	}
	else{
		delta = 10000;
		n = 10000;
	}
	for(int xi = n; xi <= n + delta; xi += 500){
		std::vector<int> v;
		fillVector(v,Range<int>({0,1000}),xi);
		writeVectors(v,file);
		auto old = std::chrono::steady_clock::now();
		int code = system(cmd.c_str());
		auto dur = std::chrono::steady_clock::now() - old;
		if(code != 0){
				std::cout << "==================== ERROR ====================" << std::endl;
				std::cout << "main returned code is " << code << std::endl;
		}
		long double elapsed_time = double(duration_cast<std::chrono::microseconds>(dur).count())/100;
		//elapsed_time -= Delta_time;
		if(elapsed_time > 0)
			mp.emplace(log(xi),log(elapsed_time));
	}
	std::string cmd2 = "rm " + file;
	system(cmd2.c_str());
	auto F = powerAp(mp,1);
	std::cout << F[0] << std::endl;
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

int main(int argc, char* argv[]){
	bool output = false;
	auto old = std::chrono::steady_clock::now();
	if(argc >= 2){
		std::string s = "output";
		if(argv[1] == s){
			output = true;
		}
	}
	std::thread time_controller(time_control);
	time_controller.detach();
	points();
	return 0;
}