#include <iostream>
#include "logger.h"

void Logger::info(const std::string &s) {
    std::cout << "[ INFO] " << Color::BLD << s << Color::RST << std::endl;
}

void Logger::warn(const std::string &s) {
    Logger::warnings++;
    std::cout << "[ WARN] " << Color::BLD << Color::YEL << s << Color::RST << std::endl;
}

void Logger::error(const std::string &s) {
    Logger::errors++;
    std::cout << "[ERROR] " << Color::BLD << Color::RED << s << Color::RST << std::endl;
}

void Logger::report() {
    if (Logger::errors > 0 || Logger::warnings > 0) {
        std::cout << "[REPRT] " << Color::BLD << Color::BLU << "Encoutered " << Logger::warnings ;
        if (Logger::warnings == 1) {
            std::cout << " warning and ";
        } else {
            std::cout << " warnings and ";
        }
        if (Logger::errors == 1) {
            std::cout << Logger::errors << " error" << Color::RST << std::endl;
        } else {
            std::cout << Logger::errors << " errors" << Color::RST << std::endl;
        }
    }
}
