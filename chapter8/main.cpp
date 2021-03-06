#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <sstream>
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


istream& testStrm(istream& is){
    string s;
    while (is >> s){
        cout << s;
    }
    is.clear();
    return is;
}
int main() {

//std::ios_base::sync_with_stdio(false);
    std::cout.flush();
//     ! cerr 怎么使用？
    pIndexofTest(1);
    {
        std::cout.flush();
        cout << "hhhh" << endl;
        std::cout.flush();
        cerr << "error" << endl;
        std::cout.flush();

    }

//    !! 流的各种状态，
    pIndexofTest(2);
/*    {
        //不能对流对象赋值，不能拷贝流对象，不能初始化ofstream参数
        ofstream out1,out2;
//        out1 = out2;

        int i = 0;
        auto& istate = cin >> i;
        cout << " state: " << istate.rdstate() << endl;
        cout << " fail: " << istate.fail() << endl;//good 与 fail 是确定流整体正确的方法
        cout << " good: " << istate.good() << endl;
        cout << " eof: " << istate.eof() << endl;// eof 是 达到了文件的结尾
        cout << " bad: " << istate.bad() << endl;// bad 流崩溃
        istate.clear();//两个版本，无参与带参，无参：所有状态复位，流设置为有效
        cout << " state: " << istate.rdstate() << endl;
        cout << " eof: " << istate.eof() << endl;
        cout << " fail: " << istate.fail() << endl;
        cout << " bad: " << istate.bad() << endl;
        cin >> i;
        cout << " state: " << istate.rdstate() << endl;
        cout << " eof: " << istate.eof() << endl;
        cout << " fail: " << istate.fail() << endl;
        cout << " bad: " << istate.bad() << endl;
        istate.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit);//带参版本可以复位特定位状态，比如这个代码复位了failbit 与 badbit  ，但是eofbit不变
        cout << " state: " << istate.rdstate() << endl;
        cout << " eof: " << istate.eof() << endl;
        cout << " fail: " << istate.fail() << endl;
        cout << " bad: " << istate.bad() << endl;
    }*/

//    !! 练习8.1 读取数据遇到文件爱你结束副结束，打印读取数据，返回流之前，复位流
    pIndexofTest(3);
/*    {
        testStrm(cin);
    }*/

//    ! 关联输入和输出流（一个输入流关联到一个输出流时，任何试图裁判嗯输入流读取数据的操作都会被刷新关联的输出流）(不太懂)
    pIndexofTest(4);
/*    {
        int i;
        cin.tie(&cout);//标准库将cin和cout关联在一起
        cin >> i;
        cout << i << " ";
        cerr << i << endl;
        ostream *oldTie = cin.tie(nullptr);//cin 不再关联其他流
        cin >> i;
        cout << i << " ";
        cerr << i << endl;
        cin.tie(&cerr);//读取cin会刷新cerr而不是cout
        cin >> i;
        cout << i << " ";
        cerr << i << endl;
        cin.tie(oldTie);//重建cin和cout的关联
        cin >> i;
        cout << i << " ";
        cerr << i << endl;
    }*/

    pIndexofTest(5);
    {
        fstream fis("/home/kunwan/Cpp-Primer-5th-Edition/chapter8/data.in");
        ofstream fos;
        fos.open("/home/kunwan/Cpp-Primer-5th-Edition/chapter8/data.out");

        int tmp;
        while (fis >> tmp){
            fos << tmp;
        }
    }

    pIndexofTest(6);
    {
        string path = "/home/kunwan/Cpp-Primer-5th-Edition/chapter8/";
        fstream fis;
        fis.open(path + "data.in");
        ofstream fos;
        fos.open(path + "/data.out");

        int tmp;
        while (fis >> tmp){
            fos << tmp << " ";
        }
        fis.close();
        fis.open(path + "data2.in");
        assert(fis);
//        fos.flush();
        fos << " mmmmmmm ";
        while (fis >> tmp){
            fos << tmp << " ";
        }
        fis.close();
        fos.close();
    }

//    !! 文件读写
    pIndexofTest(7);
    {
        string path = "/home/kunwan/Cpp-Primer-5th-Edition/chapter8/";
        fstream fis;
        fis.open(path + "data.in");
        ofstream fos0(path + "data0.out");
        ofstream fos1(path + "data1.out",ofstream::out);
        ofstream fos2(path + "data2.out",ofstream::out | ofstream::trunc);

//        保留文件中已有数据的唯一方法时显式的制定app或为in模式，默认为输出以及截断（trunc）
        ofstream fos3(path + "data3.out",ofstream::app);
        ofstream fos4(path + "data4.out",ofstream::out | ofstream::app);
        ofstream fos5(path + "data5.out",ofstream::out | ofstream::ate);

        fos0 << "     HHHout0";//重新开始
        fos1 << "     HHHout1";//重新开始
        fos2 << "     HHHout2";//重新开始
        fos3 << "     HHHout3";//后面追加
        fos4 << "     HHHout4";//后面追加
        fos5 << "     HHHout5";//重新开始

        fis.close();
    }

//    stringstream string流，从string中读取或者读如数据
    pIndexofTest(8);
    {
        string tmp = "hello 123 3.1234";
        istringstream strCin;
        string str1;
        int i;
        double d;
        strCin.str(tmp);
        strCin >> str1;
        strCin >> i >> d;
        cout << str1 << " " << i << " " << d << endl;

        string str2;
        ostringstream strCout;
        int iVal = 54;
        double dVal = 234.2324;
        bool b = true;
        strCout << iVal << " " << dVal << " " << b << endl;
        str2 = strCout.str();
        cout << str2;
    }

    return 0;
}