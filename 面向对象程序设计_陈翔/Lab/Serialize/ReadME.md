# Serialize
Hello, here is my Serialize homework. Something you may interested in is written below.
## Files
There fourteen files in total, they are:  

binary_serialize.h
binary_test.h
xml_serialize.h
xml_test.h
base64_serialize.h
base64_test.h

print.h
base64.h
tinyxml2.h
tinyxml2.cpp
user_defined_type.h

test.cpp
CMakeLsits.txt
ReadME.md


## Major Contribution
1. Implement a module to support **binary serialization/deserialization**

2. Implement a wrapper module of tinyxml2 to support **XML serialization**
   
3. Implement a wrapper module of tinyxml2 to support **XML deserialization**

4. Use binary-to-text encoding/decoding (base64) to implement **a binary mode of XML serialization**

5. All modules support the serialization of **arithmetic types**, **C++ string type** (std::string), and **STL containers** (std::pair, std::vector, std::list, std::set, and std::map)

## Test & Results
In this assignment, I designed and provided sufficient test cases, including the following tests:

1. serialization/deserialization of **arithmetic types**
2. serialization/deserialization of **C++ string type**
3. serialization/deserialization of **STL containers** (std::pair, std::vector, std::list, std::set, and std::map), which contain **arithmetic types** or **C++ string type**
4. serialization/deserialization of **UserDefinedType**. 
5. serialization/deserialization of **STL containers** (std::pair, std::vector, std::list, std::set, and std::map), which contains the **UserDefinedType**.

In this test, at the beginning each test, you will be prompted to **enter 1 or 2**. For each type of test, I provide two objects that are serialized into different files. Based on your input, the third object will be deserialized from one of the files. The sample output of this test assumes that you entered 2 for demonstration purposes.

**Attention**: If you want to add a custom user-defined type, the below content pertains to the user-defined type are what you need to pay attention to.

Regarding the UserDefinedType in this test, it is provided in *user_defined_type.h*. 
```
struct UserDefinedType {
        int idx;
        std::string name;
        bool married;
        std::vector<double> data;
        std::set<std::string> skills;
        std::map<std::string, int>  family;
        std::pair<double, int> figure;
        std::list<char> lucky_char;
}
```
This UserDefinedType contains properties of the following types: 
   * arithmetic types
   * C++ string type
   * STL containers (std::pair, std::vector, std::list, std::set, and std::map) that contain arithmetic types and C++ string types.
  
In addition to the data types mentioned above, it also needs to support ```<``` for use in STL containers such as set, and ```<<``` for output. In addition, this type should also support the following functions for serialization and deserialization:
* binary_serialize & binary_deserialize
* xml_serialize & xml_deserialize
* base64_serialize & base64_deserialize

Please refer to the file for the specific function interfaces and their internal implementations. 

In addition to providing input-output examples, we also provide an example of a ```std::map<UserDefinedType>``` in a specific serialized file format to help you better understand the implementation of serialization. If you want to learn more, you can comment out irrelevant code segments in the corresponding test function for viewing.

### Binary
The test output are something like below.
```
Input 1 or 2
>> 2
 Int1 = 42
 Int2 = 21
 Int3 = 21

 Double1 = 3.14159
 Double2 = 2.71828
 Double3 = 2.71828

 UserDefinedType1 = O
 UserDefinedType2 = P
 UserDefinedType3 = P

 UserDefinedType1 = 1
 UserDefinedType2 = 0
 UserDefinedType3 = 0

 String1 = Hello, world!
 String2 = The world!
 String3 = The world!

 Vec1 = {1 3 5 7 9 }
 Vec2 = {2 4 8 16 32 }
 Vec3 = {2 4 8 16 32 }

 List1 = {a b c d e }
 List2 = {A B C D E }
 List3 = {A B C D E }

 Map1 = {{CVPR, 2023} {ECCV, 2021} {ICLR, 2022} }
 Map2 = {{Apple, 1} {Banana, 3} {Pear, 2} }
 Map3 = {{Apple, 1} {Banana, 3} {Pear, 2} }

 Pair1 = {Transformer, 2014}
 Pair2 = {Network, 1999}
 Pair3 = {Network, 1999}

 Set1 = {1.1 2.2 3.3 4.4 5.5 }
 Set2 = {0.9 1.9 2.9 3.9 4.9 }
 Set3 = {0.9 1.9 2.9 3.9 4.9 }

 UserDefinedType1 = 
  UserDefinedType {
    idx: 12, name: Maxwell, married: No, 
    data: [1.2, 2.3, 3.4], 
    skills: {Counter Strike, Genshin}, 
    family: {father: 56, mother: 48}, 
    figure: (1.78, 56), 
    lucky_char: [a, D]
    }
 UserDefinedType2 = 
  UserDefinedType {
    idx: 38, name: Newtown, married: Yes, 
    data: [1.3, 2.4], 
    skills: {Call of Duty, Dota, Minecraft}, 
    family: {father: 52, mother: 47, son: 16, wife: 23}, 
    figure: (1.65, 50), 
    lucky_char: [x, M, L]
    }
 UserDefinedType3 = 
  UserDefinedType {
    idx: 38, name: Newtown, married: Yes, 
    data: [1.3, 2.4], 
    skills: {Call of Duty, Dota, Minecraft}, 
    family: {father: 52, mother: 47, son: 16, wife: 23}, 
    figure: (1.65, 50), 
    lucky_char: [x, M, L]
    }

 Vec1 = {
  UserDefinedType {
    idx: 12, name: Maxwell, married: No, 
    data: [1.2, 2.3, 3.4], 
    skills: {Counter Strike, Genshin}, 
    family: {father: 56, mother: 48}, 
    figure: (1.78, 56), 
    lucky_char: [a, D]
    } 
  UserDefinedType {
    idx: 38, name: Newtown, married: Yes, 
    data: [1.3, 2.4], 
    skills: {Call of Duty, Dota, Minecraft}, 
    family: {father: 52, mother: 47, son: 16, wife: 23}, 
    figure: (1.65, 50), 
    lucky_char: [x, M, L]
    } }
 Vec2 = {
  UserDefinedType {
    idx: 21, name: Sharks, married: Yes, 
    data: [12, 23, 34, 45, 56], 
    skills: {League of Legends, Overwatch}, 
    family: {father: 61, wife: 24}, 
    figure: (1.8, 78), 
    lucky_char: [c, O, l, I]
    } 
  UserDefinedType {
    idx: 76, name: Lions, married: No, 
    data: [13, 24, 35], 
    skills: {Among Us, Apex Legends, The Sims, Valorant}, 
    family: {father: 67}, 
    figure: (1.73, 63), 
    lucky_char: [p]
    } }
 Vec3 = {
  UserDefinedType {
    idx: 21, name: Sharks, married: Yes, 
    data: [12, 23, 34, 45, 56], 
    skills: {League of Legends, Overwatch}, 
    family: {father: 61, wife: 24}, 
    figure: (1.8, 78), 
    lucky_char: [c, O, l, I]
    } 
  UserDefinedType {
    idx: 76, name: Lions, married: No, 
    data: [13, 24, 35], 
    skills: {Among Us, Apex Legends, The Sims, Valorant}, 
    family: {father: 67}, 
    figure: (1.73, 63), 
    lucky_char: [p]
    } }

 Set1 = {
  UserDefinedType {
    idx: 12, name: Maxwell, married: No, 
    data: [1.2, 2.3, 3.4], 
    skills: {Counter Strike, Genshin}, 
    family: {father: 56, mother: 48}, 
    figure: (1.78, 56), 
    lucky_char: [a, D]
    } 
  UserDefinedType {
    idx: 38, name: Newtown, married: Yes, 
    data: [1.3, 2.4], 
    skills: {Call of Duty, Dota, Minecraft}, 
    family: {father: 52, mother: 47, son: 16, wife: 23}, 
    figure: (1.65, 50), 
    lucky_char: [x, M, L]
    } }
 Set2 = {
  UserDefinedType {
    idx: 21, name: Sharks, married: Yes, 
    data: [12, 23, 34, 45, 56], 
    skills: {League of Legends, Overwatch}, 
    family: {father: 61, wife: 24}, 
    figure: (1.8, 78), 
    lucky_char: [c, O, l, I]
    } 
  UserDefinedType {
    idx: 76, name: Lions, married: No, 
    data: [13, 24, 35], 
    skills: {Among Us, Apex Legends, The Sims, Valorant}, 
    family: {father: 67}, 
    figure: (1.73, 63), 
    lucky_char: [p]
    } }
 Set3 = {
  UserDefinedType {
    idx: 21, name: Sharks, married: Yes, 
    data: [12, 23, 34, 45, 56], 
    skills: {League of Legends, Overwatch}, 
    family: {father: 61, wife: 24}, 
    figure: (1.8, 78), 
    lucky_char: [c, O, l, I]
    } 
  UserDefinedType {
    idx: 76, name: Lions, married: No, 
    data: [13, 24, 35], 
    skills: {Among Us, Apex Legends, The Sims, Valorant}, 
    family: {father: 67}, 
    figure: (1.73, 63), 
    lucky_char: [p]
    } }

 Pair1 = {
  UserDefinedType {
    idx: 38, name: Newtown, married: Yes, 
    data: [1.3, 2.4], 
    skills: {Call of Duty, Dota, Minecraft}, 
    family: {father: 52, mother: 47, son: 16, wife: 23}, 
    figure: (1.65, 50), 
    lucky_char: [x, M, L]
    }, 2}
 Pair2 = {
  UserDefinedType {
    idx: 21, name: Sharks, married: Yes, 
    data: [12, 23, 34, 45, 56], 
    skills: {League of Legends, Overwatch}, 
    family: {father: 61, wife: 24}, 
    figure: (1.8, 78), 
    lucky_char: [c, O, l, I]
    }, 4}
 Pair3 = {
  UserDefinedType {
    idx: 21, name: Sharks, married: Yes, 
    data: [12, 23, 34, 45, 56], 
    skills: {League of Legends, Overwatch}, 
    family: {father: 61, wife: 24}, 
    figure: (1.8, 78), 
    lucky_char: [c, O, l, I]
    }, 4}

 List1 = {
  UserDefinedType {
    idx: 12, name: Maxwell, married: No, 
    data: [1.2, 2.3, 3.4], 
    skills: {Counter Strike, Genshin}, 
    family: {father: 56, mother: 48}, 
    figure: (1.78, 56), 
    lucky_char: [a, D]
    } 
  UserDefinedType {
    idx: 38, name: Newtown, married: Yes, 
    data: [1.3, 2.4], 
    skills: {Call of Duty, Dota, Minecraft}, 
    family: {father: 52, mother: 47, son: 16, wife: 23}, 
    figure: (1.65, 50), 
    lucky_char: [x, M, L]
    } }
 List2 = {
  UserDefinedType {
    idx: 21, name: Sharks, married: Yes, 
    data: [12, 23, 34, 45, 56], 
    skills: {League of Legends, Overwatch}, 
    family: {father: 61, wife: 24}, 
    figure: (1.8, 78), 
    lucky_char: [c, O, l, I]
    } 
  UserDefinedType {
    idx: 76, name: Lions, married: No, 
    data: [13, 24, 35], 
    skills: {Among Us, Apex Legends, The Sims, Valorant}, 
    family: {father: 67}, 
    figure: (1.73, 63), 
    lucky_char: [p]
    } }
 List3 = {
  UserDefinedType {
    idx: 21, name: Sharks, married: Yes, 
    data: [12, 23, 34, 45, 56], 
    skills: {League of Legends, Overwatch}, 
    family: {father: 61, wife: 24}, 
    figure: (1.8, 78), 
    lucky_char: [c, O, l, I]
    } 
  UserDefinedType {
    idx: 76, name: Lions, married: No, 
    data: [13, 24, 35], 
    skills: {Among Us, Apex Legends, The Sims, Valorant}, 
    family: {father: 67}, 
    figure: (1.73, 63), 
    lucky_char: [p]
    } }

 Map1 = {{
  UserDefinedType {
    idx: 12, name: Maxwell, married: No, 
    data: [1.2, 2.3, 3.4], 
    skills: {Counter Strike, Genshin}, 
    family: {father: 56, mother: 48}, 
    figure: (1.78, 56), 
    lucky_char: [a, D]
    }, 1} {
  UserDefinedType {
    idx: 38, name: Newtown, married: Yes, 
    data: [1.3, 2.4], 
    skills: {Call of Duty, Dota, Minecraft}, 
    family: {father: 52, mother: 47, son: 16, wife: 23}, 
    figure: (1.65, 50), 
    lucky_char: [x, M, L]
    }, 2} }
 Map2 = {{
  UserDefinedType {
    idx: 21, name: Sharks, married: Yes, 
    data: [12, 23, 34, 45, 56], 
    skills: {League of Legends, Overwatch}, 
    family: {father: 61, wife: 24}, 
    figure: (1.8, 78), 
    lucky_char: [c, O, l, I]
    }, 4} {
  UserDefinedType {
    idx: 76, name: Lions, married: No, 
    data: [13, 24, 35], 
    skills: {Among Us, Apex Legends, The Sims, Valorant}, 
    family: {father: 67}, 
    figure: (1.73, 63), 
    lucky_char: [p]
    }, 5} }
 Map3 = {{
  UserDefinedType {
    idx: 21, name: Sharks, married: Yes, 
    data: [12, 23, 34, 45, 56], 
    skills: {League of Legends, Overwatch}, 
    family: {father: 61, wife: 24}, 
    figure: (1.8, 78), 
    lucky_char: [c, O, l, I]
    }, 4} {
  UserDefinedType {
    idx: 76, name: Lions, married: No, 
    data: [13, 24, 35], 
    skills: {Among Us, Apex Legends, The Sims, Valorant}, 
    family: {father: 67}, 
    figure: (1.73, 63), 
    lucky_char: [p]
    }, 5} }

Test successfully!
```
At this point, the serialized content is saved in the following two files ```binary_test1.dat``` and ```binary_test2.dat```.

### XML
The test output are the same as one in the binary test, what's different is the file ```xml_test1.xml``` and ```xml_test2.xml```.
```xml_test1.xml```:  
```
<std_map size="2">
    <Key>
        <idx>12</idx>
        <name>Maxwell</name>
        <married>false</married>
        <data size="3">
            <double>1.2</double>
            <double>2.2999999999999998</double>
            <double>3.3999999999999999</double>
        </data>
        <skills size="2">
            <string>Counter Strike</string>
            <string>Genshin</string>
        </skills>
        <family size="2">
            <Key>father</Key>
            <Value>56</Value>
            <Key>mother</Key>
            <Value>48</Value>
        </family>
        <figure>
            <First>1.78</First>
            <Second>56</Second>
        </figure>
        <lucky_char size="2">
            <char>97</char>
            <char>68</char>
        </lucky_char>
    </Key>
    <Value>1</Value>
    <Key>
        <idx>38</idx>
        <name>Newtown</name>
        <married>true</married>
        <data size="2">
            <double>1.3</double>
            <double>2.3999999999999999</double>
        </data>
        <skills size="3">
            <string>Call of Duty</string>
            <string>Dota</string>
            <string>Minecraft</string>
        </skills>
        <family size="4">
            <Key>father</Key>
            <Value>52</Value>
            <Key>mother</Key>
            <Value>47</Value>
            <Key>son</Key>
            <Value>16</Value>
            <Key>wife</Key>
            <Value>23</Value>
        </family>
        <figure>
            <First>1.6499999999999999</First>
            <Second>50</Second>
        </figure>
        <lucky_char size="3">
            <char>120</char>
            <char>77</char>
            <char>76</char>
        </lucky_char>
    </Key>
    <Value>2</Value>
</std_map>

```

```xml_test2.xml```
```
<std_map size="2">
    <Key>
        <idx>21</idx>
        <name>Sharks</name>
        <married>true</married>
        <data size="5">
            <double>12</double>
            <double>23</double>
            <double>34</double>
            <double>45</double>
            <double>56</double>
        </data>
        <skills size="2">
            <string>League of Legends</string>
            <string>Overwatch</string>
        </skills>
        <family size="2">
            <Key>father</Key>
            <Value>61</Value>
            <Key>wife</Key>
            <Value>24</Value>
        </family>
        <figure>
            <First>1.8</First>
            <Second>78</Second>
        </figure>
        <lucky_char size="4">
            <char>99</char>
            <char>79</char>
            <char>108</char>
            <char>73</char>
        </lucky_char>
    </Key>
    <Value>4</Value>
    <Key>
        <idx>76</idx>
        <name>Lions</name>
        <married>false</married>
        <data size="3">
            <double>13</double>
            <double>24</double>
            <double>35</double>
        </data>
        <skills size="4">
            <string>Among Us</string>
            <string>Apex Legends</string>
            <string>The Sims</string>
            <string>Valorant</string>
        </skills>
        <family size="1">
            <Key>father</Key>
            <Value>67</Value>
        </family>
        <figure>
            <First>1.73</First>
            <Second>63</Second>
        </figure>
        <lucky_char size="1">
            <char>112</char>
        </lucky_char>
    </Key>
    <Value>5</Value>
</std_map>

```

### Base64
The test output are the same as one in the binary test, what's different is the file ```base64_test1.xml``` and ```base64_test2.xml```.
```base64_test1.xml```:
```
<std_map size="AgAAAAAAAAA=">
    <Key>
        <idx>DAAAAA==</idx>
        <name>TWF4d2VsbAA=</name>
        <married>ZmFsc2UA</married>
        <data size="AwAAAAAAAAA=">
            <binary_double>MzMzMzMz8z8=</binary_double>
            <binary_double>ZmZmZmZmAkA=</binary_double>
            <binary_double>MzMzMzMzC0A=</binary_double>
        </data>
        <skills size="AgAAAAAAAAA=">
            <binary_string>Q291bnRlciBTdHJpa2UA</binary_string>
            <binary_string>R2Vuc2hpbgA=</binary_string>
        </skills>
        <family size="AgAAAAAAAAA=">
            <Key>ZmF0aGVyAA==</Key>
            <Value>OAAAAA==</Value>
            <Key>bW90aGVyAA==</Key>
            <Value>MAAAAA==</Value>
        </family>
        <figure>
            <First>exSuR+F6/D8=</First>
            <Second>OAAAAA==</Second>
        </figure>
        <lucky_char size="AgAAAAAAAAA=">
            <binary_char>YQ==</binary_char>
            <binary_char>RA==</binary_char>
        </lucky_char>
    </Key>
    <Value>AQAAAA==</Value>
    <Key>
        <idx>JgAAAA==</idx>
        <name>TmV3dG93bgA=</name>
        <married>dHJ1ZQA=</married>
        <data size="AgAAAAAAAAA=">
            <binary_double>zczMzMzM9D8=</binary_double>
            <binary_double>MzMzMzMzA0A=</binary_double>
        </data>
        <skills size="AwAAAAAAAAA=">
            <binary_string>Q2FsbCBvZiBEdXR5AA==</binary_string>
            <binary_string>RG90YQA=</binary_string>
            <binary_string>TWluZWNyYWZ0AA==</binary_string>
        </skills>
        <family size="BAAAAAAAAAA=">
            <Key>ZmF0aGVyAA==</Key>
            <Value>NAAAAA==</Value>
            <Key>bW90aGVyAA==</Key>
            <Value>LwAAAA==</Value>
            <Key>c29uAA==</Key>
            <Value>EAAAAA==</Value>
            <Key>d2lmZQA=</Key>
            <Value>FwAAAA==</Value>
        </family>
        <figure>
            <First>ZmZmZmZm+j8=</First>
            <Second>MgAAAA==</Second>
        </figure>
        <lucky_char size="AwAAAAAAAAA=">
            <binary_char>eA==</binary_char>
            <binary_char>TQ==</binary_char>
            <binary_char>TA==</binary_char>
        </lucky_char>
    </Key>
    <Value>AgAAAA==</Value>
</std_map>

```
```base64_test2.xml```
```
<std_map size="AgAAAAAAAAA=">
    <Key>
        <idx>FQAAAA==</idx>
        <name>U2hhcmtzAA==</name>
        <married>dHJ1ZQA=</married>
        <data size="BQAAAAAAAAA=">
            <binary_double>AAAAAAAAKEA=</binary_double>
            <binary_double>AAAAAAAAN0A=</binary_double>
            <binary_double>AAAAAAAAQUA=</binary_double>
            <binary_double>AAAAAACARkA=</binary_double>
            <binary_double>AAAAAAAATEA=</binary_double>
        </data>
        <skills size="AgAAAAAAAAA=">
            <binary_string>TGVhZ3VlIG9mIExlZ2VuZHMA</binary_string>
            <binary_string>T3ZlcndhdGNoAA==</binary_string>
        </skills>
        <family size="AgAAAAAAAAA=">
            <Key>ZmF0aGVyAA==</Key>
            <Value>PQAAAA==</Value>
            <Key>d2lmZQA=</Key>
            <Value>GAAAAA==</Value>
        </family>
        <figure>
            <First>zczMzMzM/D8=</First>
            <Second>TgAAAA==</Second>
        </figure>
        <lucky_char size="BAAAAAAAAAA=">
            <binary_char>Yw==</binary_char>
            <binary_char>Tw==</binary_char>
            <binary_char>bA==</binary_char>
            <binary_char>SQ==</binary_char>
        </lucky_char>
    </Key>
    <Value>BAAAAA==</Value>
    <Key>
        <idx>TAAAAA==</idx>
        <name>TGlvbnMA</name>
        <married>ZmFsc2UA</married>
        <data size="AwAAAAAAAAA=">
            <binary_double>AAAAAAAAKkA=</binary_double>
            <binary_double>AAAAAAAAOEA=</binary_double>
            <binary_double>AAAAAACAQUA=</binary_double>
        </data>
        <skills size="BAAAAAAAAAA=">
            <binary_string>QW1vbmcgVXMA</binary_string>
            <binary_string>QXBleCBMZWdlbmRzAA==</binary_string>
            <binary_string>VGhlIFNpbXMA</binary_string>
            <binary_string>VmFsb3JhbnQA</binary_string>
        </skills>
        <family size="AQAAAAAAAAA=">
            <Key>ZmF0aGVyAA==</Key>
            <Value>QwAAAA==</Value>
        </family>
        <figure>
            <First>rkfhehSu+z8=</First>
            <Second>PwAAAA==</Second>
        </figure>
        <lucky_char size="AQAAAAAAAAA=">
            <binary_char>cA==</binary_char>
        </lucky_char>
    </Key>
    <Value>BQAAAA==</Value>
</std_map>

```
### Highlights
 1. Implemented additional XML deserialization and serialization-deserialization based on Base64. 
 2. Provides good support for general user-defined data types, as long as they meet the conditions mentioned earlier. 
 3. Sufficient test cases to cover all possible scenarios. 
 4. Modularized and functionized repetitive code segments to greatly reduce the actual amount of code and facilitate maintenance.

### Areas for improvement include
 1. Due to time constraints, serialization and deserialization of smart pointers were not implemented. 
 2. More STL containers could have been implemented, but the serialization and deserialization of STL containers are generally similar. 
 3. There are still many similar portions of code that could be consolidated to reduce code volume.

## Something else
* If there are some bugs I haven't found, please email me at yichics02@gmail.com, your mail do give me a encourage to better work.  
* Wish you a nice day!