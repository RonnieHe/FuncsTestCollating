// Try_Test.cpp : 定义控制台应用程序的入口点。
//


#include <iostream>
using namespace std;



#if 0
int _tmain(int argc, _TCHAR* argv[])
{

	//////test 1
	int *pa = new int(5);
	cout << "Poniter pa: " << hex << pa << endl;//
	cout << "Pointer *pa : " << dec << *pa << endl;//
	delete pa;

	int **ppA;
	ppA = new int*[5];//int *a[5]指针数组，每一个元素都是int指针类型。。。int (*a)[5]数组指针，指向int数组的指针
	for (int i = 0; i < 5; i++)
		ppA[i] = new int[6];


	//release
	for (int i = 0; i < 5; i++)
		delete[] ppA[i];
	delete ppA;
	
	return 0;
}
///总之一句话，定义了指针一定要知道指针指向哪里
#endif 



#include <stdlib.h>
#include "stdafx.h"
#include <WCHAR.h>

#include <iostream>
using namespace std;
int add_n(int n)
{
	int ni = 200;
	static int i=100; 
	i+=n; 
	return i; 
}

/////cannot position before include
class CBB
{
public:
	int m_nVa;
};
//////////////
struct S1
{
    int i;
    char c;
}s1;

#pragma pack(push) // 将当前pack设置压栈保存
#pragma pack(1)
struct S2
{
    int i;
    char c;
}s2;
#pragma pack()
#pragma pack(pop) // 恢复先前的pack设置
/////////
int main()
{
	//////test 1
	int *pa = new int(5);
	cout << "Poniter pa: " << hex << pa << endl;//
	cout << "Pointer *pa : " << dec << *pa << endl;//
	delete pa;

	int **ppA;
	ppA = new int*[5];//int *a[5]指针数组，每一个元素都是int指针类型。。。int (*a)[5]数组指针，指向int数组的指针
	for (int i = 0; i < 5; i++)
		ppA[i] = new int[6];


	//release
	for (int i = 0; i < 5; i++)
		delete[] ppA[i];
	delete ppA;

	getchar();
#if 1
	/////////////////////convert
	const CBB b1 ;
	//b1.m_nVa = 10;//error.....cannot change const object
	//CBB b2 = const_cast <CBB>(b1);
    CBB* b2 = NULL;
        b2= const_cast <CBB *>(&b1);
	b2->m_nVa = 20;
	cout << "const_cast convert variable value:"<<b2->m_nVa << endl;
	getchar();
//////////////////////////////////////////////////////////////////////////////////
	int c[4] = { 1, 2, 3, 4 };
	int *a[4]; //指针数组.....每一个元素都是int指针类型
	int(*b)[4]; //数组指针.....指向int数组的指针

	b = &c;	//将数组c中元素赋给数组b

	for (int i = 0; i<4; i++)
	{
		a[i] = &c[i];//a的每一项必须对应地址.
	}
	//输出看下结果
	cout << *a[1] << endl; //输出2就对
	cout << (*b)[2] << endl; //输出3就对
	getchar();
/////////////////////////////////////////////////////////////////////////////////////

	char *cArr[5] = { "Hello", "Lenovo", "Welcome", "To", "C++language" };
	//char cArr[5] = { 'A','B','C','D','E'};
	char *ppa[5];
	char **ppT = NULL;
	ppT = new char*[10];///must .otherwise,it will crush

	for (int i = 0; i<5; i++)
	{
		cout << cArr[i] << endl; //输出该地址上的存储内容

		ppa[i] = cArr[i];//a的每一项必须对应地址.
		cout << ppa[i] << endl; //输出该地址上的存储内容

		ppT[i] = cArr[i];
		cout << ppT[i] << endl; //输出该地址上的存储内容
	}
	cout << ppa[1] << endl; //输出该地址上的存储内容，Lenovo

	cout << *ppa[1] << endl; //只输出首字符...等同于ppa[1][0],只取该地址的一个字节内容
	cout << *cArr[1] << endl; //只输出首字符
	getchar();
#endif 
    /////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////
	int na = add_n(3);
	cout << na<< endl;
	na = add_n(3);
	cout << na << endl;

	getchar();
    cout << "S1 sizeof=" << sizeof(s1) << ",S2 (pack(1)) sizeof=" << sizeof(s2) << endl;
    ////////////////
    char acInput[] = "abcdxyzMyNameIsHanmeimei";//,cannot run ok
    char *cInput = "abcdxyzMyNameIsHanmeimei";
    char *pcOutput = new char[100];
    
    printf("source string (from *cInput):%s\n", cInput);//cInput point to first char, output memory until \0
	getchar();

    int nTempBuffer[500] = { 0 };
	printf("Index of int array is each char's ASCII \n");
    int i = 0;
#if 1
    while ((*cInput) != '\0')///if cInput is array, *cInput is always equal to 'a'
    {
        nTempBuffer[(*cInput - '0')]++;

        if (nTempBuffer[*cInput - '0'] == 1)
        {
           // pcOutput[i++] = *cInput;
            printf("repeat char %c \n", *cInput);
            *(pcOutput + i) = *cInput;
            i++;
        }

        cInput++;//if cInput is a array,cannot run ok
    }
    pcOutput[i] = '\0';

#else
    int j = 0,k=0;
    while (acInput[j] != '\0')
    {
        nTempBuffer[(acInput[j] - '0')]++;

        if (nTempBuffer[acInput[j] - '0'] == 1)
        {
            // pcOutput[i++] = *cInput;
            printf("char %c \n", acInput[j]);
            *(pcOutput + k) = acInput[j];
            k++;
        }
        j++;
    }
    pcOutput[k] = '\0';
#endif

    printf("source string(from *cInput, is point to '\\0'):%s\n, processed(delete repeat char) string:%s\n", cInput, pcOutput);////cInput point to '\0'
	getchar();
	return 0;
}
