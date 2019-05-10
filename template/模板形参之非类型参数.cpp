#include <iostream>

using namespace std;

//template <double R> //error
//template <string R> //error
//template <float R> // error
//template <char R>
 //template <short R>
// R ���Ƿ����Ͳ���,����һ������
template <int R>
void test(void)
{
	int arr[R]; // ��������ڱ�����ȷ����С
	cout << sizeof(arr) << endl;
}

// ����һ���ַ���
template <char * r>
void test2(void)
{
	//int arr[R]; // ��������ڱ�����ȷ����С
	cout << r << endl;
}

// ����һ������
template <int & r>
void test3(void)
{
	//int arr[R]; // ��������ڱ�����ȷ����С
	cout << r << endl;
}


// ����һ��ָ��
template <int * r>
void test4(void)
{
	//int arr[R]; // ��������ڱ�����ȷ����С
	cout << *r << endl;
}


// ����һ������ָ��
template <void (*ptr)()>
void test5(void)
{
	//int arr[R]; // ��������ڱ�����ȷ����С
	ptr();
}

char str2[] = "hello world";

int b = 10;


void print(void)
{
	cout << "����һ������ָ��!" << endl;
}

int main(void)
{
	// ʵ���˶�̬����,���û�ָ������
	test<10>();
	test<5>();

	// �������÷��ⲿʵ��
	//test2<"hello world">();


	//char str[] = "hello world";
	//test2<str>(); // �Ǿ�̬�洢

	test2<str2>(); 

	// �Ǿ�̬�洢
	//int a = 10;
	//test3<a>();
	test3<b>();

	test4<&b>();

	test5<print>();
	cin.get();
	return 0;
}