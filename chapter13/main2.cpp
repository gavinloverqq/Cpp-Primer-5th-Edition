#include <iostream>
#include <memory>

using namespace std;
//类的指针未分配内存是否调用析构函数？
class T1{
public:
    string str;

    T1(string s):str(s){}
    T1(){}
    ~T1(){
        std::cout << "xigou" << endl;
    }
};

void fcn(T1 * t){
    t = new T1("xx");
    delete t;//如果上面的语句没有new的话，这里也会调用析构函数，但是调用结束会报错， 没有这句，不会调用析构；

//    shared_ptr<T1> pt1(new T1("ss"));//可以体会智能指针可以自己释放内存

}

int main(){
    T1 *t;
    fcn(t);
//    cout << t->str << endl;//把函数参数改为引用，此处就可以了
}