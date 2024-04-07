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
    [[nodiscard]] const std::string &getLogFileName() const;

private:
    std::mutex mutex;
    std::string logFileName;
    // Private constructor to prevent instantiation from outside
    Logger() {
        std::string directoryName = "logs";
        if (!std::filesystem::exists(directoryName) && !std::filesystem::is_directory(directoryName)) {
            std::filesystem::create_directory(directoryName);
        }
        logFileName += directoryName + "/log_";
        auto now = std::chrono::system_clock::now();
        std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm{};
        localtime_r(&nowTime, &now_tm);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &now_tm);
        logFileName += std::string(buffer) + ".txt";
    }
};


#endif//KAGEBUNSHIN_LOGGER_H
