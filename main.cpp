#include <iostream>
#include "message.h"

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
    return 0;
}