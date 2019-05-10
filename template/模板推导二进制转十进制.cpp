#include <iostream>

using namespace std;

// Ö÷Ä£°å
template <unsigned long N>
struct BinToDec
{
	static const unsigned val = BinToDec<N / 10>::val * 2 + N % 10;
};

template<>
struct BinToDec<0>
{
	static const unsigned val = 0;
};


int main(void)
{
	cout << BinToDec<100>::val << endl;
	cin.get();
	return 0;
}