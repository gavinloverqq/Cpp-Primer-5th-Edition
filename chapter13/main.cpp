#include <iostream>
#include <vector>
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
        ps = new std::string(*c.ps);//拷贝ps指向的对象，而不是拷贝指针本身
        i = c.i;
    }
//    !!! 赋值构造函数这么写为什么出错
    HasPtr& operator = (const HasPtr& hp);
    /*HasPtr& operator = (const HasPtr& hp){
        ps = new std::string(*hp.ps);//拷贝ps指向的对象，而不是拷贝指针本身
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
//赋值运算符需要注意两点：
//1.如果将一个对象赋值给他自生，必须能正确工作
//2.大多数赋值运算符组合了析构函数和拷贝构造函数的工作
HasPtr& HasPtr::operator = (const HasPtr& hp){
    auto newps = new std::string(*hp.ps);//构造函数
    delete ps;//析构函数的工作
    ps = newps;
    i = hp.i;
    return *this;


//    写成这样就无法赋值给自身
//    delete ps;//析构函数的工作
//    ps = new std::string(*hp.ps);
//    i = hp.i;
//    return *this;

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



//   !!!  需要析构的类也需要拷贝和赋值操作
class HasPtr2{
public:
    HasPtr2(const std::string& s = std::string()):ps(new std::string(s)),i(0){}

    ~HasPtr2(){
        delete ps;
    }
//    !!! 需要拷贝构造函数和一个拷贝赋值运算符
private:
    std::string* ps;
    int i;
};
//一个严重的错误
HasPtr2 f(HasPtr2 hp){
    HasPtr2 ret = hp;//拷贝给丁的HasPtr2
    return ret;//ret被销毁，hp被销毁
}//两个对象被销毁，在两个对象上都要调用HasPtr的析构函数，但是默认的构造函数会让ret和hp指针都指向同一个地址，却被delete两次，显然错误

//13.14练习
class Numbered{
public:
    static int count;
    Numbered():id(++count){cout << count << " constructor " << endl;}
    Numbered(const Numbered& n):id(++count){cout << count << " copy " << endl;}
    Numbered& operator= (const Numbered& n){
        this->id = ++count;
        cout << count << " = " << endl;
        return *this;
    }
    int id;
};
void fNum(Numbered s){
    cout << "function1 " << s.id << endl;
}
void fNum2(Numbered& s){
    cout << "funtion2 " << s.id << endl;
}
int Numbered::count = 0;


// !!! 阻止拷贝，ostream类就无法使用拷贝，赋值
struct NoCopy{
    NoCopy() = default;
    NoCopy(const NoCopy&) = delete;
    NoCopy&operator = (const NoCopy&) = delete;
    ~NoCopy() = default;
};


class StrBlob{

public:
    using sizeType = std::vector <std::string>::size_type;
    StrBlob():data(make_shared<std::vector<std::string>>()){}
    StrBlob(std::initializer_list<std::string> il):data(make_shared<std::vector<std::string>>(il)){}

//    练习13.26
    StrBlob(const StrBlob& sb){
        data = make_shared <vector<string>>(*sb.data);
    }
    StrBlob&operator = (const StrBlob& sb){
        data = make_shared <vector<string>>(*sb.data);
        return *this;
    }


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


//指针类型的Hastr
class HasPtr3{

public:
    HasPtr3(const std::string& s = std::string()):ps(new std::string(s)),i(0),use(new std::size_t(1)){}
    HasPtr3(const HasPtr3& hp):ps(hp.ps),i(hp.i),use(hp.use){++*use;}
    HasPtr3&operator = (const HasPtr3& hp){
        ++*hp.use;
        if(--*use == 0){
            delete ps;
            delete use;
        }
        ps = hp.ps;
        i = hp.i;
        use = hp.use;
        return *this;
    }
    ~HasPtr3(){
        if(--*use == 0){
            delete ps;
            delete use;
        }
    }
    string&operator * (){
        return *ps;
    }
    HasPtr3& operator = (const std::string& s){
        *ps = s;
        return *this;
    }

private:
    std::string *ps;
    int i;
    std::size_t *use;
};


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

//    !!! 思考下面两种不同写法带来的输出的不同！！！
    pIndexofTest(6);
    {
        Numbered::count = 0;
        Numbered a,b,c;
        b = a, c = b;//拷贝与拷贝构造函数的不同！！！
        fNum(a);
        fNum(b);
        fNum(c);
        fNum2(a);
        fNum2(b);
        fNum2(c);
    }

    pIndexofTest(7);
    {
        Numbered::count = 0;
        Numbered a,b = a, c = a;//b,c不会调用构造函数,不会调用赋值运算，只调用拷贝构造函数
        fNum(a);//函数传参数，不会去调用构造函数，而是调用拷贝构造函数！！！
        fNum(b);
        fNum(c);
        fNum2(a);
        fNum2(b);
        fNum2(c);
    }

    pIndexofTest(8);
    {
        HasPtr3 h("hhhh");
        HasPtr3 h2 = h;
        h = "xxx1";
        cout << "h: " << *h << endl;
        cout << "h2: " << *h2 << endl;
    }

    return 0;
}