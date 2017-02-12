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


class TestA{

    friend istream& read(istream& is,TestA& a);

    //    B类可以访问A类私有成员
    friend class TestB;

public:
    TestA() = default;
    TestA(int i,int j):iVal1(i),iVal2(j){}
    TestA(istream& is){
        read(is,*this);
    }

private:
    int iVal1,iVal2;
};

istream& read(istream& is,TestA& a){
    is >> a.iVal1 >> a.iVal2;
    return is;
}

class TestB;
class TestD{
public:
    TestD() = default;
    TestD(int i,int j):iVal1(i),iVal2(j){}
    void DprintB(TestB b);//不可再此处写函数实现

private:
    int iVal1,iVal2;
};
class TestB{
    friend class TestC;//友元关系的传递

    friend void TestD::DprintB(TestB);//只让成员函数作为友元!!! (仔细看这个地方的实现,看看上面定义的TestD,以及这个函数声明,和实现的位置,尝试不这样做会发生什么)

public:
    TestB() = default;
    TestB(double i, double j):dVal1(i),dVal2(j){}

    void getAval(TestA a){
        cout << a.iVal1 << " " << a.iVal2 << endl;
    }
    void printB(){
        cout << dVal1 << " " << dVal2 << endl;
    }
private:
    double dVal1,dVal2;
};

class TestC{

public:
//    void getAval(TestA a){
//        cout << a.iVal1 << " " << a.iVal2 << endl;//B是A的友元类,C是B的友元类,但是A不是C的友元类,友元关系不可传递
//    }

};


void TestD::DprintB(TestB b){
    cout << b.dVal1 << " " << b.dVal2 << endl;
}


//  !!! 友元函数的声明的作用仅仅是影响访问权限,它本身并非普通意义上的声明。
class C1{
    friend void f(){
        cout << "c1" << endl;
    }

public:
    C1() = default;
    C1(int i):iVal1(i){}

    void G();
    void H();
private:
    int iVal1;
};
//下面的代码会发生错误,error: use of undeclared identifier 'f',f为声明!!!!
//void C1::G(){
//    f();
//}
void f();
void C1::H() {
    f();
}

//  ! 类的作用域(注意下面一种情况,返回类型是类内定义的)
class C2{
public:
    using typeT = std::string::size_type ;
    typeT func();
};
C2::typeT C2::func(){
    cout << " xxx " << endl;
}
//第二个C2省略也可以,书上说不行???????????????????? 背包



int main(){


//    ! 友元类
    pIndexofTest(1);
    {
        TestA a(cin);
        TestB b(1.2,3.333);
        b.getAval(a);
    }

//    !!! 成员函数作为友元(注意此处的实现!!!!!)
    pIndexofTest(2);
    {
        TestB b(1.2222,2.2222);
        TestD d;
        d.DprintB(b);
    }

    return 0;
}
