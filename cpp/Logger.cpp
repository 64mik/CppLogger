#include "../h/logger.h"
#include <iostream>
void Logger::setWriters(std::vector<std::unique_ptr<IWriter>> writerptr){
    this->writerptrs_ = std::move(writerptr);
}
Logger::Logger(){
    writer_ = std::thread(&Logger::deQueue, this);
}
Logger::~Logger() {
    running_ = false;
    cv_.notify_all();
    if (writer_.joinable()) writer_.join();
}
Logger& Logger::getInstance() {
    static Logger instance; //왜 오류가 나지 ->
    return instance;
}
void Logger::enQueue(const std::string& data){
    std::lock_guard<std::mutex> lock(mtx_);
    q_.push(data);
    cv_.notify_one();
}
void Logger::deQueue() {
    while (true) {
        std::string data;
        {
            std::unique_lock<std::mutex> lock(mtx_);
            cv_.wait(lock, [this] { return !q_.empty() || !running_; });
            if (!running_ && q_.empty()) break;
            data = std::move(q_.front());
            q_.pop();
        }
        for(const auto& writer : writerptrs_){
            if(writer)
                writer->write(data);
        }
    }
}
