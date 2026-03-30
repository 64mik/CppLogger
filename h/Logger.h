# ifndef LOGGER_H
# define LOGGER_H
#include <string>
#include <fstream>
#include <filesystem>
#include <time.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#define LOG Logger::Wrapper(Logger::LogLevel::INFO)
#define LOG_INFO Logger::Wrapper(Logger::LogLevel::INFO)
#define LOG_WARNING Logger::Wrapper(Logger::LogLevel::WARNING)
#define LOG_ERROR Logger::Wrapper(Logger::LogLevel::ERROR)
class Logger {
public:
    enum class LogLevel {
        INFO,
        WARNING,
        ERROR
    };
    static Logger& getInstance();
    void write(const std::string& str);
    class Wrapper{
        public:
            Wrapper(Logger::LogLevel logLevel){
                switch (logLevel)
                {
                case Logger::LogLevel::INFO:
                    logBuffer << "[INFO] ";
                    break;
                case Logger::LogLevel::WARNING:
                    logBuffer << "[WARNING] ";
                    break;
                case Logger::LogLevel::ERROR:
                    logBuffer << "[ERROR] ";
                    break;
                default:
                    break;
                }
            }
            ~Wrapper(){
                Logger::getInstance().write(logBuffer.str());
            }
            Wrapper(const Wrapper&) = delete;
            Wrapper& operator=(const Wrapper&) = delete;
            template<typename T>
            Wrapper& operator<<(const T& value){
                logBuffer << value << ' ';
                return *this;
            }
        private:
            std::ostringstream logBuffer;
    };
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
    int logTime_[6] = {};
    std::filesystem::path logDir_ = "logs";
    std::ofstream file_;
    std::string currentFileName ="";
};
# endif // LOGGER_H