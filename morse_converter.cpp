#include "morse_converter.h"
#include <unordered_map>
#include <string>
#include <cctype>


// Définition de la table statique textToMorse
const std::unordered_map<char, std::string> MorseConverter::textToMorse = {
    {'A', ".-"},    {'B', "-..."},  {'C', "-.-."},  {'D', "-.."},   {'E', "."},
    {'F', "..-."},  {'G', "--."},   {'H', "...."},  {'I', ".."},    {'J', ".---"},
    {'K', "-.-"},   {'L', ".-.."},  {'M', "--"},    {'N', "-."},    {'O', "---"},
    {'P', ".--."},  {'Q', "--.-"},  {'R', ".-."},   {'S', "..."},   {'T', "-"},
    {'U', "..-"},   {'V', "...-"},  {'W', ".--"},   {'X', "-..-"},  {'Y', "-.--"},
    {'Z', "--.."},

    {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"},
    {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."},

    {'.', ".-.-.-"}, {',', "--..--"}, {'?', "..--.."}, {'\'', ".----."}, {'!', "-.-.--"},
    {'/', "-..-."},  {'(', "-.--."},  {')', "-.--.-"}, {'&', ".-..."},  {':', "---..."},
    {';', "-.-.-."}, {'=', "-...-"},  {'+', ".-.-."},  {'-', "-....-"}, {'_', "..--.-"},
    {'\"', ".-..-."},{'$', "...-..-"},{'@', ".--.-."}, {' ', "/"} // Utilisation de '/' pour séparer les mots
};

// Définition de la table statique morseToText
const std::unordered_map<std::string, char> MorseConverter::morseToText = {
    {".-", 'A'},    {"-...", 'B'},  {"-.-.", 'C'},  {"-..", 'D'},   {".", 'E'},
    {"..-.", 'F'},  {"--.", 'G'},   {"....", 'H'},  {"..", 'I'},    {".---", 'J'},
    {"-.-", 'K'},   {".-..", 'L'},  {"--", 'M'},    {"-.", 'N'},    {"---", 'O'},
    {".--.", 'P'},  {"--.-", 'Q'},  {".-.", 'R'},   {"...", 'S'},   {"-", 'T'},
    {"..-", 'U'},   {"...-", 'V'},  {".--", 'W'},   {"-..-", 'X'},  {"-.--", 'Y'},
    {"--..", 'Z'},

    {"-----", '0'}, {".----", '1'}, {"..---", '2'}, {"...--", '3'}, {"....-", '4'},
    {".....", '5'}, {"-....", '6'}, {"--...", '7'}, {"---..", '8'}, {"----.", '9'},

    {".-.-.-", '.'}, {"--..--", ','}, {"..--..", '?'}, {".----.", '\''}, {"-.-.--", '!'},
    {"-..-.", '/'},  {"-.--.", '('},  {"-.--.-", ')'}, {".-...", '&'},  {"---...", ':'},
    {"-.-.-.", ';'}, {"-...-", '='},  {".-.-.", '+'},  {"-....-", '-'}, {"..--.-", '_'},
    {".-..-.", '\"'}, {"...-..-", '$'}, {".--.-.", '@'}, {"/", ' '} // Utilisation de '/' pour séparer les mots
};


// Fonction encode
std::string MorseConverter::encode(const std::string &text) const {
    std::string morse_code;
    bool first_char = true;

    for (char c : text) {
        c = std::toupper(c);

        if (textToMorse.find(c) == textToMorse.end()) {
            throw std::invalid_argument(std::string("Invalid character in text: ") + c);
        }
        if (!first_char) {
            morse_code += " ";
        }
        first_char = false;

        morse_code += textToMorse.at(c);
    }
    return morse_code; // Placeholder return statement
}

// Fonction decode naive
std::string MorseConverter::decode(const std::string &morse) const {
    std::string decoded_text;
    std::string raw_current_letter;
    std::string decoded_current_letter;
    bool first_char  = true;
    
    for (char c : morse){

        if (c == ' '){
            if (!raw_current_letter.empty()){
                if (morseToText.find(raw_current_letter) == morseToText.end()){
                    throw std::invalid_argument(std::string("Invalid symbol in morse: ") + raw_current_letter);
                } else {
                    if (!first_char){
                        decoded_current_letter = std::tolower(morseToText.at(raw_current_letter));
                        decoded_text.append(decoded_current_letter);
                    }
                    else{
                        decoded_current_letter = morseToText.at(raw_current_letter);
                        decoded_text.append(decoded_current_letter);
                        first_char = false;
                    }
                }
                raw_current_letter = "";
            }
        }
        else if (c == '/'){
            decoded_text += " ";
        }
        else{
            raw_current_letter += c;
        }
    }

    //Last letter
    if (!raw_current_letter.empty()){
        if (morseToText.find(raw_current_letter) == morseToText.end()){
            throw std::invalid_argument(std::string("Invalid symbol in morse: ") + raw_current_letter);
        } else {
            decoded_current_letter = std::tolower(morseToText.at(raw_current_letter));
            decoded_text.append(decoded_current_letter);
        }
    }

    return decoded_text;
}

//Fonction decode with graph

// std::string MorseConverter::decode_graph(const std::string &morse) const {
//     std::string decoded_text;
//     return decoded_text;
// }
