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
