#ifndef FILE_WRITER_H
#define FILE_WRITER_H
#include "IWriter.h"
#include <fstream>
#include <filesystem>
class FileWriter : public IWriter {
public:
    FileWriter(const std::string& logDirectory = "logs");
    ~FileWriter();
    void write(const std::string& data) override;
private:
    // 시간 계산 및 파일에 작성을 write 에 포함
    std::filesystem::path logDir_;
    std::ofstream file_;
    std::string currentFileName_;
    std::time_t last_t_ = 0;
    char timeBuf_[25]; 
    std::string lastDate_;

};
#endif // FILEWRITER_H