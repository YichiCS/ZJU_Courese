#ifndef GAME_H 
#define GAME_H
#include "Map.h" 

using namespace std;

    class MapGenerator;

    class Game
    {
        private:
            bool exits[4] = {false, false, false, false};
            string choice[4] = {"south", "north", "east", "west"};
            string action;
            string go;

            int findPrincess = 0;
            int massionCompelete = 0;
            int position_x = -1, position_y = -1;
            string name = "Brave";

        public:
            void GameStart(MapGenerator map);
            void PostionUndate(int n);
            void exitsInit();
            void Action(int check);
            void GameInit();
            bool ValidateCommand(MapGenerator map);

    };

#endif