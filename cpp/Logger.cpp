#include "../h/Logger.h"

Logger& Logger::getInstance() {
    static Logger instance;
    std::filesystem::create_directories(instance.logDir_);
    return instance;
}
Logger::~Logger() {
    if (file_.is_open()) {
        file_.close();
    }
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
void Logger::write(const std::string& str){
    updateLogTime();
    std::string newFileName = std::to_string(logTime_[YEAR]) + "-" + std::to_string(logTime_[MONTH]) + "-" + std::to_string(logTime_[DAY]) + ".log";
    if(newFileName != currentFileName){
        file_.close();
        currentFileName = newFileName;
    }
    if(!file_.is_open()){
        file_.open(Logger::logDir_ / currentFileName, std::ios::app);
        if(!file_){
            std::cerr <<"error file doesn't open";
            return;
        }
    }
    int index=0;
    std::ostringstream logBuffer;
    logBuffer << "[";
    for(int value : logTime_) {
        logBuffer << std::setfill('0') << std::setw(2) << value;
        if (index < 2) logBuffer << "-";
        else if (index == 2) logBuffer << " ";
        else if (index < 5) logBuffer << ":";
        index++;
        }
    logBuffer << "] ";
    file_ << logBuffer.str() << str << std::endl;
}