#include <iostream>
#include <string>

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


size_t countCalls(){
    static size_t cnt = 0;
    return cnt++;
}

void pointerPara(int *ip1,int *ip2){
    *ip1 = 0;
    ip2 = 0;
}

void pSwap(int *ip1,int *ip2){
    int tmp = *ip1;
    *ip1 = *ip2;
    *ip2 = tmp;
}

//    返回s中c第一次出现的位置
//    引用行参cnt统计c出现的次数
string::size_type findChar(const string &s, char c,string::size_type &cnt){
    auto position = s.length();
    auto len = position;
    cnt = 0;
    for(decltype(position) i = 0; i < len; ++i){
        if(s[i] == c){
            ++cnt;
            if(position == len){
                position = i;
            }
        }
    }
    return position;
}

int main() {

//    ！！！ 局部静态变量
    pIndexofTest(1);
    int loopCount = 10;
    while (loopCount--)
        cout << countCalls() << " ";
    cout << endl;

//    ！！！ 指针形参，指针还是值传递，指针拷贝之后，两个指针是不同的指针，因为指针我们可以间接的访问他所指的对象，所以可以通过指针修改他指向对象的值
    pIndexofTest(2);
    int iVal1 = 4,iVal2 = 5;
    pointerPara(&iVal1,&iVal2);
    cout << iVal1 << " " << iVal2 << endl;

//  ！ 练习6.10
    pIndexofTest(3);
    int iVal3 = 22,iVal4 = 33;
    pSwap(&iVal3,&iVal4);
    cout << iVal3 << " " << iVal4 << endl;

//    ！！！ 使用引用行参返回多个参数（返回多个参数有多种办法，比如定义个结构体，返回结构体）
    pIndexofTest(4);
    string s = "hello world";
    char c = 'l';
    string::size_type cnt = 0,poz;
//    返回s中c第一次出现的位置
//    引用行参cnt统计c出现的次数
    poz = findChar(s,c,cnt);
    cout << poz << " " << cnt << endl;


    return 0;
}