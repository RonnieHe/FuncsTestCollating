// VirtualFuncList_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
//////////////////////////////////////////////////////
struct A
{
	char t : 4;
	char k : 4;
	unsigned short i : 8;
	unsigned long m;
};
//////////////////
int add_n(int n)
{
	//static int i = 100;
	int i = 100;
	i += n;
	return i;//文章说，static会保持上次值，去掉static，但是却发现并没有影响？？？
}
////////////////
union Union_a {
	int a_int1;
	double a_double;
	int a_int2;
};

typedef struct
{
	Union_a a1;
	char y;
} Struct_b;

class Class_c
{
	double c_double;
	Struct_b b1;
	Union_a a2;

};
/*
short - 2
int-4
float-4
double-8
指针-4

sizeof(union)，以结构里面size最大的为union的size
*/
union U1
{
	char a[9]; //对齐大小是1，大小是9个字节
	double b; //对齐大小是8，大小是8个字节
};
union U1_Another
{
	char a[7]; //对齐大小是1，大小是9个字节
	double b; //对齐大小是8，大小是8个字节
};
/////////////////////////
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}
//
#include <iostream>
using namespace std;

class Base1 {
public:
	virtual void f() { cout << "Base1::f" << endl; }
	virtual void g() { cout << "Base1::g" << endl; }
	virtual void h() { cout << "Base1::h" << endl; }
    char cbase1;
};
class Base2 {
public:
	virtual void f() { cout << "Base2::f" << endl; }
	virtual void g() { cout << "Base2::g" << endl; }
	virtual void h() { cout << "Base2::h" << endl; }
    char nbase2;
};
class Base3 {
public:
	virtual void f() { cout << "Base3::f" << endl; }
	virtual void g() { cout << "Base3::g" << endl; }
	virtual void h() { cout << "Base3::h" << endl; }
    int nbase3;
};
class Derive : public Base1, public Base2, public Base3 {
public:
	virtual void f() { cout << "Derive::f" << endl; }
	virtual void g1() { cout << "Derive::g1" << endl; }//子类的成员函数被放到了第一个父类的表中。
    int nDerive;
};

//每个父类都有自己的虚表（所以对应每个基类，子类对象中就多一个指针所占的空间）
typedef void(*Fun)(void);

int main()
{
	Fun pFun = NULL;

	Derive d;
	int** pVtab = (int**)&d;

	//Base1's vtable
	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+0);
	pFun = (Fun)pVtab[0][0];
	pFun();

	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+1);
	pFun = (Fun)pVtab[0][1];
	pFun();

	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+2);
	pFun = (Fun)pVtab[0][2];
	pFun();

	//Derive's vtable
	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+3);
	pFun = (Fun)pVtab[0][3];
	pFun();

	//The tail of the vtable
	pFun = (Fun)pVtab[0][4];
	cout << pFun << endl;


	//Base2's vtable
	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+0);
	pFun = (Fun)pVtab[1][0];
	pFun();

	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+1);
	pFun = (Fun)pVtab[1][1];
	pFun();

	pFun = (Fun)pVtab[1][2];
	pFun();

	//The tail of the vtable
	pFun = (Fun)pVtab[1][3];
	cout << pFun << endl;



	//Base3's vtable
	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+0);
	pFun = (Fun)pVtab[2][0];
	pFun();

	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+1);
	pFun = (Fun)pVtab[2][1];
	pFun();

	pFun = (Fun)pVtab[2][2];
	pFun();

	//The tail of the vtable
	pFun = (Fun)pVtab[2][3];
	cout << pFun << endl;

////////////////////////////////////////////////test 2
	/*
	16位的系统下，
	int i = 65536;
	cout << i; // 输出0；
	int i = 65535;
	cout << i; // 输出-1；

	32位的系统下，
	int i = 65536;
	cout << i; // 输出65536；
	int i = 65535;
	cout << i; // 输出65535；
	*/

	int a = ~0, b = 65536;
	cout << "dec : " << dec << a << endl;
	//cout << showbase << uppercase;
	cout << nouppercase;
	cout << "hex a: " << hex << a << endl;//ffff ffff
	cout << "hex b: " << hex << b << endl;//0001 0000
	//16位机器，~0为ffff（65535）,65536溢出为-1
	//32位机器，~0为ffff ffff, 大于65536不变
	if (a > 65536)//不对
	{
		cout << "32 bit" << endl;
	}
	else
	{
		cout << "16 bit" << endl;
	}


	//int h1 = ~0;//会占用不少运行时间
	int h = 4294967295;//2^32-1,ffff ffff
	// h=pow(2,64);
	cout << "hex h: " << hex << h << endl;//8000 0000

	//not use if ((h + 1)> h)or (h <(h+1)),h+1=0，h=fffffffff, 0>ffffffff.....?????
	//int e = h + 1;
	//cout << "hex e: " << hex << e << endl;//32bit    =0;
	//if (e > h)//wrong ???
	if ((h + 1)> 4294967295)
	{
		cout << "64 bit" << endl;
	}
	else
	{
		cout << "32 bit" << endl;
	}

	cout << "hex h: " << hex << h << endl;//fffffffff。
	cout << "hex h+1: " << hex << (h+1) << endl;//8000 0000

	//if (0x0 > 0xffffffff)// >
	//{
	//	cout << "0x0 > 0xffffffff" << endl;
	//}
	//else
	//{
	//	cout << "0x0 < 0xffffffff" << endl;
	//}


	//////////////test 3
	//A ma; sizeof(ma)   ok
	cout << "StructA size: " << dec << sizeof(A) << endl;//=8,,,不考虑对齐，=7


	cout << "Union_a size: " << dec << sizeof(Union_a) << endl;//8
	cout << "Struct_b size: " << dec << sizeof(Struct_b) << endl;//16...not 9, because,Union align = 8,which result struct align=8,the last char need 8 byte
	cout << "Class_c size: " << dec << sizeof(Class_c) << endl;//=32

	cout << "U1 size: " << dec << sizeof(U1) << endl;//8对齐，分配>=9,实际取16byte
	cout << "U1_Another size: " << dec << sizeof(U1_Another) << endl;//8对齐，分配>=8,实际取8byte

	///////////////////
	int iTest = add_n(8);
	cout << "delete static i,return: " << dec << iTest << endl;

	return 0;
}

