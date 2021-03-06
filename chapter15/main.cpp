#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <array>
#include <list>
#include <forward_list>
#include <queue>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <functional>

using namespace std;
//using std::placeholders::_1;//placeholders命名空间在std空间中,这种时单独定义每一个
using namespace std::placeholders;//这样直接定义了所有的
//使用 ! 表示重要程度,! 越多越重要
//便于查看输出结果的分割显示函数
void pIndexofTest(int i){
    cout << endl
         << endl
         << "Test Rounds "
         << i
         << endl
         << "--------------------------------------------"
         << endl;
}

template <typename T>
void print(T& t){
    for(auto a : t)
        cout << a << " ";
    cout << endl;
}



class Quote{
public:
    Quote() = default;
    Quote(const std::string &book, double sale_price):
            bookNo(book), price(sale_price){}

    virtual ~Quote() = default;

    std::string isbn() const { return bookNo;}
    virtual double net_price(std::size_t n) const;
    virtual void debug()const {
        std::cout << price << bookNo << endl;
    }

protected:
    double price = 0.0;

private:
    std::string bookNo;
};

double Quote::net_price(std::size_t n) const {
    return n * price;
}


class Bulk_quote : public Quote{
public:
    Bulk_quote() = default;
    //遵循基类的接口，虽然可以直接初始化基类非private的成员，但最好不要这么做
    Bulk_quote(const std::string &book, double p, std::size_t qty, double disc):
            Quote(book, p), min_qty(qty), discount(disc){}

    double net_price(std::size_t) const override ;

//    !!! 回避虚函数机制（练习15.11）
    void debug()const override {
        Quote::debug();    // bookNo 是 private 的所以不能直接访问bookNo只能调用基类的debug函数来实现
        std::cout << min_qty << discount << endl;
    }

private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};

double Bulk_quote::net_price(std::size_t cnt) const {
    if(cnt >= min_qty)
        return (1 - discount) * price * cnt;
    else
        return cnt * price;
}


//多态, 也称为运行时绑定
double print_total(ostream &os, const Quote &item, size_t n){
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
}

class Base_1{
public:
    Base_1(){i = 10;};
    Base_1(int n, int i = 7):n(n), i(i){}

    int n, i;
};

class Orented_1:public Base_1{
public:
    Orented_1() = default;

    Orented_1(const string &s) : s(s) {}

    std::string s;
};

class Base_2{
public:
    static int sti;
    static void p(){
        cout << Base_2::sti << endl;
    }
};

class Derived_2 : public Base_2{
public:
    void f(const Derived_2 & obj){
        Base_2::p();
        Derived_2::p();
        obj.p();
        p();
    }
};

//注意static的初始化
int Base_2::sti = 10;

// ！！防止继承
class NoDerived final{};//NoDerived 不能作为基类
class Last final : public Base_1{}; // Last不能作为基类6

// final override 关键字的使用
struct B{
    virtual void f1(int) const ;
    virtual void f2();
    void f3();
};
struct D1 : B{
    void f1(int) const override ;
//    void f2(int) override ;//参数列表不对
//    void f3() override ;//f3不是虚函数
//    void f4() override ;//没有这个函数
};
struct D2 : B{
    void f1(int) const final ;//不允许后续其他类覆盖
};
struct D3 : D2{
    void f2();//正确，间接从B继承而来
//    void f1(int) const ;//错误 D2 已经声明为final
};

struct Base_s1{
    virtual void f1(int i = 5){
        cout << "base" << i << endl;
    }
};
struct Derived_s1 : Base_s1{
    void f1(int i = 10) override {
        cout << "derived" << i << endl;
    }
};


//15.13
struct Base_s2{
    Base_s2() = default;
    Base_s2(string s):name(s){}
    virtual void p(ostream & os){
        os << name << "base" << endl;
    }

private:
    std::string name;
};
struct Derived_s2 : public Base_s2{
    Derived_s2() = default;
    Derived_s2(string s): Base_s2(s){}
//    Derived_s2(string s){
//        Base_s2(s);
//    }

    void p(ostream & os) override {
        Base_s2::p(os);
        os << "derived " << endl;
    }
};


struct Base_s3{
    Base_s3() = default;
    Base_s3(int i):i(i){}

    virtual void f() = 0;//纯虚函数

private:
    int i;
};
struct Derived_s3 : Base_s3{
    Derived_s3() = default;
    Derived_s3(int i, string s) : Base_s3(i), s(s) {}

    void f(){
        cout << s << endl;
    }

private:
    string s;
};


// ！！！ 访问控制, 友元
class Base_4{
public:
    friend class Pal;

protected:
    int prot_mem;
};
class Sneaky : public Base_4{
    friend void clobber(Sneaky&);
    friend void clobber(Base_4&);//这个函数不是Base的友元，因此不能访问Base的protected成员
    int j;

    void f(){//成员函数可以访问
        prot_mem = j = 10;
    }
    int t = prot_mem;

};
//friend 的错误使用，下面的写法会出现如下错误error: out-of-line definition of 'clobber' does not match any declaration in 'Sneaky'
//void Sneaky::clobber(Base_4 &b) {
//    b.prot_mem = 0;
//}
//void Sneaky::clobber(Sneaky &s) {
//    s.j = s.prot_mem = 0;
//}

void clobber(Base_4 &b) {
//    b.prot_mem = 0;
}
void clobber(Sneaky &s) {
    s.j = s.prot_mem = 0;
}

// !!! 友元关系不能继承
class Pal{
public:
    int f(Base_4 b){
        return b.prot_mem;
    }
    int f2(Sneaky s){
//        return s.j; // 友元不能被继承，无法访问子类的private成员
    }
    int f3(Sneaky s){
        return s.prot_mem;  // 正确Pal是Base的友元 ，只要是A是友元B类的友元，就能访问B类中的成员，即使B类是在继承的子类中
    }
};

class DPal : public Pal{
public:
    int mem(Base_4 b){
//        return b.prot_mem;// 错误，友元关系不能继承， DPal类不是Base的友元，无法访问Base中protected的成员
    }
};



//  ！！！ 派生类说明符控制的是派生类用户的权限
class Base_5{
public:
    void pub_mem(){}
private:
    char priv_mem;
protected:
    int prot_mem;
};
struct Pub_Derv : public Base_5{
    int f(){ return prot_mem;}
//    char g(){ return priv_mem;}//基类中private的成员不可访问

    void memfcn(Base_5 & b){
        b = *this;
    }
};
struct Priv_Derv : private Base_5{
    int f1() const { return prot_mem;}//private不影响派生类的访问权限

    void memfcn(Base_5 & b){
        b = *this;
    }
};
struct Prot_Derv : protected Base_5{
    void memfcn(Base_5 & b){
        b = *this;
    }
};

// ！！！ 派生访问说明符控制继承自派生类的新类的访问权限
class Derived_from_Public : public Pub_Derv{
    int use_base(){ return prot_mem;}
    void memfcn(Base_5 & b){
        b = *this;
    }

};
class Derived_from_Private : private Priv_Derv{
//    int use_base(){ return prot_mem;}// 错误，父类全部是private的
//    void memfcn(Base_5 & b){
//        b = *this;//错误，因为Priv)_Derv是private继承Base的，因此Base对于当前类来说是不可见的
//    }
};


// ！！！ 使用using可以改变个别成员访问级别
class Base_6{
public:
    std::size_t size(){ return n;}
protected:
    std::size_t n;
    string s = "ssss";
private:
    int i;
};
class Derived_6 : private Base_6{
public:
    using Base_6::size;
//    using Base_6::i;
    using Base_6::s;

    void f(){
//        int ival1 = i;
//        string str = s;
        cout << s << endl;
    }
protected:
    using Base_6::n;
private:
//    using Base_6::s;//写在这里s变成private的

};
class Derived_from_D6 : public Derived_6{
public:
    void f2(){
        cout << s << endl;//如果注释掉上面的using Base_6::s;则这里会出错，因为Derived_6是private继承的，s变成了private，现在s是public的
    }
};


int main() {

//    ! 除非特别指出，派生类对象的基类部分执行默认初始化
    pIndexofTest(0);
    {
        Quote item;
        Bulk_quote bulk;
        Quote *p = &bulk;
        Quote &f = bulk;


        Orented_1 o1;
        cout << o1.i << endl;
//        Bulk_quote *pb = &item;
//        Bulk_quote &rb = item;
    }

//    !!! C++规定const静态类成员可以直接初始化，其他非const的静态类成员需要在类声明以外初始化，我们一般选择在类的实现文件中初始化，初始化的方式是书写一遍类型的定义：
    pIndexofTest(1);
    {
        Base_2 b;
        Base_2::p();
        Derived_2 obj;
        obj.f(obj);
    }

//    ！！ 派生类与基类的转化
    pIndexofTest(2);
    {
        Bulk_quote bulk;
        Quote *itemP = &bulk;//派生类转化为基类
//        Bulk_quote *bulkP = itemP;//不能将基类转化为派生类，但是可以通过下面的强制转换
        Bulk_quote *bulkP = static_cast<Bulk_quote*>(itemP);
    }

//    对象之间不存在类型转换，下面的例子里bulk部分不会被初始化，会被切掉
    pIndexofTest(3);
    {
        Bulk_quote bulk;
        Quote item(bulk);//使用 Quote::Quote(const Quote&)构造函数
        item = bulk;//使用Quote::operator = (const Quote&)
    }

    pIndexofTest(4);
    {
        Quote base("book1", 50);
        print_total(cout, base, 10);
        Bulk_quote derived("book2", 50, 5, 0.19);
        print_total(cout, derived, 10);
    }

//    !!! 虚函数默认实参, 通过基类的指针或者引用调用函数，则使用基类中定义的默认实参。即使运行的是派生类中的函数版本也是如此。
    pIndexofTest(5);
    {
        Derived_s1 d;
        Base_s1 *b = &d;
        b->f1();// derived 5
        d.f1();// derived 10
    }

//    !!! 回避虚函数机制
    pIndexofTest(6);
    {
        Derived_s2 d("sss");
        d.p(cout);
    }

//    ! 纯虚函数
    pIndexofTest(7);
    {
//        Base_s3 s;//error: variable type 'Base_s3' is an abstract class
        Derived_s3 s(4, "ss");
        s.f();
    }

//    派生说明符控制的是派生类的用户
    pIndexofTest(8);
    {
        Pub_Derv d1;
        Priv_Derv d2;
        d1.pub_mem();
//        d2.pub_mem();//继承方式是private的，所以错误
    }

//    派生类向基类转换的可访问性（书P544）不太懂
    pIndexofTest(9);
    {
        Pub_Derv d1;
        Priv_Derv d2;
        Prot_Derv d3;
        Base_5 *p = &d1;
//        p = &d2;
//        p = &d3;
    }

    {
        int a[5]={12,34,56,78,90}, *p=a;
        cout << (*p++) << endl;
    }

    return 0;
}