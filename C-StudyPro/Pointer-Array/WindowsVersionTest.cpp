// WindowsVersionTest.cpp : 定义控制台应用程序的入口点。
//
//
#include "stdafx.h"
#include <stdio.h>
//
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}
//
#if 1 ==2
#include <windows.h>


#pragma warning (disable: 4996)
void main()
{
    DWORD dwVersion = 0;
    DWORD dwMajorVersion = 0;
    DWORD dwMinorVersion = 0;
    DWORD dwBuild = 0;

    dwVersion = GetVersion();

    // Get the Windows version.

    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

    // Get the build number.

    if (dwVersion < 0x80000000)
        dwBuild = (DWORD)(HIWORD(dwVersion));

    printf("Version is %d.%d (%d)\n",
        dwMajorVersion,
        dwMinorVersion,
        dwBuild);
}

#elif 1==3

#include <windows.h>
#include <stdio.h>

#include <VersionHelpers.h>

#pragma warning (disable: 4996)
void main()
{
    OSVERSIONINFO osvi;
    BOOL bIsWindowsXPorLater;

    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    GetVersionEx(&osvi);

    bIsWindowsXPorLater =
        ((osvi.dwMajorVersion > 5) ||
        ((osvi.dwMajorVersion == 5) && (osvi.dwMinorVersion >= 1)));

    if (bIsWindowsXPorLater)
        printf("The system meets the requirements.\n");
    else printf("The system does not meet the requirements.\n");


    if (!IsWindowsVersionOrGreater(5, 0, 1))
    {
        MessageBox(NULL, L"You need at least Windows 2000 with SP1", L"Version Not Supported", MB_OK);
    }
}
#elif 1==0

void main()
{
    char *buf = "Hello";//指向一段5字节内存地址，buf指向‘H’
    printf("The buf=%s,ponter = %p.\n", buf,buf);
    printf("The buf= %c,%c,%c \n", buf[0], buf[1], buf[2]);


    buf[0] = 'a';//指向‘a’地址，但是buf指向的内容不变
    //printf("The buf[0]= %c,ponter = %p,address=0x%x. \n", buf[0], &buf[0], &buf[0]);
    printf("The buf[0]= %c,ponter = %p\n", buf[0], &buf[0]);
    printf("The buf[0]= %c,%c,%c \n", buf[0],buf[1],buf[2]);

    printf("The buf is %s\n,ponter = %p.", buf,buf);
}
#elif 1==0
int main()
{
    const char wang[] = { "wang" };
    char *p;
    //p = wang;//error. const char*  not char*
    p =(char*) wang;
    p[2] = 'c';
    printf("p is %s\n", p);//otput: p is wang
   //ronnie 实际输出：p is wacg
    return 0;
}
#elif 1==0

    //char *s2 = s1;//error. const char*  not equal char*
    int main() {
        const char* s1 = "test"; // 在只读数据区（objdump -h test后的.rodata区）开辟5字节存储"test",并用s1指向首字符‘t’。 
        //char *s2 = s1; // s2也指向只读数据区中“test”的首字符't'。 
        char *s2 =(char*) s1;
        s2 = "It's modified!"; // 在只读数据区开辟15字节存储"It's modified!"，并将s2由指向't'转而指向"It's modified!"的首字符'I'。 
        printf("s1=%s\n,s2=%s", s1,s2); // 从s1所指的‘t’开始输出字符串"test"。 

        //ronnie实际输出：s1=test,s2=It's modified!
    }
#elif 1==0
#include<stdio.h>
int main() {
    int a = 3;
    char s1[] = "test";
    int b = 4;
    char s2[] = "test2";
    printf("the address of a is %u\n", &a);
    printf("s1 is %u\n", s1);
    printf("the address of s1 is %u\n", &s1);
    printf("the address of b is %u\n", &b);
    printf("s2 is %u\n", s2);
    printf("the address of s2 is %u\n", &s2);
}
#elif 1==0

int main()
{
    char buf[4];
    printf("buf[0]address is:0x%x\nbuf[1]address is:0x%x\nbuf[2]address is:0x%x\nbuf[3]address is:0x%x\nbuf[4]address is:0x%x\n", \
        &buf[0], &buf[1], &buf[2], &buf[3], &buf[4]);
    const int a = 0;
    printf("a address is:0x%x\n",&a);

    buf[4] =  97;///overflow buff, and the address is variable a   . so variable a changed by address.

    printf("buf[0]address is:0x%x\nbuf[1]address is:0x%x\nbuf[2]address is:0x%x\nbuf[3]address is:0x%x\nbuf[4]address is:0x%x\n", \
        &buf[0], &buf[1], &buf[2], &buf[3], &buf[4]);

    printf("the a is %d\n", a);//ronnie test: 0
    //可以知道buf[4]的地址和int a的地址是一样，那么buf[4]实际上就是访问了const int a；
    //那么对buf[4]的修改，自然也修改了const int a的空间，这也是为什么我们在最后打印a的值的时候看到了97这个结果。
}
#elif 1==0
int main()
{
    char *arr[5] = { "red", "white", "blue", "dark", "LongLongLongLongLongLongLongLongLongLong-green" };
    //指针数组，每一元素都是指针，指向一段内存，指针+-，都是指向数组下一个元素首地址
    //arr 类型 char *[]
    printf("arr[0]=%s ,\*(arr[0]+1)= %c, arr[1]+1=%s \n",arr[0],*(arr[0]+1),arr[1]+1);
    printf("arr[0] address=%x,arr[1] adress=%p \n  arr[2] address=%x,arr[3] adress=%p \n \
           arr[4] address=%x,arr[5] adress=%p \n",\
        arr[0], arr[1], arr[2], arr[3],  arr[4], arr[5]);

    char m[2][5] = { "xxx", "yyyy" };
    char(*ptr)[5] = m;//定义数组指针，该指针指向一个5维数组，指针+-，指向下一个5维数组。
    //ptr 类型char (*)[5]

    printf("ptr[0] x=%x, ptr s=%s, ptr[0] s=%s,,ptr[1] s=%s, \n \
                      ptr[0]+2 x=%x, ptr[0]+1 s=%s \n", ptr[0], ptr, ptr[0], ptr[1], ptr[0] + 2, ptr[0] + 1);

    printf("sizeof(arr) (not 4+6+5+5+6)=%d  (why 20), sizeof(m)=%d\n", sizeof(arr), sizeof(m));//5*6-2-1
    printf("sizeof 计算是类型的大小，arr 其实是5 * sizeof(char *[]),指针是4byte，无论每一个字符长度是多少，sizeof结果都是20");
    return 0;
}
#elif 1==1
#include <string.h>
#include <stdlib.h>
int compare_int(void const *a, void const *b)
{
    if (*(int *)a == *(int *)b)
        return 0;
    else
        return 1;
}
int compare_char(void const *a, void const *b)
{
    if (strcmp((char *)a, (char *)b) == 0)
        return 0;
    else
        return 1;
}
void Compare(void const *a, void const *b, int(*compare)(void const *, void const *))
{
    if (compare(a, b) == 0)
        printf("they are equal\n");
    else
        printf("not equal\n");
}
int main(void)
{
    int m = 4, n = 5;
    Compare(&m, &n, compare_int);
    char a[4] = "abc", b[4] = "abc";
    Compare(a, b, compare_char);



    int aA = 3, bB = 4;
    int *pa = NULL, *pb = NULL, *ptem = NULL;
    pa = &aA;
    pb = &bB;
    
    printf("a=%d,b=%d,*pa=%d,*pb=%d,pa=%d,pb=%d \n", aA, bB, *pa, *pb, pa, pb);


    if (1 == 0)    /// change address
    {    
        ptem = pa;
        pa = pb;
        pb = ptem;

        printf("a=%d,b=%d,*pa=%d,*pb=%d,pa=%p,pb=%p \n", aA, bB, *pa, *pb, pa, pb);//a/b not change, but *pa/*pb changed
    }
    else    /// change variable value
    {
        int tem = 0;
        tem = *pa;
       *pa = *pb;
        *pb = tem;

        printf("a=%d,b=%d,*pa=%d,*pb=%d,pa=%d,pb=%d \n", aA, bB, *pa, *pb, pa, pb);//change a/b,
    }

}
/*
使用以上技巧的函数被称为回调函数(callback function)。
用户将一个函数指针作为参数传递给其它函数，后者将“回调”用户的函数。
分别为比较整型与字符串编写不同的比较函数compar_int(void const *,void const *)和compar_char(void const *,void const *)，
通过向Compare(const void *,const void *,int (*compare)(void const *, void const *))传递不同的函数指针，
通过同一接口实现对不同类型数据的比较。

*/
#endif