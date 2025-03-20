#include "message.h"
#include <iostream>
#include <sstream>
#include <fstream>

Message::Message(const std::string &text) : text(text) {}

Message Message::fromFile(const std::string &filename) {

    std::ifstream file(filename);
    std::stringstream buffer;

    if (file.is_open()) {
        buffer << file.rdbuf();
        file.close();
        return Message(buffer.str());
    } else {
        throw std::runtime_error("Error opening file: " + filename);
    }
}

void Message::save(const std::string &filename) const {
    std::ofstream
    file(filename);
    if (file.is_open()) {
        file << text;
        file.close();
    } else {
        throw std::runtime_error("Error opening file: " + filename);
    }
}

std::string Message::get_text() const {
    return text;
}

void Message::set_text(const std::string &text) {
    this->text = text;
}

void Message::print() const {
    std::cout << text << std::endl;
}
