# ifndef LOGGER_H
# define LOGGER_H
#include <string>
#include <fstream>
class Logger {
public:
    static Logger& getInstance();
    Logger& operator<<(const std::string& message);
private:
    Logger() = default;
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::string logFileName_ = "log.log";   //추후 날짜별롬 로그 생성하도록 수정 필요
    std::ofstream file_;
    
};
# endif // LOGGER_H