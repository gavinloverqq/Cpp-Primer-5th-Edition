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


//  !! 顶层const形参
void fcn(const int i){/*fcn能传入const int 也能传入 int (忽略顶层const)*/}
//void fcn(int i){}//此处在定义这样的函数是错误的,因为上面的函数忽略了顶层const,和这个函数一模一样,因此不能再定义


void reset(int &i){
    i = 0;
}
void reset(int *i){
    *i = 0;
}

//  !!! 数组引用形参,两端括号必不可少
void print(int &arr[10]){}//错误,将arr声明成了引用的数组,数组里存了10个int形的引用
void print(int (&arr)[10]){}//正确,arr是具有10个int的int形数组的引用

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

//    !!! 指针或引用参与const
    {
        int i = 10;
        const int ci = i;
        reset(&i);
//        reset(&ci);//不能用指向const int对象的指针初始化int *
        reset(i);
//        reset(ci);//不能把普通指针绑定到const 对象上
//        reset(42);//不能把普通指针绑定到字面值上
    }

    return 0;
}