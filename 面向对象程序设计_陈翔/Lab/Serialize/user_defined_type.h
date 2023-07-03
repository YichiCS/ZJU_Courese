#ifndef USER_DEFINED_TYPE_H
#define USER_DEFINED_TYPE_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>
#include <typeinfo>
#include <type_traits>

#include "base64_serialize.h"
#include "xml_serialize.h"
#include "binary_serialize.h"

using namespace base64_lib;
using namespace xml_serialize_lib;
using namespace binary_serialize_lib;

 
namespace user_defined_type{
    struct UserDefinedType {
        int idx;
        std::string name;
        bool married;
        std::vector<double> data;
        std::set<std::string> skills;
        std::map<std::string, int>  family;
        std::pair<double, int> figure;
        std::list<char> lucky_char;

        void binary_serialize(std::ofstream& ofs) const{
            binary_serialize_lib::binary_serialize(idx, ofs);
            binary_serialize_lib::binary_serialize(name, ofs);
            binary_serialize_lib::binary_serialize(married, ofs);
            binary_serialize_lib::binary_serialize(data, ofs);
            binary_serialize_lib::binary_serialize(skills, ofs);
            binary_serialize_lib::binary_serialize(family, ofs);
            binary_serialize_lib::binary_serialize(figure, ofs);
            binary_serialize_lib::binary_serialize(lucky_char, ofs);
        }

        void binary_deserialize(std::ifstream& ifs){
            binary_serialize_lib::binary_deserialize(idx, ifs);
            binary_serialize_lib::binary_deserialize(name, ifs);
            binary_serialize_lib::binary_deserialize(married, ifs);
            binary_serialize_lib::binary_deserialize(data, ifs);
            binary_serialize_lib::binary_deserialize(skills, ifs);
            binary_serialize_lib::binary_deserialize(family, ifs);
            binary_serialize_lib::binary_deserialize(figure, ifs);
            binary_serialize_lib::binary_deserialize(lucky_char, ifs);
        }

        void xml_serialize(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement* element) const {
                
            XMLElement* idx_ele = doc.NewElement("idx");
            xml_serialize_lib::SerializeHelper<decltype(idx)>::serialize(idx, doc, idx_ele);
            element->InsertEndChild(idx_ele);

            XMLElement* name_ele = doc.NewElement("name");
            xml_serialize_lib::SerializeHelper<decltype(name)>::serialize(name, doc, name_ele);
            element->InsertEndChild(name_ele);

            XMLElement* married_ele = doc.NewElement("married");
            xml_serialize_lib::SerializeHelper<decltype(married)>::serialize(married, doc, married_ele);
            element->InsertEndChild(married_ele);

            XMLElement* data_ele = doc.NewElement("data");
            xml_serialize_lib::SerializeHelper<decltype(data)>::serialize(data, doc, data_ele);
            element->InsertEndChild(data_ele);

            XMLElement* skills_ele = doc.NewElement("skills");
            xml_serialize_lib::SerializeHelper<decltype(skills)>::serialize(skills, doc, skills_ele);
            element->InsertEndChild(skills_ele);

            XMLElement* family_ele = doc.NewElement("family");
            xml_serialize_lib::SerializeHelper<decltype(family)>::serialize(family, doc, family_ele);
            element->InsertEndChild(family_ele);

            XMLElement* figure_ele = doc.NewElement("figure");
            xml_serialize_lib::SerializeHelper<decltype(figure)>::serialize(figure, doc, figure_ele);
            element->InsertEndChild(figure_ele);
            
            XMLElement* lucky_char_ele = doc.NewElement("lucky_char");
            xml_serialize_lib::SerializeHelper<decltype(lucky_char)>::serialize(lucky_char, doc, lucky_char_ele);
            element->InsertEndChild(lucky_char_ele);
        }

        void xml_deserialize(const tinyxml2::XMLElement* element){
            using namespace xml_serialize_lib;

            const XMLElement* idx_ele = element->FirstChildElement("idx");
            xml_serialize_lib::SerializeHelper<decltype(idx)>::deserialize(idx, idx_ele);

            const XMLElement* name_ele = element->FirstChildElement("name");
            xml_serialize_lib::SerializeHelper<decltype(name)>::deserialize(name, name_ele);

            const XMLElement* married_ele = element->FirstChildElement("married");
            xml_serialize_lib::SerializeHelper<decltype(married)>::deserialize(married, married_ele);

            const XMLElement* data_ele = element->FirstChildElement("data");
            xml_serialize_lib::SerializeHelper<decltype(data)>::deserialize(data, data_ele);

            const XMLElement* skills_ele = element->FirstChildElement("skills");
            xml_serialize_lib::SerializeHelper<decltype(skills)>::deserialize(skills, skills_ele);

            const XMLElement* family_ele = element->FirstChildElement("family");
            xml_serialize_lib::SerializeHelper<decltype(family)>::deserialize(family, family_ele);

            const XMLElement* figure_ele = element->FirstChildElement("figure");
            xml_serialize_lib::SerializeHelper<decltype(figure)>::deserialize(figure, figure_ele);

            const XMLElement* lucky_char_ele = element->FirstChildElement("lucky_char");
            xml_serialize_lib::SerializeHelper<decltype(lucky_char)>::deserialize(lucky_char, lucky_char_ele);
        }

        void base64_serialize(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement* element) const {
                
            XMLElement* idx_ele = doc.NewElement("idx");
            base64_serialize_lib::SerializeHelper<decltype(idx)>::serialize(idx, doc, idx_ele);
            element->InsertEndChild(idx_ele);

            XMLElement* name_ele = doc.NewElement("name");
            base64_serialize_lib::SerializeHelper<decltype(name)>::serialize(name, doc, name_ele);
            element->InsertEndChild(name_ele);

            XMLElement* married_ele = doc.NewElement("married");
            base64_serialize_lib::SerializeHelper<decltype(married)>::serialize(married, doc, married_ele);
            element->InsertEndChild(married_ele);

            XMLElement* data_ele = doc.NewElement("data");
            base64_serialize_lib::SerializeHelper<decltype(data)>::serialize(data, doc, data_ele);
            element->InsertEndChild(data_ele);

            XMLElement* skills_ele = doc.NewElement("skills");
            base64_serialize_lib::SerializeHelper<decltype(skills)>::serialize(skills, doc, skills_ele);
            element->InsertEndChild(skills_ele);

            XMLElement* family_ele = doc.NewElement("family");
            base64_serialize_lib::SerializeHelper<decltype(family)>::serialize(family, doc, family_ele);
            element->InsertEndChild(family_ele);

            XMLElement* figure_ele = doc.NewElement("figure");
            base64_serialize_lib::SerializeHelper<decltype(figure)>::serialize(figure, doc, figure_ele);
            element->InsertEndChild(figure_ele);
            
            XMLElement* lucky_char_ele = doc.NewElement("lucky_char");
            base64_serialize_lib::SerializeHelper<decltype(lucky_char)>::serialize(lucky_char, doc, lucky_char_ele);
            element->InsertEndChild(lucky_char_ele);
        }

        void base64_deserialize(const tinyxml2::XMLElement* element){
            using namespace xml_serialize_lib;

            const XMLElement* idx_ele = element->FirstChildElement("idx");
            base64_serialize_lib::SerializeHelper<decltype(idx)>::deserialize(idx, idx_ele);

            const XMLElement* name_ele = element->FirstChildElement("name");
            base64_serialize_lib::SerializeHelper<decltype(name)>::deserialize(name, name_ele);

            const XMLElement* married_ele = element->FirstChildElement("married");
            base64_serialize_lib::SerializeHelper<decltype(married)>::deserialize(married, married_ele);

            const XMLElement* data_ele = element->FirstChildElement("data");
            base64_serialize_lib::SerializeHelper<decltype(data)>::deserialize(data, data_ele);

            const XMLElement* skills_ele = element->FirstChildElement("skills");
            base64_serialize_lib::SerializeHelper<decltype(skills)>::deserialize(skills, skills_ele);

            const XMLElement* family_ele = element->FirstChildElement("family");
            base64_serialize_lib::SerializeHelper<decltype(family)>::deserialize(family, family_ele);

            const XMLElement* figure_ele = element->FirstChildElement("figure");
            base64_serialize_lib::SerializeHelper<decltype(figure)>::deserialize(figure, figure_ele);

            const XMLElement* lucky_char_ele = element->FirstChildElement("lucky_char");
            base64_serialize_lib::SerializeHelper<decltype(lucky_char)>::deserialize(lucky_char, lucky_char_ele);
        }

        bool operator<(const UserDefinedType& other) const {
            return idx < other.idx;
        }

        friend std::ostream& operator<<(std::ostream& os, const UserDefinedType& udt) {
            os << std::endl <<"  UserDefinedType {" << std::endl << "    ";
            os << "idx: " << udt.idx ;
            os << ", name: " << udt.name ;
            os << ", married: " << (udt.married ? "Yes" : "No");
            os << ", " << std::endl  << "    "<< "data: [";
            for (size_t i = 0; i < udt.data.size(); ++i) {
            os << udt.data[i];
            if (i < udt.data.size() - 1) {
                os << ", ";
            }
            }
            os << "], " << std::endl  << "    "<< "skills: {";
            auto skills_it = udt.skills.begin();
            for (; skills_it != udt.skills.end(); ++skills_it){
                os << *skills_it;
                if (std::next(skills_it) != udt.skills.end()){
                    os << ", ";
                }
            }
            os << "}, " << std::endl  << "    "<< "family: {";
            auto family_it = udt.family.begin();
            for (; family_it != udt.family.end(); ++family_it){
                os << family_it->first << ": " << family_it->second;
                if (std::next(family_it) != udt.family.end()){
                    os << ", ";
                }
            }
            os << "}, " << std::endl  << "    "<< "figure: (" << udt.figure.first << ", " << udt.figure.second << ")";
            os << ", " << std::endl  << "    "<< "lucky_char: [";
            auto lc_it = udt.lucky_char.begin();
            for (; lc_it != udt.lucky_char.end(); ++lc_it){
                os << *lc_it;
                if (std::next(lc_it) != udt.lucky_char.end()){
                    os << ", ";
                }
            }
            os << "]"<< std::endl << "    }" ;
            return os;
        }
    };

    
}
#endif