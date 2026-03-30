# ifndef LOGGER_H
# define LOGGER_H
#include <string>
#include <fstream>
#include <filesystem>
#include <time.h>
#define LOG Logger::getInstance(Logger::LogLevel::INFO)
#define LOG_INFO Logger::getInstance(Logger::LogLevel::INFO)
#define LOG_WARNING Logger::getInstance(Logger::LogLevel::WARNING)
#define LOG_ERROR Logger::getInstance(Logger::LogLevel::ERROR)
class Logger {
public:
    enum class LogLevel {
        INFO,
        WARNING,
        ERROR
    };
    static Logger& getInstance(const LogLevel logLevel=LogLevel::INFO);
    Logger& operator<<(const std::string& message);
private:
    enum LogTimeIndex {
        YEAR,
        MONTH,
        DAY,
        HOUR,
        MIN,
        SEC
    };
    Logger() = default;
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    void updateLogTime();
    std::string getLogPrefix();
    std::string padding(const int num, int value, std::string delimiter = "0");

    int logTime_[6] = {};
    std::string logFileName_ = "";
    std::filesystem::path logDir_ = "logs";
    std::ofstream file_;
    
    LogLevel currentLogLevel_ = LogLevel::INFO;
    
};
# endif // LOGGER_H