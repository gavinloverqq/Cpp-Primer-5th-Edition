#include <iostream>
#include <vector>
#include <string>
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


struct ST{
    int a;
    double b;
    char c;
    long long l;
};

vector <int> ivec5(10,1);//sizeof 为24
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

//    !!! C++早期负数商是向上或向下取整、C++11新标准规定一律向0取整
    pIndexofTest(2);
    int ival1 = 3,ival2 = -2;
    cout << ival1 / ival2 << " mod: " << ival1 % ival2 << endl;//输出-1

//    !! 赋值运算符
    pIndexofTest(3);
    int ival3;
    cout << (ival3 = 4) << endl;//赋值运算符的结果是他左侧的对象,
    cout << (ival3 = 3.64) << endl;//结果的类型就是左侧的类型,类型不同时,右侧转化成左侧的类型

//    vector的又一种赋值方法
    pIndexofTest(4);
    ival3 = {3};//p129 说此处会发生窄化转换的错误,但是此处并没有发生错误 !!!!!!
    vector <int> ivec;
    ivec = {1,2,3,4};//非内置类型可以使用初始化列表来赋值
    for (auto a : ivec)
        cout << a << " ";
    cout << endl;

//    ! 多重赋值
    pIndexofTest(5);
    int ival4,*pVal4;
//    ival4 = pVal4 = 0;//多重赋值类型由右边的对象类型转换得到,此处指针无法转换为int
//    ival4 = *pVal4 = 0;//略加修改就可以了
    double dVal;
    ival4 = dVal = 3.5;
    cout << ival4 << " " << dVal << endl;//3 3.5
    dVal = ival4 = 3.5;
    cout << ival4 << " " << dVal << endl;//3 3
    string s1,s2;
    s1 = s2 = "aha";

//    !! 复合运算符的求值次数与等价的非复合运算符是有区别的
    int ival5 = 0;
    ival5 += 10;//只求值一次
    ival5 = ival5 + 10;//求值一次,赋值一次

//    后置运算符执行自增后要返回其原始副本
    pIndexofTest(6);
    int iArr[] = {1,2,3,4,-1,-4};
    auto pa = begin(iArr);
    while (pa != end(iArr) && *pa >= 0)
        cout << *pa++ << " ";// *pa++ 等价于 *(pa++) 后置递增运算符其实是执行自增运算后然后返回其原始副本 而不是以前理解的(pa++)这种操作就是++后再返回,返回的是++后的结果。要知道后置递增运算符不管如何都要返回其原始副本

//    优先级判断
    pIndexofTest(7);
    //证明.运算符优先级高于*运算符
    string str = "hahah nnnn",*pStr = &str;
    cout << pStr->size() << endl;
    cout << (*pStr).size() << endl;//如果写成 *pStr.size() 则先算pStr.size() 然后解引用,但是pStr.size()非法,指针没有这个成员
    cout << *pStr++ << endl;//证明++高于*;否则先算解引用pStr得到string 但是string没有++ 运算,会报编译错误

//    ! 条件运算符优先级非常低
    pIndexofTest(8);
    int grade = 73;
    cout << ((grade < 60) ? "fail" : "pass");
//    cout << (grade < 60) ? "fail" : "pass"; //cout << (grade < 60) 输出0或者1,然后cout ? "fail" : "pass";
//    cout << grade < 60 ? "fail" : "pass"; //cout << grade 然后 cout < 60 ? "fail" : "pass";

//    位运算符
    pIndexofTest(9);
    int iVal6 = -1;
    unsigned char uChVal1 = 1, uChVal2 = 1;
    cout << (uChVal1 >> 1) << endl;// 0 小整形会提升至int
    cout << (iVal6 >> 1) << endl;//输出 -1 //带符号的数右移左侧插入的是0还是1,要视环境而定。 !!!
    cout << (uChVal2 << 1) << endl;// 2

//    ! 位运算符优先级高于关系运算符、赋值、条件运算符,低于算数运算符
    pIndexofTest(10);
    cout << 42 + 10;
    cout << (42 > 10);
//    cout << 42 > 10;//移位运算符高于关系运算符

//    !!! 习题4.25 位运算符会提升小整数类型
    pIndexofTest(11);
    cout << (~'q' << 6) << endl;//q是char形,8位,0111 0001 提升至int 0000 0000 0000 0000 0000 0000 0111 0001 取反并左移6位 1111 1111 1111 1111 1110 0011 1000 0000 得到一个有符号的负数,c++的整数以补码存储,取反加一得到1000 0000 0000 0000 0001 1100 1000 0000

//    !!! sizeof,注意vector与string的输出,还有指针的输出,以及非法指针的处理
    pIndexofTest(12);
    ST data,*p;
    int *ip;
    cout << sizeof(ST) << //ST中总共有 4 + 8 + 1 + 8 = 21字节,但是此处输出 32 字节,还有11字节是什么???
            " " << sizeof(data) <<
            " " << sizeof *p << //sizeof 优先级与 * 一样,表达式从右往左,等价于 sizeof(*p) ;sizeof不会去解引用指针,而是直接计算所占空间大小。因此即使 p 指向未定义的地方,此处也不会出错
            " " << sizeof p <<
            " " << sizeof(ip) <<
            " " << sizeof(data.b) <<
            " " << sizeof(ST::b) << endl;//C++ 11 允许使用作用域运算符来获取类成员的大小
    vector <int> ivec2;
    vector <int> ivec3;
    vector <int> ivec4(50);//sizeof 为 24 此处值得思考!!!
    ivec2.push_back(1);
    cout << sizeof(ivec2) << " " << sizeof(ivec3) << " " << sizeof(ivec4) << " " << sizeof(ivec5) << endl;//此处均输出24
    cout << sizeof(string) << endl;//24
    int x[10],*px = x;//sizeof不会把数组转化为指针
    cout << sizeof(x) / sizeof(*x) << endl;
    cout << sizeof(px) / sizeof(*px) << endl;
    cout << sizeof(char *) << " " << sizeof(int *) << " " << sizeof(float *) << " " << sizeof(double *) << " " << sizeof(void *) << " " << endl;
    cout << (5 / -2) << " " << (5 % -2) << endl;//商向0取整,余数和被除数同号

//    算术转换
    pIndexofTest(13);
    int iVal7 = -1;
    unsigned int uiVal1 = 1;
    cout << (iVal7 * uiVal1) << endl;//有符号的会转化成无符号的数

//    !!! 强制类型转换
    pIndexofTest(14);
//    格式:castname<type>(expr);
    int iValSc1 = 5,iValSc2 = 3;
    double slope = static_cast<double>(iValSc1) / iValSc2 ;//只要不包含底层const,都可以使用static_cast
    cout << slope << endl;
    void* pVoid = &iValSc1;//static_cast可以找回void*的值
    cout << *static_cast<int*>(pVoid) << endl;

    const char *pCntCh;
    char *pCh = const_cast<char*>(pCntCh);//const_cast只能去掉const,前后类型其实是一样的
//    char *pChSc = static_cast<char*>(pCntCh);//static_cast不能转化掉const性质
//    static_cast<string>(pCntCh);//书上说正确,但是运行时发生错误,exit code 11,带const 不能使用static_cast ????
//    const_cast<string>(pCntCh);//错误,const_cast只改变常量属性;也就是说只能改变对象底层的const
    int iVal8 = 65,*ip1 = &iVal8;
    char *pCh1 = reinterpret_cast<char*>(ip1);
    string rcStr(pCh1);
    cout << rcStr << endl;//会读内存里的内容,能读到A

//    旧式C风格强制类型转换
//    type(expr);//函数形式的类型转换
//    (type)expr;//C语言风格的强制类型转换

//    练习 4.37 a
    {
        const string *ps;
        void *pv;
//        改写下面旧式转换
        pv = (void*)ps;
        pv = static_cast<void*>(const_cast<string*>(ps));
    }
    return 0;
}