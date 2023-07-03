#ifndef BASE64_H
#define BASE64_H

#include <iostream>
#include <sstream>

namespace base64_lib{

    //对二进制数据进行base64解编码
    static const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    // 将二进制数据编码为 Base64 字符串
    std::string base64_encode(const std::vector<char>& input) {
        std::string output;
        output.reserve(((input.size() + 2) / 3) * 4);

        for (std::size_t i = 0; i < input.size(); i += 3) {
            const std::size_t remaining = input.size() - i;

            const unsigned char a = static_cast<unsigned char>(input[i]);
            const unsigned char b = remaining > 1 ? static_cast<unsigned char>(input[i + 1]) : 0;
            const unsigned char c = remaining > 2 ? static_cast<unsigned char>(input[i + 2]) : 0;

            const unsigned char a1 = a >> 2;
            const unsigned char b1 = ((a & 0x03) << 4) | (b >> 4);
            const unsigned char c1 = ((b & 0x0f) << 2) | (c >> 6);
            const unsigned char d1 = c & 0x3f;

            output.push_back(base64_chars[a1]);
            output.push_back(base64_chars[b1]);
            output.push_back(remaining > 1 ? base64_chars[c1] : '=');
            output.push_back(remaining > 2 ? base64_chars[d1] : '=');
        }

        return output;
    }

    // 将 Base64 字符串解码为二进制数据
    std::vector<char> base64_decode(const std::string& input) {
        std::vector<char> output;
        output.reserve((input.size() / 4) * 3);

        unsigned int buf = 0;
        int buf_bits = 0;

        for (std::size_t i = 0; i < input.size(); ++i) {
            const char c = input[i];
            if (c == '=') {
                break;
            }

            const char* p = std::find(base64_chars, base64_chars + 64, c);
            if (p == base64_chars + 64) {
                throw std::invalid_argument("Invalid character in input string");
            }

            const int index = p - base64_chars;
            buf = (buf << 6) | index;
            buf_bits += 6;

            if (buf_bits >= 8) {
                buf_bits -= 8;
                output.push_back(static_cast<char>((buf >> buf_bits) & 0xff));
            }
        }

        return output;
    }

    // Convert an arithmetic type to binary data
    template <typename T>
    std::vector<char> to_binary(const T& value) {
        std::vector<char> output;
        output.resize(sizeof(T));
        std::memcpy(output.data(), &value, sizeof(T));
        return output;
    }

    // Convert a string to binary data
    std::vector<char> to_binary(const std::string& value) {
        std::vector<char> output;
        output.reserve(value.size() + 1);
        output.assign(value.begin(), value.end());
        output.push_back('\0'); // Add a null terminator
        return output;
    }
    // Convert binary data to an arithmetic type
    template <typename T>
    T from_binary(const std::vector<char>& input) {
        if (input.size() != sizeof(T)) {
            throw std::invalid_argument("Invalid input size");
        }
        T value;
        std::memcpy(&value, input.data(), sizeof(T));
        return value;
    }

    // Convert binary data to a string
    std::string from_binary(const std::vector<char>& input) {
        if (input.empty() || input.back() != '\0') {
            throw std::invalid_argument("Invalid input format");
        }
        return std::string(input.begin(), input.end() - 1);
    }

}

#endif