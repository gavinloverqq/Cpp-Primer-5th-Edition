1.练习13.13值得仔细看看，能看清楚构造函数，赋值构造函数，拷贝构造函数等执行过程
2.一个类需要自定义析构函数几乎可以肯定需要自定义拷贝赋值运算符和拷贝构造函数
3.需要拷贝的类也需要赋值操作
4.error: invalid use of qualified-name  //ans： The definition of the static member can't be inside a function
5.拷贝构造函数因为有构造二字，因此在拷贝初始化的时候是起着构造函数的作用的，看pIndexofTest(7)结果
6.练习13.27不错的题，值得一做