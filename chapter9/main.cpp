#include <bits/stdc++.h>


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
        list<string> sLst2(sLst);
//        deque<string> sDq(sLst);
//        vector<string> sVec(chVec);

        forward_list<string> fwLst(chVec.begin(),chVec.end());
        for(auto a : fwLst){
            cout << a << endl;
        }
        cout << "************************************************" << endl;

        auto pLst = --sLst.end();
        cout << static_cast<string>(*pLst) << endl;
        deque<string> sDq2(sLst.begin(),pLst);
        for(auto a : sDq2){
            cout << a << endl;
        }
    }
    return 0;
}