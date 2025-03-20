#include <iostream>
#include "message.h"
#include "morse_converter.h"
#include "audio_wav.h"

int main(){
    std::cout << "===== Testing fromFile =====" << std::endl;
    Message msg2 = Message::fromFile("text_files/helloworld.txt");
    msg2.print();

    std::cout << "===== Testing save =====" << std::endl;
    Message msg3 = Message("Save Test");
    msg3.save("text_files/SaveTest.txt");

    std::cout << "===== Testing encode and decode =====" << std::endl;
    MorseConverter mc;
    Message msg = Message::fromFile("text_files/helloworld.txt");
    std::string morse = mc.encode(Message::fromFile("text_files/helloworld.txt").get_text());
    std::cout << "Original text: " << msg.get_text() << std::endl;
    std::cout << "Encoded: " << morse << std::endl;

    std::string text_decoded = mc.decode(morse);
    std::cout << "Decoded: " << text_decoded << std::endl;

    std::cout << "===== Testing reading and saving morse messages =====" << std::endl;
    Message msg4 = Message::fromFile("text_files/helloworld.txt");
    msg4.print();
    std::string morse2 = mc.encode(msg4.get_text());
    Message morse_message = Message(morse2);
    morse_message.save("text_files/helloworld_morse.txt");
    Message msg5 = Message::fromFile("text_files/helloworld_morse.txt");
    msg5.print();
    std::string text_decoded2 = mc.decode(morse2);
    std::cout << "Decoded: " << text_decoded2 << std::endl;

    std::cout << "===== Testing audio wav =====" << std::endl;
    AudioWav aw;
    aw.generateEmptyWav("audio_files/empty.wav");

    return 0;
}