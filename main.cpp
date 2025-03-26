#include <iostream>
#include "message.h"
#include "morse_converter.h"
#include "audio_wav.h"
#include "utils.h"


#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>


int main(){

    MorseConverter mc;
    AudioWav audio;

    Message message = Message::fromFile("data/text_files/long_text.txt");
    std::string morse = mc.encode(message.get_text());

    audio.encodeToWav_pulse(morse, "data/audio_files/long_text_pulse.wav");
    audio.encodeToWav_sin(morse, "data/audio_files/long_text_sin.wav");

    std::string encoded_morse_from_audio = audio.decodeFromWav("data/audio_files/long_text_pulse.wav");
    std::cout << "Decoded morse from audio: " << encoded_morse_from_audio << std::endl;

    Message decoded_text = Message(mc.decode(encoded_morse_from_audio));
    decoded_text.print();

    //Gather data
    std::vector<int16_t> samples = audio.generateSamplesFromMorse_pulse(morse);
    saveSamplesToBinary("data/samples/long_text_pulse.bin", samples);

    return 0;
}