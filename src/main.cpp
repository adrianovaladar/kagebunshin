#include <filesystem>
#include <fstream>
#include <iostream>
#include <stack>

const int numberArguments = 2;

int main(int argc, char **argv) {
    try {
        std::string directoryToSearch;
        if (argc != numberArguments)
            throw std::runtime_error("Number of arguments should be equal to " + std::to_string(numberArguments));
        directoryToSearch = argv[1];
        std::stack<std::string> fileNames;
        for (const auto &entry: std::filesystem::recursive_directory_iterator(directoryToSearch)) {
            std::cout << entry.path() << std::endl;
            fileNames.push(entry.path());
        }
    } catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
