#include <iostream>
#include "h/logger.h"
#include "h/loggerFactory.h"
#include <chrono>
#include <memory>
void hello(){
    LOG << "Hello, Logger";
}
void test(int count){
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < count; ++i) {
        if(i % 2 == 0) {
            LOG_WARNING << i << "This is a warning log message.";
        } else {
            hello();
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> diff = end - start;
    std::cout << count << "회 실행 시간: " << diff.count() << " ms";
}
int main() {
    auto writerptrs_ = LoggerFactory::getWriters({"file"});//, "console"});     둘다 정상 작동.
    Logger::getInstance().setWriters(std::move(writerptrs_));
    test(10000);
    //포인터가 해제된 메모리를 찾는 문제 수정
    //10000회 실행 시간: 191.366 ms -> 10000회 실행 시간: 28.7653 ms
    return 0;
}
//getInstance() 내부의 std::filesystem::create_directories(logDir_); 성능병목 주 원인이였음.