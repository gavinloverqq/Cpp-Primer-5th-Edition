1.共享对象的类如何创建
2.成员函数的const版本与非const版本的区别，看class c6，以及阅读书248，结合例子才能比较清楚
3.练习12.1-12.5是比较好的习题，值得一做
4.复习initializer_list的使用
5.pIndexofTest(6)的一开始关于new采用值初始化与默认初始化对类的构造函数的调用不是很清楚，具体描述在书的p408第一段
6.auto pa3 = new auto{1,2,3};//此处与书中描述不一致 p408
7.delete不是new分配的指针 报错：Process finished with exit code 139 (interrupted by signal 11: SIGSEGV)
8.delete释放了两次的指针 报错：Process finished with exit code 134 (interrupted by signal 6: SIGABRT)
9.test13的指针似乎并没有释放
10. process(new int());// 练习12.12(b) 答案错误 error: could not convert ‘(operator new(4ul), (<statement>, ((int*)<anonymous>)))’ from ‘int*’ to ‘std::shared_ptr<int>’

11.
```
    {
        shared_ptr<int> p(new int(33));
        process(shared_ptr<int> (p));//拷贝引起 引用计数增加，执行结束后p的引用计数仍然是1

        process(shared_ptr<int> (p.get()));//p.get返回普通指针，用来初始化一个智能指针，结束后智能指针被释放，p变成空悬指针
    }
```
上面这段代码会引起下面的文件操作异常，不知道为什么？
```
        string path = "/home/kunwan/Cpp-Primer-5th-Edition/chapter12/";
        fstream fis;
        fis.open(path + "data.in");
        ofstream fos;
        fos.open(path + "/data.out");

        int tmp;
        while (fis >> tmp){
            fos << tmp << " ";
        }
        fis.close();

//        fcout.close();
    
```


12. 如果eq函数是非const，注意右值(常量、表达式、函数返回值等)绑定到非const引用的错误,因为把右值绑定到非const引用上，就有可能修改右值（而右值是不允许修改的） 
也就是说一个函数如果参数是 引用类型 ：例如：eq（strBlobPtr &， strBlobPtr&）那么这个函数是不能接受 右值为参数的 比如左边的函数就无法这样调用 eq（s.begin(), s.end()）,因为函数调用是右值
``` error: invalid initialization of non-const reference of type ‘StrBlobPtr&’ from an rvalue of type ‘StrBlobPtr’ ```

参考: 
> https://www.zhihu.com/question/20759966
> https://www.kancloud.cn/wizardforcel/cpp-11-faq/106078

13. 练习12.22是个好题






---
add:
1. 接收指针参数的智能指针构造函数是explicit的，因此不能将一个内置指针隐式转换为一个智能指针 必须使用直接初始化形式
2. 如果只能指针管理的不是new分配的内存，需要给他传递一个删除器