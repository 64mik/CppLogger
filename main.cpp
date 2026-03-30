#include <iostream>
#include "h/Logger.h"
int main() {
    
    LOG << "hello";
    LOG_INFO << "This is a log message. hello world!";
    LOG_INFO << "This is another log message.";
    LOG_ERROR << "This is an error message test.";
    LOG_WARNING << "This is a warning message test.";
    return 0;
}

//로그 레벨까지 구현해서 로그 레벨에 따라 다른 파일로 출력하거나, 콘솔에도 출력하는 기능도 추가할 예정
// ex: [2026-03-30 12:39:13] [INFO] main.cpp:10 This is a log message. hello world!

//콘솔, 파일, 네트워크 등 다양한 출력 방식 지원하도록 인터페이스 추상화도 필요할듯

// 날짜 및 시간 자동 추가 기능 -> 파일 이름에 사용 및 로그 메시지 포맷팅에 사용
