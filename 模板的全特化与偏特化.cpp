//#include <iostream>
//
//using namespace std;
//
//// ��ģ��
//template <typename T1,typename T2>
//class A
//{
//private:
//	T1 a;
//	T2 a2;
//public:
//	void print() {
//		cout << "A(T1,T2)" << endl;
//	}
//};
//
////���ȫ�ػ�,�ṹ����ģ������һ��,��ͽ�˽�˶���
//template <>
//class A<int,float>
//{
//public:
//	void print() {
//		cout << "A<int,float>" << endl;
//	}
//	void show() {
//		cout << "show A<int,float>" << endl;
//	}
//};
//
//
//template <>
//class A<float, float>
//{
//public:
//	void print() {
//		cout << "A<float,float>" << endl;
//	}
//	void show() {
//		cout << "show A<float,float>" << endl;
//	}
//};
//
//// ����ģ��
//template<typename T1, typename T2>
//void test(T1 a, T2 b)
//{
//	cout << "test(T1,T2)" << endl;
//}
//
//// ����ȫ�ػ�
//template<>
//void test(int a, float b)
//{
//	cout << "test(int,float)" << endl;
//}
//
//
//int main()
//{
//	// ģ����
//	A<int, int> a;
//	a.print();
//	//a.show(); û�г�Ա����,������ػ�������
//
//	// ȫ�ػ�
//	A<int, float> b;
//	b.print();
//	b.show();
//
//	A<float, float> c;
//	c.print();
//	c.show();
//
//	// ģ�庯��
//	test(1, 2);
//	test(1, 1.0f);
//	test<int,float>(1, 2);
//	test<int, double>(1, 2);
//	cin.get();
//	return 0;
//}