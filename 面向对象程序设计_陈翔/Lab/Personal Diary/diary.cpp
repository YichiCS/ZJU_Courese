#include <iostream>
#include <string>
#include <vector>

#include "pdremove.h"
#include "pdlist.h"
#include "pdshow.h"
#include "pdadd.h"

using namespace std;

void commandExecute(string command, const vector<string>& args){
    if(command == "usage"){
        cout << "Here the command you can use:" << endl;
        cout << "Quit: quit" << endl;
        cout << "Usage: usage" << endl;
        cout << "Add: add <filename>" << endl;
        cout << "Show: show <filename> <date>" << endl;
        cout << "Remove: remove <filename> <date>" << endl;
        cout << "List: list <filename> <start>(optional) <end>(optional)" << endl;

        return ;
    }
    else if(command == "add"){
        PdAdd(args);
        return ;
    }
    else if(command == "remove"){
        PdRemove(args);
        return ;
    }
    else if(command == "list"){
        PdList(args);
        return ;
    }
    else if(command == "show"){
        PdShow(args);
        return ;
    }
    else{
        cout << "No such command, you can enter 'diary usage' for help. " << endl;
    }
}

int main(int argc, char* argv[]){
    vector<string> args(argv, argv + argc);
    if (args.size() < 2){
        cout << "Useage: diary <command> <args>" << endl;
        return 0;
    }

    string command  = args[1];
    commandExecute(command, args);

    return 0;
}