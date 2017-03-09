#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <exception>
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

    return 0;
}



