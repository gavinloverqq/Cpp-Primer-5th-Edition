#include <iostream>
#include <string>
#include <stdlib.h>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>

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

template <typename T>
void print(T& t){
    for(auto a : t)
        cout << a << " ";
    cout << endl;
}



void addFamily(map<string, vector<string>> &families, const string& family){
//    families[family];
    if(families.find(family) == families.end())
        families[family] = vector <string> ();
}

void addChild(map<string, vector<string>> &families, const string& family, const string& child){
    families[family].push_back(child);
}

int main() {

//    !!! 单词计数， 其中关注一下如何获取 str 的size问题，具体见笔记
    pIndexofTest(0);
    {
        map<string, size_t> word_count;
        string str[10] = {"asc", "sddf", "key", "word", "key", "words", "sss", "cc", "ssd", "dd"};
        for (int i = 0; i < sizeof(str) / sizeof(str[0]) ; ++i) {
            ++word_count[str[i]];
        }
//        for (const auto &w : word_count) {
//            cout << w.first << " " << w.second << endl;
//        }
        for (int j = 0; j < sizeof(str) / sizeof(str[0]); ++j) {
            cout << str[j] << " " << word_count[str[j]] << endl;
        }
    }

//    ! set
    pIndexofTest(1);
    {
        set <string> exclude = {"key", "cc"};
        map<string, size_t> word_count;
        string str[10] = {"asc", "sddf", "key", "word", "key", "words", "sss", "cc", "ssd", "dd"};
        for (int i = 0; i < sizeof(str) / sizeof(str[0]) ; ++i) {
            if(exclude.find(str[i]) == exclude.end())
                ++word_count[str[i]];
        }
        for (int j = 0; j < sizeof(str) / sizeof(str[0]); ++j) {
            cout << str[j] << " " << word_count[str[j]] << endl;
        }

    }

//    !!! 范围初始化set， multiset 与 set
    pIndexofTest(2);
    {
        vector <int> ivec;
        for (int i = 0; i < 10; ++i) {
            ivec.push_back(i);
            ivec.push_back(i);
        }
        set <int> iset(ivec.begin(), ivec.end());
        multiset <int> muiset(ivec.begin(), ivec.end());
        cout << iset.size() << endl;
        cout << ivec.size() << endl;
        cout << muiset.size() << endl;
    }

    pIndexofTest(3);
    {
        map <string, vector<string> > families;
        addFamily(families, "张");
        addChild(families, "张", "强");
        addChild(families, "张", "刚");
        addChild(families, "李", "双江");
        addFamily(families, "李");

        for (auto f : families) {
            cout << f.first << " : ";
            for (int i = 0; i < f.second.size(); ++i) {
                cout << f.second[i] << " ";
            }
            cout << endl;
        }
    }

//    pair
    pIndexofTest(4);
    {
        string str[10] = {"asc", "sddf", "key", "word", "key", "words", "sss", "cc", "ssd", "dd"};
        vector <pair<string, int>> pairVec;
        for (int i = 0; i < sizeof(str) / sizeof(str[0]) ; ++i) {
            pairVec.push_back(make_pair(str[i], i));
        }
        for (auto p : pairVec) {
            cout << p.first << " " << p.second << endl;
        }
    }

//    ! mapped_type 只有map type有
    pIndexofTest(5);
    {
        set <string>::value_type v1;//v1 is a string
        set <string>::key_type v2;//v2 is a string
        map <string, int>::value_type v3;//v3 is a pair
        map <string, int>::key_type v4;//v4 is a string
        map <string, int>::mapped_type v5;//v5 is an int
    }

//    !! key is const, value is not
    pIndexofTest(6);
    {
        set <string> exclude = {"key", "cc"};
        map<string, size_t> word_count;
        string str[10] = {"asc", "sddf", "key", "word", "key", "words", "sss", "cc", "ssd", "dd"};
        for (int i = 0; i < sizeof(str) / sizeof(str[0]) ; ++i) {
            if(exclude.find(str[i]) == exclude.end())
                ++word_count[str[i]];
        }
        auto map_it = word_count.begin();
        cout << map_it->first << " " << map_it->second << endl;
//        map_it->first = "new key"; // key is const!     //   error: no viable overloaded '='
        ++map_it->second;

        map<string, size_t >::mapped_type v = map_it->second;
        map<string, size_t >::value_type p = *(map_it++);
        cout << v << endl;
        cout << p.first << " " << p.second << endl;
    }

//    !! Iterators for sets are const
    pIndexofTest(7);
    {
        set <int> iset = {0, 1, 2, 3, 4, 5};
        set <int>::iterator set_it = iset.begin();
        while (set_it != iset.end()){
//            *set_it = 42; // error: cannot assign to return value because function 'operator*' returns a const value
            cout << *set_it++ << " ";
        }

    }


    return 0;
}