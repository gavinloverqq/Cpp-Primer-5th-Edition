#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

// 使用 ! 表示重要程度,! 越多越重要
//便于查看输出结果的分割显示函数
//看CAN驱动代码时发现把测试代码全部放到语句块里,就不用一直想命名的事情了
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

    /*pIndexofTest(1);
    {
        int iVal1 = 5, iVal2, iEvenCnt = 0, iOddCnt = 0;
        cin >> iVal2;
        switch (iVal2) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 9:
                ++iEvenCnt;
                break;
            case 2:
            case 4:
            case 6:
            case 8:
                ++iOddCnt;
                break;
        }
        cout << iEvenCnt << " " << iOddCnt << endl;
    }*/

//    case标签要满足两条:1、整型 2、常量
//    以下代码报错:error: statement requires expression of integer type ('string' (aka 'basic_string<char, char_traits<char>, allocator<char> >') invalid)
    /*{
        const string str1 = "aa", str2 = "bb";
        string str3;
        int iStr1 = 0, iStr2 = 0;
        cin >> str3;
        switch (str3) {
            case str1:
                ++iStr1;
                break;
            case str2:
                ++iStr2;
                break;
        }
    }*/

//    ! do while 循环
   /* pIndexofTest(2);
    {
        string str;
        int iVal = 10;
        do{
            iVal *= 10;
            cin >> str;
        }while (!str.empty() && str[0] != 'q');//注意while中不得定义变量,因为定义了变量,其实是没有任何地方可以使用的,do{}不可能使用,因为要先执行一次循环。注意while后面的分号
    }*/

//    goto
    /*pIndexofTest(3);
    {
        int iVal;
        cin >> iVal;
        begin:
            cout << "goto begin\n";
        if(iVal > 10)
            goto begin;
        else{
            cout << " break \n";
        }
    }*/

//    异常,关于异常类,异常类的初始化(默认初始化,带参数的初始化,),以及异常嵌套等问题参看书p173-177
    pIndexofTest(4);
    {
        int iVal1,iVal2;
        cin >> iVal1 >> iVal2;
        try {
            if(0 == iVal2)
                throw runtime_error("除数是0");
            cout << iVal1 / iVal2 << endl;
        }
        catch (runtime_error err){
            cout << err.what() << endl << "请重新输入\n";
        }

    }

    return 0;
}