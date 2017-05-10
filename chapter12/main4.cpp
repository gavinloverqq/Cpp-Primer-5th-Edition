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

class QueryResult{
    friend std::ostream & print(std::ostream &, const QueryResult& );

public:
    using lineNo = std::vector<std::string>::size_type;

    QueryResult(std::string s,
                std::shared_ptr<std::set<lineNo> > p,
                std::shared_ptr<std::vector<std::string> > f):
            sought(s), lines(p), file(f){}

private:
    std::string sought;
    std::shared_ptr<std::set<lineNo> > lines;
    std::shared_ptr<std::vector<std::string> > file;
};

std::ostream & print(std::ostream &os, const QueryResult &qr){
    os << qr.sought << "occurs " << qr.lines->size() << " times:" << endl;
    for (auto bg = qr.lines->begin(); bg != qr.lines->end(); ++bg) {
        os << "(line " << *bg + 1 << ") " << (*qr.file)[*bg] << endl;
    }
    return os;
}


class TextQuery{
public:
    using lineNo = std::vector<std::string>::size_type;

    TextQuery(std::ifstream &fcin): file(new vector<string>){
        string text;
        while (getline(fcin, text)){
            file->push_back(text);
            lineNo n = file->size() - 1;
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
        static std::shared_ptr<std::set<lineNo> > nodata(new std::set<lineNo>); // 为什么要static ？
        auto loc = wm.find(s);
        if(loc == wm.end())
            return QueryResult(s, nodata, file);
        else
            return QueryResult(s, loc->second, file);
    }

private:
    std::shared_ptr<std::vector<std::string> > file;
    std::map<std::string, std::shared_ptr<std::set<lineNo>> > wm;
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
    ifstream fcin;
    fcin.open("/Users/wankun/Desktop/Cpp-Primer-5th-Edition/chapter12/data.in");
    runQueries(fcin);
}