#include <iostream>


using namespace std;

template <typename T>//模板参数列表不能为空
int compare(const T &v1, const T &v2){
    if(v1 < v2) return -1;
    if(v2 > v1) return 1;
    return 0;
}

// 类型参数可以指定返回类型
template <typename T>
T foo(T* p){
    T tmp = *p;
    return tmp;
}

// 类型参数前必须使用关键字class或typename，这两个关键字含义相同，可以互换
template <typename T, class U>
T calc(const T&, const U&);

// 非类型模板参数
template <unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M]){
    return strcmp(p1, p2);
}

// inline 或 constexpr 放在模板参数列表之后，返回值类型之前
int main() {
    {
        cout << compare(0, 1) << endl;
        cout << compare("hi", "heeee") << endl;
    }
    return 0;
}