#ifndef BASE64_TEST_H
#define BASE64_TEST_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>
#include <type_traits>

#include "print.h"
#include "base64.h"
#include "base64_serialize.h"
#include "user_defined_type.h"


namespace base64_test{

    int choice;
    std::string file1 = "base64_test1.xml";
    std::string file2 = "base64_test2.xml";

    //读入两个数据，序列化到两个文件
    template <typename T, typename U>
    void write(T& obj1, U& obj2){

        base64_serialize_lib::base64_serialize(obj1, file1); 
        base64_serialize_lib::base64_serialize(obj2, file2); 
    }

    //根据输入，反序列化其中一个文件到输出
    template <typename T>
    void load(T& obj){

        if (choice == 1)    base64_serialize_lib::base64_deserialize(obj, file1); 
        else if (choice == 2) base64_serialize_lib::base64_deserialize(obj, file2); 
    }

    //测试指定类型的序列化/反序列化是否运行
    template <typename T, typename U, typename V>
    void test(T& obj1, U& obj2, V& obj3){
        write(obj1, obj2);
        load(obj3);
        print_lib::print(obj1, 1);
        print_lib::print(obj2, 2);
        print_lib::print(obj3, 3);
        std::cout << std::endl;
    }

    void base64_test() {

        std::cout << "Input 1 or 2" << std::endl;
        std::cin >> choice ;
        //choice = 1;
        //choice = 2;  

        //测试 int 的序列化和反序列化
       {
            int a = 42;
            int b = 21;
            int c;
            test(a, b, c);
        }
        //测试 double 的序列化和反序列化
         {
            double x = 3.1415926;
            double y = 2.7182818;
            double z;
            test(x,y,z);
        }
        //测试 char 的序列化和反序列化
        {
            char ch1 = 'O';
            char ch2 = 'P';
            char ch3;
            test(ch1, ch2, ch3);
        }
       //测试 bool 的序列化和反序列化
        {
            bool m = true;
            bool n = false;
            bool t;
            test(m, n, t);
        }
       //测试 std::string 的序列化和反序列化
        {
            std::string string1 = "Hello, world!";
            std::string string2 = "The world!";
            std::string string3;
            test(string1, string2, string3);
        }
         //测试 std::vector 的序列化和反序列化
        {
            std::vector<int> vec1 = {1, 3, 5, 7, 9};
            std::vector<int> vec2 = {2, 4, 8, 16, 32};
            std::vector<int> vec3;
            test(vec1, vec2, vec3);
        }
        // 测试 std::list 的序列化和反序列化
        {
            std::list<std::string> list1 = {"a", "b", "c", "d", "e"};
            std::list<std::string> list2 = {"A", "B", "C", "D", "E"};
            std::list<std::string> list3;
            test(list1, list2, list3);
        }
       // 测试 std::map 的序列化和反序列化
        {
            std::map<std::string, int> map1{{"CVPR", 2023}, {"ICLR", 2022}, {"ECCV", 2021}};
            std::map<std::string, int> map2{{"Apple", 1}, {"Pear", 2}, {"Banana", 3}};
            std::map<std::string, int> map3;
            test(map1, map2, map3);
        }
        // 测试 std::pair 的序列化和反序列化
        {
            // 测试 std::pair 的序列化和反序列化
            std::pair<std::string, int> pair1{"Transformer", 2014};
            std::pair<std::string, int> pair2{"Network", 1999};
            std::pair<std::string, int> pair3;
            test(pair1, pair2, pair3);
        }
         // 测试 std::set 的序列化和反序列化
        {
            std::set<double> set1{1.1, 2.2, 3.3, 4.4, 5.5};
            std::set<double> set2{0.9, 1.9, 2.9, 3.9, 4.9};
            std::set<double> set3;
            test(set1, set2, set3);
        }
        //测试 UserDefinedType 的序列化和反序列化
        {
            struct UserDefinedType obj1 = {12, "Maxwell", false, {1.2, 2.3, 3.4},
                                            {"Counter Strike", "Genshin"}, 
                                            {{"father", 56}, {"mother", 48}},
                                            {1.78, 56},
                                            {'a', 'D'}
                                            };
            struct UserDefinedType obj2 = {38, "Newtown", true, {1.3, 2.4},
                                            {"Minecraft", "Call of Duty", "Dota"},
                                            {{"father", 52}, {"mother", 47}, {"wife", 23}, {"son", 16}},
                                            {1.65, 50},
                                            {'x', 'M', 'L'}
                                            };
            struct UserDefinedType obj3;
            test(obj1, obj2, obj3);
            struct UserDefinedType obj4 = {21, "Sharks", true, {12, 23, 34, 45, 56},
                                            {"League of Legends", "Overwatch"},
                                            {{"father", 61}, {"wife", 24}},
                                            {1.80, 78},
                                            {'c', 'O', 'l', 'I'}
                                            };
            struct UserDefinedType obj5 = {76, "Lions", false, {13, 24, 35},
                                            {"The Sims", "Among Us", "Valorant", "Apex Legends"},
                                            {{"father", 67}},
                                            {1.73, 63},
                                            {'p'}
                                            };

        //测试 STL 容器中的 UserDefinedType

            std::vector<UserDefinedType> vec_obj1 = {obj1,obj2};
            std::vector<UserDefinedType> vec_obj2 = {obj4,obj5};
            std::vector<UserDefinedType> vec_obj3;
            test(vec_obj1, vec_obj2, vec_obj3);

            std::set<UserDefinedType> set_obj1 = {obj1,obj2};
            std::set<UserDefinedType> set_obj2 = {obj4,obj5};
            std::set<UserDefinedType> set_obj3;
            test(set_obj1, set_obj2, set_obj3);

            std::pair<UserDefinedType, int> pair_obj1 = {obj2, 2};
            std::pair<UserDefinedType, int> pair_obj2 = {obj4,4};
            std::pair<UserDefinedType, int> pair_obj3;
            test(pair_obj1, pair_obj2, pair_obj3);

            std::list<UserDefinedType> list_obj1 = {obj1, obj2};
            std::list<UserDefinedType> list_obj2 = {obj4, obj5};
            std::list<UserDefinedType> list_obj3;
            test(list_obj1, list_obj2, list_obj3);

            std::map<UserDefinedType, int> map_obj1 = {{obj1,1},{obj2, 2}};
            std::map<UserDefinedType, int> map_obj2 = {{obj4,4},{obj5, 5}};
            std::map<UserDefinedType, int> map_obj3;
            test(map_obj1, map_obj2, map_obj3);

       }

        std::cout << "Test successfully!" << std::endl;

        return ;
    }
}

#endif