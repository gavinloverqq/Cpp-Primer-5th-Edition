#include <iostream>
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




class Screen{
public:
    using pos = std::string::size_type;//定义类型的成员，必须先定义后使用

    Screen() = default;
    Screen(pos ht,pos wd,char c):height(ht),width(wd),contents(ht * wd,c){}
    char get()const{
        return contents[cursor];
    }//隐士内联
    inline char get(pos ht,pos wd)const;//显式内联
    Screen& move(pos r,pos c);//能在之后设为内联

    Screen& set(char);
    Screen& set(pos,pos,char);

    //可变数据成员
    void changeMutFunc()const{
        mutNum++;
    }

    //根据对象是否是const重载了display函数。
    Screen& display(std::ostream& os){
        doDisplay(os);
        return *this;
    }
    const Screen& display(std::ostream& os)const {
        doDisplay(os);
        return *this;
    }

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;

    //可变数据成员，即使对象是const，也可以被修改；
    mutable int mutNum;

    //常量函数
    void doDisplay(std::ostream& os)const {
        os << contents;
    }

};
//声明时未设为内联
inline Screen& Screen::move(pos r, pos c) {
    pos row = r * width;
    cursor = row + c;
    return *this;
}
//无需在定义和声明的地方都说明inline
char Screen::get(pos r, pos c)const{
    pos row = r * width;
    return contents[row + c];
}

//以下两个函数返回的是对象本身,而不是对象副本;
inline Screen& Screen::set(char c) {
    contents[cursor] = c;
    return *this;
}
inline Screen& Screen::set(pos r, pos col, char ch) {
    contents[r*width + col] = ch;
    return *this;
}

//!类内初始值，使用{}初始化
class Window_mgr{
private:
    std::vector <Screen> screens{Screen(24,80,' ')};
};



int main(){


    pIndexofTest(1);
    return 0;
}
