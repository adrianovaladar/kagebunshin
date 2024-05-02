#include "TextFinder.h"
#include "Logger.h"
#include "ThreadPool.h"
#include <fstream>
#include <iostream>
#include <mutex>
#include <stack>
#include <utility>
#include <memory>

std::mutex mutex;

TextFinder::TextFinder(std::filesystem::path &&directoryToSearch, std::vector <std::string> &&wordsToSearch) : directory(std::move(directoryToSearch)), words(std::move(wordsToSearch)) {}

class DirectoryNotFoundException : public std::runtime_error {
public:
    explicit DirectoryNotFoundException(const std::string& message)
        : std::runtime_error(message) {}
};

void TextFinder::findInFile(std::stack<std::filesystem::path> &files) {
    std::filesystem::path file;
    {
        std::scoped_lock lock(mutex);
        file = files.top();
        //std::cout << "Thread " << std::this_thread::get_id() << " processing task." << std::endl;
        files.pop();
    }
    std::ifstream f;
    f.open(file, std::ifstream::in);
    bool found;
    if(!f.is_open()) {
        logger.log("Unable to open " + std::string(file), LOGLEVEL::Warning);
        return;
    }
    for(const auto &w: words) {
        found = false;
        std::string line;
        while (std::getline(f, line) && !found) {
            if (line.find(w) != std::string::npos) {
                logger.log("'" + w + "' found in " + std::string(file), LOGLEVEL::Info);
                found = true;
            }
        }
        if (!found) {
            logger.log("'" + w + "' not found in " + std::string(file), LOGLEVEL::Info);
            return;
        }
    }
    logger.log("All words were found in " + std::string(file), LOGLEVEL::Info);
    std::cout << file << std::endl;
}

void TextFinder::find() {
    try {
        if (!std::filesystem::exists(directory)) {
            logger.log("Directory not found", LOGLEVEL::Error);
            throw DirectoryNotFoundException("Directory not found");
        }
        std::unique_ptr<std::stack<std::filesystem::path>> files(new std::stack<std::filesystem::path>);
        for (const auto &entry: std::filesystem::recursive_directory_iterator(directory)) {
            //std::cout << entry.path() << std::endl;
            files->push(entry.path());
        }
        ThreadPool pool;
        for(int i {}; i < files->size(); i++) {
            pool.submit([this, &files](){
                this->findInFile((*files));
            });
        }
    } catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

void TextFinder::find(std::filesystem::path &&directoryToSearch, std::vector <std::string> &&wordsToSearch) {
    directory = directoryToSearch;
    words = wordsToSearch;
    find();
}
