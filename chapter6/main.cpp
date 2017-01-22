#include <iostream>
#include <string>
#include <vector>
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
//void print(int &arr[10]){}//错误,将arr声明成了引用的数组,数组里存了10个int形的引用
void print(int (&arr)[10]){}//正确,arr是具有10个int的int形数组的引用

//  !!! 传递多维数组,数组名本身是指向数组首元素的指针,而多维数组是数组的数组,因此指针是要指向数组的指针,因此后面的数组大小不可省略
void print2(int *matrix[10]){}//错误,10个指针构成的数组
//void print2(int matrix[][10]){}//和上面等价,更能看出参数意义
void print2(int (*matrix)[10]){}//正确,指向10个int组成的数组的指针

//  !!!! 练习6.22 编写一个函数,令其交换两个int指针,练习6.24也很值得注意
void swapPointer(int *a,int *b){
    int *tmp = a;
    a = b;
    b = tmp;
}
//上面是错误写法,既不会交换指针也不会交换指针的值
//下面是正确写法,要知道形参只是拷贝!!!  一个问题,可以定义指针的指针,那么指针可以定义多少层呢?
void swapPointer(int *&a,int *&b){
    int *tmp = a;
    a = b;
    b = tmp;
}

//  !!  练习6.24 下面代码中的错误
void print(const int ia[10]){
    for(size_t i = 0; i != 10; ++i)
        cout << ia[i] << endl;
}
//  值得注意的是上面的代码参数的维度10只是我们期望的维度,实际上不一定,不是10维同样可传入,因此有一定风险


//  !!! 含有可变形参的函数(C语言版本如何实现??)
void muiltParam(initializer_list <string> st){
    for(auto bg = st.begin(); bg != st.end(); ++bg){
        cout << *bg << " + ";
    }
    cout << endl;
}
void muiltParam2(int a,initializer_list <string> st){
    cout << "output a int value: " << a << endl;
    for(auto bg = st.begin(); bg != st.end(); ++bg){
        cout << *bg << " + ";
    }
    cout << endl;
}

//  !!! 不要返回局部对象的引用或指针 ,调用一个返回引用的函数返回左值,其他返回类型得到右值
const string & manip(){
    string ret;
    if(!ret.empty())
        return ret;//错误,返回了局部对象的引用
    else
        return "Empty";//错误,"Empty"是个局部临时变量
}

//  ! 函数可以返回花括号包围的值得列表
vector <string> process(){
    return {"hen","ha","hei","ha"};
}
vector <string> process(initializer_list <string> iStr){
    vector <string> vecStr;
    auto a = iStr.end();
    while (a != iStr.begin()){
        vecStr.push_back(*--a);
    }
    return vecStr;
}

//  递归输出vector对象的值
//  自己写的不太好的写法
int recvecLen = 10;
void recVec(vector <int> vec,int lev){
    if(lev == recvecLen - 1){
        cout << vec[lev] << " ";
        return;
    }
    cout << vec[lev] << " ";
    recVec(vec,lev + 1);
}
//  答案的写法
void recVec2(vector <int> vec, unsigned index){
    unsigned sz = vec.size();
    if(!vec.empty() && index < sz){
        cout << vec[index] << " ";
        recVec2(vec,index + 1);
    }
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

//    !!! 含有可变形参的函数//initializer_list中的元素永远是常量值!!!//使用引用是为了避免拷贝!!!
    pIndexofTest(5);
    muiltParam({"hello","haha","nima"});
    muiltParam2(2,{"a","b","c"});

//    ! 函数可以返回花括号包围的值得列表
    pIndexofTest(6);
    vector <string> str1 = process();
    for(auto a : str1){
        cout << a << endl;
    }
    vector <string> str2(process({"aa","bb","cc"}));
    for(auto a : str2){
        cout << a << endl;
    }

//    ! 递归输出vector对象的值
    pIndexofTest(7);
    vector <int> iVec;
    for (int j = 0; j < 10; ++j) {
        iVec.push_back(j*2);
    }
    recVec(iVec,0);

//    !!! 返回数组指针的几种办法
//    直接返回
//    int (* func(int i))[10];//返回指向10个int的数组的指针
//    类型别名
//    typedef int arrT[10];
//    using arrT = int [10];
//    arrT * func(int i);
//    使用尾置返回类型
//    auto func(int i) -> int(*) [10];
//    使用decltype
//    int odd[10] = {1};
//    decltype(odd) * func(int i);



    return 0;
}