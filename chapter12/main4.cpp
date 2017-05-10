#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <exception>
#include <new>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

class QueryResult;

class TextQuery{
public:
    using lineNo = std::vector<std::string>::size_type;

    TextQuery(std::ifstream &fcin): file(new vector<string>){
        string text;
        while (getline(fcin, text)){
            file->push_back(text);
            int n = file->size() - 1;
            istringstream line(text);
            string word;
            while (line >> word){
                auto &lines = wm[word];
                if(!lines)
                    lines.reset(new set<lineNo>);
                lines->insert(n);
            }
        }
    }

    QueryResult query(const std::string& s) const { // const 不加 影响什么 ？

    }

private:
    std::shared_ptr<std::vector<std::string> > file;

    std::map<std::string, std::shared_ptr<std::set<lineNo>> > wm;

};

class QueryResult{



    TextQuery tq;
};


void runQueries(ifstream &fcin){
    TextQuery tq(fcin);
    while (1){
        cout << "enter a word or q to quit:" << endl;
        string s;
        if(!(cin >> s) || s == "q")
            break;
        print(cout,tq.query(s)) << endl;
    }
}
int main(){

}