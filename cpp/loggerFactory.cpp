#include "../h/loggerFactory.h"
namespace mik64{
    std::vector<std::shared_ptr<IWriter>> LoggerFactory::getWriters(std::initializer_list<std::string> writerTypes){
        std::vector<std::shared_ptr<IWriter>> writers ={};
        for(const auto& type : writerTypes) {
            if(type == "file") {
                writers.push_back(std::make_shared<FileWriter>());
            } else if(type == "console") {
                writers.push_back(std::make_shared<ConsoleWriter>());
            }
        }
        return writers;
    }
}