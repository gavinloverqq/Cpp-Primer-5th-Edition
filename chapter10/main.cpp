#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <array>
#include <list>
#include <forward_list>
#include <queue>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <functional>

using namespace std;
//using std::placeholders::_1;//placeholders命名空间在std空间中,这种时单独定义每一个
using namespace std::placeholders;//这样直接定义了所有的
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

template <typename T>
void print(T& t){
    for(auto a : t)
        cout << a << " ";
    cout << endl;
}


bool isShorter(const string& s1,const string& s2){
    return s1.length() < s2.length();
}

bool partitionBylength(const string& s1){
    return s1.length() < 5;
}

bool checkSize(const string& s,string::size_type sz){
    return s.size() >= sz;
}

void printString(ostream& os,const string& s,const char c){
   os << s << c;
}
int main() {

//  !! find的使用,find使用了 == 操作,在[a,b]区间内查找,返回位置
    pIndexofTest(1);
    {
        vector <int> iVec{1,4,6,8};
        cout << find(iVec.begin(),iVec.end(),4) - iVec.begin() << endl;//find返回的是指针的位置
        cout << find(iVec.begin(),iVec.begin() + 3,6) - iVec.begin() << endl;
        cout << find(iVec.begin(),iVec.end(),10) - iVec.end() << endl;
        cout << find(iVec.begin(),iVec.end() - 1,8) - iVec.begin() << endl;//
        cout << find(iVec.begin(),iVec.end(),8) - iVec.begin() << endl;
    }

//    练习10.1
    pIndexofTest(2);
    {
        vector <int> iVec{1,4,6,8,4};
        cout << count(iVec.begin(),iVec.end(),4) << endl;
        list <string> sLst{"aaa","bbb","ccc","aaa"};
        cout << count(sLst.begin(),sLst.end(),"aaa") << endl;
    }

//    !!! 泛型算法不会执行迭代器操作,不会改变底层容器大小,不会直接添加或删除元素

//    ! accumulate 的使用,注意区间范围,很容易理解这个范围,因为第二个参数一般是尾后迭代器,如果右边是闭区间,则会访问未定义的地址
    pIndexofTest(3);
    {
        vector <int> iVec{1,2,4,5,6};
        cout << accumulate(iVec.begin(),iVec.end(),0) << endl;//在区间 [a,b) 内以初值为 c 累加

        list <string> sLst{"aa","bb","cc"};
//        cout << accumulate(sLst.cbegin(),sLst.cend(),"dd")<< endl;//错误,const char * 不能转换成string
        cout << accumulate(sLst.cbegin(),sLst.cend(),static_cast<string>("dd")) << endl;

//        !!! accumulate 的第三个参数决定了和的类型,0是整形,因此和就是整形,0.0是double,和就是小数
        vector <double> dVec{1.22,2.33,3.44};
        cout << accumulate(dVec.begin(),dVec.end(),0) << endl;
        cout << accumulate(dVec.begin(),dVec.end(),0.0) << endl;
    }

//    !! equal 利用 == 来判断,通常第二个序列比第一个序列长
    pIndexofTest(4);
    {
        vector <int> iVec1{1,3,2};
        vector <int> iVec2{1,3};
        cout << equal(iVec1.begin(),iVec1.end() - 1,iVec2.begin()) << endl;
        cout << equal(iVec1.begin(),iVec1.end(),iVec2.begin()) << endl;//第二个序列比第一个序列短也没什么问题???
    }

//    !!! 练习10.5 对于string 与 c 风格字符串 调用equal会有什么不同
    pIndexofTest(5);
    {
        char* p[] = {"aa","bb","cc"};
        char* p2[] = {"aa","bb","cc"};
        char* r[] = {strdup(p[0]),strdup(p[1]),strdup(p[2])};//stdup将字符串拷贝到新的位置
        string s[] = {"aa","bb","cc"};
        char* tp[] = {p[0],p[1],p[2]};

//        !!!!! 这里有很多问题值得思考
//        equal 使用 == 来比较两个序列中的元素是否相等,string 重载了 == 比较两个串的长度是否相同,对应串中字符是否相同,而c风格字符串,本质是char* 类型,用 == B比较两个char * 对象,只检查两个指针值是否相等,即比较地址是否相同,而不比较其中字符是否相同
//        所以两个指针都指向相同地址是,equal返回true,否则即使串内容完全相同,也会返回false
        cout << equal(begin(p),end(p),begin(tp)) << endl;// 1
        cout << equal(begin(p),end(p),begin(p2)) << endl;// 1 注意此处,也就是说p2和p地址相同

//        !!!! 注意下面的讨论,int的2维数组,与char 二维数组有何不同?char 2维数组中的以为名字指的是一个串,而int指的是一个数组的首地址
        cout << p - p2 << endl;//4
        cout << p2[0] - p[0] << endl;//0
//        cout << p2[0] - p2 << endl;//错误 error: 'char *' and 'char **' are not pointers to compatible types 二维数组中地址的问题???
        cout << &p2[0] << endl;
        cout << p2[0] << endl;
        cout << p2 << endl;
        cout << reinterpret_cast<unsigned long long> (p2[0]) - reinterpret_cast<unsigned long long>(p) << endl;
        {
            int a[][2] = {
                    {1,2},
                    {3,4}
            };
            int b[][2] = {
                    {2,3},
                    {3,4}
            };
            cout << a << endl;//0x7fff5c2a3930
            cout << a[0] << endl;//0x7fff5c2a3930
//            cout << a - a[0] << endl; //错误
        }


        cout << equal(begin(p),end(p),begin(r)) << endl;// 0
        cout << equal(begin(p),end(p),s) << endl;// 1
    }

//    ! fill 操作,fill不检查写操作,,在使用写容器元素的算法时,要保证序列原大小不少于我们要写的元素个数,算法不会执行容器操作,不可能改变容器大小
    pIndexofTest(5);
    /*{
        vector <int> iVec{1,2,4};
        print(iVec);
        fill(iVec.begin(),iVec.end(),0);
        print(iVec);
        fill_n(iVec.begin(),iVec.size(),333);
        print(iVec);
        fill_n(iVec.begin(),iVec.size() + 10,2);
        print(iVec);
    }*/

//    ! back_insert 接受一个指向容器的引用,返回一个与该容器绑定的插入迭代器
    pIndexofTest(6);
    /*{
        vector <int> iVec;
        auto it = back_inserter(iVec);
        *it = 44;
        print(iVec);

//        !!! 与书上p341说法不一致
//        vector <int> iVec2;
//        fill_n(back_inserter(iVec2),10,0);
//        print(iVec2);
    }*/

//    ! copy 拷贝算法
    pIndexofTest(7);
    {
        int a1[] = {1,2,34,5};
        int a2[10] = {7,8,9,10,11,12,13,14,15,16};
        auto a = copy(begin(a1),end(a1),a2);//接受三个参数,前两个迭代器决定范围,最后一个迭代器表示目的序列的起始位置
        print(a2);
        cout << *a  << endl;//返回值指向拷贝序列的最后一个字符的位置
    }

//    ! replace
    pIndexofTest(8);
    {
        list <int> iLst(10,11);
        iLst.front() = 12;
        replace(iLst.begin(),iLst.end(),11,0);
        print(iLst);
        vector <int> iVec;
        replace_copy(iLst.begin(),iLst.end(),back_inserter(iVec),12,333);
//        replace_copy(iLst.begin(),iLst.end(),iVec.begin(),12,333);//同测试6,和书中不一样
        print(iLst);
//        print(iVec);
//        cout << iVec[1] << endl;
    }


//    !!! 练习10.7
    pIndexofTest(9);
    {
        vector <int> iVec;
        iVec.resize(10);//改变容量，改变size
//        iVec.reserve(10);//改变容量，不改变size
        fill_n(iVec.begin(),10,2);
        print(iVec);
    }

//    !! unique 需要先排序才可使用unique，算法不能执行容器操作，因此要使用erase删除后面重复的元素，unique返回不重复区域的后一个位置，不执行erase的话，后面的元素仍然存在，但是不知道值是什么
    pIndexofTest(10);
    {
        vector <string> sVec{"aa","ee","ff","bb","cc","bb"};
        sort(sVec.begin(),sVec.end());
        auto a = unique(sVec.begin(),sVec.end());
        print(sVec);
        sVec.erase(a,sVec.end());
        print(sVec);
    }

//    !!! 练习10.10算法不改变容器的大小的原因是什么？

//    ! 项选法传递函数，（stable_sort是怎么实现的）
    pIndexofTest(11);
    {
        vector <string> sVec{"aaf","eee","ffs","bb","ccdd","bb"};
        sort(sVec.begin(),sVec.end());
        auto a = unique(sVec.begin(),sVec.end());
        print(sVec);
        sVec.erase(a,sVec.end());
        print(sVec);
        stable_sort(sVec.begin(),sVec.end(),isShorter);//stable_sort 稳定排序是怎么实现的？
        print(sVec);
    }

//    !!! 练习10.13 partition 算法的使用 ,接收一个谓词，对容器内容进行划分，使得谓词返回true的值会排在容器的前半部分，算法返回一个迭代器，指向最后一个true的元素后面
    pIndexofTest(12);
    {
        vector <string> sVec{"aafxxx","eeeww","ffsqqqq","bb","ccdd","bb"};
        sort(sVec.begin(),sVec.end());
        print(sVec);
        auto p = partition(sVec.begin(),sVec.end(),partitionBylength);
        print(sVec);
        for (;p != sVec.end() ; ++p) {
            cout << *p << " ";
        }
        cout << endl;

    }

//    !!! lambda表达式
    pIndexofTest(13);
    {
        auto f = [] { return 42;};
        cout << f() << endl;
        auto f1 = [] { cout << 5 << endl;return 42;};//如果lambda的函数体包含任何单一的return语句之外的内容，且未制定返回的类型，则返回void？？？
        cout << f1() << endl;
    }

//    !! 向lambda传递参数‘
    pIndexofTest(14);
    {
        vector <string> sVec{"aaf","eee","ffs","bb","ccdd","bb"};
        sort(sVec.begin(),sVec.end());
        auto a = unique(sVec.begin(),sVec.end());
        print(sVec);
        sVec.erase(a,sVec.end());
        print(sVec);
//        stable_sort(sVec.begin(),sVec.end(),[](const string& s1,const string& s2){ return s1.length() < s2.length();});//stable_sort 使用lambda表达式
        stable_sort(sVec.begin(),sVec.end(),[](const string& s1,const string& s2) -> bool { return s1.length() < s2.length();});//stable_sort 使用lambda表达式
        print(sVec);
    }

//    !! 使用捕获参数列表
    pIndexofTest(15);
    {
        vector <string> sVec{"aaf","eee","ffs","bb","ccdd","bb"};
        sort(sVec.begin(),sVec.end());
        auto a = unique(sVec.begin(),sVec.end());
        print(sVec);
        sVec.erase(a,sVec.end());
        print(sVec);
        stable_sort(sVec.begin(),sVec.end(),isShorter);
        print(sVec);
        int sz = 3;
        auto wc = find_if(sVec.begin(),sVec.end(),[sz](const string& s1){ return s1.length() > sz;});// 捕获参数列表
        auto count = sVec.end() - wc;
        cout << count << " words length is longer than " << sz << endl;
    }

//    !! 练习
    pIndexofTest(16);
    {
        auto f1 = [](int a,int b)->int{ return a + b;};
        cout << f1(3,5) << endl;

        int iVal1 = 2;
        auto f2 = [iVal1](int a)->int{ return a + iVal1;};
        cout << f2(2) << endl;

    }

//    !! 值捕获 ，值捕获的前提是变量可以拷贝，与函数参数不同被捕获的变量是在lambda创建时拷贝，而不是在调用时拷贝
    pIndexofTest(17);
    {
        int iVal1 = 33;
        auto f1 = [iVal1]{ return iVal1;};
        iVal1 = 0;
        cout << f1() << endl;// 33
    }

//    !! 引用捕获,引用捕获与返回引用：使用引用捕获一个变量必须确保被引用的对象在lambda执行的时候是存在的，lambda捕获的是局部变量。这些变量在函数结束的时候就不存在了，如果lambda可能在函数结束后执行，捕获的引用指向的局部变量已经消失
    pIndexofTest(18);
    {
        int iVal = 22;
        auto f1 = [&iVal]{ return iVal;};
        iVal = 1;
        cout << f1() << endl;// 1

        ostream& os = cout;
        char c = ' ';
        vector <string> sVec{"aaf","eee","ffs","bb","ccdd","bb"};
        for_each(sVec.begin(),sVec.end(),[&os,c](const string& s){os << s << c;});// ostream必须使用引用捕获
    }

//    !! 隐式捕获，注意混合捕获时显式捕获的方式必须与隐式捕获的方式不同前面使用了&，后面必须使用值捕获，前面使用了=，后面必须使用引用捕获；隐式捕获必须写在最前面
    pIndexofTest(19);
    {
        int sz = 3;
        vector <int> iVec{2,3,1,5,4,8,11};
        sort(iVec.begin(),iVec.end());
        auto p = find_if(iVec.begin(),iVec.end(),[=](int i){ return i > sz;});// = 表示值捕获
        for (;p != iVec.end();++p) {
            cout << *p << " ";
        }
        cout << endl;

        ostream& os = cout;
        int add = 100;
        for_each(iVec.begin(),iVec.end(),[&,add](int a){os << a + add << " ";});// & 表示引用捕获
    }

//    !! 可变lambda 值拷贝的变量,lambda不会改变其值,如果要改变其值,必须在参数列表首加上mutable关键字
    pIndexofTest(20);
    {
        int i = 42;
//        auto f = [i](){ int k = 5;return k+i;};// 正确;
//        auto f = [i](){ return ++i;};//error: increment of read-only variable ‘i’
        auto f = [i]()mutable { return ++i;};//mutable关键字
//        auto f = [&i](){ return ++i;};//mutable关键字
        cout << i << endl;
        i = 10;
        auto j = f();
        cout << j << endl;//如果是引用此处应该输出11

        int s = 5;
        auto f2 = [&s](){ return ++s;};//可通过引用改变
        cout << s << endl;//5
        cout << f2() << endl;//6
        s = 10;
        cout << f2() << endl;//11
    }

//    !! 指定lambda的返回类型,当我们要为lambda定义返回类型时,必须使用尾至返回类型
    pIndexofTest(21);
    {
        vector <int> iVec{1,2,3,4,-1,-2,-4};
//        transform(iVec.begin(),iVec.end(),iVec.begin(),[](int i){ return i < 0 ? -i : i;});//返回值是个表达式,因此能推断出返回值类型

        transform(iVec.begin(),iVec.end(),iVec.begin(),[](int i){
            if(i < 0)
                return -i;
            else
                return i;
        });//按书本所说此处应该发生错误,不能推断出lambda的返回类型,但是编译可以通过
        print(iVec);

        //当我们要为lambda定义返回类型时,必须使用尾至返回类型
        transform(iVec.begin(),iVec.end(),iVec.begin(),[] (int i) -> int {
            if(i < 0)
                return -i;
            else
                return i;
        });
    }

//    ! 练习10.20
    pIndexofTest(22);
    {
        int sz = 3;
        vector <int> iVec{2,3,1,5,4,8,11};
        long long ret = count_if(iVec.begin(),iVec.end(),[=](const int a){return a > sz;});
        cout << ret << endl;
    }

//    ! 练习10.21
    pIndexofTest(23);
    {
        int i = 10;
        auto f = [&]() -> bool {
            while (i > 0)
                --i;
            return i == 0;
        };
        cout << f() << endl;
        cout << "i = " << i << endl;
    }

//    !!! 标准库bind函数
    pIndexofTest(24);
    {
        int sz = 4;
        vector <string> sVec{"aaf","eee","ffs","bb","ccdd","bb"};
        auto p = find_if(sVec.begin(),sVec.end(),[sz](const string& s){ return s.size() >= sz;});
        cout << *(p) << endl;

        auto check4 = bind(checkSize,_1,4);
        string s = "123545";
        bool b1 =  check4(s);
        auto p2 = find_if(sVec.begin(),sVec.end(),bind(checkSize, _1, sz));//
//        auto p2 = find_if(sVec.begin(),sVec.end(),bind(checkSize, std::placeholders::_1, sz));
        cout << *p2 << endl;
    }

//    !! bind重排参数顺序
    pIndexofTest(25);
    {
        vector <string> sVec{"aaf","eee","ffs","bb","ccdd","bb"};
        sort(sVec.begin(),sVec.end(),isShorter);
        print(sVec);
        sort(sVec.begin(),sVec.end(),bind(isShorter,_2,_1));//重排参数顺序
        print(sVec);
    }

//    !! 绑定引用参数
    pIndexofTest(26);
    {
        vector <string> sVec{"aaf","eee","ffs","bb","ccdd","bb"};
        ostream& os = cout;
        char c = ' ';
        for_each(sVec.begin(),sVec.end(),[&,c](const string& s){os << s << c;});
        print(sVec);
//        for_each(sVec.begin(),sVec.end(),bind(printString,os,_1,c));//不能拷贝os;
        for_each(sVec.begin(),sVec.end(),bind(printString,ref(os),_1,c));//使用标准库函ref函数返回引用 cref函数返回const 的引用
        print(sVec);
    }
    return 0;
}