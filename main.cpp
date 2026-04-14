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
    Logger::getInstance().setWriters(LoggerFactory::getWriters({"file"}));
    LOG_INFO << "This is an info message " << 1;
    LOG_WARNING << "This is a" << " warning message";
    LOG_ERROR << 0.1 << "This is an error message";
    //test(10000);
    return 0;
}