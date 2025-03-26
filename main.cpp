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

    //read wav
    std::vector<int16_t> samples = audio.readWav("data/audio_files/long_text_pulse.wav");
    std::cout << audio.sampleRateReading << std::endl;

    //test writing + read differents samplerate
    audio.setSampleRateWriting(22050);
    audio.writeWav("data/audio_files/long_text_pulse_22050.wav", samples);
    std::vector<int16_t> samples2 = audio.readWav("data/audio_files/long_text_pulse_22050.wav");
    std::cout << audio.sampleRateReading << std::endl;
    
    return 0;
}