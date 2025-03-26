#include <iostream>
#include <vector>
#include <fstream>

void saveSamplesToBinary(const std::string& filename, const std::vector<int16_t>& samples) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Unable to open file for writing!" << std::endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(samples.data()), samples.size() * sizeof(int16_t));
    file.close();
    std::cout << "Samples saved to " << filename << " (binary format)." << std::endl;
}