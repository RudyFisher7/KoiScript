//
// Created by rfish on 7/16/2024.
//

#include "scripting/log/log.hpp"


namespace Koi {
namespace Scripting {

void Logger::_koi_log(const std::string& prefix, const std::string& message) {
    std::cout << prefix << message << std::endl;
}


void Logger::_koi_log_if_not(bool condition, const std::string& prefix, const std::string& message) {
    if (!condition) {
        _koi_log(prefix, message);
    }
}


void Logger::_koi_log_if_not(bool condition, void(*callback)()) {
    if (!condition) {
        callback();
    }
}

} // Scripting
} // Koi