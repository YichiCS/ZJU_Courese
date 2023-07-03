#include <iostream>
#include <string>
#include "Map.h"
#include "Game.h"

using namespace std;

void Game::GameInit(){
    cout << "Before the Game begin, what's your name, my brave hero?" << endl;
    cout << "Enter your name:" << endl;
    cin >> name ;
    cout << "Welcome " << name << ". Let's start our adventure now :D" << endl;
}
//初始化勇者姓名

void Game::GameStart(MapGenerator map){

    GameInit();

    std::pair<int, int> startPosition = map.startPosition();
    position_x = startPosition.first;
    position_y = startPosition.second;
    //传递初始位置

    while(!massionCompelete){
        
        map.exitsFind(position_x, position_y, exits);

        cout << "Welcome to (" << position_x << ", " << position_y << ")," << name <<". Now, you have the following choices:";
        for(int i = 0;i < 4;i++){
            if(exits[i])    cout << " go " << choice[i];
        }
        cout << "." << endl << "Enter your commond:" << endl;
        
        int flag = 1;

        do{
            if(!flag) cout << "Please Enter a valid action." << endl;
            cin >> go >> action;
            flag = 0;
        }while(!ValidateCommand(map));
            
        for(int i = 0;i < 4;i++){
            if(action == choice[i])  PostionUndate(i);
        }
        
        Action(map.PositionCheck(position_x, position_y));
        cout << endl;
    }

    return ;
}
//游戏主体

void Game::Action(int check){
    switch (check){
        case -1:{
            massionCompelete = 1;
            cout << endl << "The poor " << name <<" died at the hands of the devil's minions" << endl;
            break;
        }
        case 1:{
            findPrincess = 1;
            cout << endl << name <<", you have found the princess, escort her back :D" << endl;
            break;
        }
        case 2:{
            if(findPrincess == 1){
                massionCompelete = 1;
                cout << endl << "Good job, " << name <<", you have successfully completed the task of rescuing the princess, go to the king to get the reward!" << endl; 
                break;
            }
        }
    }
    return ;
}
//判断是否有重要事件

void Game::PostionUndate(int n){
    switch(n){

        case 0: position_x++;break;
        case 1: position_x--;break;
        case 2: position_y++;break;
        case 3: position_y--;break;
    }
    return ;
}
//根据操作改变位置


void Game::exitsInit(){
    for(int i = 0;i < 4;i++){
        exits[i] = 0;
    }
    return ;
}
//初始化出路

bool Game::ValidateCommand(MapGenerator map){
    int test_x = position_x;
    int test_y = position_y;
    for(int i = 0;i < 4;i++){
        if(action == choice[i]){
            switch(i){
                case 0: test_x++;break;
                case 1: test_x--;break;
                case 2: test_y++;break;
                case 3: test_y--;break;
            }
        }
    }
    if(map.isHarm(test_x, test_y))    return true;
    else return false;

}
//检查操作是否可用