#include <iostream>
#include "Map.h"
//定义地图的文件
#include "Game.h"
//定义行动的文件

using namespace std;

int main(){
    //初始化地图，随机放置怪物
    MapGenerator map;
    map.MapInit();
    map.MapOut();
    //开始游戏  

    Game game;
    game.GameStart(map);
    return 0;
}