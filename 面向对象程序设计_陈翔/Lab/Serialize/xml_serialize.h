#ifndef XML_SERIALIZE_H
#define XML_SERIALIZE_H


#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <tuple>
#include <list>
#include <map>
#include <set>
#include <typeinfo>
#include <type_traits>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace xml_serialize_lib {
template <class T>

    struct TypeMapper {
        static constexpr const char *type() { return "UserDefinedType"; }
    };

    template <>
    struct TypeMapper<int> {
        static constexpr const char *type() { return "int"; }
    };

    template <>
    struct TypeMapper<double> {
        static constexpr const char *type() { return "double"; }
    };

    template <>
    struct TypeMapper<char> {
        static constexpr const char *type() { return "char"; }
    };

    template <>
    struct TypeMapper<bool> {
        static constexpr const char *type() { return "bool"; }
    };

    template <>
    struct TypeMapper<std::string> {
        static constexpr const char *type() { return "string"; }
    };

    template <typename T>
    struct TypeMapper<std::vector<T>> {
        static constexpr const char *type() { return "std_vector"; }
    };

    template <typename T>
    struct TypeMapper<std::list<T>> {
        static constexpr const char *type() { return "std_list"; }
    };

    template <typename T>
    struct TypeMapper<std::set<T>> {
        static constexpr const char *type() { return "std_set"; }
    };

    template <typename TKey, typename TValue>
    struct TypeMapper<std::map<TKey, TValue>> {
        static constexpr const char *type() { return "std_map"; }
    };

    template <typename T1, typename T2>
    struct TypeMapper<std::pair<T1, T2>> {
        static constexpr const char *type() { return "std_pair"; }
    };

    template<typename T>
    struct SerializeHelper {
        static void serialize(const T& obj, XMLDocument& doc, XMLElement* element){
            if constexpr (std::is_arithmetic_v<T>) {
                element->SetText(obj);
            } else {
                obj.xml_serialize(doc, element);
            }
        }
        static void deserialize(T& obj, const XMLElement* element){
            if constexpr (std::is_arithmetic_v<T>) {
                obj = element->DoubleText();
            } else {
                obj.xml_deserialize(element);
            }
        }
    }; 
    //针对 bool
    template<>
    struct SerializeHelper<bool> {
        static void serialize(const bool& obj, XMLDocument& doc, XMLElement* element) {
            element->SetText(obj ? "true" : "false");
        }
        static void deserialize(bool& obj, const XMLElement* element) {
            const char* text = element->GetText();
            obj = (text != nullptr && strcmp(text, "true") == 0);
        }
    };

    //针对std::string
    template<>
    struct SerializeHelper<std::string> {
        static void serialize(const std::string& obj, XMLDocument& doc, XMLElement* element) {
            element->SetText(obj.c_str());
        }

        static void deserialize(std::string& obj, const XMLElement* element) {
            obj = element->GetText();
        }
    };

    //针对std::vector
    template<typename T>
    struct SerializeHelper<std::vector<T>> {
        static void serialize(const std::vector<T>& obj, XMLDocument& doc, XMLElement* element){
            element->SetAttribute("size", static_cast<int>(obj.size()));
            for(const auto& elem : obj) {
                //XMLElement* childElement = doc.NewElement("Element");
                const char* typeName = TypeMapper<typename std::remove_cv<typename std::remove_reference<decltype(elem)>::type>::type>::type();
                XMLElement* childElement = doc.NewElement(typeName);
                SerializeHelper<T>::serialize(elem, doc, childElement);
                element->InsertEndChild(childElement);
            }
        }
        static void deserialize(std::vector<T>& obj, const XMLElement* element){
            obj.clear();
            int size;
            element->QueryIntAttribute("size", &size);
            obj.resize(size);
            const char* typeName = TypeMapper<T>::type();
            const XMLElement* childElement = element->FirstChildElement(typeName);
            for(auto& elem : obj) {
                SerializeHelper<T>::deserialize(elem, childElement);
                childElement = childElement->NextSiblingElement(typeName);
            }
        }
    };
    //std::set
    template<typename T>
    struct SerializeHelper<std::set<T>> {
        static void serialize(const std::set<T>& obj, XMLDocument& doc, XMLElement* element){
            element->SetAttribute("size", static_cast<int>(obj.size()));
            for(const auto& elem : obj) {
                //XMLElement* childElement = doc.NewElement("Element");
                const char* typeName = TypeMapper<typename std::remove_cv<typename std::remove_reference<decltype(elem)>::type>::type>::type();
                XMLElement* childElement = doc.NewElement(typeName);
                SerializeHelper<T>::serialize(elem, doc, childElement);
                element->InsertEndChild(childElement);
            }
        }
        static void deserialize(std::set<T>& obj, const XMLElement* element){
            obj.clear();
            int size;
            element->QueryIntAttribute("size", &size);
            const char* typeName = TypeMapper<T>::type();
            const XMLElement* childElement = element->FirstChildElement(typeName);
            //const XMLElement* childElement = element->FirstChildElement("Element");
            for(int i = 0; i < size; i++) {
                T elem;
                SerializeHelper<T>::deserialize(elem, childElement);
                obj.insert(elem);
                childElement = childElement->NextSiblingElement(typeName);
            }
        }
    };
    //std::map
    template<typename K, typename V>
    struct SerializeHelper<std::map<K, V>> {
        static void serialize(const std::map<K, V>& obj, XMLDocument& doc, XMLElement* element){
            element->SetAttribute("size", static_cast<int>(obj.size()));
            for(const auto& elem : obj) {
                XMLElement* keyElement = doc.NewElement("Key");
                const char* keyTypeName = TypeMapper<K>::type();
                //keyElement->SetAttribute("type", keyTypeName);
                SerializeHelper<K>::serialize(elem.first, doc, keyElement);

                XMLElement* valueElement = doc.NewElement("Value");
                const char* valueTypeName = TypeMapper<V>::type();
                //valueElement->SetAttribute("type", valueTypeName);
                SerializeHelper<V>::serialize(elem.second, doc, valueElement);

                element->InsertEndChild(keyElement);
                element->InsertEndChild(valueElement);
            }
        }
        static void deserialize(std::map<K, V>& obj, const XMLElement* element){
            obj.clear();
            int size;
            element->QueryIntAttribute("size", &size);
            const XMLElement* keyElement = element->FirstChildElement("Key");
            const XMLElement* valueElement = element->FirstChildElement("Value");
            
            for(int i = 0; i < size; i++) {
                K key;
                SerializeHelper<K>::deserialize(key, keyElement);
                keyElement = keyElement->NextSiblingElement("Key");

                V value;
                SerializeHelper<V>::deserialize(value, valueElement);
                valueElement = valueElement->NextSiblingElement("Value");

                obj[key] = value;
            }
        }
    };
    //std::list
    template<typename T>
    struct SerializeHelper<std::list<T>> {
        static void serialize(const std::list<T>& obj, XMLDocument& doc, XMLElement* element){
            element->SetAttribute("size", static_cast<int>(obj.size()));
            for(const auto& elem : obj) {
                //XMLElement* childElement = doc.NewElement("Element");
                const char* typeName = TypeMapper<typename std::remove_cv<typename std::remove_reference<decltype(elem)>::type>::type>::type();
                XMLElement* childElement = doc.NewElement(typeName);
                SerializeHelper<T>::serialize(elem, doc, childElement);
                element->InsertEndChild(childElement);
            }
        }
        static void deserialize(std::list<T>& obj, const XMLElement* element){
            obj.clear();
            int size;
            element->QueryIntAttribute("size", &size);
            const char* typeName = TypeMapper<T>::type();
            const XMLElement* childElement = element->FirstChildElement(typeName);
            //const XMLElement* childElement = element->FirstChildElement("Element");
            for(int i = 0; i < size; i++) {
                T elem;
                SerializeHelper<T>::deserialize(elem, childElement);
                obj.push_back(elem);
                childElement = childElement->NextSiblingElement(typeName);
            }
        }
    };
    //std::pair
    template<typename T1, typename T2>
    struct SerializeHelper<std::pair<T1, T2>> {
        static void serialize(const std::pair<T1, T2>& obj, XMLDocument& doc, XMLElement* element){
            XMLElement* firstElement = doc.NewElement("First");
            SerializeHelper<T1>::serialize(obj.first, doc, firstElement);
            element->InsertEndChild(firstElement);

            XMLElement* secondElement = doc.NewElement("Second");
            SerializeHelper<T2>::serialize(obj.second, doc, secondElement);
            element->InsertEndChild(secondElement);
        }
        static void deserialize(std::pair<T1, T2>& obj, const XMLElement* element){
            const XMLElement* firstElement = element->FirstChildElement("First");
            if (firstElement) {
            SerializeHelper<T1>::deserialize(obj.first, firstElement);
            }

            const XMLElement* secondElement = element->FirstChildElement("Second");
            if (secondElement) {
                SerializeHelper<T2>::deserialize(obj.second, secondElement);
            }
        }
    };

    //通用接口
    template<typename T>
    void xml_serialize(const T& obj, const std::string& xmlFilePath) {
        XMLDocument doc;
        std::string typeName = TypeMapper<T>::type();
        //获取类型名
        XMLElement* element = doc.NewElement(typeName.c_str());
        SerializeHelper<T>::serialize(obj, doc, element);
        doc.InsertEndChild(element);
        doc.SaveFile(xmlFilePath.c_str());
    }
    template<typename T>
    void xml_deserialize(T& obj, const std::string& xmlFilePath) {
        XMLDocument doc;
        XMLError err = doc.LoadFile(xmlFilePath.c_str());
        if (err != XML_SUCCESS) return ;
        //加载文件
        const XMLElement* rootElement = doc.RootElement();
        if (!rootElement) return ;
        //获取 root
        SerializeHelper<T>::deserialize(obj, rootElement);
        //xml反序列化
        return ;
    }
}

#endif
