#include <iostream>
#include <string>

using namespace std;

struct Students{
    string name;
    int score1;
    int score2;
    int score3;
    double average=0;
};
//define a struction to store the data;

int main()
{
    struct Students student[10];
    int     max[3]={0,0,0},min[3]={6,6,6};
    double  avr[3]={0,0,0};
    int i;

    for(i=0;i<10;i++){

        cin >> student[i].name >> student[i].score1 >> student[i].score2 >> student[i].score3;
        //input the stu's name and the scores;
        student[i].average = ( student[i].score1 + student[i].score2 + student[i].score3 )/3.0;
        //caculate the avr score;

        if(student[i].score1 >= max[0])   max[0] = student[i].score1;
        if(student[i].score2 >= max[1])   max[1] = student[i].score2;
        if(student[i].score3 >= max[2])   max[2] = student[i].score3;

        if(student[i].score1 <= min[0])   min[0] = student[i].score1;
        if(student[i].score2 <= min[1])   min[1] = student[i].score2;
        if(student[i].score3 <= min[2])   min[2] = student[i].score3;
        //choose the minium and the maxium;

        avr[0] += student[i].score1;
        avr[1] += student[i].score2;
        avr[2] += student[i].score3;
        //caculate the avr;
    }

    cout << "no\t" << "name\t" << "score1\t" << "score2\t" << "score3\t" << "average\t" << endl;
    for(i=0;i<10;i++){
        cout << i+1 << "\t" << student[i].name << "\t" << student[i].score1 << "\t" << student[i].score2 << "\t" << student[i].score3 << "\t" << student[i].average << "\t" << endl;
    }
    cout << "\t" << "average\t" << avr[0] / 10 << "\t" << avr[1] / 10 << "\t" << avr[2] / 10 << "\t" << endl;
    cout << "\t" << "min\t" << min[0] << "\t" << min[1] << "\t" << min[2] << "\t" << endl;
    cout << "\t" << "max\t" << max[0] << "\t" << max[1] << "\t" << max[2] << "\t" << endl;
    //putput all the results;

    return 0;

}