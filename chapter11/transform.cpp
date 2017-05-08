#include <iostream>
#include <string>
#include <stdlib.h>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>

using namespace std;


void buildMap(ifstream& mapFile, map<string, string>& wordMap){
    string key, value;
    while (mapFile >> key && getline(mapFile, value)){
        if(value.size() > 1){
            wordMap.insert({key, value.substr(1)});//substr(1) 可以跳过前导空格
        } else {
            cerr << "no rule for " + key;
        }
    }
}

const string& transformWord(const string& word, const map<string, string>& wordMap){
    string value;
    auto bg = wordMap.find(word);
    if(bg != wordMap.end()){
        return bg->second;
    } else {
        return word;
    }
}

void wordTransform(ifstream& mapFile, ifstream& wordFile){
    map<string, string> wordMap;
    buildMap(mapFile, wordMap);
    string text;
    while (getline(wordFile, text)){
        stringstream strIn(text);
        string word;
        bool firstWord = true;//判断是否是第一个单词
        while (strIn >> word){
            if(firstWord){
                firstWord  = false;
            } else {
                cout << " ";
            }
            cout << transformWord(word, wordMap);
        }
        cout << endl;
    }
}




int main(){
    string path = "/Users/wankun/Desktop/Cpp-Primer-5th-Edition/chapter11/";
    ifstream finMap(path + "map.in");
    ifstream finWord(path + "word.in");

    wordTransform(finMap, finWord);
}
