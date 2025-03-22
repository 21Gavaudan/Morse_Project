

#include "audio_wav.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <filesystem>

#define PI 3.14159265358979323846

void AudioWav::writeWav(const std::string &filename, const std::vector<int16_t> &samples) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Unable to create WAV file!" << std::endl;
        throw std::runtime_error("Unable to create WAV file: " + filename);
    }

    WavHeader header(samples.size());

    file.write(reinterpret_cast<const char*>(&header), sizeof(header));  // Write header
    if (!file) {
        std::cerr << "Error: Failed to write WAV header!" << std::endl;
        throw std::runtime_error("Failed to write WAV header to file: " + filename);
    }

    file.write(reinterpret_cast<const char*>(samples.data()), samples.size() * sizeof(int16_t));  // Write audio data
    if (!file) {
        std::cerr << "Error: Failed to write WAV data!" << std::endl;
        throw std::runtime_error("Failed to write WAV data to file: " + filename);
    }

    file.close();
    std::cout << "WAV file generated: " << filename << std::endl;
}

std::vector<int16_t> AudioWav::readWav(const std::string &filename) const {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier " << filename << std::endl;
        throw std::runtime_error("Could not open file " + filename);
    }
    
    // Skip the header
    file.seekg(44);
    
    // Read the audio data
    std::vector<int16_t> samples;
    int16_t sample;
    while(file.read(reinterpret_cast<char *>(&sample), sizeof(int16_t))) {
        samples.push_back(sample);
    }
    
    file.close();
    
    return samples;
}

std::vector<int16_t> AudioWav::generateSamplesFromMorse(const std::string& morse, float dotDurationSec, double freq) const {
    std::vector<int16_t> samples;

    int sampleRate = 44100;
    int dotDuration = sampleRate * dotDurationSec;
    int dashDuration = 3 * dotDuration;
    int silenceDuration = dotDuration;
    int wordPause = 7 * dotDuration;

    for (char c : morse){
        int duration = 0;
        if (c == '.'){
            duration = dotDuration;
        }
        else if (c == '-'){
            duration = dashDuration;
        }
        else if (c == ' '){ 
            samples.insert(samples.end(), silenceDuration, 0); 
            continue; 
        }
        else if (c == '/'){ 
            samples.insert(samples.end(), wordPause, 0); 
            continue; 
        }
        
        for (int i = 0; i < duration; i++){
            double time = static_cast<double>(i) / sampleRate;
            int16_t sample = static_cast<int16_t>(30000 * sin(2.0 * PI * freq * time));
            samples.push_back(sample);
        }
        samples.insert(samples.end(), silenceDuration, 0); // pause après chaque son

    }
    return samples;
}

void AudioWav::encodeToWav(const std::string &morse, const std::string &filename) const {
    std::vector<int16_t> samples = generateSamplesFromMorse(morse, 0.1f, 750.0);
    writeWav(filename, samples);
}
