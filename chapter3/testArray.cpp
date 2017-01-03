#include <iostream>
#include <string>
#include <cstring>
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

int main(){

//    !! 数组的定义,注意string类型
    unsigned int cnt = 10;
//    cnt 不是常量表达式
//    string bad[cnt];//error: variable length array of non-POD element type 'string' (aka 'basic_string<char, char_traits<char>, allocator<char> >')
    string *bad = new string[cnt];//上述写法可以改成动态的声明
//    int 型的数组可以
    int arr[cnt];

//    ! 数组的初始化
    int a[] = {2,3,4};
//    int a2[3] = a;//不能使用一个数组初始化另一个数组
//    a2 = a;//理由同上


//    !!! 复杂数组声明(有圆括号的话先从圆括号读起,从内向外读)
    int arr1[10];
    int *ptrs[10];
//    int &refs[10] = /* ?? */ 不存在引用的数组
    int (*Parray)[10];//指向10个int指针组成的数组
    int (&arrRef)[10] = arr1;//绑定在 10个int组成的数组上
    int * (&ParrRef)[10] = ptrs;//绑定在 10个int指针组成的数组上

//    模仿迭代器
    pIndexofTest(4);
    int arr2[3] = {1,2,3};
    int *pEnd = &arr2[3];
    for (int *i = arr2; i != pEnd ; ++i) {
        cout << *i << " ";
    }
    cout << endl;

//    ! 使用标准库函数
    pIndexofTest(5);
    int arr3[] = {3,3,3,3};
    int *pStdBegin = begin(arr3);
    int *pStdEnd = end(arr3);
    while (pStdBegin != pStdEnd)
        cout << *pStdBegin++ << " ";//由此可得出++ 优先级高于 *
//      cout << (*pStdBegin)++ << " ";//这样写的话会死循环,因为每次把(*pStdBegin)上的值取出来加1,但是指针没有加,永远达不到循环终止条件。
    cout << endl;

//    两个指针指向不相关的对象
    pIndexofTest(6);
    int ival1 = 2,ival2 = 3;
    int *pVal = &ival1, *pVal2 = &ival2;
    cout << (pVal < pVal2) << endl;//可以比较,但是比较毫无意义。

//    数组指针越界问题
    pIndexofTest(7);
    int arr4[] = {4,5,6,7};
    int *pArr4_1 = arr4;
    int *pArr4_2 = pArr4_1 + 4;//尾后指针,正确,但是不可解引用
    int *pArr4_3 = pArr4_1 + 5;//错误,越界了,但是编译器并不报错

//    !! 数组中使用auto于decltype
    pIndexofTest(8);
    int arr5[] = {5,6,7,7};
//    auto pa[](arr5);//auto 不能定义数组
    auto pa(arr5);//等价于 auto pa = arr5;
    cout << *pa << endl;
    decltype(arr5) decp;//注意与上面和下面的区别
    cout << decp << endl;//输出地址 0x7fff54db2af0
    decltype(arr5) decArr = {1,2,3};//4个int组成的数组,不是指针数组!!!
//    decltype(arr5) decArr = {1,2,3,3,4,5,6,7};//error: excess(过量) elements in array initializer
    for (auto a : decArr)//输出 1 2 3 0
        cout << a << " ";
    cout << endl;

//    !!! 注意数组索引可以使用负值,和string、vector不一样,数组的索引 不 是 无符号的值
    pIndexofTest(9);
    int arr6[] = {1,2,3,4,5,6,7,8,9};
    int *pArr6_1 = arr6 + 4;
    cout << pArr6_1[3] << endl;//相当于 *(pArr6 + 3) 输出8
    cout << pArr6_1[-2] << endl;//相当于 *(pArr6 - 2) 输出2

//    !! 指向常量的指针 与 常量指针 与 绑定到常量的引用。为什么没有常量引用?因为引用一经绑定便不能再绑定到其他对象,因此没有常量引用
    pIndexofTest(10);
    const int cntRP = 100;
    const int * pCntRP = &cntRP;
    const int *const cnpCntRP = &cntRP;
    const int &rCntRp = cntRP;

//    ! C风格的字符串操作:拷贝与连接

    pIndexofTest(11);
    char cStr1[] = "hello",cStr2[] = "world";
    char cStr3[30];
    strcpy(cStr3,cStr1);
    strcat(cStr3," ");
    strcat(cStr3,cStr2);
    for (int j = 0; j < strlen(cStr3); ++j) {
        cout << cStr3[j];
    }
    cout << endl;

//    !!! string对象转化为C风格字符串,注意返回值是const类型
    pIndexofTest(12);
    string str1 = "code code haha";
//    char *cStr4 = str1;//不能用string对象初始化char*
//    const char *cStr4 = str1.c_str();
//    const char *bd = begin(cStr4);//此处不可用begin();
    const char *cStr4 = str1.c_str();//字符串返回的是const char 的指针!!!
    const char *bd = cStr4,*ed = cStr4 + strlen(cStr4);
    while (bd != ed)
        cout << *bd++;
    cout << endl;


}