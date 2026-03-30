#include <iostream>
#include "h/Logger.h"
int main() {
    Logger::getInstance() << "This is a log message. hello world!";
    Logger::getInstance() << "This is another log message.";
    return 0;
}


//파일 핸들러 불러와서 이용하고 일단 싱글톤 패턴 구현해서 여기애서 테스트하는걸로
//추후 인터페이스 추상화로 로그 레벨이나 포맷, 출력 방식 등 다양하게 확장할 수 있도록 수정 필요
