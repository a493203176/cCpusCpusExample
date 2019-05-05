#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;


class Timer {
public:
	Timer() :m_begin(high_resolution_clock::now()) {

	}
private:
	time_point<high_resolution_clock>m_begin;

};