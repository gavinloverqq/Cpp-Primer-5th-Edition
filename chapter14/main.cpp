#include <iostream>
#include <set>

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

int main() {
    pIndexofTest(0);
    {
//        C1 c(5, "ssss");
        C1 c1, c2, c3;
        cin >> c1 >> c2;
        c3 = c1 + c2;
        c1 += c2;
        cout << c1 << c2 << c3;

        set <C1> sc;
        sc.insert(c1);
        sc.insert(c2);
        sc.insert(c3);
        for (auto p : sc) {
            cout << p << endl;
        }
    }
    return 0;
}