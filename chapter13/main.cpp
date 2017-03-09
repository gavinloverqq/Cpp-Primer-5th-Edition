#include <iostream>
#include <vector>

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

template <typename T>
void print(T& t){
    for(auto a : t)
        cout << a << " ";
    cout << endl;
}




//!! 拷贝构造函数 ,通常不是explicit的,
class C1{
public:
    C1(){}
    C1(const C1&){}//拷贝构造函数必须传引用,如果不传引用,那么实参传入,我们需要拷贝这个实参,为了拷贝实参,又要调用拷贝构造函数

};

//!! 类里有数组,如何赋值与拷贝
/*class C2{
public:
    C2(const C2&);
    C2(int ii,string ss,int aa[10]):i(ii),s(ss),a(aa){}

private:
    int i;
    string s;
    int a[10];

};
C2::C2(const C2& c):i(c.i),s(c.s){}
//C2::C2(const C2& c):i(c.i),s(c.s),a(c.a){}*/

class C3{
public:
    C3(){}
    C3(int ii,string ss):i(ii),s(ss){cout << " constructor " << endl;}
    C3(const C3& c):i(c.i+100),s(c.s + "hhhhhhhhhhh"){cout << " copy constructor " << endl;}
    int i;
    string s;
};

class C4{
public:
    C4(int aa):a(aa){}
private:
    int a;
    C4(const C4& c){cout << " copy constructor " << endl;}
};

// !! 合成拷贝赋值运算符,赋值运算符通常应该返回一个指向其左侧对象的引用
class C5{
public:
    C5& operator = (const C5& c){
        a = c.a;
        s = c.s;
        cout << " operator =  " << endl;
        return *this;
    }

    C5(int aa,string bb):a(aa),s(bb){}
private:
    int a;
    string s;
};

class HasPtr{
public:
    HasPtr(const std::string& s = std::string()):ps(new std::string(s)),i(0){}
    HasPtr(const HasPtr& c){
//        ps = c.ps;
        ps = new std::string(*c.ps);//拷贝ps指向的对象，而不是拷贝指针本身 ？？？这里不是很懂
        i = c.i;
    }
//    !!! 赋值构造函数这么写为什么出错
    HasPtr& operator = (const HasPtr& hp);
    /*HasPtr& operator = (const HasPtr& hp){
        ps = new std::string(*hp.ps);//拷贝ps指向的对象，而不是拷贝指针本身 ？？？这里不是很懂
        i = hp.i;
        return *this;
    }*/
    ~HasPtr(){
        delete ps;
    }

private:
    std::string* ps;
    int i;
};

HasPtr& HasPtr::operator = (const HasPtr& hp){
    auto newps = new std::string(*hp.ps);//拷贝ps指向的对象，而不是拷贝指针本身 ？？？这里不是很懂
    delete ps;
    ps = newps;
    i = hp.i;
    return *this;
}


struct X{
    X(){cout << " constructor " << endl;}
    X(const X&){cout << "copy constructor " << endl;}
    X& operator = (const X& t){cout << " copy-assignment operator" << endl;
        return *this;}
    ~X(){cout << " destructor " << endl;}
};
void f1(X x){}
void f2(X& x){}





int main() {

//    !!! 使用insert或push,容器会对元素拷贝初始化,使用emplace会u直接调用构造函数直接初始化
    pIndexofTest(1);
    {
        vector <C3> vC;
        vC.push_back(C3(1,"ss"));
        cout << vC[0].i << endl;
        cout << endl;
        vC.emplace_back(3,"kk");
        cout << vC[1].i << " " << vC[0].i << endl;
//        vC.emplace(vC.begin(),2,"xx");

    }

//    !!!(看不太懂这里) 我们使用的初始化值要求通过一个explicit的构造函数来进行类型转换,那么使用拷贝初始化还是直接初始化就无关紧要了
    pIndexofTest(2);
    {
        vector <int> v(19);
//        vector <int> v2 = 10;//错误:接收大小参数的构造函数时explicit的
//        void f(vector <int> );
//        f(10);//不能用一个explicit的构造函数初始化一个实参
//        f(vector <int> (10));//正确
    }

//    ! 编译器可以绕过拷贝构造函数 (但是拷贝构造函数必须可见)
    pIndexofTest(3);
    {
        C4 c(1);
//        C4 c2 = C4(2);拷贝构造函数不可见
    }

//    ! 合成赋值拷贝运算符
    pIndexofTest(4);
    {
        C5 c5(2,"ss");
        c5 = C5(4,"xx");
    }

//    !!! 练习13.13 这个例子值得仔细看看
    pIndexofTest(5);
    {
        cout << " 局部变量 " << endl;
        X x;
        cout << "  " << endl;

        cout << " 非引用参数传递 " << endl;
        f1(x);
        cout << "  " << endl;

        cout << " 引用参数传递 " << endl;
        f2(x);
        cout << "  " << endl;

        cout << " 动态分配 " << endl;
        X* px = new X;
        cout << "  " << endl;

        cout << " 添加到容器 " << endl;
        vector <X> vX;
        vX.push_back(x);
        cout << "  " << endl;

        cout << " 动态释放 " << endl;
        delete px;
        cout << "  " << endl;

        cout << " 间接初始化和赋值 " << endl;
        X y = x;
        y = x;
        cout << "  " << endl;

        cout << " 程序结束 " << endl;
    }
    return 0;
}