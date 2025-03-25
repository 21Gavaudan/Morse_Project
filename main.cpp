#include <iostream>
#include "message.h"
#include "morse_converter.h"
#include "audio_wav.h"

int main(){
    std::cout << "===== Testing MorseConverter =====" << std::endl;
    MorseConverter mc;
    Message msg = Message::fromFile("text_files/helloworld.txt");
    msg.print();
    std::string morse = mc.encode(msg.get_text());
    Message morse_msg(morse);
    morse_msg.save("text_files/hello_morse.txt");
    morse_msg.print();
    std::cout << "===== Testing reading and saving morse messages =====" << std::endl;

    AudioWav audio;

    audio.encodeToWav_pulse(morse, "audio_files/hello_pulse.wav");
    audio.encodeToWav_sin(morse, "audio_files/hello_sin.wav");


    std::string decoded = audio.decodeFromWav("audio_files/hello_pulse.wav");
    std::cout << "Decoded Morse: " << decoded << std::endl;

    MorseConverter converter;
    std::string text = converter.decode(decoded);
    std::cout << "Decoded text: " << text << std::endl;

//     std::vector samples = audio.generateSamplesFromMorse_pulse(morse2, 0.1f, 440.0);
//     bool zeros = false;
//     int last_i = 0;
//     for (int i = 0; i < samples.size(); i++){
//         if (samples[i] == 0){
//             if (!zeros){
//                 std::cout << i << " -- 0 -- " << i - last_i << std::endl;
//                 if (i - last_i == 1){
//                     std::cout << samples[i] << std::endl;
//                 }
//                 zeros = true;
//                 last_i = i;
//             }
//     }
//         else{
//             if (zeros){
//                     std::cout << i << " -- 1 -- " << i - last_i << std::endl;
//                     if (i - last_i == 1){
//                         std::cout << samples[i] << std::endl;
//                     }
//                     zeros = false;
//                     last_i = i;
//             }
//     }
// }
//     std::string values_samples = "";
//     for (int i = 0; i < samples.size(); i++){
//         values_samples += std::to_string(samples[i]) + " ";
//     }
//     Message samples_msg(values_samples);
//     samples_msg.save("text_files/samples.txt");
    return 0;
}