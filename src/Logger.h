#ifndef KAGEBUNSHIN_LOGGER_H
#define KAGEBUNSHIN_LOGGER_H

#include <filesystem>
#include <mutex>
#include <source_location>
#include <string>

enum class LOGLEVEL : char {
    Info = 'I',
    Warning = 'W',
    Error = 'E'
};

class Logger {
public:
    static Logger &getInstance() {
        static Logger instance;// Static local variable ensures lazy initialization and thread safety
        return instance;
    }
    Logger(const Logger &) = delete;           // Disable copy constructor
    Logger &operator=(const Logger &) = delete;// Disable copy assignment operator
    void log(const std::string &text, LOGLEVEL level, std::source_location source = std::source_location::current());

private:
    std::mutex mutex;
    std::string directoryName;
    // Private constructor to prevent instantiation from outside
    Logger() : directoryName("logs") {
        if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
            std::filesystem::create_directory(directoryName);
        }
    }
};


#endif//KAGEBUNSHIN_LOGGER_H
