// OverLoad-Override-Hide.cpp : �������̨Ӧ�ó������ڵ㡣
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

	void   xfn(int i)//������xfn�ĺ���
	{
		cout<<"Derived::xfn(int i)"<<endl;

	}

	void yfn(int c) //�����˻���yfn�ĺ���
	{
		cout<<"Derived::yfn(int i)"<<endl;
	}

	void zfn() //�����˻���zfn�ĺ���

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

	//�麯�������أ����ǻ��ǿ���ͨ��ָ����ʵ�����������麯������Ȼͨ��ָ��Ҳ����
	a*ap = new c;
	ap->print(1);//int print in c
}

#else
////////////////////////////////////////////////////////////////////Test
/*
�麯��ʵ�ֶ�̬�������е��麯���ķ������Ϳ���Ϊ��������Ӧ�麯���ķ������Ϳ��Բ���ȫ��ͬ�� 
�緵�����û�ָ�룬����ķ������Ϳ����Ǹ���ķ������͵����࣬�������������ͱ�����ȫ��ͬ��
��������������������
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