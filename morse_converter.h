#include <unordered_map>
#include <string>
#pragma once

class MorseConverter {
    private:
            static const std::unordered_map<char, std::string> textToMorse;
            static const std::unordered_map<std::string, char> morseToText; //key is morse, value is char
    public:
        MorseConverter() = default;
        std::string encode(const std::string &text) const;
        std::string decode(const std::string &morse) const;
};