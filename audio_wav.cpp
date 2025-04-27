#include "audio_wav.h"
#include <fstream>
#include <iostream>
#include <filesystem>

#define PI 3.14159265358979323846


//Private

void AudioWav::writeWav(const std::string &filename, const std::vector<int16_t> &samples) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Unable to create WAV file!" << std::endl;
        throw std::runtime_error("Unable to create WAV file: " + filename);
    }

    WavHeader header(samples.size(), sampleRateWriting);

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
    
    char header[44];
    file.read(header, 44);
    if (file.gcount() < 44) {  // Check if 44 bytes were actually read
        throw std::runtime_error("Erreur: Fichier trop petit pour être un WAV valide " + filename);
    }
    int sampleRate;
    std::memcpy(&sampleRate, &header[24], sizeof(sampleRate));
    this->sampleRateReading = sampleRate;

    // Read the audio data
    std::vector<int16_t> samples;
    int16_t sample;
    while(file.read(reinterpret_cast<char *>(&sample), sizeof(int16_t))) {
        samples.push_back(sample);
    }
    
    file.close();
        
    return samples;
}

// Public 

//Basics methods

void AudioWav::setAmplitude(int amplitude) {
    this->amplitude = amplitude;
}

void AudioWav::setSampleRateWriting(int sampleRateWriting) {
    this->sampleRateWriting = sampleRateWriting;
}

void AudioWav::setSampleRateReading(int sampleRateReading) {
    this->sampleRateReading = sampleRateReading;
}

void AudioWav::setDotDurationSec(float dotDurationSec) {
    this->dotDurationSec = dotDurationSec;
}

void AudioWav::setFreq(double freq) {
    this->freq = freq;
}

//Morse related methods

std::vector<int16_t> AudioWav::generateSamplesFromMorse_sin(const std::string& morse) const {
    std::vector<int16_t> samples;

    int dotDuration = sampleRateWriting * dotDurationSec;
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
            samples.insert(samples.end(), silenceDuration, 0); // pause après chaque son
            continue; 
        }
        else if (c == '/'){ 
            samples.insert(samples.end(), wordPause, 0); 
            samples.insert(samples.end(), silenceDuration, 0); // pause après chaque son
            continue; 
        }
        
        for (int i = 0; i < duration; i++){
            double time = static_cast<double>(i) / sampleRateWriting;
            int16_t sample = static_cast<int16_t>(amplitude * sin(2.0 * PI * freq * time));
            samples.push_back(sample);
        }
        samples.insert(samples.end(), silenceDuration, 0); // pause après chaque son

    }
    return samples;
}

std::vector<int16_t> AudioWav::generateSamplesFromMorse_pulse(const std::string& morse) const {
    std::vector<int16_t> samples;

    int dotDuration = sampleRateWriting * dotDurationSec;
    int dashDuration = 3 * dotDuration;
    int silenceDuration = dotDuration;
    int wordPause = 7 * dotDuration;

    for (char c : morse){
        if (c == '.'){
            samples.insert(samples.end(), dotDuration, amplitude); 
        }
        else if (c == '-'){
            samples.insert(samples.end(), dashDuration, amplitude); 
        }
        else if (c == ' '){ 
            samples.insert(samples.end(), silenceDuration, 0); 
        }
        else if (c == '/'){ 
            samples.insert(samples.end(), wordPause, 0); 
        }
        
        samples.insert(samples.end(), silenceDuration, 0); // pause après chaque son

    }
    return samples;
}

void AudioWav::encodeToWav_pulse(const std::string &morse, const std::string &filename) const {
    std::vector<int16_t> samples = generateSamplesFromMorse_pulse(morse);
    writeWav(filename, samples);
}

void AudioWav::encodeToWav_sin(const std::string &morse, const std::string &filename) const {
    std::vector<int16_t> samples = generateSamplesFromMorse_sin(morse);
    writeWav(filename, samples);
}

std::string AudioWav::decodeFromWav(const std::string& filename) const {
    std::vector<int16_t> samples = readWav(filename);

    // Calculate important times
    int dotSamples = static_cast<int>(sampleRateReading * dotDurationSec);
    int letterPauseSamples = 3 * dotSamples;
    int wordPauseSamples = 7 * dotSamples;

    int threshold = 1000; // Energy threshold (adapt if necessary)
    int windowSize = dotSamples / 10; // Small window size to detect changes (ex: 10% of a dot)
    
    std::string morse;

    int silenceCounter = 0;
    int signalCounter = 0;
    bool inSignal = false;

    for (size_t i = 0; i < samples.size(); i += windowSize) {
        // Compute energy over a window
        int64_t energy = 0;
        for (int j = 0; j < windowSize && (i + j) < samples.size(); ++j) {
            energy += samples[i + j] * samples[i + j];
        }
        energy /= windowSize;

        if (energy > threshold * threshold) {
            if (!inSignal) {
                // Transition silence -> signal
                if (silenceCounter >= wordPauseSamples / windowSize) {
                    morse += " / ";
                } else if (silenceCounter >= letterPauseSamples / windowSize) {
                    morse += " ";
                }
                silenceCounter = 0;
                inSignal = true;
            }
            signalCounter++;
        } else {
            if (inSignal) {
                // Transition signal -> silence
                if (signalCounter >= (2 * dotSamples) / windowSize) {
                    morse += "-";
                } else {
                    morse += ".";
                }
                signalCounter = 0;
                inSignal = false;
            }
            silenceCounter++;
        }
    }

    // Final signal check
    if (inSignal) {
        if (signalCounter >= (2 * dotSamples) / windowSize) {
            morse += "-";
        } else {
            morse += ".";
        }
    }

    return morse;
}
