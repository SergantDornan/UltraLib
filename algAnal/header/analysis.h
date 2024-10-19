#ifndef anal_H
#define anal_H
#include <chrono>
#include <thread>
#include <mutex>
#include <algs.h>
#include <filework.h>
#include <sstream>
const int n = 1000;
const int N = 3000;
extern "C" int mainfunc(int args, char* argv[]);
extern "C" int entry(int argc, char* argv[]);
const int defaultIterations = std::thread::hardware_concurrency();
const std::string workingFolder = "/home/andrew/MasterFolder/UBERMENSCHENAMOGUS228/algAnal/";
const std::string analFile = workingFolder + "analFile";
#endif