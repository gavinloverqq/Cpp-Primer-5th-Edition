#include <iostream>
#include "Sales_item.h"

using namespace std;
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



class Test{
    friend istream& read(istream& is,Test& t);
    friend ostream& print(ostream& os,Test& t);
    friend Test add2(const Test& t1,const Test& t2);

public:
    //C成员函数中都有一个隐式参数this，当我门调用一个成员函数时，用请求该函数的对象的地址初始化this;不允许任何自定义为this的参数，this是常量指针
    void func1() { cout << str << endl;};//this的类型是：Test* const，此时无法将this绑定到常量对象上，也就是说无法接收常量参数来初始化this
    //!!! const成员函数，const放在参数列表后，表示this是指向常量的指针，此时函数称为常量成员函数。常量对象或常量引用或指针都只能调用常量成员函数。
    void func2()const { cout << str << endl;};//此时this指针是 const Test* const
    void func3();
    Test& combine(const Test&);


    Test(){}
    Test(int i1,int i2,std::string str1):iVal1(1),iVal2(2),str(str1){}
    Test(istream&);


private:
    int iVal1,iVal2;
    std::string str;
};

void Test::func3() {
    cout << __func__ << endl;
}

//!!! 返回this对象的函数，调用一个返回引用的函数可以返回一个左值，否则都是返回右值；下面的函数类似 += 的功能
Test& Test::combine(const Test &cnt){
    iVal1 += cnt.iVal1;
    iVal2 += cnt.iVal2;
    string tStr = cnt.str;
    str += tStr;
    return *this;
}

istream& read(istream& is,Test& t){
    is >> t.iVal1 >> t.iVal2 >> t.str;
    return is;
}
ostream& print(ostream& os,Test& t){
    os << t.iVal1 << " " << t.iVal2 << " " << t.str;
}
//!!! 思考下面两个函数的不同，有一个有错误，错在哪里！！！
Test& add1(const Test& t1,const Test& t2){
    Test t = t1;
    t.combine(t2);
    return t;
}
Test add2(const Test& t1,const Test& t2){
    Test t = t1;
    t.combine(t2);
    return t;
}

//!! 定义在类外部的构造函数,使用流初始化
Test::Test(istream& is) {
    read(is,*this);
}


class Test2{
public:
    int iVal1,iVal2;
};

//!!! c++ 11 默认构造函数
class Test3{
    Test3() = default;
    int iVal1 = 5;
    string str;
};

int main() {

    pIndexofTest(1);
    Test testObj(1,1,"haha");
    testObj.func1();//等价 Test::func1(&testObj)


//    !!! this
    pIndexofTest(2);
    const Test testCntObj(2,2,"hhhhhhhhhhhhhhhha");
//    testCntObj.func1();//无法将this绑定到常量对象上，也就是说无法接收常量参数来初始化this
    testCntObj.func2();

//    ！！！ 流函数
    pIndexofTest(3);
    /*{
        cout << "输入t1 t2 的值" << endl;
        Test t1,t2,tAdd;
        read(cin,t1);
        print(cout,t1) << endl;
        read(cin,t2);
        print(cout,t2) << endl;
//        tAdd = add1(t1,t2);//!!! add1调用会出错，因为add1函数返回了局部对象的引用（指针也是错误的）p201 与combine函数不同，this是行参
        tAdd = add2(t1,t2);
        print(cout,tAdd) << endl;
    }*/

//    ！！  没有构造函数的类，对象被默认初始化，值是未定义的
    pIndexofTest(4);
    {
        Test2 t2;
        cout << t2.iVal2 << endl;
    }

//    !! 定义在类外部的构造函数，以及使用流初始化
    pIndexofTest(5);
    {
        Test t(cin);
        print(cout,t) << endl;
    }

    return 0;
}