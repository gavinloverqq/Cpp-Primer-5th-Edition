#include <iostream>

using namespace std;
extern int testDefinition;

int _a = 6;//违反规定?

int reused = 444;

//c++ 11 类型别名,类似于typedef
using Node = struct {
    int a,b;
};

//struct {
//
//}//error: anonymous structs and classes must be class members //struct 后面不加分号

int main(){

    int __a = 7;//违反规定?
    int _A = 8;//违反规定?


//    cin >> int inputValue;//error: expected primary-expression before 'int'
//    int i = {3.14};//warning: narrowing conversion of '3.1400000000000001e+0' from 'double' to 'int' inside { } [-Wnarrowing] 一种不建议的窄化操作
//    double salary = wage = 999.99;//'wage' was not declared in this scope
//    int i1 = 3.14; //警告

    int h;//内置类型int 在函数体内不被初始化，会输出一个奇异值
    cout << h << endl;

//    extern int pi = 3;//error: 'extern' variable cannot have an initializer 在函数体内部,试图初始化一个由extern关键字标记的变量将引发错误
//    cout << pi << endl;

    cout << testDefinition << endl;

    int opt1 = 0xff, opt2 = 0xe1;
    cout << (opt1 bitand opt2) << " " << opt2 << endl; // 操作符替代符

    int reused = -222;
    cout << ::reused << " " << reused << endl;//使用作用域操作符,获取全局变量reused的值

//    int ival = 9;
//    int &refVal = ival;
//    int &refVal2;//error: declaration of reference variable 'refVal2' requires an initializer 引用必须被初始化

    int ival = 9;
    int *p = &ival;
    int* &refVal = p;
    int *pr = refVal;//不能定义指向引用的指针???


    int exi = 3;
    int *expi = &exi;
    *expi = *expi * *expi;
    cout << exi << endl;//9

    int ival1 = 2;
    int &refVal1 = ival1;
    int &refVal2 = refVal1;//不能建立引用的引用??

//    int ival2 = 3;
//    int& *rp = &ival2;//error

//    const int cni;//error: default initialization of an object of const type 'const int' const必须初始化

    const int cnt = 1;
    const int & refCnt = cnt;
//    int & refValCnt = cnt;//error: binding value of type 'const int' to reference to type 'int' drops 'const' qualifier

    double dval = 3.14;
    const int &ri = dval;//编译可以通过,但是是非法的

    int ival4 = 5;
    const int & refVal4 = ival4;
    ival4 = 6;
//    refVal4 = 7;//error: cannot assign to variable 'refVal4' with const-qualified type 'const int &'不可通过常引用修改变量的值

    constexpr int cntExpr = cnt + 1;//声明常量表达式

    char ch = '0';
    char* pch = &ch;
    cout << sizeof(void *) << " " << sizeof(int) << endl;//8,1//不同平台指针大小不一样大。

    Node nd;
    nd.a = 3,nd.b = 4;
    cout << nd.a << endl;

    decltype(nd) nd2;//从表达式推断出要定义的变量的类型,但不用表达式的值初始化变量 decltype(foo());//但是编译器并不调用foo()
    nd2.a = 5;
    cout << nd2.a << endl;

}


