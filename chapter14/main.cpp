#include <iostream>


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
public:
    C1() = default;
    C1(int a, string b):a(a), b(b){}

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

int main() {
    pIndexofTest(0);
    {
//        C1 c(5, "ssss");
        C1 c;
        cin >> c;
        cout << c;
    }
    return 0;
}