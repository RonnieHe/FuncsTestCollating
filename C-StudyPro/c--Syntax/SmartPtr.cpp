// SmartPtr.cpp : 定义控制台应用程序的入口点。
//



#include "stdafx.h"
//
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}


#if EnableProject==1
/*
* author: xizero00
* mail:xizero00@163.com
* date:2011-08-07 20:19:11
* smart pointer sample
*/



#include <iostream>   
using namespace std;


//智能指针类   
class smartPtr
{
    //友元类   
    friend class HasPtr;//hasPtr can access all private and protected members or functions
private:
    //实际的指针   
    int *p;
    //引用计数   
    size_t use;
    //智能指针类的构造函数   
    smartPtr(int *ptr) : p(ptr), use(1) {}
    //析构函数   
    ~smartPtr() { delete p; }

};

//使用智能指针的类   
//使用智能指针的类一般需要  复制构造函数、赋值操作符重载、析构函数   
class HasPtr
{
private:
    smartPtr *ptr;
    int val;
public:
    //默认构造函数   
    HasPtr() : ptr(NULL), val(0) {}

    //带参数的构造函数   
    HasPtr(int *p, int v) : ptr(new smartPtr(p)), val(v) {}

    //复制构造函数   
    HasPtr(const HasPtr &h) : ptr(h.ptr), val(h.val) { ++ptr->use; }

    //赋值重载，用于对赋值操作进行监控   
    HasPtr& operator= (const HasPtr&);

    //析构函数，监控删除操作   
    ~HasPtr() { if (0 == --ptr->use) delete ptr; } // 判断是否为最后一个引用   


    //属性   
    int get_int() const
    {
        return val;
    }

    void set_int(int v)
    {
        val = v;
    }

    int* get_ptr() const
    {
        return ptr->p;
    }


    void set_ptr(int *p)
    {
        ptr->p = p;
    }


};

//赋值 操作符重载   
HasPtr& HasPtr::operator= (const HasPtr &h)
{
    ++h.ptr->use;

    if (0 == --ptr->use)
    {
        delete ptr;
    }

    ptr = h.ptr;
    val = h.val;
    return *this;
}




int main(int argc, char **argv)
{
    int *obj = new int[2]{1, 2};
    HasPtr *h1 = new HasPtr(obj, 2);
    //HasPtr *h2 = new HasPtr( obj , 1 );   
    HasPtr h3 = *h1;//引用h1其中的指向数据的指针两次   
    cout << "h1:" << *(h1->get_ptr()) << endl;
    cout << "h3:" << *(h3.get_ptr()) << endl;


    cout << "删除h1，此时剩下h3" << endl;
    //如果不用智能指针会导致obj所指向的数据被删除了，   
    //而h3中的会成为悬垂指针   
    //因为这里使用类智能指针   
    //所以不会删除obj所指向的数据的空间，所以不会出错！   
    delete h1;
    cout << "h3:" << *(h3.get_ptr()) << endl;


    //cout << "h2:" << *h2.get_ptr() << endl;   

    return 0;
}

#endif