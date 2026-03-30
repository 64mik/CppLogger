#include "../h/Logger.h"
#include <iostream>


Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}
Logger::~Logger() {
    if (file_.is_open()) {
        file_.close();
    }
}
Logger& Logger::operator<<(const std::string& message) {
    if (!file_.is_open()) {
        file_.open(logFileName_, std::ios::app);
        if (!file_) {
            std::cerr << "Failed to open log file." << std::endl;
            return *this;
        }
    }
    file_ << message << std::endl;  // 일단 매번 로그 메시지를 비우고, 나중에 버퍼 구현 필요.
    //알아서 시간이랑 파일명 등을 넣어서 로그 메시지 포맷팅 하는 기능도 추가할 예정 
    // ex: [2026-03-30 12:39:13] main.cpp:10 This is a log message. hello world!
     
    return *this;
}