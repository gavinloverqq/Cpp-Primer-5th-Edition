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
//    static void p(){
//        cout << Base_2::sti << endl;
//    }
};

//class Derived_2:public Base_2{
//public:
//    void f(const Derived_2 & obj){
////        sti = 10;
//        Base_2::p();
//        Derived_2::p();
//        obj.p();
//        p();
//    }
//};

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

    pIndexofTest(1);
    {
//        Base_2::sti = 10;
        Base_2 b;

//        Base_2::p();

//        Derived_2 obj;
//        obj.f(obj);
    }
    return 0;
}