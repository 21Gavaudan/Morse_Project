#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include "message.h"
#include "morse_converter.h"
#include "audio_wav.h"
#include "utils.h"

void printUsage() {
    std::cout << "Usage:" << std::endl;
    std::cout << "  ./myprogram --encode <input_text_file> <output_wav_file>" << std::endl;
    std::cout << "  ./myprogram --decode <input_wav_file> <output_text_file>" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printUsage();
        return 1;
    }

    std::string command = argv[1];
    std::string inputFile = argv[2];
    std::string outputFile = argv[3];

    MorseConverter mc;
    AudioWav audio;

    if (command == "--encode") {
        try {
            Message message = Message::fromFile(inputFile);
            std::cout << "Message loaded: " << message.get_text() << std::endl;

            std::string morse = mc.encode(message.get_text());
            std::cout << "Encoded Morse: " << morse << std::endl;

            audio.setSampleRateWriting(44100);
            audio.setAmplitude(16384);
            audio.setDotDurationSec(0.1);
            audio.setFreq(440);
            audio.encodeToWav_sin(morse, outputFile);
            std::cout << "Encoded audio file generated: " << outputFile << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error encoding message: " << e.what() << std::endl;
            return 1;
        }
    } else if (command == "--decode") {
        try {
            // Lire le fichier audio WAV
            std::string decodedMorse = audio.decodeFromWav(inputFile);
            std::cout << "Decoded Morse: " << decodedMorse << std::endl;
            // Décoder le Morse en texte
            std::string decodedText = mc.decode_graph(decodedMorse);
            std::cout << "Decoded text (graph method): " << decodedText << std::endl;
            std::string decodedText_naive = mc.decode(decodedMorse);
            std::cout << "Decoded text (simple method): " << decodedText_naive << std::endl;
            // Écrire le texte dans un fichier
            Message decodedMessage(decodedText);
            decodedMessage.save(outputFile);
            std::cout << "Decoded text file generated using graph method: " << outputFile << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error decoding message: " << e.what() << std::endl;
            return 1;
        }
    } else {
        printUsage();
        return 1;
    }

    return 0;
}