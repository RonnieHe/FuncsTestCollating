// TemplateClassorFunc.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}
//
#if 1==0
#include <iostream>
using namespace std;

//定义函数模板
template <typename T>  void printArray(const T* const array, int count)
{
    for (int i = 0; i<count; i++)
    {
        cout << array[i] << " ";

    }
    cout << endl;
}//函数模板定义结束

int _tmain(int argc, _TCHAR* argv[])
{
    const int ACOUNT = 5;
    const int BCOUNT = 7;
    const int CCOUNT = 6;

    int a[ACOUNT] = { 1, 2, 3, 4, 5 };
    double b[BCOUNT] = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7 };
    char c[CCOUNT] = "HELLO";

    //通过调用printArray输出每个数组
    //编译器会使用它的重载解析功能找到与这个函数调用最为匹配的printArray函数定义
    cout << "Array a contains:" << endl;
    printArray(a, ACOUNT);   //用int*类型的第一个实参a调用

    cout << "Array b contains:" << endl;
    printArray(b, BCOUNT);   //用double*类型的第一个实参b调用

    cout << "Array c contains:" << endl;
    printArray(c, CCOUNT);   //用char*类型的第一个实参c调用

    cout << endl;
    system("pause");
    return 0;
}
#elif 1==1


#include <iostream>
using namespace std;

#include "stackTest.h"   //栈类模板定义

int _tmain(int argc, _TCHAR* argv[])
{
    stack<double> doubleStack(5);   //实例化一个大小为5的doubleStack对象
    double doubleValue = 1.1;

    cout << "Pushing elements onto doubleStack\n";

    while (doubleStack.push(doubleValue))   //将double值1.1,2.2,3.3,4.4和5.5压入doubleStack中
    {
        cout << doubleValue << ' ';
        doubleValue += 1.1;
    }

    cout << "\nStack is full.Cannot push " << doubleValue
        << "\n\nPoping elements from doubleStack\n";


    //pop elements from doubleStack
    //在一个while循环中调用pop函数，从堆栈中移走这5个值
    while (doubleStack.pop(doubleValue))
    {
        cout << doubleValue << ' ';
    }

    cout << "\nStack is empty,Cannot pop\n";

    stack<int> intStack;   //实例化了整数堆栈intStack，由于没有指定大小，因此它的大小就是默认构造函数，这里为10
    int intValue = 1;
    cout << "\nPushing elements onto intStack\n";

    //循环调用push函数，将一些值压入intStack中，直到栈满
    while (intStack.push(intValue))
    {
        cout << intValue++ << ' ';
    }

    cout << "\nStack is full.Cannot push " << intValue
        << "\n\nPoping elements from intStack\n";

    //调用pop函数，将这些值从intStack中移走，直到栈空。
    while (intStack.pop(intValue))
    {
        cout << intValue << ' ';
    }
    cout << "\nStack is empty.Cannot pop" << endl;
    system("pause");
    return 0;
}


#endif