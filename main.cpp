#include <iostream>
#include "message.h"
#include "morse_converter.h"
#include "audio_wav.h"

int main(){
    std::cout << "===== Testing fromFile =====" << std::endl;
    Message msg_helloworld = Message::fromFile("text_files/helloworld.txt");
    msg_helloworld.print();

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
    Message morse_message = Message(morse);
    morse_message.save("text_files/helloworld_morse.txt");
    Message msg_morse_encoded = Message::fromFile("text_files/helloworld_morse.txt");
    msg_morse_encoded.print();
    std::string text_decoded2 = mc.decode(msg_morse_encoded.get_text());
    std::cout << "Decoded: " << text_decoded2 << std::endl;

    std::cout << "===== Testing audio wav =====" << std::endl;
    AudioWav aw;
    aw.encodeToWav(morse, "audio_files/helloworld_morse.wav");
    return 0;
}