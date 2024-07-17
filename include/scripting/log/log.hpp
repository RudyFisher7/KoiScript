//
// Created by rfish on 7/16/2024.
//

#ifndef KOI_SCRIPTING_LOG_HPP
#define KOI_SCRIPTING_LOG_HPP


//fixme:: define in build system
#define ENABLE_KOI_SCRIPTING_LOG 1

#ifdef ENABLE_KOI_SCRIPTING_LOG

#include <iostream>
#include <string>


#define KOI_SCRIPTING_LOG_PREFIX "KoiScript Log:\n\t"

#define KOI_LOG(message) Koi::Scripting::Logger::_koi_log(KOI_SCRIPTING_LOG_PREFIX, message);\
    KOI_FILE_AND_LINE_INFO


#define KOI_LOG_IF_NOT(condition, arg) Koi::Scripting::Logger::_koi_log_if_not(condition, KOI_SCRIPTING_LOG_PREFIX, arg);\
    if (!(condition)) {\
        std::cout << "\t\t" << KOI_CONDITION_STRING((condition)) << " is false.\n";\
        KOI_FILE_AND_LINE_INFO\
    }


#define KOI_CONDITION_STRING(condition) #condition


#define KOI_FILE_AND_LINE_INFO\
    std::cout << "\t\t\t" << __FILE__ << ":" << __LINE__ << std::endl;\


namespace Koi {
namespace Scripting {

class Logger final {
public:
    static void _koi_log(const std::string& prefix, const std::string& message);
    static void _koi_log_if_not(bool condition, const std::string& prefix, const std::string& message);
    static void _koi_log_if_not(bool condition, void(*callback)());
};

} // Scripting
} // Koi

#else

#define KOI_LOG(message)
#define KOI_ASSERT(condition, message)
#define KOI_CONDITION_STRING(condition)
#define KOI_FILE_AND_LINE_INFO

#endif

#endif //KOI_SCRIPTING_LOG_HPP
