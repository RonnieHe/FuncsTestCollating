// MemoryAnalysisTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}

/*
程序内存根据使用情况大致分为:
Free - 没有被使用的
Image - 加载到内存的模块(dll,exe等)
MappedFile - 内存映射文件
unclassified - 实际上应该是堆(heap)
Stack - 堆栈
TEB - 线程环境块(thread environment block)
PEB - 进程环境块(process environment block)

内存根据使用类型又可以分为:
MEM_IMAGE  - 加载到内存的模块(dll, exe等)
MEM_MAPPED - 内存映射
MEM_PRIVATE - 私有(stack, heap, teb, peb等)

内存根据使用状态又可分为:
MEM_FREE - 空闲
MEM_COMMIT - 已经提交
MEM_RESERVE - 保留

根据页面属性又可分为只读，可读写，可执行，写时拷贝等。

最常接触的内存应该是: Module(Image), Heap, Stack


////////////
taskmgr.exe模块在内存中分为4块，
第一块是只读的, 实际上是PE文件头；
第二块是可执行的，实际上就是代码节（.text）;
第三块是可读写的,实际上数据节(.Data)； 
最后一块也是只读的,实际上资源节(.rsrc)。


*/



//全局变量和静态变量会被编译到可执行文件的数据节(分只读和可读写)中, 非静态的局部变量则分配在堆栈(stack)上，而new(malloc)出来的内存则分配在堆(heap)上。
/*
地址 400000 - 401000 : PE文件头，属性是只读
地址 401000 - 41d000 : .text, 属性是只读可执行，表示代码节
地址 41d000 -  422000 : .rdata, 属性是只读， 表示只读数据
地址 422000 -  426000 : .data, 属性是写入时拷贝，表示可读写数据
地址 426000 - 427000 : .rsrc, 属性是只读，表示资源节

*/
#include <iostream>

using namespace  std;



const char* global_const_string = "hello world \n";

int global_int = 20;

static int global_static_int = 30;


int main()

{

    static int local_static_int = 100;

    int local_int = 200;

    int* pValue = new int(300);



    cout << global_const_string << global_int

        << global_static_int << local_static_int

        << local_int << *pValue;


    delete pValue;


    system("pause");


    return 0;

}
