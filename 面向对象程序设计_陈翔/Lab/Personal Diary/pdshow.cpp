#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "pdlist.h"

using namespace std;

bool isDate4(const string& dateStr) {
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

void PdShow(const vector<string>& args){

    if (args.size() != 4) {
        cout << "Usage: diary list <filename> <date>" << endl;
        return;
    }

    string filename = args[2];
    string date = args[3];
    //传递参数
    
    ifstream file(filename);
    if (!file){
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    string line;
    vector<string> lines;

    
    int flag = 0;
    while (getline(file, line)){
        if(flag == 1 && isDate4(line))  break;
        if(line == date)     flag = 1;
        if(flag)    lines.push_back(line); 
    }

    for (const auto& l : lines) {
        cout << l << endl;
    }
    //输出日记内容

    cout << endl << "The diary on " << date << "has been shown." << endl;


}