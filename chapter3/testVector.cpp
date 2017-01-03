#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node{
    int a = 4,b = 6;
};
void printNode(vector <Node> vecN){
    for (auto a : vecN) {
        cout << a.a << " " << a.b << endl;
    }
}

void printString(vector <string> vecS){
    for (auto a : vecS)
        cout << a << endl;
}

int main() {
    Node n1;
    n1.a = 10,n1.b = 11;
    vector < Node > vecN(10,n1);
    printNode(vecN);

//    列表初始化
    vector <string> vecS0 = {"hahaha","hello","world"};
//    vector <string> vecS1 = ("hahaha","hello","world");//提供的是初始化元素值得列表,则只能使用花括号初始化,不能使用圆括号
    printString(vecS0);

//    构造初始化
    vector <string> vecS1(10,"hhhh");
    printString(vecS1);

//    {}的形式却无法做列表初始化时,编译器则尝试构造初始化
    vector <string> vecS2{3,"XXX"};
    printString(vecS2);

//    vector 对象是常量就不能通过下标来返回对象的值? p92
    vector <const int> cnVeci = {1,2,3,4};
    for (vector <int> :: size_type i = 0;i < cnVeci.size();i++)
        cout << cnVeci[i] << " ";
    cout << endl;

//    把字符串转换成大写,注意下面的错误
    string str1 = "hello world";
    if (str1.begin() != str1.end()){//确保非空
        auto it = str1.begin();
//        错误!!!
//        while (it != str1.end())
//            *it = toupper(*it++);//输出:hHHHHHHHHHH
        while (it != str1.end()) {
            *it = toupper(*it);
            it++;
        }
    }
    cout << str1 << endl;

//    范围for不要向迭代器所属容器中添加元素,p315 有详细解释
//    auto itN = vecN.begin();
//    int i = 0;
//    for (itN = vecN.begin(); itN != vecN.end(); ++itN,++i){
//        cout << i << ": " << itN->a << " " << itN->b <<endl;
//        if(i == 8){
//            Node tN;
//            tN.a = 3,tN.b = 4;
//            vecN.push_back(tN);
//        }
//    }


}

