#include "../inc/NGram.h"

#include <algorithm>
#include <fstream>
#include <iostream>

/*
 * Example:
 * Using n-gram classes for generating random sequences of words from the given
 * file.
 */

void sanitize(std::string& str);
std::vector<std::string> file_to_vector(const std::string& file_path);
int file_example(const std::string& filename, unsigned advances);

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cout<< "Usage: ngram *filename* *number of advances* " << std::endl;
        return 1;
    }
    file_example(argv[1], atoi(argv[2]));
    return 0;
}

void sanitize(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](char c) { return std::tolower(c); });
    str.erase(std::remove_if(str.begin(), str.end(),
                   [](char c) { return !std::isalnum(c); }), str.end());
}

std::vector<std::string> file_to_vector(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open())
        throw std::runtime_error("Cant load file!");

    std::vector<std::string> sequence;
    std::string word;
    for (; !file.eof(); file >> word) {
        sanitize(word);
        sequence.push_back(word);
    }
    return sequence;
}

int file_example(const std::string& filename, unsigned advances) {
    auto s = file_to_vector(filename);
    std::cout << "File read..." << std::endl;
    static const NGram<std::string, 3> ngram(s);
    std::cout << "Distinct items: " << ngram.getItems().size() << '\n';

    static auto state = ngram.getRandomState();
    for (unsigned i = 0; i < advances; i++) {
        std::cout << state[0] << ' ' << std::flush;
        if (!state.advance())
            break;
    }
    return 0;
}

