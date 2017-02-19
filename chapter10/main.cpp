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


template <typename T>
void print(T& t){
    for(auto a : t)
        cout << a << " ";
    cout << endl;
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
    {
        vector <int> iVec{1,2,4};
        print(iVec);
        fill(iVec.begin(),iVec.end(),0);
        print(iVec);
        fill_n(iVec.begin(),iVec.size(),333);
        print(iVec);
        fill_n(iVec.begin(),iVec.size() + 10,2);
        print(iVec);
    }

    return 0;
}