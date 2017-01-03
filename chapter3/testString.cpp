#include <iostream>
#include <string>
using namespace std;
//using namespace string;

int main() {

//    getline 会读入换行符而停止,但是不会把换行符存到string里
//    string::size_type 是个无符号的类型,不是基本类型。
    string str1;
    while (getline(cin,str1)) {
        string::size_type t = str1.size();
        if(str1 == "eof")
            break;
        cout << t << str1 << endl;
    }

//    string 比较大小:长度不同时,如果对应位置上字符相同,则长的大;如果某些位置上字符不同,第一个不同位置上的相异字符的比较结果
    string str2 = "1234",str3 = "132",str4 = "123";
    cout << (str2 > str3) << " " << (str2 > str4) << endl;

//    string 与字面值相加,加号两边必须有个是string
    str2 = str3 + " hhh " + "ni ma";//等价于 (str3 + " hhh ") + "ni ma" 注意与下面的区别
//    str3 = " hhh " + "ni ma" + str2;//error: invalid operands to binary expression ('const char *' and 'const char *')


//    c++ 11 的string遍历的写法 : 范围for,遍历给定序列
    string str5 = "asfasgah asg wr sfsgs hello";
    for (auto c : str5) {
        cout << c;
    }
    cout << endl;

//    统计标点符号数
    string str6 = "hi ! nima, wocao:hahha.wtf!!!";
    decltype(str6.size()) punctCnt = 0;
    for (auto c : str6) {
        if(ispunct(c))
            punctCnt++;
    }
    cout << punctCnt << " punctuation in " << str6 << endl;

    string str7 = "to upper";
//    下面的代码输出:
//    8479328580806982
//    to upper

//    for (auto c : str7){
//        cout << toupper(c);
//    }
//    cout << endl << str7 << endl;

    for (char c : str7){
        cout << (c = toupper(c));//为什么这样就会变成字母二三名会输出asc码
    }
    cout << str7 << endl;

//    空格前的转换成大写
    string str8 = "Hello world";
    for (decltype(str8.size()) i = 0; i < str8.size() && str8[i] != ' '; ++i) {
        str8[i] = toupper(str8[i]);
    }
    cout << str8 << endl;

//    练习3.6,字符转换成'X'
    string str9 = "hahhahahh";
    for (auto &c : str9)
        c = 'X';
    cout << str9 << endl;
    string str10 = "hahhahahh";
    for (char &c : str10)
        c = 'X';
    cout << str10 << endl;

    string str11 = "hahha,nima;shi sha : cha ! he";
    for (auto c : str11){
        if(!ispunct(c))
            cout << c;
    }
    cout << endl;

//    c 绑定到常量字符串,编译错误
//    const string str12 = "hahhahahh";
//    for (auto &c : str12)// error: cannot assign to variable 'c' with const-qualified type 'const char &'
//        c = 'X';
//    cout << str12 << endl;

    return 0;

}