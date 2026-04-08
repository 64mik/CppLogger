#ifndef IWRITER_H
#define IWRITER_H
#include <string>
class IWriter {
public:
    virtual ~IWriter() = default;
    virtual void write(const std::string& data) = 0;
};
#endif // IWRITER_H