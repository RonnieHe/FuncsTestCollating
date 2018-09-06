
/*
* author:xizero00
* mail:xizero00@163.com
* date:2011-08-07 20:11:24
* Handle Class Sample  句柄类示例
*/

#ifndef SAMPLE_H   
#define SAMPLE_H   

#include <iostream>   
#include <stdexcept>   
using namespace std;




//基类   
class Item_base
{
public:
    //基类的虚函数,用于智能地复制对象   
    virtual Item_base* clone() const
    {
        return new Item_base(*this);
    }
};


//子类   
class Bulk_item : public Item_base
{
    //子类的虚函数的重载,用于智能地复制对象   
    virtual Bulk_item* clone() const
    {
        return new Bulk_item(*this);
    }
};

//子类的子类   
class Sales_item : public Bulk_item
{
public:
    //默认构造函数,用来初始化一个引用计数器   
    Sales_item() : p(0), use(new size_t(1)) { cout << "Sales_item的引用计数器初始化为1" << endl; }

    //带有一个参数的,且该参数为基类引用的构造函数   
    Sales_item(const Item_base&);



    //复制构造函数,需要注意的是，每复制一次就需要增加引用计数一次   
    Sales_item(const Sales_item &i) : p(i.p), use(i.use) { ++*use; cout << "由于采用了复制构造函数,Sales_item类型的对象引用计数为:" << *use << endl; } //也可以这样写   
    //Sales_item( const Sales_item &i ): p( i.clone() ) , use( new size_t( 1 ) ) { ++*use; }   


    //析构函数,析构的时候会判断是否能够释放指针所指向的数据   
    ~Sales_item() { cout << "在析构函数中:"; decr_use(); }


    //赋值操作符重载   
    Sales_item& operator= (const Sales_item&);

    //访问操作符重载   
    const Item_base* operator-> () const
    {
        if (p)
        {
            return p;
        }
        else
        {
            throw logic_error("p指针错误");
        }
    }

    //解引用操作符重载   
    const Item_base& operator* () const
    {
        if (p)
        {
            return *p;
        }
        else
        {//重载虚函数,用于智能地复制对象   
            throw logic_error("p指针错误");
        }
    }


    //重载虚函数,用于智能地复制对象   
    /*
    virtual Sales_item* clone() const
    {
    return new Sales_item( *this );
    }
    */

private:
    //两个指针存储着引用计数器以及数据的指针   
    Item_base *p;
    size_t *use;

    //减少引用   
    void decr_use()
    {
        cout << "在 dec_use函数中引用计数减少了,当前计数值为:" << *use - 1 << endl;
        if (--*use == 0)
        {
            delete p;
            delete use;
            cout << "在 dec_use函数中计数器减为0,释放对象" << endl;
        }

    }
};


//赋值操作符重载,每次复制都会增加引用计数   
Sales_item& Sales_item::operator= (const Sales_item &si)
{
    cout << "由于采用类赋值操作,";
    cout << "被赋值的对象的引用计数为:" << *si.use;
    cout << "即将被赋值的对象的引用计数为:" << *use << endl;
    //这里需要特别注意的就是待复制的对象的计数器需要加1而被赋值的对象需要减1     

    //增加被复制对象的引用计数   
    ++*si.use;
    cout << "被赋值的对象的赋值之后的引用计数为:" << *si.use << endl;
    //将即将被赋值的对象的引用计数减1   
    decr_use();
    cout << " 即将被赋值的对象赋值之后的引用计数为:" << *use << endl;


    //复制指针   
    p = si.p;
    use = si.use;

    //返回   
    return *this;
}


#endif //SAMPLE_H  
