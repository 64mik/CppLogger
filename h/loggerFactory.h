#ifndef LOGGERFACTORY_H
#define LOGGERFACTORY_H
#include "fileWriter.h"
#include "consoleWriter.h"
#include <vector>
#include <memory>
class LoggerFactory {
public:
    static std::vector<std::unique_ptr<IWriter>> getWriters(std::initializer_list<std::string> writerTypes);
private:
};
#endif // LOGGERFACTORY_H