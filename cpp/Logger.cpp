#include "../h/Logger.h"
#include <iostream>

Logger& Logger::getInstance(const LogLevel logLevel) {
    static Logger instance;
    instance.currentLogLevel_ = logLevel;
    instance.updateLogTime();
    instance.logFileName_ = std::to_string(instance.logTime_[YEAR])+ "-" + instance.padding(2, instance.logTime_[MONTH]) + "-" + instance.padding(2, instance.logTime_[DAY]) + ".log";
    std::filesystem::create_directories(instance.logDir_);
    return instance;
}
Logger::~Logger() {
    if (file_.is_open()) {
        file_.close();
    }
}
std::string Logger::getLogPrefix() {
    updateLogTime();
    std::string prefix= "[";
    int index=0;
    for(int i : logTime_) {
        prefix += padding(2, i);
        if (index < 2) prefix += "-";
        else if (index == 2) prefix += " ";
        else if (index < 5 && index!=5) prefix += ":";
        index++;
    }
    prefix += "] ";
    switch (currentLogLevel_)
    {
    case LogLevel::INFO:
        prefix += "[INFO] ";
        break;
    case LogLevel::WARNING:
        prefix += "[WARNING] ";
        break;
    case LogLevel::ERROR:
        prefix += "[ERROR] ";
        break;
    default:
        break;
    }
    return prefix;
}
Logger& Logger::operator<<(const std::string& message) {
    if (!file_.is_open()) {
        file_.open(logDir_ / logFileName_, std::ios::app);
        if (!file_) {
            std::cerr << "Failed to open log file >> " << (logDir_ / logFileName_).string() << std::endl;
            return *this;
        }
    }
    file_ << getLogPrefix() << message << std::endl;  // 일단 매번 로그 메시지를 비우고, 나중에 버퍼 구현 필요.
    return *this;
}
std::string Logger::padding(const int num, int value, std::string delimiter) {
    std::string result = std::to_string(value);
    while (result.length() < num) {
        result = delimiter + result;
    }
    return result;
}
void Logger::updateLogTime() {
    struct tm* t;
    time_t timer;
    timer = time(NULL);
    t = localtime(&timer);
    logTime_[YEAR] = t->tm_year + 1900;
    logTime_[MONTH] = t->tm_mon + 1;
    logTime_[DAY] = t->tm_mday;
    logTime_[HOUR] = t->tm_hour;
    logTime_[MIN] = t->tm_min;
    logTime_[SEC] = t->tm_sec;
}