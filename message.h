#include <string>
#pragma once

class Message {
    private:
        std::string text;
    public:
        explicit Message(const std::string &text);              //constructor
        static Message fromFile(const std::string &filename);      //create message from a .txt file
        void save(const std::string &filename) const;          //save message to a .txt file
        std::string get_text() const;                //getter
        void set_text(const std::string &text);     //setter
        void print() const;
};