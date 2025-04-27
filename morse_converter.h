#include <string>
#include <unordered_map>


struct MorseNode {
    char value;
    MorseNode* left;
    MorseNode* right;

    MorseNode(char v = '\0') : value(v), left(nullptr), right(nullptr) {}
};

class MorseConverter {
public:
    MorseConverter();
    std::string encode(const std::string &text) const;
    std::string decode(const std::string &morse) const;
    std::string decode_graph(const std::string &morse) const;

private:
    static const std::unordered_map<char, std::string> textToMorse;
    static const std::unordered_map<std::string, char> morseToText;
    std::string normalizeString(const std::string &text) const;
    MorseNode* root;
    void buildGraph();
};