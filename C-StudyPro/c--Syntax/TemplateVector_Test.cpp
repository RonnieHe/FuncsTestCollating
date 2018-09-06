// TemplateVector_Test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
//
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}
#include <vector>
#include <iostream>

using namespace std;

template <typename T> void print_elem(const T& t) ///������ģ�����͵�ָ��
{
	cout << "(" << t << ") ";
}

template <typename T> void print_collection(const T& t)  ///������ģ�����͵�ָ��
{
	cout << "  " << t.size() << " elements: ";

	for (const auto& p : t) //����t�����е�ÿһ��Ԫ�أ�ʹ��ָ���ȡ���ݣ�
	{
		print_elem(p);
	}
	cout << endl;
}

int main()
{
	vector<int> v;
	for (int i = 0; i < 10; ++i) {
		v.push_back(10 + i);
	}

	cout << "vector data: " << endl;
	print_collection(v);//print all elements

	// pop_back() until it's empty, printing the last element as we go
	while (v.begin() != v.end()) {
		cout << "v.back(): "; print_elem(v.back()); cout << endl;
		v.pop_back();
	}
}
