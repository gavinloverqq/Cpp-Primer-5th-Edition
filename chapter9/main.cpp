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


void func(forward_list <string>& fwLst,string s1,string s2){
    if(!fwLst.empty()){
        auto prev = fwLst.before_begin();
        auto curr = fwLst.begin();
        while (curr != fwLst.end()){
            if(*curr == s1){
                fwLst.insert_after(curr,s2);
                break;
            } else{
                ++curr;
                ++prev;
            }
        }
        if(curr == fwLst.end())
            fwLst.insert_after(prev,s2);
    }
}





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
        list <int>::iterator pLst = iLst.begin();
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
        vector <int>::iterator pVec = iVec1.begin();

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
        vector <int> iVec1;
        vector <int> iVec2(iVec1);
        vector <int> iVec3(10,1);
        vector <int> iVec4(3);

        vector <int> iVec5{1,2,3};
        vector <int> iVec6 = {1,2,3};
        cout << (iVec5 == iVec6) << endl;
        vector <int> iVec7(3);
        vector <int> iVec8(iVec2.begin(),iVec2.end());

    };

//    !! 插入元素 (vector ,string ,deque 插入元素会使所有指向容器的迭代器，引用失效)
    pIndexofTest(8);
    {
        forward_list <int> fwLst{1,2,3,4,5,6,7};
        print(fwLst);
        fwLst.push_front(33);
//        fwLst.push_back() forward_list 和 array 不支持push_back
        deque <int> iDq{1,2,3,4,5,6,7};
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

        vector <int> iVec{0,0,0};
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
        vector <Test> tVec(3);
        cout << "  " << endl;
        tVec.push_back(Test(1,2,"hh"));
        tVec.emplace_back(4,4,"nnnn");
        cout << "  " << endl;
        tVec.emplace_back();//使用默认构造函数


    }

//    !! 练习9.22
    pIndexofTest(11);
    {
        vector <int> iVec{1,2,3,4,5};
        vector <int>::iterator pVec = iVec.begin(),
            pMid = iVec.begin() + iVec.size() / 2;
        int value = 2,num = 0,len = iVec.size();
        while (pVec != pMid){
            if(*pVec == value){
                pVec = iVec.insert(pVec,2 * value);
                num++;
                pMid = iVec.begin() + len / 2 + num;
                pVec++;
                pVec++;
            } else
                pVec++;
        }
        print(iVec);
    }

//    !! 顺序容器的访问
    pIndexofTest(12);
    {
        forward_list <int> fwLst{1,2,3,4,5};
        if(!fwLst.empty()) {//对空容器调用front和back操作就像使用越界的数组下标一样，是一种严重的错误
            auto val1 = *fwLst.begin(), val2 = fwLst.front();
            auto last = fwLst.end();
//            auto val3 = *(--last);//forward_list不支持--
//            auto val4 = fwLst.back();//forward_list不支持back操作//以上两种操作其他顺序容器都支持
        }
        deque <int> iDq{1,2,3,4,5};
        cout << iDq[1] << "  " << endl;
        iDq.push_back(22);
        cout << iDq[1] << "  " << endl;
        iDq.push_front(555);
        cout << iDq[1] << "  " << endl;
    }

//    !! 访问成员函数（front back 下标 at）返回的是引用
    pIndexofTest(13);
    {
        list <int> iLst{1,2,3,4,5};
        iLst.front() = 999;
        auto& v1 = iLst.back();//返回引用
        auto v2 = iLst.back();//返回一个拷贝
        v2 = -2;
        print(iLst);
        v1 = -100;
        print(iLst);
    }

//    !! at 与 下标 的区别
    pIndexofTest(14);
    {
        vector <int> iVec;
//        cout << iVec[0];//运行时错误
//        cout << iVec.at(0);//抛出out_of_range异常
    }

//    !! 元素删除（deuque 除首尾之外的任何元素删除会使所有迭代器，引用，指针失效；vector string 删除点之后的迭代器，引用，指针失效
//    ???? 如何验证迭代器失效，迭代器失效指的是什么？？？？
    pIndexofTest(15);
    {
        vector <int> iVec{1,2,3,4,5,6,7,8,9};
        print(iVec);
        iVec.pop_back();
        print(iVec);
//        iVec.pop_front();
        auto p = iVec.erase(iVec.begin());//删除p，返回p之后的元素
        cout << *p << endl;
        print(iVec);

        auto p1 = iVec.erase(iVec.begin() + 1,iVec.end() - 2);//删除b e 之间的元素，返回最后一个被删元素之后的迭代器，若最后是尾后迭代器，则还是返回尾后迭代器
        cout << *p1 << endl;
        print(iVec);

        auto p2 = iVec.erase(iVec.begin(),iVec.begin());//删除范围相等情况：返回当前迭代器，不删除任何元素
        cout << *p2 << endl;
        print(iVec);

        iVec.clear();
        print(iVec);
    }

//    ! 练习9.26
    pIndexofTest(16);
    {
        int a[] = {1,2,3,4,5,6,7,8,10,11,13,14};
        vector <int> iVec(a,a + sizeof(a) / sizeof(int));
        list <int> iLst(a,a + sizeof(a) / sizeof(int));
        auto pV = iVec.begin();
        auto pL = iLst.begin();
        while (!iVec.empty() && pV != iVec.end()){
            if(*pV % 2){
                pV = iVec.erase(pV);
            } else
                ++pV;
        }
        print(iVec);
        while (!iLst.empty() && pL != iLst.end()){
            if(*pL % 2 == 0){
                pL = iLst.erase(pL);
            } else
                ++pL;
        }
        print(iLst);

    }

//    ! forward_list由于单向链表的特殊结构,只能找到节点的后继,不能找到节点的前驱,因此在 插入 删除 操作上略有不同
    pIndexofTest(17);
    {
        forward_list <int> fwLst{1,2,3,4,5,6,7,8,9,11,12,14,16};
        print(fwLst);
        fwLst.insert_after(++fwLst.begin(),{44,55,66,77});
        print(fwLst);
        fwLst.emplace_after(fwLst.begin(),999);
        print(fwLst);
        auto prev = fwLst.before_begin();
        auto curr = fwLst.begin();
        while (curr != fwLst.end()){
            if(*curr % 2){
                curr = fwLst.erase_after(prev);
            } else{
                ++curr;
                ++prev;
            }
        }
        print(fwLst);
    }

//    !! 练习9.28 ,
    pIndexofTest(18);
    {
        forward_list <string> str1{"aa","bb","cc","dd"},str2{"ee","ff","gg"};
        string s1 = "cc",s2 = "xxxx";
        func(str1,s1,s2);
        func(str2,s1,s2);
        print(str1);
        print(str2);
    }

//    !! resize
    pIndexofTest(19);
    {
        vector <int> iVec(10,42);
        iVec.resize(15);//前10个42,后5个0
        iVec.resize(25,-1);//后10个-1,加到末尾
        print(iVec);
        iVec.resize(5);//只保留前5个
        print(iVec);
    }

//    !!! 容器操作可能使迭代器,指针,引用失效
    pIndexofTest(20);
    {
        vector <int> iVec{1,2,3,4,5,6,7,8,9};
        auto pVec = iVec.begin();
        while (pVec != iVec.end()){
            if(*pVec % 2){
                pVec = iVec.insert(pVec,*pVec);//迭代器失效
                pVec += 2;
            } else
                pVec = iVec.erase(pVec);//迭代器失效
        }
        print(iVec);
    }

//    !! 补保存end返回的迭代器
    pIndexofTest(21);
    {
        vector <int> iVec{1,2,3,4,5,6,7,8,9};
        auto bg = iVec.begin();
        auto ed = iVec.end();
//            while(bg != ed)//ed指向的内存数据已经变了
        while (bg != iVec.end()){
            bg++;
            bg = iVec.insert(bg,42);
            cout << *ed << endl;
            bg++;
        }
    }

//    !! forward_list删除元素要保存前驱和后继
    pIndexofTest(22);
    {
        forward_list <int> fwLSt{1,2,3,4,5,6,7,8,9};
        auto curr = fwLSt.begin();
        auto prev = fwLSt.before_begin();
        while (curr != fwLSt.end()){
            if(*curr & 1){
                curr = fwLSt.insert_after(curr,*curr);
                ++curr;
                ++prev;
                ++prev;
            } else {
                curr = fwLSt.erase_after(prev);
            }
        }
        print(fwLSt);
    }

//    !! vector和string 是如何增长的
    pIndexofTest(23);
    {
        vector <int> iVec{1,2,3,4};
        cout << iVec.capacity() << endl;//capacity 不重新分配内存空间的话可以保存多少元素
        iVec.reserve(100);//reserve 分配至少容纳n个元素的内存空间
        cout << iVec.capacity() << endl;
        iVec.reserve(2);//当需求内存大于当前容量时，重新分配更多的内存，当需求内存小于当前容量，reserve 不起任何作用，capacity显示的也是当前容量值
        cout << iVec.capacity() << endl;
        iVec.resize(20);//同样resize也不会回收预留内存
        cout << iVec.capacity() << endl;
        iVec.resize(120);
        cout << iVec.capacity() << endl;
    }

//    !! insert size capacity resize
    pIndexofTest(24);
    {
        vector <int> iVec;
        cout << iVec.size() << " " << iVec.capacity() << endl;
        for (int i = 0; i < 20; ++i) {
           iVec.push_back(i);
        }
        cout << iVec.size() << " " << iVec.capacity() << endl;
        iVec.reserve(50);
        cout << iVec.size() << " " << iVec.capacity() << endl;
        while (iVec.size() != iVec.capacity())
            iVec.push_back(333);
        cout << iVec.size() << " " << iVec.capacity() << endl;
        iVec.push_back(4);
        cout << iVec.size() << " " << iVec.capacity() << endl;
        iVec.shrink_to_fit();
        cout << iVec.size() << " " << iVec.capacity() << endl;
        iVec.insert(iVec.begin(),10);//与书中，描述不符
        cout << iVec.size() << " " << iVec.capacity() << endl;
    }

//    ! 练习9.40答案错误
    pIndexofTest(25);
    {
        stringstream strCin;
        string data{"1 2 3 4 5 65"};
        strCin.str(data);
        vector <int> iVec;
        iVec.reserve(10);
        int i;
        while (strCin >> i){
            iVec.push_back(i);
        }
        iVec.resize(iVec.size() + iVec.size() / 2);
        cout << iVec.size() << " " << iVec.capacity() << endl;
    }


    return 0;
}

