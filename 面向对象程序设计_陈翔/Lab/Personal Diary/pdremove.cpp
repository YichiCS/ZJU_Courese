#include <iostream>
#include <fstream>

#include "pdremove.h"

using namespace std;

bool isDate1(const string& dateStr) {
    if (dateStr.length() != 10){
        return false;
    }
    if (dateStr[4] != '-' || dateStr[7] != '-'){
        return false;
    }

    int year = stoi(dateStr.substr(0, 4));
    int month = stoi(dateStr.substr(5, 2));
    int day = stoi(dateStr.substr(8, 2));

    if (year < 2023 || month < 1 || month > 12 || day < 1 || day > 31){
        return false;
    }

    return true;
}
//检查该行是否为日期

void PdRemove(const vector<string>& args){

    if(args.size() != 4){
        cout << "Usage: diary remove <filename> <date>" << endl;
        return ;
    }

    string filename = args[2];
    string date = args[3];

    ifstream file(filename);
    if (!file) {
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    string line;
    vector<string> lines;
    bool found = false;
    int flag = 0;
    while (getline(file, line)) {
        if (flag == 1 && isDate1(line)) flag = 0;
        if (line == date) {
            found = true;
            flag = 1;
        }
        if(flag == 0) lines.push_back(line); 
    }
    //保存非目标日期日记，跳过目标日

    if(found == false){
        cout << "Error: Diary on " << date << " not found" << endl;
        return ;
    }
    //若没有改日，报错

    while (getline(file, line) && line != "") {}

    ofstream outfile(filename);
    for (const auto& l : lines) {
        outfile << l << endl;
    }
    //写入日记到目标文件

    cout << endl << "Diary on " << date << " has been deleted from " << filename << endl;

}