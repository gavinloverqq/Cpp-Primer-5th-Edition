#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <exception>
#include <new>
#include <fstream>
#include <sstream>
#include <cstring>
#include <list>

using namespace std;
// 可以直接用initializer_list 初始化 vector
void foo(initializer_list<string> strIni){
    vector <string> strVec(strIni);
    for (auto p : strVec) {
        cout << p << " ";
    }
}


int main(){
    list <string> lst{"aasd", "sss", "cc"};
    vector<string> strVec(lst.begin(), lst.end());

    for (auto p : strVec) {
        cout << p << " ";
    }

    cout << endl;
    foo({"aaa", "bbb", "ccc"});
}
