#include "../h/loggerFactory.h"
std::vector<std::unique_ptr<IWriter>> LoggerFactory::getWriters(std::initializer_list<std::string> writerTypes){
    std::vector<std::unique_ptr<IWriter>> writers ={};
    for(const auto& type : writerTypes) {
        if(type == "file") {
            writers.push_back(std::make_unique<FileWriter>());
        } else if(type == "console") {
            writers.push_back(std::make_unique<ConsoleWriter>());
        }
    }
    return writers;
}