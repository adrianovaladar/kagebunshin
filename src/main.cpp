#include "TextFinder.h"
#include <filesystem>
#include <iostream>

const int numberArguments = 3;

class InvalidArgumentException : public std::runtime_error {
public:
    explicit InvalidArgumentException(const std::string &message)
        : std::runtime_error(message) {}
};

int main(int argc, char **argv) {
    try {
        std::filesystem::path directory;
        if (argc < numberArguments)
            throw InvalidArgumentException("Minimum number of arguments is " + std::to_string(numberArguments));
        directory = argv[1];
        std::vector<std::string> words;
        for (int i{2}; i < argc; i++)
            words.emplace_back(argv[i]);
        TextFinder tf(std::move(directory), std::move(words));
        tf.find();
    } catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
