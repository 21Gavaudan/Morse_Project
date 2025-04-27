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

std::string MorseConverter::normalizeString(const std::string& input) const {
    std::string result;

    for (size_t i = 0; i < input.length(); ++i) {
        unsigned char c = input[i];

        if (c == 0xC3) { // Start of an accented character
            if (i + 1 < input.length()) {
                unsigned char next = input[i + 1];
                i++; // move to next byte

                switch (next) {
                    case 0xA0: case 0xA2: case 0xA4: result += 'a'; break; // à â ä
                    case 0xA7: result += 'c'; break; // ç
                    case 0xA8: case 0xA9: case 0xAA: case 0xAB: result += 'e'; break; // è é ê ë
                    case 0xAE: case 0xAF: result += 'i'; break; // î ï
                    case 0xB4: case 0xB6: result += 'o'; break; // ô ö
                    case 0xB9: case 0xBB: case 0xBC: result += 'u'; break; // ù û ü
                    case 0xBF: result += 'y'; break; // ÿ
                    default: result += '?'; break; // Unknown character
                }
            }
        } else {
            result += c; // Regular ASCII char
        }
    }

    return result;
}


// Fonction encode
std::string MorseConverter::encode(const std::string& text) const {
    std::string normalizedText = normalizeString(text);
    std::string morse_code;
    bool first_char = true;

    for (char c : normalizedText) {
        c = std::toupper(c);  // Uppercase after normalization

        if (textToMorse.find(c) == textToMorse.end()) {
            throw std::invalid_argument(std::string("Invalid character in text: ") + c);
        }
        if (!first_char) {
            morse_code += " ";
        }
        first_char = false;

        morse_code += textToMorse.at(c);
    }
    return morse_code;
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

MorseConverter::MorseConverter() {
    root = new MorseNode();
    buildGraph();
}

void MorseConverter::buildGraph() {
    for (const auto& pair : morseToText) {
        const std::string& code = pair.first;
        char letter = pair.second;

        MorseNode* current = root;
        for (char symbol : code) {
            if (symbol == '.') {
                if (!current->left) current->left = new MorseNode();
                current = current->left;
            } else if (symbol == '-') {
                if (!current->right) current->right = new MorseNode();
                current = current->right;
            }
        }
        current->value = letter;
    }
}

std::string MorseConverter::decode_graph(const std::string& morse) const {
    std::string decoded_text;
    MorseNode* current = root;
    bool buildingLetter = false; // NEW: track if we are inside a letter

    for (char c : morse) {
        if (c == '.') {
            if (current->left) {
                current = current->left;
                buildingLetter = true;
            } else {
                throw std::invalid_argument("Invalid Morse code: unexpected dot");
            }
        } else if (c == '-') {
            if (current->right) {
                current = current->right;
                buildingLetter = true;
            } else {
                throw std::invalid_argument("Invalid Morse code: unexpected dash");
            }
        } else if (c == ' ') {
            if (buildingLetter && current && current->value) {
                decoded_text += std::tolower(current->value);
                current = root;   // reset only after finishing a letter
                buildingLetter = false;
            }
            // else: ignore multiple spaces
        } else if (c == '/') {
            if (buildingLetter && current && current->value) {
                decoded_text += std::tolower(current->value);
                buildingLetter = false;
            }
            decoded_text += ' '; // Word separator
            current = root;
        } else {
            throw std::invalid_argument(std::string("Invalid character in Morse string: ") + c);
        }
    }

    // Handle the last letter if needed
    if (buildingLetter && current && current->value) {
        decoded_text += std::tolower(current->value);
    }

    return decoded_text;
}
