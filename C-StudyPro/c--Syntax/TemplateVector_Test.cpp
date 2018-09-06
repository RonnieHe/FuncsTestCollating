// TemplateVector_Test.cpp : 定义控制台应用程序的入口点。
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

template <typename T> void print_elem(const T& t) ///参数是模板类型的指针
{
	cout << "(" << t << ") ";
}

template <typename T> void print_collection(const T& t)  ///参数是模板类型的指针
{
	cout << "  " << t.size() << " elements: ";

	for (const auto& p : t) //对于t类型中的每一个元素（使用指针获取内容）
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
