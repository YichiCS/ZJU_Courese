#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "pdadd.h"

using namespace std;

bool isDate0(const string& dateStr) {
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
//检验该行是否为日期

void PdAdd(const vector<string>& args){

    if (args.size() != 3) {
        cout << "Usage: diary add <filename>" << endl;
        return;
    }

    string filename = args[2];

    ifstream file(filename);
    if (!file){
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    time_t now = time(nullptr);
    char date[11];
    strftime(date, sizeof(date), "%F", localtime(&now));
    string dateStr(date);
    //增加当天时间戳


    string line;
    vector<string> lines;
    bool found = false;
    int flag = 0;
    while (getline(file, line)) {
        if (flag == 1 && isDate0(line)) flag = 0;
        if (line == date) {
            found = true;
            flag = 1;
            //break;
        }
        if(flag == 0) lines.push_back(line);  
    }
    //寻找是否有时间戳相同的日记，对其进行替换操作

    cout << "Please enter your diary (end with single line '.'): " << endl;

    lines.push_back(dateStr);
    while (getline(cin, line) && line != "."){
        lines.push_back(line);
    }
    //增加新的日记内容

    ofstream outfile(filename);
    for (const auto& l : lines) {
        outfile << l << endl;
    }
    //将更新的日记内容写入文件

    cout << endl << "The diary on "<< date << " has been update in " << filename << endl;


}