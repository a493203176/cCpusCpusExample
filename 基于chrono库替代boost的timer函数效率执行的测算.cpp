#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Timer��һ�������Ķ�ʱ����,�����������ǵĺ���Ч��
class Timer {
public:
	Timer() :m_begin(high_resolution_clock::now()) {

	}
	template<typename Duration=milliseconds>
	int64_t elapsed() const {
		return duration_cast<Duration>(
			high_resolution_clock::now() - m_begin
			).count();
	}


	int64_t micro_elapsed() const {
		return elapsed<microseconds>();
	}
private:
	time_point<high_resolution_clock>m_begin;
};
// C++11 �Դ���һ��chrono�����ʱ�����
int main(void) {
	Timer t;
	for (long long i = 0; i < 1000000000; i++);
	cout << t.elapsed() << endl;
	cout << t.micro_elapsed() << endl;
	cin.get();
}