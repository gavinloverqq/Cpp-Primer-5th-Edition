#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <array>
#include <list>
#include <forward_list>
#include <queue>
#include <sstream>


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


class Test{
public:
    int i,j;
    string str;
    Test(){
        cout << "defualt constructor" << endl;
    }
    Test(int ii,int jj,string s):i(ii),j(jj),str(s){}
};
int main() {

//    !! 除string vector deque，array 其他容器只支持 ++ -- == != * -> 这几个操作！！！
    pIndexofTest(1);
    {
        list <int> iLst;
        iLst.push_back(5);
        iLst.push_back(6);
        iLst.push_back(7);
        list<int>::iterator plstbg = iLst.begin();
        list<int>::iterator plstend = iLst.end();

//        while (plstbg < plstend)(不支持这个操作)
        while (plstbg != plstend){
            cout << *plstbg++ << " ";
        }
        cout << "  " << endl;

        deque <int> idq;
        idq.push_back(4);
        idq.push_back(5);
        idq.push_back(6);
        idq.push_back(7);
        deque<int>::reverse_iterator rpdqbg = idq.rbegin();
        deque<int>::reverse_iterator rpdqend = idq.rend();
        while (rpdqbg != rpdqend){
            cout << *rpdqbg++ << " ";
        }
        cout << endl;

        list<string> strLst;
        strLst.push_back("hello");
        strLst.push_back("wworld");
        strLst.push_back("cccc");
        strLst.push_back("xxxxxxxxxx");
        list<string>::reference ref = *strLst.begin();
        ref = "mmmm";
        for (auto l : strLst){
            cout << l << endl;
        }
    }

//    !! 容器的初始化与拷贝
    pIndexofTest(2);
    {
        list <string> sLst = {"hah","bbb","456","ccc","123"};
        vector<char *> chVec = {"dd","ee","ff"};
        list<string> sLst2(sLst);//相同容器类型可以直接初始化
//        deque<string> sDq(sLst);//容器类型不匹配
//        vector<string> sVec(chVec);//容器类型必须匹配

//        不同容器类型,但是元素类型相同也可以初始化!!!,有下面两种初始化方式
        forward_list<string> fwLst(chVec.begin(),chVec.end());
        for(auto a : fwLst){
            cout << a << endl;
        }
        cout << "************************************************" << endl;

        auto pLst = --sLst.end();
        cout << static_cast<string>(*pLst) << endl;
        deque<string> sDq2(sLst.begin(),pLst);//拷贝元素,直到但不包括plst
        for(auto a : sDq2){
            cout << a << endl;
        }
    }

//    ! array 的使用 ,有哪些使用场景呢?
    pIndexofTest(3);
    {
        array <int,4> arr;//array必须给出元素类型和大小,一共两种初始化方式
        arr = {3,4,5,6};//直接给出初始化列表
        arr = {2};//此处和书中p302描述不符
        array <int,4> arr2 = {1};//除了第一个初始化为1,后面都默认初始化为0
        arr2 = arr;//类型和大小都匹配才能拷贝
    }

//    !! assign 的3中使用方式,只能用在顺序容器中,不能用在关联容器和array中
    pIndexofTest(4);
    {
        vector <int> iVec = {1,2,3,4,5,6,7};
        list <int> iLst;
        iLst.assign(iVec.begin() + 2,iVec.end());//两个迭代器
        for(auto a : iLst)
            cout << a << " ";
        cout << endl;

        forward_list <int> fwLst;
        fwLst.assign({4,5,6,7});//一个初始化列表
        for(auto a : fwLst)
            cout << a << " ";
        cout << endl;

        deque <int> dq;
        dq.assign(10,333);//替换为n个值为t的数
        for(auto a : dq)
            cout << a << " ";

    }

//    !!! 赋值对指针,迭代器,引用的副作用
    pIndexofTest(5);
    {
        vector <int> iVec = {1,2,3,4,5,6,7};
        list <int> iLst = {8,8,8,8,8,8,8,8,8};
        list<int>::iterator pLst = iLst.begin();
        cout << *pLst << endl;//1
        iLst.assign(iVec.begin() + 2,iVec.end());//两个迭代器
        for(auto a : iLst)
            cout << a << " ";
        cout << endl;
        cout << *pLst << endl;//3,赋值相关操作,会导致左边的容器内部迭代器,引用,和指针失效,swap操作不会(除了array和string)
    }

//    !! swap ,除string和array,其他的指针,引用,迭代器依然指向之前的元素,均有效
    pIndexofTest(6);
    {
        vector <int> iVec1(10,234);
        vector<int>::iterator pVec = iVec1.begin();
        cout << *pVec << endl;
        vector <int> iVec2(3,1);
        swap(iVec1,iVec2);//除array外,swap不对任何元素进行拷贝,删除或插入操作。都是常数时间完成
        for(auto a : iVec1)
            cout << a << " ";
        cout << endl;
        cout << *pVec << endl;//和上面的输出一样,都是234,证明元素没有移动。//除string外,其他容器之前定义的指针,迭代器,引用都还有效,依然指向之前的元素

        string str1 = "hello";
        string str2 = "world";
        string::iterator iStr = str1.begin();
        cout << *iStr << endl;//输出h
        str1.swap(str2);
        cout << *iStr << endl;//输出w

        queue <int> q1;
        q1.push(34);
        q1.push(55);
        queue <int> q2;
        q2.push(7);
        q2.push(59);
        q2.push(9);
        swap(q1,q2);
        while (!q1.empty()) {
            cout << q1.front() << " ";
            q1.pop();
        }
        cout << endl;

    }

//    ! 6种初始化方式
    pIndexofTest(7);
    {
        vector<int> iVec1;
        vector<int> iVec2(iVec1);
        vector<int> iVec3(10,1);
        vector<int> iVec4(3);

        vector<int> iVec5{1,2,3};
        vector<int> iVec6 = {1,2,3};
        cout << (iVec5 == iVec6) << endl;
        vector<int> iVec7(3);
        vector<int> iVec8(iVec2.begin(),iVec2.end());

    };

//    !! 插入元素 (vector ,string ,deque 插入元素会使所有指向容器的迭代器，引用失效)
    pIndexofTest(8);
    {
        forward_list <int> fwLst{1,2,3,4,5,6,7};
        print(fwLst);
        fwLst.push_front(33);
//        fwLst.push_back() forward_list 和 array 不支持push_back
        deque<int> iDq{1,2,3,4,5,6,7};
        print(iDq);

        iDq.push_back(23);
        iDq.push_front(666);
        print(iDq);

//        !! insert的4中用法，第一个参数都是传入迭代器，后续插入是在迭代器前面插入
        deque<int>::iterator pDq;
        pDq = iDq.begin();
        iDq.insert(pDq,8888);
        print(iDq);

        cout << *pDq << endl;//666
        iDq.insert(pDq,3,-1);
        print(iDq);

        vector<int> iVec{0,0,0};
        iDq.insert(iDq.end(),iVec.begin(),iVec.end());
        print(iDq);

        iDq.insert(pDq,{999,999,999});
        print(iDq);

        iDq.insert(pDq+3,1111);
        cout << *pDq << endl;//666 迭代器失效指的是什么呢？

    }

//    !! insert的返回值,返回插入第一个新元素的迭代器
    pIndexofTest(9);
    {
        stringstream strCin;
        string data = "1 2 3 4 5 6 7";
        strCin.str(data);
        list<int> iLst;
        auto p = iLst.begin();
        int tmp;
        // 理解此循环相当于push_front;
        while (strCin >> tmp){
            p = iLst.insert(p,tmp);
        }
        print(iLst);
    }

//    emplace 用法，emplace调用元素的构造器，直接在容器内存中创建对象，push_back会创建一个临时对象，然后拷贝到容器中
    pIndexofTest(10);
    {
        vector<Test> tVec(3);
        cout << "  " << endl;
        tVec.push_back(Test(1,2,"hh"));
        tVec.emplace_back(4,4,"nnnn");
        cout << "  " << endl;
        tVec.emplace_back();//使用默认构造函数


    }

    return 0;
}

