#ifndef MAP_H 
#define MAP_H
const int MAX_LENGTH = 8;
const int MAX_HEIGHT = 8;
// MapGenerator 类保证生成一个有解的迷宫
// 迷宫支持自定义大小、起始点、目标点

    class MapGenerator
    {
        private:
            int length = 4;
            int height = 4;
            //迷宫尺寸
            int maze[MAX_LENGTH][MAX_HEIGHT]= {0};
            //迷宫内容
            int start_x = 0, start_y = 0;
            int end_x = length - 1, end_y = height -1;
            int monster_x = -1, monster_y = -1;
            //入口与出口

        public:
            void MapInit();
            //迷宫随机初始化
            void MapCustomize();
            //迷宫自定义
            void MapOut();
            //输出地图
            bool isValid(int x, int y);
            bool isHarm(int x, int y);
            bool bfs();

            void exitsFind(int x, int y, bool* exits);
            int PositionCheck(int x, int y);

            std::pair<int, int>  startPosition();
    };

#endif