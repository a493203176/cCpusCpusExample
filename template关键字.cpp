//#include <iostream>
//
//using namespace std;
//
//template <typename T>
//class A
//{
//public:
//	// ���߱�����T::iterator ��һ������
//	typename T::iterator * iter;//������typename,��Ȼ����
//};
//
//class B
//{
//public:
//	typedef int iterator; // ��Ƕ����
//};
//
//int main()
//{
//	// ģ����
//	A<B> a;
//
//	cout << typeid(a.iter).name() << endl;
//
//	//cout<< typeid(a.iter).name()
//
//	cin.get();
//	return 0;
//}