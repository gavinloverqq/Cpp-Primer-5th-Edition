#include <iostream>

using namespace std;

class Test{
public:
    std::string retStr(){ return str;};
    void func1();

private:
    int iVal1,iVal2;
    std::string str;
};

void Test::func1() {
    cout << __func__ << endl;
}

int main() {

    cout << "Hello, World!" << endl;
    return 0;
}