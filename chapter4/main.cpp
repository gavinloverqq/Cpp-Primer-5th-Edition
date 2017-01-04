#include <iostream>

using namespace std;

// 使用 ! 表示重要程度,! 越多越重要
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

int main() {

//    !!! 求值顺序
//    int i = f1() * f2();//无法知道先计算f1() 还是 f2() 的值
//    int i = 0;
//    cout << i << ++i << endl;//无法知道先计算 i 还是 ++i
//    只有以下4种运算符明确了求值顺序,先算左侧,再算右侧。 分别是: &&  ||  ?:  , 其他都是不确定行为

//    求值顺序与优先级和结合律无关
//    f() + g() * h() + j() //在这个算式中,并不能确定哪个函数先计算出结果,调用顺序不确定。

//    !! 类型提升
    pIndexofTest(1);
    bool b = true;
    bool b2 = -b;
    cout << b2 << endl;//输出 1 计算-b的时候回发生小整数类型提升至稍大的整数类型int 即 int 形的 -1; -1 不为 0 在转换成bool形会转换成 true ,因此此处输出 1

    cout << "Hello, World!" << endl;
    return 0;
}