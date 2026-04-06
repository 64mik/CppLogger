# ifndef LOGGER_H
# define LOGGER_H
#include <string>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <queue>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <atomic>

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
                getInstance().enQueue(logBuffer.str());
            }
            Wrapper(const Wrapper&) = delete;
            Wrapper& operator=(const Wrapper&) = delete;
            template<typename T>
            Wrapper& operator<<(const T& value){
                logBuffer << value;
                return *this;
            }
        private:
            std::ostringstream logBuffer;
    };
private:
    Logger();
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    void enQueue(const std::string& str);
    void deQueue();
    void write(const std::string& data);

    std::filesystem::path logDir_ = "logs";
    std::ofstream file_;
    std::string currentFileName_;
    std::condition_variable cv_;
    std::mutex mtx_;
    std::queue<std::string> q_;
    std::thread writer_;
    std::atomic<bool> running_{true};
    std::time_t last_t_ = 0;
    char timeBuf_[25]; 
    std::string lastDate_;
};
# endif // LOGGER_H