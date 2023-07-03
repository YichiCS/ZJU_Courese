#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "pdlist.h"

using namespace std;

bool isDate3(const string& dateStr) {
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

void PdList(const vector<string>& args){

    if (args.size() < 3 || args.size() > 5) {
        cout << "Usage: diary list <filename> <start>(optional) <end>(optional)" << endl;
        return;
    }
    
    int begin = 0;
    int end = 0;
    string startDate, endDate;

    string filename = args[2];
    if (args.size() == 4){
        begin = 1;
        startDate = args[3];
    }   
    if (args.size() == 5){
        begin = 1;
        startDate = args[3];
        end = 1;
        endDate = args[4];
    }
    //传递参数
    
    ifstream file(filename);
    if (!file){
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    string line;
    vector<string> lines;

    int mode = begin + end;
    if(begin == 0 && end == 0){
        while (getline(file, line)){
            lines.push_back(line); 
        }
    }//全输出
    else if(begin == 1 && end == 0){
        int flag = 0;
        while (getline(file, line)){
            if(line == startDate)   flag = 1;
            if(flag)    lines.push_back(line); 
        }
    }//仅开头
    else if(begin == 0 && end == 1){
        int flag = 0;
        while (getline(file, line)){
            if(flag == 1 && isDate3(line))  break;
            if(line == endDate)   flag = 1;
            lines.push_back(line); 
        }
    }//仅结尾
    else{
        int flag0 = 0;
        int flag1 = 0;
        while (getline(file, line)){
            if(flag1 == 1 && isDate3(line))  break;
            if(line == endDate)     flag1 = 1;
            if(line == startDate)   flag0 = 1;
            if(flag0)    lines.push_back(line); 
        }
    }//开头结尾

    for (const auto& l : lines) {
        cout << l << endl;
    }
    //输出日记内容

    cout << endl << "The diary has been listed." << endl;


}