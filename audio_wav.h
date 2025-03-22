#pragma once
#include <string>
#include <cstdint>  // For fixed-size types like uint32_t

struct WavHeader {
    char riff[4] = {'R', 'I', 'F', 'F'};   // RIFF header
    uint32_t fileSize;                     // File size - 8 bytes
    char wave[4] = {'W', 'A', 'V', 'E'};   // "WAVE"
    char fmt[4] = {'f', 'm', 't', ' '};    // "fmt "
    uint32_t fmtChunkSize = 16;            // PCM chunk size
    uint16_t audioFormat = 1;              // PCM format (1 = uncompressed)
    uint16_t numChannels = 1;              // Mono (1 channel)
    uint32_t sampleRate = 44100;           // Sample rate (44.1 kHz)
    uint32_t byteRate;                     // sampleRate * numChannels * bitsPerSample / 8
    uint16_t blockAlign;                   // numChannels * bitsPerSample / 8
    uint16_t bitsPerSample = 16;           // 16-bit samples
    char data[4] = {'d', 'a', 't', 'a'};   // "data"
    uint32_t dataSize;                     // Size of audio data

    // Constructor to compute derived values
    WavHeader(uint32_t numSamples) {
        dataSize = numSamples * sizeof(int16_t);  // Total size of audio data
        fileSize = 36 + dataSize;                // Total file size
        byteRate = sampleRate * numChannels * bitsPerSample / 8;
        blockAlign = numChannels * bitsPerSample / 8;
    }
};

class AudioWav {
    private:        
        std::vector<int16_t> readWav(const std::string &filename) const;
        void writeWav(const std::string &filename, const std::vector<int16_t> &samples) const;
        std::vector<int16_t> generateSamplesFromMorse(const std::string& morse, float dotDurationSec = 0.1f, double freq = 750.0) const;
    public:
        //constructor
        AudioWav() = default;

        //Morse related functions
        void encodeToWav(const std::string &morse, const std::string &filename) const;
        std::string decodeFromWav(const std::string &filename) const;
};