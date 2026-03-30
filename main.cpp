#include <iostream>
#include "h/Logger.h"
int main() {
    
    LOG << "hello" << 10;
    LOG_INFO << "This is a log message. hello world!";
    LOG_INFO << "This is another log message.";
    LOG_ERROR << "This is an error message test.";
    LOG_WARNING << "This is a warning message test.";
    return 0;
}

//콘솔, 파일, 네트워크 등 다양한 출력 방식 지원하도록 인터페이스 추상화도 필요할듯