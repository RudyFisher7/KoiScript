/*
 * MIT License
 *
 * Copyright (c) 2024 kiyasui-hito
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#ifndef KOI_SCRIPTING_LOG_HPP
#define KOI_SCRIPTING_LOG_HPP


//fixme:: define in build system
#define ENABLE_KOI_SCRIPTING_LOG 1

#ifdef ENABLE_KOI_SCRIPTING_LOG


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

#else

#define KOI_LOG(message)
#define KOI_LOG_IF_NOT(condition, message)
#define KOI_CONDITION_STRING(condition)
#define KOI_FILE_AND_LINE_INFO

#endif


#include <iostream>
#include <string>


namespace Koi {
namespace Scripting {

/**
 * @brief Logger class. It is recommended to use above macros instead.
 */
class Logger final {
public:
    static void _koi_log(const std::string& prefix, const std::string& message);
    static void _koi_log_if_not(bool condition, const std::string& prefix, const std::string& message);
    static void _koi_log_if_not(bool condition, void(*callback)());
};

} // Scripting
} // Koi


#endif //KOI_SCRIPTING_LOG_HPP
