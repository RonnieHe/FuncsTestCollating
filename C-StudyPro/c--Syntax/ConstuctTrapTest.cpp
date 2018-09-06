// ConstuctTrapTest.cpp : 定义控制台应用程序的入口点。
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
    //默认构造函数   
    Base() : d(0) {}

    //带一个参数的构造函数   
    Base(int val) : d(val) { cout << "基类构造函数: val = " << val << endl; }
public:
    int d;
};


class Inherit : public Base
{
public:
    //默认构造函数   
    Inherit() :Base() {}

    //带一个参数的构造函数   
    //在执行此构造函数的时候会调用基类的相应的构造函数   
    //但是，问题就出在这个继承下来的d，它并没有被初始化，这里必须要注意！   
    Inherit(int v) : Base(v + d) { cout << "子类构造函数: v = " << v << " , d = " << d << endl; }


};


int main(int argc, char **argv)
{
    Inherit i(1);
    //call base(1) first, then herit......
    //no default construct func to be called

    /*
    执行结果为：

    1.基类构造函数: val = 12382197 (随机数字)
    2.子类构造函数: v = 1 , d = 12382197

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