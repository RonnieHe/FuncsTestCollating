
#include "stdafx.h"

#if  EnableProject==2 
/*
* author:xizero00
* mail:xizero00@163.com
* date:2011-08-07 20:11:24
*/
#include "HandleSmartPtr.h"   
int main(int argc, char **argv)
{
    //重点关注i1和i2的引用计数   
    Sales_item i1, i2;//i1和i2的引用计数分别为1   
    Sales_item i3(i1);//i1的引用计数变为2   
    Sales_item i4 = i1;//i1的引用计数变为3,因为这样还是调用的复制构造函数   
    i4 = i2; // i2的引用计数变为2   

    return 0;
}

/*
下面给出编译所需的Makefile

1.# author:xizero00
2.# mail : xizero00@163.com
3.# date:2011 - 08 - 08 00 : 51 : 25
4.install :
5.    g++ sample.cc - g - o sample
6.    ls - al sample*
7.    . / sample
8.clean :
9.    rm - f sample
10.    ls - al sample*


注意：代码是在linux下编译，您只需要将三个文件放在同一个目录，然后在当前目录打开终端，输入make，就可以查看到结果。


如果您想清理生成的文件 输入make clean即可

下面是我执行的结果：

1.Sales_item的引用计数器初始化为1
2.Sales_item的引用计数器初始化为1
3.由于采用了复制构造函数, Sales_item类型的对象引用计数为:2
4.由于采用了复制构造函数, Sales_item类型的对象引用计数为 : 3
5.由于采用类赋值操作, 被赋值的对象的引用计数为 : 1即将被赋值的对象的引用计数为 : 3
6.被赋值的对象的赋值之后的引用计数为 : 2
7.在 dec_use函数中引用计数减少了, 当前计数值为 : 2
8. 即将被赋值的对象赋值之后的引用计数为 : 2
9.在析构函数中 : 在 dec_use函数中引用计数减少了, 当前计数值为 : 1
10.在析构函数中 : 在 dec_use函数中引用计数减少了, 当前计数值为 : 1
11.在析构函数中 : 在 dec_use函数中引用计数减少了, 当前计数值为 : 0
12.在 dec_use函数中计数器减为0, 释放对象
13.在析构函数中 : 在 dec_use函数中引用计数减少了, 当前计数值为 : 0
14.在 dec_use函数中计数器减为0, 释放对象
结论：我们可以看到，句柄类能够很方便并且能够很安全地释放内存，不会导致内存的泄露

*/
#endif