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

#define LOG Logger::Wrapper(Logger::LogLevel::L_INFO, __FUNCTION__, __LINE__)
#define LOG_INFO Logger::Wrapper(Logger::LogLevel::L_INFO, __FUNCTION__, __LINE__)
#define LOG_WARNING Logger::Wrapper(Logger::LogLevel::L_WARNING, __FUNCTION__, __LINE__)
#define LOG_ERROR Logger::Wrapper(Logger::LogLevel::L_ERROR, __FUNCTION__, __LINE__)
class Logger {
public:
    enum class LogLevel {
        L_INFO,
        L_WARNING,
        L_ERROR
    };
    static Logger& getInstance();
    class Wrapper{
        public:
            Wrapper(Logger::LogLevel logLevel, const char* func_name, int line = 0){
                switch (logLevel)
                {
                case Logger::LogLevel::L_INFO:
                    logBuffer << "[INFO] ";
                    break;
                case Logger::LogLevel::L_WARNING:
                    logBuffer << "[WARN] ";
                    break;
                case Logger::LogLevel::L_ERROR:
                    logBuffer << "[ERR_] ";
                    break;
                default:
                    break;
                }
                if (line > 0) {
                    logBuffer << line << "| ";
                }
                logBuffer << func_name << "(): ";
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