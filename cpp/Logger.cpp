#include "../h/Logger.h"

Logger::Logger(){
    std::filesystem::create_directories(logDir_);
    writer_ = std::thread(&Logger::deQueue, this);
}
Logger::~Logger() {
    running_ = false;
    cv_.notify_all();
    if (writer_.joinable()) writer_.join();
    if (file_.is_open()) {
        file_.close();
    }
}
Logger& Logger::getInstance() {
    static Logger instance;
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
        write(data);
    }
}
void Logger::write(const std::string& data) {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    if (in_time_t != last_t_) {
        std::tm t;
        localtime_s(&t, &in_time_t);
        char dateBuf[11];
        strftime(dateBuf, sizeof(dateBuf), "%Y-%m-%d", &t);
        std::string newDate(dateBuf);

        if (newDate != lastDate_) {
            if (file_.is_open()) file_.close();
            lastDate_ = newDate;
            currentFileName_ = lastDate_ + ".log";
            file_.open(logDir_ / currentFileName_, std::ios::app);
        }
        strftime(timeBuf_, sizeof(timeBuf_), "[%Y-%m-%d %H:%M:%S] ", &t);
        last_t_ = in_time_t;
    }
    file_ << timeBuf_ << data << '\n';
}

