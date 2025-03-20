#pragma once
#include <string>

class AudioWav {
    private:
        //private
    public:
        AudioWav() = default;
        void encodeToWav(const std::string &morse, const std::string &filename) const;
        std::string decodeFromWav(const std::string &filename) const;
        void generateEmptyWav(const std::string &filename) const;
};