#include "TextFinder.h"
#include "Logger.h"
#include <iostream>
#include <mutex>
#include <stack>
#include <utility>

std::mutex mutex;

TextFinder::TextFinder(std::filesystem::path &&directoryToSearch, std::vector<std::string> &&wordsToSearch) : directory(std::move(directoryToSearch)), words(std::move(wordsToSearch)) {}

class DirectoryNotFoundException : public std::runtime_error {
public:
    explicit DirectoryNotFoundException(const std::string &message)
        : std::runtime_error(message) {}
};

void TextFinder::find() {
    try {
        if (!std::filesystem::exists(directory)) {
            logger.log("Directory not found", LOGLEVEL::Error);
            throw DirectoryNotFoundException("Directory not found");
        }
        std::stack<std::filesystem::path> files;
        for (const auto &entry: std::filesystem::recursive_directory_iterator(directory)) {
            std::cout << entry.path() << std::endl;
            files.push(entry.path());
        }
    } catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}
