# ifndef LOGGER_H
# define LOGGER_H
#include "IWriter.h"
#include <string>
#include <sstream>
#include <queue>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <memory>
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
    void setWriters(std::vector<std::unique_ptr<IWriter>> writerptr);
    void flush();
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
protected:
    Logger();
    ~Logger();
private:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    void enQueue(const std::string& str);
    void deQueue();

    std::thread writer_;
    std::condition_variable cv_;
    std::mutex mtx_;
    std::queue<std::string> q_;
    std::atomic<bool> running_{true};
    std::atomic<bool> is_ptr_changed_{false};
    std::atomic<int> processing_count_{0};

    std::vector<std::unique_ptr<IWriter>> writerptrs_;
};
# endif // LOGGER_H