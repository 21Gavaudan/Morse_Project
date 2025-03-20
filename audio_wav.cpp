

#include "audio_wav.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <filesystem>

void AudioWav::generateEmptyWav(const std::string &filename) const {
    // Créer le dossier audio_files s'il n'existe pas
    std::filesystem::create_directories("audio_files");
    
    std::cout << "Tentative de création du fichier WAV: " << filename << std::endl;
    
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier " << filename << std::endl;
        throw std::runtime_error("Could not open file " + filename);
    }
    
    // Write the header
    file.write("RIFF", 4);
    uint32_t fileSize = 36;
    file.write(reinterpret_cast<const char *>(&fileSize), 4);
    file.write("WAVE", 4);
    file.write("fmt ", 4);
    uint32_t fmtSize = 16;
    file.write(reinterpret_cast<const char *>(&fmtSize), 4);
    uint16_t audioFormat = 1;
    file.write(reinterpret_cast<const char *>(&audioFormat), 2);
    uint16_t numChannels = 1;
    file.write(reinterpret_cast<const char *>(&numChannels), 2);
    uint32_t sampleRate = 44100;
    file.write(reinterpret_cast<const char *>(&sampleRate), 4);
    uint32_t byteRate = 44100 * 2;
    file.write(reinterpret_cast<const char *>(&byteRate), 4);
    uint16_t blockAlign = 2;
    file.write(reinterpret_cast<const char *>(&blockAlign), 2);
    uint16_t bitsPerSample = 16;
    file.write(reinterpret_cast<const char *>(&bitsPerSample), 2);
    file.write("data", 4);
    uint32_t dataSize = 0;
    file.write(reinterpret_cast<const char *>(&dataSize), 4);
    
    file.close();
    
    // Vérifier que le fichier a bien été créé
    std::ifstream check_file(filename);
    if (check_file.good()) {
        std::cout << "Fichier WAV créé avec succès: " << filename << std::endl;
    } else {
        std::cerr << "Erreur: Le fichier n'a pas été créé correctement" << std::endl;
    }
}