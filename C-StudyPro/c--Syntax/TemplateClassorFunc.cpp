// TemplateClassorFunc.cpp : �������̨Ӧ�ó������ڵ㡣
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

//���庯��ģ��
template <typename T>  void printArray(const T* const array, int count)
{
    for (int i = 0; i<count; i++)
    {
        cout << array[i] << " ";

    }
    cout << endl;
}//����ģ�嶨�����

int _tmain(int argc, _TCHAR* argv[])
{
    const int ACOUNT = 5;
    const int BCOUNT = 7;
    const int CCOUNT = 6;

    int a[ACOUNT] = { 1, 2, 3, 4, 5 };
    double b[BCOUNT] = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7 };
    char c[CCOUNT] = "HELLO";

    //ͨ������printArray���ÿ������
    //��������ʹ���������ؽ��������ҵ����������������Ϊƥ���printArray��������
    cout << "Array a contains:" << endl;
    printArray(a, ACOUNT);   //��int*���͵ĵ�һ��ʵ��a����

    cout << "Array b contains:" << endl;
    printArray(b, BCOUNT);   //��double*���͵ĵ�һ��ʵ��b����

    cout << "Array c contains:" << endl;
    printArray(c, CCOUNT);   //��char*���͵ĵ�һ��ʵ��c����

    cout << endl;
    system("pause");
    return 0;
}
#elif 1==1


#include <iostream>
using namespace std;

#include "stackTest.h"   //ջ��ģ�嶨��

int _tmain(int argc, _TCHAR* argv[])
{
    stack<double> doubleStack(5);   //ʵ����һ����СΪ5��doubleStack����
    double doubleValue = 1.1;

    cout << "Pushing elements onto doubleStack\n";

    while (doubleStack.push(doubleValue))   //��doubleֵ1.1,2.2,3.3,4.4��5.5ѹ��doubleStack��
    {
        cout << doubleValue << ' ';
        doubleValue += 1.1;
    }

    cout << "\nStack is full.Cannot push " << doubleValue
        << "\n\nPoping elements from doubleStack\n";


    //pop elements from doubleStack
    //��һ��whileѭ���е���pop�������Ӷ�ջ��������5��ֵ
    while (doubleStack.pop(doubleValue))
    {
        cout << doubleValue << ' ';
    }

    cout << "\nStack is empty,Cannot pop\n";

    stack<int> intStack;   //ʵ������������ջintStack������û��ָ����С��������Ĵ�С����Ĭ�Ϲ��캯��������Ϊ10
    int intValue = 1;
    cout << "\nPushing elements onto intStack\n";

    //ѭ������push��������һЩֵѹ��intStack�У�ֱ��ջ��
    while (intStack.push(intValue))
    {
        cout << intValue++ << ' ';
    }

    cout << "\nStack is full.Cannot push " << intValue
        << "\n\nPoping elements from intStack\n";

    //����pop����������Щֵ��intStack�����ߣ�ֱ��ջ�ա�
    while (intStack.pop(intValue))
    {
        cout << intValue << ' ';
    }
    cout << "\nStack is empty.Cannot pop" << endl;
    system("pause");
    return 0;
}


#endif