#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <exception>
#include <new>
#include <fstream>
#include <sstream>
#include <cstring>

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
class StrBlobPtr;
class StrBlob{
    friend class StrBlobPtr;

public:
    StrBlobPtr begin();
    StrBlobPtr end();


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

// 练习12.14
struct destination{};
struct connection{};
connection connect(destination* pd){
    cout << "打开连接" << endl;
    return connection();
}
void disconnect(connection c){
    cout << " 关闭连接 " << endl;
}
//未使用shared_ptr
void f(destination& d){
    cout << " 直接管理连接 " << endl;
    connection c = connect(&d);
//    忘记调用disconnect;或者异常退出,无法关闭c
}
void endConnection(connection* p){
    disconnect(*p);
}
//使用shared_ptr
void f1(destination& d){
    cout << "shared_ptr管理连接" << endl;
    connection c = connect(&d);
    shared_ptr<connection> p(&c,endConnection);
    //忘记调用disconnect,或异常退出,connection 会正确关闭
    cout << endl;
}
void f2(destination& d){
    cout << "shared_ptr管理连接 并使用lambda函数" << endl;
    connection c = connect(&d);
    shared_ptr<connection> p(&c,endConnection);
    //忘记调用disconnect,或异常退出,connection 会正确关闭
    cout << endl;

}

//    !! 我们可以拷贝或赋值一个将要被销毁的unique_ptr，如：从函数返回一个unique_ptr
unique_ptr<int> uclone(int p){
    return unique_ptr<int> (new int(p));
}
unique_ptr<int> uclone2(int p){
    unique_ptr<int> ret(new int(p));
    return ret;
}


// 向unique_ptr传递删除器
void f3(destination& d){
    connection c = connect(&d);
    unique_ptr<connection, decltype(endConnection)*> p(&c,endConnection);
}


using vStr = std::vector<std::string>;
class StrBlobPtr{
    friend bool eq(const StrBlobPtr& sbp1,const StrBlobPtr& sbp2);
//    friend bool eq(StrBlobPtr& sbp1,StrBlobPtr& sbp2);
//    friend bool eq(StrBlobPtr sbp1,StrBlobPtr sbp2);
public:
    StrBlobPtr():curr(0){}
    StrBlobPtr(StrBlob& a,size_t sz = 0):wptr(a.data),curr(sz){}
    std::string& deref()const;
    StrBlobPtr& incr();//前缀递增


private:
//    若检查成功，check返回一个指向vector的shared_ptr
    std::shared_ptr<vStr> check(std::size_t,const std::string&)const;
//    保存一个weak_ptr，意味着底层vector可能被销毁
    std::weak_ptr<vStr> wptr;
    std::size_t curr;//在数组中的当前位置
};
std::shared_ptr<vStr> StrBlobPtr::check(std::size_t i, const std::string& msg) const {
    auto ret = wptr.lock();
    if(!ret)
        throw std::runtime_error("unbound StrBlibPtr");
    if(i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}
//解引用
std::string& StrBlobPtr::deref() const {
    auto p = check(curr,"dereference past end");
    return (*p)[curr];
}
//前缀递增
StrBlobPtr& StrBlobPtr::incr() {
    check(curr,"increment past end of StrBlobPtr");
    ++curr;
    return *this;
}
StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this);}
StrBlobPtr StrBlob::end(){
    auto ret = StrBlobPtr(*this ,data->size());
    return ret;
}
//注意此处必须使用const引用，因为函数返回值是右值，右值无法绑定到非const上
bool eq(const StrBlobPtr& sbp1,const StrBlobPtr& sbp2){
//bool eq(StrBlobPtr& sbp1,StrBlobPtr& sbp2){
    auto p1 = sbp1.wptr.lock();
    auto p2 = sbp2.wptr.lock();
    if(p1 == p2)
        return (!p1 || sbp1.curr == sbp2.curr);
    else
        return false;
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
        strCin.clear();
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

//        process(new int());// 练习12.12(b) 答案错误 error: could not convert ‘(operator new(4ul), (<statement>, ((int*)<anonymous>)))’ from ‘int*’ to ‘std::shared_ptr<int>’

        int* x(new int(33));//x是普通指针
//        process(x);//不能将普通指针隐士转化为智能指针 error: could not convert ‘x’ from ‘int*’ to ‘std::shared_ptr<int>’
        process(shared_ptr<int>(x));//合法的，内存会被释放
        int j = *x;//为定义的，x是一个空悬指针。虽然输出了0
        cout << j << endl;
    }

//    !!! get用来将指针的访问权限传递给代码，你只有确定代码不会delete指针的情况下，才能使用get。永远不要用get初始化另一个智能指针或为林一个指针赋值
    pIndexofTest(13);
    {
        shared_ptr<int> p(new int(42));//引用计数为1
        int* q = p.get();//正确：但使用q时要注意，不要让它管理的指针被释放
        {//新陈序块
            shared_ptr<int> (q);//未定义，两个独立的shared_ptr指向相同的内存
        }//程序块结束，q被销毁，他指向的内存被释放
        int foo = *p;//未定义，p指向的内存已经被释放了
        cout << foo << endl;//似乎并没有被释放？？？？？？？？
    }

//    ! reset unique 操作
    pIndexofTest(14);
    {
        shared_ptr <int> (p);
//        p = new int(1024);//错误，不能将一个指针赋值给shared_ptr error: no match for ‘operator=’ (operand types are ‘std::shared_ptr<int>’ and ‘int*’)
        p.reset(new int (33));

        if(!p.unique())//p 不是当前唯一用户，分配新的拷贝
            p.reset(new int(*p));
        *p += 5;//p是唯一用户，可以改变对象的值
    }

//    !!! 练习12.10 12.11 （好题） (这段代码会引起文件操作异常，不知道为什么！
    pIndexofTest(15);
//    {
//        shared_ptr<int> p(new int(33));
//        process(shared_ptr<int> (p));//拷贝引起 引用计数增加，执行结束后p的引用计数仍然是1
//
//        process(shared_ptr<int> (p.get()));//p.get返回普通指针，用来初始化一个智能指针，结束后智能指针被释放，p变成空悬指针
//    }

//    !! 练习12.14
    pIndexofTest(16);
    {
        destination d;
        f(d);
        f1(d);
        f2(d);
    }

//    ! unique_ptr
    pIndexofTest(17);
    {
//        unique_ptr 一切与拷贝有关的操作都不行
        unique_ptr<double> p1;//可以指向一个double的unique_ptr
//        unique_ptr<double> p2(p1);//错误：不支持拷贝

//        通过release或reset将指针的所有权从一个（非const）unique_ptr转移给unique
        unique_ptr<double> p2(p1.release());//release将p1置为空
        unique_ptr<double> p3(new double(11.111));
        p2.reset(p3.release());//reset释放了p2原来的内存

//        release会切断unique_ptr和他原来管理的对象进间的练习。release返回的指针通常被用来初始化另一个智能指针或给另一个指针赋值

        p2.release();//错误，p2内存不会释放，而且丢失了指针
        auto p = p2.release();//正确，必须记得delete（p）

    }

//    !! 我们可以拷贝或赋值一个将要被销毁的unique_ptr，如：从函数返回一个unique_ptr
    pIndexofTest(18);
    {/*
        unique_ptr<int> clone(int p) {
            return unique_ptr<int>(new int(p));
        }
//        也可以返回一个局部对象的拷贝
        unique_ptr<int> clone2(int p) {
            unique_ptr<int> ret(new int(p));
            return ret;
        }*/
    }

//    !! 向unique_ptr传递删除器
    pIndexofTest(19);
    {
        /*void f(destination& d){
            connection c = connect(&d);
//            加*是需要返回函数指针类型
            unique_ptr<connection, decltype(endConnection)*>p(&c,endConnection);
        }*/

    }

//    !! weak_ptr 不增加shared_ptr的引用计数，由于对象可能不存在，我们不能直接使用weak_ptr来直接访问对象，必须调用lock
    pIndexofTest(20);
    {
        auto p = make_shared<int> (42);
        weak_ptr<int> wp(p);

//        p.reset();注释此行，下面的判断能进去，不注释，不能进去，因为释放了p，weak_ptr悬空
        if(shared_ptr<int> np = wp.lock()){
            cout << "wp is locked" << endl;
        }

    }


//    !!! 注意右值引用问题
    pIndexofTest(21);
    {
        string path = "/home/kunwan/Cpp-Primer-5th-Edition/chapter12/";
        fstream fis;
        fis.open(path + "data.in");

        string tmp;
        StrBlob sb;
        while (fis >> tmp){
            cout << tmp << " ";
            sb.push_back(tmp);
        }
//        StrBlobPtr sbp(sb);
        for (auto bg= sb.begin();!eq(bg,sb.end()); bg.incr()) {
            cout << bg.deref() << endl;
        }
        fis.close();
    }

//    !! new 和数组,动态数组不是数组类型，因此不能使用 begin end
    pIndexofTest(22);
    {
        typedef int arrT[33];
        int *p = new arrT;
        for(int i = 0; i < 33; i++){
            *(p+i) = i + 10;
        }
        cout << p[22];
    }

//    ! 初始化动态数组 释放动态数组
    pIndexofTest(23);
    {
        int *pi1 = new int[10];//10个为初始化的int
        int *pi2 = new int[10]();//10个初始化为0的int
        int *pi3 = new int[10]{1,2,3,4,5,6};//10个int分别用列表中对应的初始化器初始化，如果初始化器元素个数大于10，new失败，不会分配任何内存，会抛出一个异常bad_array_new_length

//      动态分配一个空数组是合法的
        char arr[0];//按书上说此处为错误，不能定义长度为0 的数组
        char* pch = new char[0];//此处类似于尾后指针，不能对长度为0的动态数组解引用

        delete [] pi1;//delete数组忘记括号对，以及delete单一对象使用了括号对，结果是未定义的;delete动态数组是逆序delete
    }

//    !!智能指针与动态数组
    pIndexofTest(24);
    {
//        unique_ptr可以管理动态数组，不支持访问成员的运算符（点，箭头）支持下标运算符
        unique_ptr<int[]> up(new int[10]);
        for(int i = 0; i < 10; ++i)
            up[i] = i*2;
        cout << up[2] << endl;

//        shared_ptr 不能直接管理动态数组，必须自己定义删除器 ,未定义删除器是未定义行为
        shared_ptr<int> sp(new int[10],[](int* p){delete [] p;});
//        shared_ptr 不支持下标运算符，不支持指针的算术运算,只能使用get
        for(int i = 0; i != 10; i++)
            *(sp.get() + i) = i * 3;
        cout << *(sp.get() + 2) << endl;
        sp.reset();
    }

    pIndexofTest(25);
    {
        const char s1[] = "ssssssssssss";
        const char s2[] = "xxxxxxxxxxxxxxx";
        char *pch = new char[200];
        int idx = 0;
        for(int i = 0; i < sizeof(s1)/sizeof(char); ++i)
            pch[idx++] = *(s1 + i);
        idx--;//注意此处！！！！
        for(int i = 0; i < sizeof(s2)/sizeof(char); ++i)
            pch[idx++] = *(s2 + i);
//        strcpy(pch,s1);
//        strcat(pch,s2);
        cout << pch << endl;

        string str1 = "gggggggg";
        string str2 = "hhhhhhhh";
        char *pstr = new char[200];
        strcpy(pstr,(str1 + str2).c_str());
        cout << pstr << endl;


    }
    return 0;
}


