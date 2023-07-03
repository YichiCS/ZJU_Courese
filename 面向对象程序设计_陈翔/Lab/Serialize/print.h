#ifndef TOOL_LIB_H
#define TOOL_LIB_H

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>

#include "user_defined_type.h"

using namespace user_defined_type;

namespace print_lib{

    //打印对象
    template <typename T>
    void print(T obj, int num) {
        std::cout << /*&obj <<*/ " UserDefinedType" << num << " = " << obj << std::endl;
    }
    //int型
    void print(const int& obj, int num) {
        std::cout << /*&obj <<*/ " Int" << num << " = " << obj << std::endl;
    }
    //double型
    void print(const double& obj, int num) {
        std::cout << /*&obj <<*/ " Double" << num << " = " << obj << std::endl;
    }
    //string型
    void print(const std::string& obj, int num){
        std::cout << /*&obj <<*/ " String" << num << " = " << obj << std::endl;
    }
    //vector
    template <typename U>
    void print(const std::vector<U>& obj, int num){
        std::cout << /*&obj <<*/ " Vec" << num << " = {";
        for(auto& elem : obj){
            std::cout << elem << " ";
        }
        std::cout << "}" << std::endl;
    }
    //list
    template <typename U>
    void print(const std::list<U>& obj, int num){
        std::cout << /*&obj <<*/ " List" << num << " = {";
        for(auto& elem : obj){
            std::cout << elem << " ";
        }
        std::cout << "}" << std::endl;
    }
    //map
    template <typename U, typename V>
    void print(const std::map<U, V>& obj, int num){
        std::cout << /*&obj <<*/ " Map" << num << " = {";
        for(auto& elem : obj){
            std::cout << "{" <<elem.first << ", " <<elem.second << "} ";
        }
        std::cout << "}" << std::endl;
    }
    //pair
    template <typename U, typename V>
    void print(const std::pair<U, V>& obj, int num) {
        std::cout << /*&obj <<*/ " Pair" << num << " = {" << obj.first << ", " << obj.second << "}" << std::endl;
    }
    //set
    template <typename U>
    void print(const std::set<U>& obj, int num){
        std::cout << /*&obj <<*/ " Set" << num << " = {";
        for(auto& elem : obj){
            std::cout << elem << " ";
        }
        std::cout << "}" << std::endl;
    }

    
}

#endif