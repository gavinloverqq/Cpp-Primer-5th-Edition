#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <exception>
#include <new>
#include <sstream>

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


shared_ptr <int> foo(int arg){
//    shared_ptr负责释放内存
    return make_shared <int> (arg);
}

void use_foo(int arg){
    shared_ptr <int> p = foo(arg);
//    使用p
}//p 离开了作用域,他指向的内存会被释放掉,p被销毁,p指向的对象也会被销毁

//共享相同状态的类
class StrBlob{
public:
    using sizeType = std::vector <std::string>::size_type;
    StrBlob():data(make_shared<std::vector<std::string>>()){}
    StrBlob(std::initializer_list<std::string> il):data(make_shared<std::vector<std::string>>(il)){}
    sizeType size()const { return data->size();}
    bool empty()const{ return data->empty();}

    void push_back(const std::string& s){data->push_back(s);}
    void pop_back(){
        check(0,"pop on empty strBlob");
        data->pop_back();
    }

    std::string& front(){
        check(0,"front on empty strBlob");
        return data->front();
    }
    std::string& back(){
        check(0,"back on empty strBlob");
        return data->back();
    }

private:
    std::shared_ptr <std::vector <std::string> > data;
    void check(sizeType t,const std::string& msg) const{
        if(t >= data->size()){
            throw out_of_range(msg);
        }
    }

};

// !!! (阅读p248)   const 在函数名前,与后 : const只加在成员函数的后面,表示此成员函数是只读函数,函数内不能修改成员变量的值,在后面表示返回的值是个const的值
class C6{
public:
    C6(){}
    C6(int aa):a(aa){}

    int foo1() const {
        return a + 5;
    }

//    error: invalid conversion from ‘const int*’ to ‘int*’
//    int* foo1() const {
//        return &(a);
//    }

//    error 修改了成员变量的值
//    int foo4() const {
//        return a += 5;
//    }

    const int* foo2(){
        return &a;
    }
    const int foo3()const{
        return a + 4;
    }

    int a;
};


int* func1(int a){
    return new int(a + 5);
};
void func2(int a){
    int* pi = func1(a);
    return;
}//pi离开作用域后所指向的内存没有被释放 发生内存泄露
void func3(int a) {
    int *pi = func1(a);
    delete pi;//修复上述错误，或者把指针返回，以后在delete
    return;
}


// !!! 练习12.6 (值得一做）
vector <int>* exFunc1(){
    return new (nothrow) vector <int>;
}
void exFunc2(istream& is, vector <int>* pVec){
    int t;
    cout << " input 999 to quit" << endl;
    while (is >> t){
        if(t == 999)
            break;
        pVec->push_back(t);
    }
}
void exFunc3(vector <int>* pVec){
//    while (!pVec->empty()){
//        cout << pVec->back() << endl;
//        pVec->pop_back();//vecor 没有pop_front？？？
//    }
    for(auto a : *pVec)
        cout << a << " ";
    cout << endl;
    delete pVec;
}

shared_ptr<vector<int>> exSmartPoint(){
    return make_shared <vector<int>>();
}
void exSmartPoint2(istream& is,shared_ptr<vector<int>> sPvec){
    int t;
    cout << " input 999 to quit" << endl;
    while (is >> t){
        if(t == 999)
            break;
        sPvec->push_back(t);
    }
}
void exSmartPoint3(shared_ptr<vector<int>> sPvec){
    for(auto a : *sPvec)
        cout << a << " ";
    cout << endl;
}


void process(shared_ptr<int> ptr){

}


//接收指针参数的智能指针构造函数是explicit的，因此不能将一个内置指针隐式转换为一个智能指针 必须使用直接初始化形式
shared_ptr<int> clone(int p){
//    return new int(p);//错误，此处会发生隐士转换为shared_ptr<int>
}
shared_ptr<int> clone2(int p){
    return shared_ptr<int> (new int (p));//正确，显式创建shared_ptr<int>
}



int main() {

//    shared_ptr 智能指针
    pIndexofTest(1);
    {
        string s = "jhjjj";
        shared_ptr <string> p = make_shared <string> ("hhhhhhhhhhhhh");
//        *p = "hhhh";
        cout << *p << endl;

        shared_ptr <string> p1 = make_shared <string> (10,'x');
//        shared_ptr <string> p1 = make_shared <string> (10,"x");//error: invalid conversion from ‘const char*’ to ‘char’ [
        cout << *p1 << endl;

//        上面的错误原因如下:因为make_shared是调用构造函数来初始化对象,而string没有 (10,"sss")的构造函数!
//        string s1(10,"x");
//        cout << s1 << endl;
    }

//    shared_ptr 的拷贝和赋值,依靠计数器来决定对象是否销毁(为0时销毁),作为参数传递给函数,或者作为函数返回值都会发生拷贝
    pIndexofTest(2);
    {
        auto p = make_shared <int> (33);
        auto q(p);//pq指向相同的对象,此对象有两个引用者
        cout << " p use counts: " << p.use_count()<< endl;
        cout << " q use counts: " << q.use_count()<< endl;

        auto r = make_shared <int> (43);
        cout << " r use counts: " << r.use_count()<< endl;
        r = q;//给r赋值,令它指向另一个地址
//        递增q指向的对象的引用计数
//        递减r原来指向的对象的引用计数
//        r原来的对象没有引用者,自动释放
        cout << " q use counts: " << q.use_count()<< endl;
        cout << " r use counts: " << r.use_count()<< endl;
    }

//    使用动态内存,出于以下三种原因:
//    不知到需要使用多少对象
//    不知道对象的准确类型
//    需要在多个对象间共享数据

//    !!! 使用动态内存的常见原因是允许多个对象共享相同的对象
    pIndexofTest(3);
    {
        C6 c(12);
        int a = c.foo1();
//        int *b = c.foo2();
    }

//    ! 简单测试下StrBlob类
    pIndexofTest(4);
    {
        string s("ddd");
        string s1("ddd");
        string s2("ddd");
        StrBlob str = {"AAA","bbb","ccc"};
        str.push_back("aaa");
        str.pop_back();
        str.front();
//        StrBlob str1(s,s1,s2);//initializer_list传入参数是需要列表初始化
        StrBlob str1({s,s1,s2});
    }

//    !!! 练习12.1 （练习12.1-12.5 都是好题，值得重新做）；
    pIndexofTest(5);
    {
        StrBlob b1;
        {
            StrBlob b2({"aa","bb"});
            b1 = b2;
            b2.push_back("cc");
        }
        while (!b1.empty()){
            cout << b1.back() << endl;
            b1.pop_back();
        }
    }

//    !!! new
    pIndexofTest(6);
    {
//        值初始化，对于有自己的构造函数的类类型（如string）要求值初始化没有意义的，无论采用什么形式，对象都会通过默认构造函数来初始化
        int* pi = new int(9);
        cout << *pi << endl;
//        默认初始化
        int* p2 = new int;//*p2 的值未定义
        int* p3 = new int();//值初始化 *p3 的值为 0;

        string* pstr = new string(10,'x');
        cout << *pstr << endl;

        vector <int> *pVec = new vector<int> {1,2,3,4};
        print(*pVec);

//        只有单一初始化器才能使用auto
        auto pa = new auto(5);
        auto pa2 = new auto({1,2,3});
        auto pa3 = new auto{1,2,3};//此处与书中描述不一致

//        动态分配的const对象,动态分配的对象必须进行初始化
        const int* cntPi = new const int(44);
//        定义了默认构造函数的类类型，可以隐式初始化,否则必须显式初始化
        const string* cntPstr = new const string;

//        内存耗尽，new会抛出一个异常bad_alloc;
        int* p4 = new int;//分配失败，抛出异常
        int* p5 = new (nothrow) int;//分配失败，返回一个空指针 ，这种形式为定位new
    }

//    !!! delete
    pIndexofTest(7);
    {
        int i, *pi1 = &i, *pi2 = nullptr;
        double *pd = new double(3.14), *pd2 = pd;
//        delete i;//错误：error: type ‘int’ argument given to ‘delete’, expected pointer
//        delete pi1;//delete不是new分配的内存，未定义行为 Process finished with exit code 139 (interrupted by signal 11: SIGSEGV)
        delete pi2;//释放空指针没有错误
        delete pd;
//        delete pd2;//delete 已经释放的内存 未定义行为 Process finished with exit code 134 (interrupted by signal 6: SIGABRT)

//        虽然const对象的值不能被改变，但他本身是可以被销毁的
        const int* cntPi = new const int(11);
        delete cntPi;
    }

//    ! 空悬指针，delete后，指针仍然保留这动态内存的地址
    pIndexofTest(8);
    {
        int* p(new int(42));
        auto q = p;
        delete p;//p,q都变成空悬指针
        p = nullptr;//重置指针，但是q还是指向那段地址
    }

//    !!! 练习12.6
    pIndexofTest(9);
    {
//        vector <int>* pVec = exFunc1();
//        exFunc2(cin,pVec);
//        exFunc3(pVec);
//        pVec = nullptr;//空悬指针
    }

//    练习 12.7
    pIndexofTest(10);
    {
        stringstream strCin;
        string sIn{"1 2 3 999"};
        strCin.str(sIn);
//        shared_ptr<vector<int>> sPvec = exSmartPoint();
        auto sPvec = exSmartPoint();
        exSmartPoint2(strCin,sPvec);
        exSmartPoint3(sPvec);
    }

//    shared_ptr 和 new 结合使用
    pIndexofTest(11);
    {
        shared_ptr<int> p2(new int(42));
//        shared_ptr<int> p3 = new int(42);//接收指针参数的智能指针构造函数是explicit的，因此不能将一个内置指针隐式转换为一个智能指针 必须使用直接初始化形式 error: conversion from ‘int*’ to non-scalar type ‘std::shared_ptr<int>’ requested


    }

//    !!! 不要混用普通指针和智能指针 使用一个内置指针来访问一个智能指针所负责的所负责的对象是很危险的，因为我们无法知道对象和是会被销毁
    pIndexofTest(12);
    {
        shared_ptr <int> p(new int(42));//p的引用计数为1，
        process(p);//拷贝p，增加引用计数
        int i = *p;
        cout << i << endl;

        int* x(new int(33));//x是普通指针
//        process(x);//不能将普通指针隐士转化为智能指针 error: could not convert ‘x’ from ‘int*’ to ‘std::shared_ptr<int>’
        process(shared_ptr<int>(x));//合法的，内存会被释放
        int j = *x;//为定义的，x是一个空悬指针。虽然输出了0
        cout << j << endl;
    }
    return 0;
}


