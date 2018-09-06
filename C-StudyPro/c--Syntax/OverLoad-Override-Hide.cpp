// OverLoad-Override-Hide.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
//
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}

////////////////////////////////////////////////////////////////////Test
#if 1
#include <iostream>

using namespace std;

class Base
{

public:
	virtual void  xfn(int i) 
	{
		cout<<"Base::xfn(int i)"<<endl;
	}

	void yfn(float f)
	{
		cout<<"Base::yfn(float f)"<<endl;
	}
	void zfn()
	{
		cout<<"Base::zfn()"<<endl;
	}

};

class Derived :public Base
{

public:

	void   xfn(int i)//覆盖了xfn的函数
	{
		cout<<"Derived::xfn(int i)"<<endl;

	}

	void yfn(int c) //隐藏了基类yfn的函数
	{
		cout<<"Derived::yfn(int i)"<<endl;
	}

	void zfn() //隐藏了基类zfn的函数

	{
		cout << "Drived::zfn()" << endl;
	}

};


int main()

{

	Derived d;

	Base* pB = &d;
	Derived* pD = &d;

	pB->xfn(5);
	pD->xfn(5);
	pB->yfn(3.14f);
	pD->yfn(3.14f);

	pB->zfn();
	pD->zfn();


	return 0;
}

/*Answer
Derived::xfn(int i)
Derived::xfn(int i)
Base::yfn(float f)
Derived::yfn(int i)
Base::zfn()
Drived::zfn()
*/

#elif 0
////////////////////////////////////////////////////////////////////Test
#include<iostream>
class a{
public:
	virtual void print(){
		std::cout << "NULL print in a" << std::endl;
	}
	virtual void print(int){
		std::cout << "int print in a" << std::endl;
	}
};
class b :public a{
public:
	virtual void print(){//can hide print(int) in a
		std::cout << "NULL print in b" << std::endl;
	}
};
class c :public b{
public:
	virtual void print(int){//can hide print() in b,a
		std::cout << "int print in c" << std::endl;
	}
};
int main(){
	b b1;
	b1.print();
	//b1.print(1);//compile error,hide
	c c1;
	c1.print(1);
	//c1.print();//compile error,hide

	//虚函数被隐藏，但是还是可以通过指针访问到，如果不是虚函数，当然通过指针也不能
	a*ap = new c;
	ap->print(1);//int print in c
}

#else
////////////////////////////////////////////////////////////////////Test
/*
虚函数实现多态，子类中的虚函数的返回类型可以为父类中相应虚函数的返回类型可以不完全相同， 
如返回引用或指针，子类的返回类型可以是父类的返回类型的子类，但函数参数类型必须完全相同，
否则会出现上面代码情况。
*/

#include <iostream>
class test{};
class test1 :public test{};
test t;
test1 t1;
class base{
public:
	virtual test& print(test1*){
		std::cout << "print in base" << std::endl;
		return t;
	}

};
class derived :public base{
public:
	test1& print(test1*){
		std::cout << "print in derived" << std::endl;
		return t1;
	}
};
int main(){
	base*b = new(std::nothrow) derived;
	b->print(new test1);//OK:   print in derived     wrong answer:   base :: print
	delete b;
	b = new (std::nothrow)base;
	b->print(new test1);//OK:   print in base     wrong answer:derived::print
	delete b;
}


#endif 