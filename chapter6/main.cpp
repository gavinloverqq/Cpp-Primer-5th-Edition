#include <iostream>
#include <string>
#include <vector>

#include <cassert>

//#define NDEBUG
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

//  ! 仅仅返回值不同的函数不是重载,第二个声明是重复声明,是错误的。很好理解这条规则,因为你用了这个函数,但是编译器不知道你需要它返回什么,因此不知道是用哪个函数


//  !!! 关于顶层const与底层const的一点讨论
//  顶层const:指的是const对象是常量,底层const指的是const的指针所指对象,或者引用的对象是常量
/*{
//  不能删除底层const
    int i;
    const int &j = i;
    const int *p = &i;
    int &r = j, *q = p;//错误,此处删除了底层const

    const int ci = 5;
    int iVal = ci;//可以,此处删除了顶层const
}*/

//  !!! 重载与const形参
    void fun(int i);
    void fun(const int i);//重复声明,错误!
    void fun(int *i);
    void fun(int* const i);//重复声明

    void fun(int* i);
    void fun(const int *i);//新函数,作用于指向常量的指针,为什么是新函数,参看上一条,不能删除底层const,因此指针指向的常量才能传入此函数
    void fun(int& i);
    void fun(const int& i);//新函数,作用域常量引用


//  !!! const cast 重载的应用
const string& shorterStr(const string& s1,const string& s2){
    return s1.length() < s2.length() ? s1 : s2;
}
//以上函数对非常量的调用返回的也是常量,因此要获得一个新函数:当非常量参数传入,返回非常量参数,常量返回常量
string& shorterStr(string& s1,string& s2){
    auto& r = shorterStr(const_cast<const string&>(s1), const_cast<const string&>(s2));
    return const_cast< string& >(r);
}

//  !!! 默认实参(本节有与书中的描述不对的地方!!!!!!!!!)
//void dfuFuc1(int a = 2,int b,string c){}//error: missing default argument on parameter 'b',//一个形参有了默认值,后面的所有值都需要有默认值,很容易理解:一旦前面有默认值后面没有默认值,那我传入函数一些参数,编译器怎么知道我前面的参数是要取代默认参数还是使用默认参数呢?如:fun(int a = 1,int b = 2,int c),调用:fun(3,5) 3传给a还是b呢?;
void dfuFuc1(int a ,int b = 2,string c = "c"){}
//void dfuFuc1(int ,int b = 3,string);//error: redefinition of default argument//函数声明中不能修改一个已存在的默认值
//void dfuFuc1(int ,int b = 2,string c = "c");//错误! 此处与书中p212描述有出入!需要回头再细看!!!!!!!

//  ! constexpr 函数 (与书本描述有不对的地方!!!!!!!!!)
constexpr int newSz(){
    return 42;
}//函数类型、所有形参、都必须是字面值。函数体有且只有一条return,隐式的内联函数
constexpr int foo = newSz();
constexpr size_t scale(int cnt){//允许返回值不是一个常量
    return cnt * newSz();
}
int GiVal = scale(2);//传入必须是字面值,才能得到产量表达式
int GiVal2 = 2;
int GiVal3 = scale(GiVal2);//书中说变量传入会错误,实际编译并没有!!!!!!

//  !!! 关于内联函数为什么要放在头文件中,见习题6.43
//  因为内联函数的定义对于编译器而言必须是可见的,编译器能够在调用点内联展开该函数的代码,所以仅有函数的原型不够。内联函数与一般函数不同,内联函数有可能在程序中定义不止一次因此此时必须保证所有的源文件中定义完全相同,在头文件中可保证这一点。



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

//    !!! assert 与NDEBUG
    pIndexofTest(8);
    {
        int iVal;
        cin >> iVal;
        assert(iVal > 6);
        cout << iVal << " > 6" << endl;
//        学习几个局部静态变量,以及 cerr
#ifdef NDEBUG
        cerr << "Error: " << __FILE__ << " : in function " << __func__
        << " at line " << __LINE__ << endl
        << "       Compiled on " << __DATE__
        << " at " << __TIME__ << endl;
#endif
    }

    return 0;
}