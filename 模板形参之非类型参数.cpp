#include <iostream>

using namespace std;

//template <double R> //error
//template <string R> //error
//template <float R> // error
//template <char R>
 //template <short R>
// R 就是非类型参数,他是一个整数
template <int R>
void test(void)
{
	int arr[R]; // 数组必须在编译期确定大小
	cout << sizeof(arr) << endl;
}

// 传入一个字符串
template <char * r>
void test2(void)
{
	//int arr[R]; // 数组必须在编译期确定大小
	cout << r << endl;
}

// 传入一个引用
template <int & r>
void test3(void)
{
	//int arr[R]; // 数组必须在编译期确定大小
	cout << r << endl;
}


// 传入一个指针
template <int * r>
void test4(void)
{
	//int arr[R]; // 数组必须在编译期确定大小
	cout << *r << endl;
}


// 传入一个函数指针
template <void (*ptr)()>
void test5(void)
{
	//int arr[R]; // 数组必须在编译期确定大小
	ptr();
}

char str2[] = "hello world";

int b = 10;


void print(void)
{
	cout << "我是一个函数指针!" << endl;
}

int main(void)
{
	// 实现了动态数组,由用户指定长度
	test<10>();
	test<5>();

	// 不能引用非外部实体
	//test2<"hello world">();


	//char str[] = "hello world";
	//test2<str>(); // 非静态存储

	test2<str2>(); 

	// 非静态存储
	//int a = 10;
	//test3<a>();
	test3<b>();

	test4<&b>();

	test5<print>();
	cin.get();
	return 0;
}