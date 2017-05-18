#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <map>
#include <functional>

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

// !!！ 输入输出重载（注意有返回值、以及不能当成成员函数）！ 注意输入重载时需要对输入失败的处理！！！！
class C1{
    friend ostream& operator << (ostream & os, const C1 & c);
    friend istream& operator >> (istream & is, C1 & c);
    friend C1 operator + (const C1 & c1, const C1 & c2);
    friend bool operator == (const C1 & c1, const C1 & c2);
    friend bool operator != (const C1 & c1, const C1 & c2);
    friend bool operator < (const C1 & c1, const C1 & c2);

public:
    C1() = default;
    C1(int a, string b):a(a), b(b){}

    C1& operator += (const C1 & c1){
        this->a += c1.a;
        this->b += c1.b;
        return *this;
    }

    C1& operator = (const C1& c1){
        this->a = c1.a;
        this->b = c1.b;
        return *this;
    }

private:
    int a;
    string b;
};
ostream& operator << (ostream & os, const C1 & c){
    os << c.a << endl << c.b << endl;
    return os;
}
istream& operator >> (istream & is, C1 & c){
    is >> c.a >> c.b;

    if(!is) // 如果输入失败！
        c = C1();

    return is;
}

// !! 使用复合运算符实现算术运算符
C1 operator + (const C1 & c1, const C1 & c2){
    C1 tmp = c1;
    tmp += c2;
    return tmp;
}

// ! 相等运算符 (相等运算符要满足传递性）
bool operator == (const C1 & c1, const C1 & c2){
    return c1.a == c2.a && c1.b == c2.b;
}
bool operator != (const C1 & c1, const C1 & c2){
    return !(c1 == c2);
}

// !!! 关系运算符的定义需要考虑与 == 运算符保持一致，如果两个对象是不等的，则一个对象应该小于另一个对象
bool operator < (const C1 & c1, const C1 & c2){
    return c1.a < c2.a;
}






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



using vStr = std::vector<std::string>;
class StrBlobPtr{
    friend bool eq(const StrBlobPtr& sbp1,const StrBlobPtr& sbp2);

public:
    StrBlobPtr():curr(0){}
    StrBlobPtr(StrBlob& a,size_t sz = 0):wptr(a.data),curr(sz){}
    std::string& deref()const;
    StrBlobPtr& incr();//前缀递增

    std::string& operator * ()const{
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }

//    !!! 注意此处的重载
    std::string *operator -> () const  {
        cout << "ss" << endl;
        return & this->operator*();//(等价于 ： *this.XXXXXX)
    }


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
        throw std::runtime_error("unbound StrBlobPtr");
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
//注意此处必须使用const引用，因为函数返回值是右值，右值无法绑定到非const上,注意看第588行的使用！！！
bool eq(const StrBlobPtr& sbp1,const StrBlobPtr& sbp2){
    auto p1 = sbp1.wptr.lock();
    auto p2 = sbp2.wptr.lock();
    if(p1 == p2)
        return (!p1 || sbp1.curr == sbp2.curr);
    else
        return false;
}


//练习14.32
class C2{
public:
    std::string* operator -> () const {
        return p->operator->();
    }
private:
    StrBlobPtr* p;
};

//函数调用运算符的重载
struct Node{
    int operator ()(int val){
        return val >= 0 ? val : -val;
    }
};

class PrintString{
public:
    PrintString(ostream& o = cout, char c = ' '):os(o), seq(c){}
    void operator()(string& s){
        os << s << seq;
    }

private:
    ostream &os;
    char seq;//将不同输出隔开的字符
};




//可调用对象
int add(int i, int j){
    return i + j;
}
int add2(int i, int j){
    return i + j;
}
double add2(double i, double j){
    return i + j;
}
struct divide{
    int operator()(int i, int j){
        return i / j;
    }
};


//类型转换运算符
class SmallInt{
public:
    SmallInt(int i):val(i){
        if(i < 0 || i > 255)
            throw std::out_of_range("bad value");
    }

//    类型转换
    operator int() const{
        return val;
    }

private:
    int val;
};



int main() {
    pIndexofTest(0);
    {
//        C1 c(5, "ssss");
//        C1 c1, c2, c3;
//        cin >> c1 >> c2;
//        c3 = c1 + c2;
//        c1 += c2;
//        cout << c1 << c2 << c3;
//
//        set <C1> sc;
//        sc.insert(c1);
//        sc.insert(c2);
//        sc.insert(c3);
//        for (auto p : sc) {
//            cout << p << endl;
//        }
    }

//    !!! -> * 运算符的重载
    pIndexofTest(1);
    {
        StrBlob a1 = {"ni", "hao", "bye", "now"};
        StrBlobPtr p(a1);
        *p = "okay";
        cout << p->size() << endl;
        cout << (*p).size() << endl;
    }

//    !!! 函数调用运算符
    pIndexofTest(2);
    {
        int i = -42;
        Node node;
        cout << node(i) << endl;

        string str = "hhhh";
        PrintString ps;
        ps(str);

    }

//    ！！！ 标准库定义的函数对象， 头文件（functional）
    pIndexofTest(3);
    {
        plus <int> iadd;
        cout << iadd(10, 20) << endl;

//        标准库函数对象可以用在此处！
        string str = "sdfsdfhhkdf";
        sort(str.begin(), str.end(), greater<char>());//注意后面有个括号
        cout << str << endl;

//        标准库函数对象对于指针同样适用
        string s1 = "sss", s2 = "gg", s3 = "xx";
        vector <string*> pStrVev = {&s1, &s2, &s3};
//        按照书上的说法，指针适用 < 比较 应该是未定义行为，但是此处并没有什么异常情况？？？？
        sort(pStrVev.begin(), pStrVev.end(), [](string* a, string* b){ return a < b;});
        for (auto p : pStrVev) {
            cout << *p << endl;
        }
//        可以使用标准库比较指针
        sort(pStrVev.begin(), pStrVev.end(), greater<string*>());
        for (auto p : pStrVev) {
            cout << *p << endl;
        }
    }

//    可调用对象、functional
    pIndexofTest(4);
    {
        map<string, int (*)(int, int)> binops;
        binops.insert({"+", add});

//        此处描述和书上不符，书上讲lambda是表达式，有自己的类型，不是函数指针，因此和map类型不匹配
        auto mod = [](int a, int b){ return a % b;};
        binops.insert({"%", mod});
        cout << binops["%"](10, 3) << endl;

        function<int(int, int)> f1 = add;
        cout << f1(3, 8) << endl;

        map<string, function<int(int, int)> > ops = {
                {"+", add},
                {"-", std::minus<int>()},
                {"%", mod},
                {"*", [](int i, int j){ return i * j;}},
                {"/", divide()}
        };
        cout << ops["+"](10, 5) << endl;
        cout << ops["-"](10, 5) << endl;
        cout << ops["/"](10, 5) << endl;
        cout << ops["*"](10, 5) << endl;
        cout << ops["%"](10, 7) << endl;
    }

//    ！！ 重载的函数与function，使用函数指针或者lambda解决
    pIndexofTest(5);
    {
        map<string, function<int(int, int)> > ops;
//        ops.insert({"+", add2});//add 重载过，有int 和 double版本，因此会出错误 error: no viable conversion from '<overloaded function type>' to 'function<int (int, int)>'
        int (*fp) (int, int) = add2;
        ops.insert({"+", fp});
        ops.insert({"+", [](int a, int b){ return add2(a, b);}});
    }

//    ！！类型转换
    pIndexofTest(6);
    {

    }
    return 0;
}