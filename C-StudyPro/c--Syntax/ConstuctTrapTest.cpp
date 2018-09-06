// ConstuctTrapTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}
#if 0==0
/*
* author:xizero00
* mail: xizero00@163.com
* date:2011-08-07 21:00:59
* constructor trap
*/

#include <iostream>   

using namespace std;


class Base
{
public:
    //Ĭ�Ϲ��캯��   
    Base() : d(0) {}

    //��һ�������Ĺ��캯��   
    Base(int val) : d(val) { cout << "���๹�캯��: val = " << val << endl; }
public:
    int d;
};


class Inherit : public Base
{
public:
    //Ĭ�Ϲ��캯��   
    Inherit() :Base() {}

    //��һ�������Ĺ��캯��   
    //��ִ�д˹��캯����ʱ�����û������Ӧ�Ĺ��캯��   
    //���ǣ�����ͳ�������̳�������d������û�б���ʼ�����������Ҫע�⣡   
    Inherit(int v) : Base(v + d) { cout << "���๹�캯��: v = " << v << " , d = " << d << endl; }


};


int main(int argc, char **argv)
{
    Inherit i(1);
    //call base(1) first, then herit......
    //no default construct func to be called

    /*
    ִ�н��Ϊ��

    1.���๹�캯��: val = 12382197 (�������)
    2.���๹�캯��: v = 1 , d = 12382197

    */
    return 0;
}
#elif 0==1

#include <stdio.h>
#define begin main
int begin(void)
{
    printf("Hello, World!\n");
    return 0;
}

#elif 0==2

//#include <stdio.h>
//#include <stdlib.h>
//
// _start(void) {
//    printf("Hello, World!\n");
//    exit(0);
//}
//



//#include <stdio.h>
//#include <stdlib.h>
//
// int nomain(int i, int j, int k) {
//     printf("Hello, World!\n");
//     exit(0);
// }
//

#endif