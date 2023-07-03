#ifndef BINARY_SERIALIZATION_H
#define BINARY_SERIALIZATION_H

#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <tuple>
#include <list>
#include <map>
#include <set>
#include <type_traits>

namespace binary_serialize_lib{

    //通用模版
    template<typename T>
    struct SerializeHelper {
        static void serialize(const T& obj, std::ofstream& ofs){
            if constexpr (std::is_arithmetic_v<T>) {
                ofs.write(reinterpret_cast<const char*>(&obj), sizeof(T));
            } else {
                obj.binary_serialize(ofs);
            }
        }
        static void deserialize(T& obj, std::ifstream& ifs){
            if constexpr (std::is_arithmetic_v<T>) {
                ifs.read(reinterpret_cast<char*>(&obj), sizeof(T));
            } else {
                obj.binary_deserialize(ifs);
            }
        }
    };

    //针对std::string
    template<>
    struct SerializeHelper<std::string> {
        static void serialize(const std::string& obj, std::ofstream& ofs) {
            size_t len = obj.size();
            SerializeHelper<size_t>::serialize(len, ofs);
            ofs.write(obj.data(), len);
        }

        static void deserialize(std::string& obj, std::ifstream& ifs) {
            size_t len;
            SerializeHelper<size_t>::deserialize(len, ifs);
            std::vector<char> buffer(len);
            ifs.read(buffer.data(), len);
            obj.assign(buffer.begin(), buffer.end());
        }
    };
    //针对std::vector
    template<typename T>
    struct SerializeHelper<std::vector<T>> {
        static void serialize(const std::vector<T>& obj, std::ofstream& ofs){
            size_t len = obj.size();
            SerializeHelper<size_t>::serialize(len, ofs);
            for(const auto& elem : obj) {
                SerializeHelper<T>::serialize(elem, ofs);
            }
        }
        static void deserialize(std::vector<T>& obj, std::ifstream& ifs){
            obj.clear();
            size_t len;
            SerializeHelper<size_t>::deserialize(len, ifs);
            obj.resize(len);
            for(auto& elem : obj) {
                SerializeHelper<T>::deserialize(elem, ifs);
            }
        }
    };
    //针对std::set
    template<typename T>
    struct SerializeHelper<std::set<T>> {
        static void serialize(const std::set<T>& obj, std::ofstream& ofs){
            size_t len = obj.size();
            SerializeHelper<size_t>::serialize(len, ofs);
            for(const auto& elem : obj) {
                SerializeHelper<T>::serialize(elem, ofs);
            }
        }
        static void deserialize(std::set<T>& obj, std::ifstream& ifs) {
            size_t len;
            SerializeHelper<size_t>::deserialize(len, ifs);
            obj.clear();
            for (size_t i = 0; i < len; i++) {
                T elem;
                SerializeHelper<T>::deserialize(elem, ifs);
                obj.insert(elem);
            }
        }
    };
    //针对std::map
    template<typename K, typename V>
    struct SerializeHelper<std::map<K, V>> {
        static void serialize(const std::map<K, V>& obj, std::ofstream& ofs){
            size_t len = obj.size();
            SerializeHelper<size_t>::serialize(len, ofs);
            for(const auto& elem : obj) {
                SerializeHelper<K>::serialize(elem.first, ofs);
                SerializeHelper<V>::serialize(elem.second, ofs);
            }
        }
        static void deserialize(std::map<K, V>& obj, std::ifstream& ifs){
            size_t len;
            SerializeHelper<size_t>::deserialize(len, ifs);
            obj.clear();
            for(size_t i = 0; i < len; i++) {
                K key;
                V value;
                SerializeHelper<K>::deserialize(key, ifs);
                SerializeHelper<V>::deserialize(value, ifs);
                obj.insert({key, value});
            }
        }
    };
    //针对std::list
    template<typename T>
    struct SerializeHelper<std::list<T>> {
        static void serialize(const std::list<T>& obj, std::ofstream& ofs){
            size_t len = obj.size();
            SerializeHelper<size_t>::serialize(len, ofs);
            for(const auto& elem : obj) {
                SerializeHelper<T>::serialize(elem, ofs);
            }
        }
        static void deserialize(std::list<T>& obj, std::ifstream& ifs){
            size_t len;
            SerializeHelper<size_t>::deserialize(len, ifs);
            obj.clear();
            for(size_t i = 0; i < len; i++) {
                T elem;
                SerializeHelper<T>::deserialize(elem, ifs);
                obj.push_back(elem);
            }
        }
    };
    //针对std::pair
    template<typename T, typename U>
    struct SerializeHelper<std::pair<T, U>> {
        static void serialize(const std::pair<T, U>& obj, std::ofstream& ofs){
            SerializeHelper<T>::serialize(obj.first, ofs);
            SerializeHelper<U>::serialize(obj.second, ofs);
        }
        static void deserialize(std::pair<T, U>& obj, std::ifstream& ifs){
            SerializeHelper<T>::deserialize(obj.first, ifs);
            SerializeHelper<U>::deserialize(obj.second, ifs);
        }
    };

    //通用接口
    template<typename T>
    void binary_serialize(const T& obj, std::ofstream& ofs){
        SerializeHelper<T>::serialize(obj, ofs);
    }
    template<typename T>
    void binary_deserialize(T& obj, std::ifstream& ifs){
        SerializeHelper<T>::deserialize(obj, ifs);
    }
}
#endif 