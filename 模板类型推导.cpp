//#include <iostream>
//
//using namespace std;
//
//template <typename T>
//void f1(T *)
//{
//	cout << typeid(T).name() << endl;
//}
//
//template <typename T,int N>// ���Ͳ���T,�����Ͳ���N
//void f2(T(&p)[N]) // ����pΪT[N]���������
//{
//	cout <<N<<","<< typeid(T).name()<<"," <<p[2]<< endl;
//}
//
//
//class S
//{
//public:
//	void f(double *) {}
//};
//
//template <typename T1, typename T2,typename T3>// 
//void f3( T1( T2::*)(T3 *)) // T2һ����һ����,���߽ṹ��
//{
//	cout << typeid(T1).name() << " " << typeid(T2).name() << " " << typeid(T3).name() << " " << endl;
//}
//
//template <int N> // �����Ͳ���N
//class X
//{
//public:
//	typedef int l; // ������һ������
//	void f(int) {}
//};
//
//template <int N> // �����Ͳ���N
//void f4(void (X<N>::* p)(typename X<N>::l))// l��ģ�������
//{
//	cout << N << " " << typeid(X<N>::l).name() << endl;
//}
//// f4�Ĳ���X<N>�ĳ�Ա����,�ú����ķ�������Ϊvoid,����һ�� X<N>::l����
//
//template <typename T> 
//void f5(T t1)
//{
//	cout << typeid(T).name() <<","<< t1 << endl;
//}
//
//
//template <typename T>
//class M
//{
//};
//
//template <typename T>
//class N : public M<T>
//{
//};
//
//template <typename T>
//void f7(M<T>)
//{
//	cout << typeid(T).name() << endl;
//}
//
//template <typename T>
//void f8(T)
//{
//	cout << typeid(T).name() << endl;
//}
//
//// ��������,����Ͳ�����س�ָ��
//template <typename T>
//void f9(T &t)
//{
//	cout << typeid(T).name() << endl;
//}
//
//
///*
//	T & t  ��ʾ���ñ���
//	T && t ��ʾ������ֵ���ò���,����,����=�ұ�
//*/
//template <typename T>
//void f10(T && t)
//{
//	cout << typeid(T).name() << endl;
//}
//
//
//template <typename T>
//void f11()
//{
//	typename T::vType t; // ��ʾT�������и�vType����
//	cout << typeid(t).name() << endl;
//}
//
//class Y
//{
//public:
//	typedef float vType;
//};
//
//
//int main(void)
//{
//
//	int **** p = 0;
//	f1(p);// ���Ƶ�Ϊint ***
//	//f1<int ***>(p); �����Զ��Ƶ�,<int ***>���Ա�ʡ��
//
//	int a[10] = {1,2,3,4};
//	char c[42] = "hello";
//	f2(a); // T���Ƶ�int, N���Ƶ�Ϊ10
//	f2(c); // T���Ƶ�char, N���Ƶ�Ϊ42
//
//	f3(&S::f);// ͨ������Ĳ���,�Զ��Ƶ�����,������
//	
//	f4(&X<10>::f);
//
//	// ����ָ��f6
//	void(*f6)(char) = &f5;// �Ƶ��ɹ�,����T�滻Ϊchar
//	f6('A');
//
//	N<int> n;
//	M<long> m1;
//	f7(n);// �Ƶ�int
//	f7(m1); // �Ƶ�long
//
//	const char * p8 = "abc";
//
//	f8(p8); // char const * 
//	f9(p8); // char const * 
//	double pp[20];
//	f8(pp); // double * 
//	f9(pp); // double [20]
//
//
//	int aa = 99;// ��ʹ��ֵ,Ҳ����ֵ
//	f10(aa); // 	int
//	f10(100); // ������ֵ 	int
//	f10(0.003);// ������ֵ 	double
//	f10("asdf");// ������ֵ 	char const [5]
//
//	f11<Y>();
//	cin.get();
//	return 0;
//}