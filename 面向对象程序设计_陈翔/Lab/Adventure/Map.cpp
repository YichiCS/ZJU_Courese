#include <iostream>
#include <queue>
#include <time.h>
#include "Map.h"

using namespace std;

void MapGenerator::MapCustomize(){
    int choice = -1;
    cout << "Do you want to customize the game or play according to preset parameters?" <<endl;
    cout << "1. Customize" << endl << "2. Preset parameters" << endl;
    while (choice != 1 && choice != 2){

        cin >> choice;
        if (choice != 1 && choice != 2){
            cout << "Please enter 1 or 2 to continue :D" << endl; 
        }
        else if (choice == 2) return ;
        else break;
    }
    cout << "Please enter a custom map size, up to 8*8." << endl ;
    cout << "Example: 6 6" << endl;
    cin >> length >> height ;
    length = max(0,min(length, MAX_LENGTH));
    height = max(0,min(height, MAX_HEIGHT));
    return ;
}
//自定义地图

void MapGenerator::MapInit(){
    time_t t;
    srand(t);
    MapCustomize();

    end_x = rand() % length;
    end_y = rand() % height;

    bool hasSolution = false;
    maze[start_x][start_y] = 2;
    maze[end_x][end_y] = 3;
    while (!hasSolution) {
        // 生成新的随机迷宫
        for(int i = 0;i < length; i++){
            for(int j = 0;j < height;j++){
                if((i == start_x && j == start_y) || (i == end_x && j == end_y) )   continue;
                if (rand() % 2 == 0) { 
                    maze[i][j] = 1;
                } 
                else maze[i][j] = 0;
            }
        }
        monster_x = end_x;
        monster_y = end_y;
        while (monster_x == end_x && monster_y == end_y){
            monster_x = rand() % length;
            monster_y = rand() % height;
        }
        if ((monster_x == start_x && monster_y == start_y) || (monster_x == end_x && monster_y == end_y))   continue;
        maze[monster_x][monster_y] = 4;
        // 判断迷宫是否有解
        if (isValid(0, 0) && isValid(length - 1, height - 1) && bfs()) {
            cout << "Map has generated"<< endl;
            hasSolution = true;
        } 
        else {
            cout << "Map is generating" << endl;
        }
    }
    //迷宫生成
    return ;
}
// 生成一个保证有解的迷宫

void MapGenerator::MapOut(){

    for(int i = 0;i < length; i++){
        for(int j = 0;j < height;j++){
            cout<< maze[i][j] << ' ';
        }
        cout << endl;
    }

    cout << endl;
    return ;
    //迷宫输出
}

bool MapGenerator::isValid(int x, int y) {
    if (x < 0 || x >= length || y < 0 || y >= height || maze[x][y] == 1 || maze[x][y] == 4) {
        return false;
    }
    return true;
}
//判断一个点是否可通行

bool MapGenerator::isHarm(int x, int y) {
    if (x < 0 || x >= length || y < 0 || y >= height || maze[x][y] == 1) {
        return false;
    }
    return true;
}
//判断一个点在游戏中是否可行走

bool MapGenerator::bfs() {
    // 定义一个队列用于存储待搜索的节点
    queue<pair<int, int> > q;
    // 定义一个二维数组用于记录每个节点是否被访问过
    bool visited[MAX_LENGTH][MAX_HEIGHT]= { false };

    // 将起始节点加入队列
    q.push(make_pair(start_x, start_y));
    // 将起始节点标记为已访问
    visited[start_x][start_y] = true;

    // 开始搜索
    while (!q.empty()) {
        // 取出队列中的第一个节点
        pair<int, int> node = q.front();
        q.pop();

        // 如果当前节点是终点，则返回true
        if (node.first == end_x && node.second == end_y) {
            return true;
        }

        // 否则，遍历当前节点的所有相邻节点
        // 并将未访问过的相邻节点加入队列
        if (isValid(node.first + 1, node.second) && !visited[node.first + 1][node.second]) {
            q.push(make_pair(node.first + 1, node.second));
            visited[node.first + 1][node.second] = true;
        }
        if (isValid(node.first, node.second + 1) && !visited[node.first][node.second + 1]) {
            q.push(make_pair(node.first, node.second + 1));
            visited[node.first][node.second + 1] = true;
        }
        if (isValid(node.first - 1, node.second) && !visited[node.first - 1][node.second]) {
            q.push(make_pair(node.first - 1, node.second));
            visited[node.first - 1][node.second] = true;
        }
        if (isValid(node.first, node.second - 1) && !visited[node.first][node.second - 1]) {
            q.push(make_pair(node.first, node.second - 1));
            visited[node.first][node.second - 1] = true;
        }
    }
    // 如果队列为空且没有到达终点，则返回false
    return false;
}


std::pair<int, int>  MapGenerator::startPosition(){
    return std::make_pair(start_x, start_y);
}
//返回输出坐标

void MapGenerator::exitsFind(int x, int y, bool* exits){
    memset(exits, 0, sizeof(exits));
    if(isHarm(x + 1, y))   exits[0] = true;
    if(isHarm(x - 1, y))   exits[1] = true;
    if(isHarm(x, y + 1))   exits[2] = true;
    if(isHarm(x, y - 1))   exits[3] = true;
    return ;
}
//返回可行的出路

int MapGenerator::PositionCheck(int x, int y){
    if(x == monster_x && y == monster_y)    return -1;
    if(x == end_x && y == end_y)            return 1;
    if(x == start_x && y == start_y)        return 2;
    return 0;
}
//检查特殊点