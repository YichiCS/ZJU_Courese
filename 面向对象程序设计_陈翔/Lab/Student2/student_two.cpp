#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class Student 
{
    public :
        
        vector<string>  name;
        vector<string>  course;             //The name of the student & The courses chosen by the student
        vector<string>  grade;                 //The grade the student got
        int  courseNum = 0;                 //The grade the student got
        double averageGrade = 0;


};

class Course
{
    public :
        string name;
        double chosenNum = 0;
        double maxGrade = -1;
        double minGrade = 999;
        double averageGrade = 0;
};
// The course class contain the all information we need for the output


int main(){

    vector<Student> Stu;
    //Used for store the information of the students
    vector<Course> Courses;
    vector<string> courseName;
    //Used for store all the courses

    std::fstream fin;
    fin.open("studentGrades.txt",std::ios::in);
    //Read in the file


    cout << "How mant students do you want to inquire?" << endl;
    cout << "Enter here please :" << endl;  

    int Num ;

    cin >> Num;

    cout << "Querying the grades of " <<  Num << " students for you now." << endl;


    
    char line[128]={0};
    int k= 0;

    while(fin.getline(line,sizeof(line)) && k < Num ){
        Student stu;
        string word = "";
        for(auto x : line){
            
            if((x ==' ' || x =='\0') && word != ""){
                if(stu.name.empty())    stu.name.push_back(word);
                else if(stu.course.size()==stu.grade.size()){

                    stu.course.push_back(word);

                    if (!count(courseName.begin(), courseName.end(), word)){
                        courseName.push_back(word);
                        Course cour;
                        cour.name = word;
                        Courses.push_back(cour);
                    }
                    //Push the first apper course into the courseName and create a new Course object
                } 

                else{
                    stu.grade.push_back(word);

                    stu.averageGrade += stoi(word);
                    stu.courseNum += 1;
                }
                //Calculate the average grades
                    
                word = "";
            }
            else if(x != ' ' && x != '\0'){
                word = word + x;
            }
        }
        stu.averageGrade /= stu.courseNum;
        Stu.push_back(stu);
        //Push the new stu into the Stu

        memset(line, '\0', sizeof(line));
        k++;
        //reset the line for the next time getline
    } 
    //Read in the data of students

    for(int i = 0; i < Courses.size(); i++){

        for (int j = 0;j < Num; j++){

            if (Stu[j].courseNum == 0) continue;
            //if all the course chosen by this student has been search, next student

            for(int k = 0; k < Stu[j].course.size();k++){
                if (Stu[j].course[k] == Courses[i].name){
                    Courses[i].averageGrade += stoi(Stu[j].grade[k]);
                    Courses[i].chosenNum += 1;

                    if (stoi(Stu[j].grade[k]) > Courses[i].maxGrade)
                        Courses[i].maxGrade =  stoi(Stu[j].grade[k]);
                    //Find the max
                    
                    if (stoi(Stu[j].grade[k]) < Courses[i].minGrade)
                        Courses[i].minGrade =  stoi(Stu[j].grade[k]);
                    //Find the min

                    Stu[j].courseNum --;
                    break;
                }
            }
        }
        Courses[i].averageGrade /= Courses[i].chosenNum;
    }
    if (Num > Stu.size()){
        Num = Stu.size();
        cout << "Sorry, there is not have so many students. Output all the students instead.\n";
    }


    cout << "no\t" << "name\t" ;
    for (int i= 0;i < Courses.size();i++){
        cout<<Courses[i].name<<'\t';
    }
    cout << "average\t\n";
    //Output the headline

    for (int i = 0;i < Num;i++){
        cout<< (i+1) << '\t' << Stu[i].name[0]<< '\t';
        for (int j= 0;j < Courses.size();j++){
            for(int k = 0;k < Stu[i].course.size();k++){
                if (Stu[i].course[k] == Courses[j].name){
                    cout<< Stu[i].grade[k];
                    break;
                }
            }
            cout<< '\t';
        }
        cout<<Stu[i].averageGrade<< '\t' << '\n';
    }
    cout << '\t' << "average\t";
    for(int i = 0; i<Courses.size(); i++){
        cout << Courses[i].averageGrade<<'\t';
    }
    cout << "\n\t" << "max\t";
    for(int i = 0; i<Courses.size(); i++){
        cout << Courses[i].maxGrade<<'\t';
    }
    cout << "\n\t" << "min\t";
    for(int i = 0; i<Courses.size(); i++){
        cout << Courses[i].minGrade<<'\t';
    }
            
    cout<<"\n Wish you a nice day!"<<endl;
}