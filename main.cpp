#include <iostream>
#include "message.h"
#include "morse_converter.h"

int main(){
    std::cout << "===== Testing constructor =====" << std::endl;
    Message msg("Hello, World!");
    msg.print();

    std::cout << "===== Testing fromFile =====" << std::endl;
    Message msg2 = Message::fromFile("text_files/helloworld.txt");
    msg2.print();

    std::cout << "===== Testing save =====" << std::endl;
    Message msg3 = Message("Save Test");
    msg3.save("text_files/SaveTest.txt");

    std::cout << "===== Testing encode and decode =====" << std::endl;
    MorseConverter mc;
    std::string morse = mc.encode("Hello, World!");
    std::cout << "Original text: Hello, World!" << std::endl;
    std::cout << "Encoded: " << morse << std::endl;

    std::string text_decoded = mc.decode(morse);
    std::cout << "Decoded: " << text_decoded << std::endl;
    return 0;
}