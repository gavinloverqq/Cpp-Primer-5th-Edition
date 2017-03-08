#include <iostream>
#include <memory>

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

    return 0;
}