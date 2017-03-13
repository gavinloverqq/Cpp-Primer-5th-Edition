//
// Created by kunwan on 3/13/17.
//
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(){
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
}