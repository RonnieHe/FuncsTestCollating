// SmartPtr.cpp : �������̨Ӧ�ó������ڵ㡣
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


//����ָ����   
class smartPtr
{
    //��Ԫ��   
    friend class HasPtr;//hasPtr can access all private and protected members or functions
private:
    //ʵ�ʵ�ָ��   
    int *p;
    //���ü���   
    size_t use;
    //����ָ����Ĺ��캯��   
    smartPtr(int *ptr) : p(ptr), use(1) {}
    //��������   
    ~smartPtr() { delete p; }

};

//ʹ������ָ�����   
//ʹ������ָ�����һ����Ҫ  ���ƹ��캯������ֵ���������ء���������   
class HasPtr
{
private:
    smartPtr *ptr;
    int val;
public:
    //Ĭ�Ϲ��캯��   
    HasPtr() : ptr(NULL), val(0) {}

    //�������Ĺ��캯��   
    HasPtr(int *p, int v) : ptr(new smartPtr(p)), val(v) {}

    //���ƹ��캯��   
    HasPtr(const HasPtr &h) : ptr(h.ptr), val(h.val) { ++ptr->use; }

    //��ֵ���أ����ڶԸ�ֵ�������м��   
    HasPtr& operator= (const HasPtr&);

    //�������������ɾ������   
    ~HasPtr() { if (0 == --ptr->use) delete ptr; } // �ж��Ƿ�Ϊ���һ������   


    //����   
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

//��ֵ ����������   
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
    HasPtr h3 = *h1;//����h1���е�ָ�����ݵ�ָ������   
    cout << "h1:" << *(h1->get_ptr()) << endl;
    cout << "h3:" << *(h3.get_ptr()) << endl;


    cout << "ɾ��h1����ʱʣ��h3" << endl;
    //�����������ָ��ᵼ��obj��ָ������ݱ�ɾ���ˣ�   
    //��h3�еĻ��Ϊ����ָ��   
    //��Ϊ����ʹ��������ָ��   
    //���Բ���ɾ��obj��ָ������ݵĿռ䣬���Բ������   
    delete h1;
    cout << "h3:" << *(h3.get_ptr()) << endl;


    //cout << "h2:" << *h2.get_ptr() << endl;   

    return 0;
}

#endif