#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    unsigned char c = -1;
    printf("%d\n",c);// 255
    cout << c << endl;// 输出空字符

    //含有无符号类型的表达式
    unsigned u = 10;
    int i = -42;
    cout << i + i << endl;// -84
    cout << u + i << endl;// 4294967264  首先把-42转换成无符号的数，转换过程：-42 + 无符号的最大数  然后加上 10
    cout << i + u << endl;// 4294967264

    // 无符号数减去一个值，无论这个值是有符号还是无符号的，都必须确保解不能是一个负值
    unsigned u1 = 42,u2 = 10;
    cout << u1 - u2 << endl;// 32
    cout << u2 - u1 << endl;// 4294967264

    //unsigned 不会小于 0 ，因此下面的循环会是一个死循环，在j = 0 时，循环正常 j-- 后 会等于unsigned int 的最大值 4294967295
//    for (unsigned j = 10; j >= 0; --j) {
//        cout << j << endl;
//    }

    int i1 = -10;
    cout << u + i1 << endl; // 0

    //c++ 11 的列表初始化
    int c11{11};
    cout << c11 << endl;

    long double ld = 3.1415926;
//    int a{ld},b = {ld};//报错：存在丢失信息的风险（int 可能存不下ld的值）
    int cc(ld),d = ld;// 正确： 转换执行，的确丢失了部分值

    return 0;
}