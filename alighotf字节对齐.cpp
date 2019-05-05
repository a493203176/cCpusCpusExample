//
//#include <iostream>
//
//using std::cout;
//using std::endl;
//
// struct alignas(16) TestStruct
//{
//	char a;
//	int b;
//};
//
//int main(void)
//{
//	cout << "sizeof(char)" << sizeof(char) << endl;
//	cout << "sizeof(int)" << sizeof(int) << endl;
//	cout << "sizeof(TestStruct)" << sizeof(TestStruct) << endl;
//	
//	cout << "offset char a: " << offsetof(TestStruct,a) << endl;
//	cout << "offset char b: " << offsetof(TestStruct, b) << endl;
//	cout << "alignof(TestStruct)" << alignof(TestStruct) << endl;
//	std::cin.get();
//	return 0;
//}