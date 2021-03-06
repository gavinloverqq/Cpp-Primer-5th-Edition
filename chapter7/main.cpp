#include <iostream>
#include <vector>
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

//流作为左值必须返回引用,要修改流,必须传入引用
istream& read(istream& is,Test& t){
    is >> t.iVal1 >> t.iVal2 >> t.str;
    return is;
}
ostream& print(ostream& os,Test& t){
    os << t.iVal1 << " " << t.iVal2 << " " << t.str;
    return os;
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

//! 练习7.25 为什么含有指针数据成员的类一般不宜使用默认的拷贝和赋值操作
class Screen{
public:
    using pos = std::string::size_type;//定义类型的成员，必须先定义后使用

    Screen() = default;
    Screen(pos ht,pos wd,char c):height(ht),width(wd),contents(ht * wd,c){}
    char get()const{
        return contents[cursor];
    }//隐士内联
    inline char get(pos ht,pos wd)const;//显式内联
    Screen& move(pos r,pos c);//能在之后设为内联

    Screen& set(char);
    Screen& set(pos,pos,char);

    //可变数据成员
    void changeMutFunc()const{
        mutNum++;
    }

    //根据对象是否是const重载了display函数。
    Screen& display(std::ostream& os){
        doDisplay(os);
        return *this;
    }
    const Screen& display(std::ostream& os)const {
        doDisplay(os);
        return *this;
    }

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;

    //可变数据成员，即使对象是const，也可以被修改；
    mutable int mutNum;

    //常量函数
    void doDisplay(std::ostream& os)const {
        os << contents;
    }

};
//声明时未设为内联
inline Screen& Screen::move(pos r, pos c) {
    pos row = r * width;
    cursor = row + c;
    return *this;
}
//无需在定义和声明的地方都说明inline
char Screen::get(pos r, pos c)const{
    pos row = r * width;
    return contents[row + c];
}

//以下两个函数返回的是对象本身,而不是对象副本;
inline Screen& Screen::set(char c) {
    contents[cursor] = c;
    return *this;
}
inline Screen& Screen::set(pos r, pos col, char ch) {
    contents[r*width + col] = ch;
    return *this;
}

//!类内初始值，使用{}初始化
class Window_mgr{
private:
    std::vector <Screen> screens{Screen(24,80,' ')};
};


//!练习7.31:定义一对类x和y,x包含指向y的指针,y包含x的对象
class Y;
class X{
    Y* y;
};
class Y{
    X x;
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
    /*{
        Test t(cin);
        print(cout,t) << endl;
    }*/

//    !! 返回this成员函数,(引用与非引用的区别)
    pIndexofTest(6);
    {
        Screen myScreen;
        myScreen.move(4,0).set('#');//执行顺序,从左到右//如果move返回的是Screen不是引用,则Screen temp = myScreen.move(4,0);temp.set('#'),set只能改变临时副本,不能改变myScreen的值
    }

//    !!! const 成员函数返回*this (需复习书p247,以及p208)
    pIndexofTest(7);
    {

        // 如果没有非常量版本的display函数,下面的表达会出错
//        Screen myScreen;
//        myScreen.display(cout).set('*');//display返回常量引用,调用set会发生错误
//        !!! 一个const成员函数,如果以引用的形式返回*this,则返回的类型是常量引用

        const Screen blank(5,3,'c');
        Screen myScreen(5,3,'c');
        myScreen.set('$').display(cout);//调用非常量版本
        cout << endl;
        blank.display(cout);//调用常量版本
    }

    pIndexofTest(8);
    cout << "友元关系不传递" << endl;
    return 0;
}