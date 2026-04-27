#include <iostream>
#include "h/mlog.h"
#include "h/loggerFactory.h"
#include <chrono>
#include <memory>
void hello(){
    MLOG << "Hello, Logger";
}
void test(int count){
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < count; ++i) {
        if(i % 2 == 0) {
            MLOG_WARNING << i << "This is a warning log message.";
        } else {
            hello();
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> diff = end - start;
    std::cout << count << "회 실행 시간: " << diff.count() << " ms" << std::endl;
    mik64::Logger::getInstance().flush();
    auto file_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> file_diff = file_end - start;
    std::cout << count << "회 파일 작성 시간: " << file_diff.count() << " ms" << std::endl;
}
int main() {
    mik64::Logger::getInstance().setWriters(mik64::LoggerFactory::getWriters({"file"}));
    MLOG_INFO << "This is an info message " << 1;
    MLOG_WARNING << "This is a" << " warning message";
    MLOG_ERROR << 0.1 << "This is an error message";
    test(100000);    //100000회 실행 시간 평균: 425.735 ms 100000회 파일 작성 시간 평균: 426.301 ms | ~Logger()의 notify 버그수정, 파일 작성 시간이 비정상적으로 늘어나는 문제 수정
    return 0;
}