
/*
* author:xizero00
* mail:xizero00@163.com
* date:2011-08-07 20:11:24
* Handle Class Sample  �����ʾ��
*/

#ifndef SAMPLE_H   
#define SAMPLE_H   

#include <iostream>   
#include <stdexcept>   
using namespace std;




//����   
class Item_base
{
public:
    //������麯��,�������ܵظ��ƶ���   
    virtual Item_base* clone() const
    {
        return new Item_base(*this);
    }
};


//����   
class Bulk_item : public Item_base
{
    //������麯��������,�������ܵظ��ƶ���   
    virtual Bulk_item* clone() const
    {
        return new Bulk_item(*this);
    }
};

//���������   
class Sales_item : public Bulk_item
{
public:
    //Ĭ�Ϲ��캯��,������ʼ��һ�����ü�����   
    Sales_item() : p(0), use(new size_t(1)) { cout << "Sales_item�����ü�������ʼ��Ϊ1" << endl; }

    //����һ��������,�Ҹò���Ϊ�������õĹ��캯��   
    Sales_item(const Item_base&);



    //���ƹ��캯��,��Ҫע����ǣ�ÿ����һ�ξ���Ҫ�������ü���һ��   
    Sales_item(const Sales_item &i) : p(i.p), use(i.use) { ++*use; cout << "���ڲ����˸��ƹ��캯��,Sales_item���͵Ķ������ü���Ϊ:" << *use << endl; } //Ҳ��������д   
    //Sales_item( const Sales_item &i ): p( i.clone() ) , use( new size_t( 1 ) ) { ++*use; }   


    //��������,������ʱ����ж��Ƿ��ܹ��ͷ�ָ����ָ�������   
    ~Sales_item() { cout << "������������:"; decr_use(); }


    //��ֵ����������   
    Sales_item& operator= (const Sales_item&);

    //���ʲ���������   
    const Item_base* operator-> () const
    {
        if (p)
        {
            return p;
        }
        else
        {
            throw logic_error("pָ�����");
        }
    }

    //�����ò���������   
    const Item_base& operator* () const
    {
        if (p)
        {
            return *p;
        }
        else
        {//�����麯��,�������ܵظ��ƶ���   
            throw logic_error("pָ�����");
        }
    }


    //�����麯��,�������ܵظ��ƶ���   
    /*
    virtual Sales_item* clone() const
    {
    return new Sales_item( *this );
    }
    */

private:
    //����ָ��洢�����ü������Լ����ݵ�ָ��   
    Item_base *p;
    size_t *use;

    //��������   
    void decr_use()
    {
        cout << "�� dec_use���������ü���������,��ǰ����ֵΪ:" << *use - 1 << endl;
        if (--*use == 0)
        {
            delete p;
            delete use;
            cout << "�� dec_use�����м�������Ϊ0,�ͷŶ���" << endl;
        }

    }
};


//��ֵ����������,ÿ�θ��ƶ����������ü���   
Sales_item& Sales_item::operator= (const Sales_item &si)
{
    cout << "���ڲ����ำֵ����,";
    cout << "����ֵ�Ķ�������ü���Ϊ:" << *si.use;
    cout << "��������ֵ�Ķ�������ü���Ϊ:" << *use << endl;
    //������Ҫ�ر�ע��ľ��Ǵ����ƵĶ���ļ�������Ҫ��1������ֵ�Ķ�����Ҫ��1     

    //���ӱ����ƶ�������ü���   
    ++*si.use;
    cout << "����ֵ�Ķ���ĸ�ֵ֮������ü���Ϊ:" << *si.use << endl;
    //����������ֵ�Ķ�������ü�����1   
    decr_use();
    cout << " ��������ֵ�Ķ���ֵ֮������ü���Ϊ:" << *use << endl;


    //����ָ��   
    p = si.p;
    use = si.use;

    //����   
    return *this;
}


#endif //SAMPLE_H  
