#ifndef LOGGERFACTORY_H
#define LOGGERFACTORY_H
#include "fileWriter.h"
#include "consoleWriter.h"
#include <vector>
#include <memory>
namespace LoggerFactory {
    std::vector<std::shared_ptr<IWriter>> getWriters(std::initializer_list<std::string> writerTypes);
}
#endif // LOGGERFACTORY_H