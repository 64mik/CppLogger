#include "../h/logger.h"
#include <iostream>
namespace mik64 {
    void Logger::setWriters(std::vector<std::shared_ptr<IWriter>> writerptr){
        std::lock_guard<std::mutex> lock(mtx_);
        this->writerptrs_ = std::move(writerptr);
        is_ptr_changed_ = true;
    }
    Logger::Logger(){
        writer_ = std::thread(&Logger::deQueue, this);
    }
    Logger::~Logger() {    
        {
            std::lock_guard<std::mutex> lock(mtx_);
            running_ = false;
        }
        cv_.notify_all();
        if (writer_.joinable()) writer_.join();
    }
    Logger& Logger::getInstance() {
        static Logger instance;
        return instance;
    }
    void Logger::flush() {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this] { return (q_.empty() && processing_count_ == 0) || !running_; });
    }
    void Logger::enQueue(const std::string& data){
        std::lock_guard<std::mutex> lock(mtx_);
        q_.push(data);
        cv_.notify_one();
    }
    void Logger::deQueue() {
        std::string data;
        std::vector<std::shared_ptr<IWriter>> writers;
        while (true) {
            {
                std::unique_lock<std::mutex> lock(mtx_);
                cv_.wait(lock, [this] { return !q_.empty() || !running_; });
                if (!running_ && q_.empty()) break;
                data = std::move(q_.front());
                q_.pop();
                if(is_ptr_changed_) {
                    writers.clear();
                    for(const auto& writer : writerptrs_){
                        writers.push_back(writer);
                    }
                    is_ptr_changed_ = false;
                }
                processing_count_++;
            }
            for(const auto& writer : writers){  //미설정시 애초에 for문 진입 안함
                if(writer)
                    writer->write(data);
            }
            processing_count_--;
            cv_.notify_one();
        }
    }
}