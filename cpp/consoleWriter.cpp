#include "../h/consoleWriter.h"
#include <iostream>
namespace mik64 {
    ConsoleWriter::ConsoleWriter() {
    }
    ConsoleWriter::~ConsoleWriter() {
    }
    void ConsoleWriter::write(const std::string& data) {
        std::cout << data << std::endl;
    }
}