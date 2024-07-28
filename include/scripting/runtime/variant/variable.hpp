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


#ifndef KOI_SCRIPTING_RUNTIME_VARIABLE_HPP
#define KOI_SCRIPTING_RUNTIME_VARIABLE_HPP


#include "scripting/runtime/basic_type.hpp"

#include <ostream>
#include <string>


namespace Koi {
namespace Scripting {
namespace Runtime {

class Variable final {
public:
    static const unsigned int MAX_SIZE;
    static const std::string VOID_STRING;

private:
    int _size = 0u;
    BasicType _type = SCRIPTING_RUNTIME_BASIC_TYPE_VOID;
    union {
        bool _value_bool = false;
        int _value_int;
        float _value_float;
        char* _value_text;
    };

public:
    Variable();

    explicit Variable(BasicType in_type);


    explicit Variable(char in_value);


    explicit Variable(int in_value);


    explicit Variable(float in_value);


    explicit Variable(const char* in_value); // must be null-terminated


    Variable(const char* in_value, unsigned int size);


    explicit Variable(const std::string& in_value);


    Variable(const Variable& rhs);


    Variable(Variable&& rhs) noexcept;


    Variable& operator=(const Variable& rhs);


    Variable& operator=(Variable&& rhs) noexcept;


    ~Variable();


    bool operator==(const Variable& rhs) const;


    bool operator!=(const Variable& rhs) const;


    explicit operator bool() const;


    explicit operator char() const;


    explicit operator int() const;


    explicit operator float() const;


    explicit operator const char*() const;


    explicit operator std::string() const;

    BasicType get_type() const;


    int get_size() const;
    bool get_bool() const;
    char get_char() const;
    int get_int() const;
    float get_float() const;
    const char* get_c_string() const;
    std::string get_string() const;


    void set_value_void();


    void set_value(bool value);


    void set_value(char value);


    void set_value(int value);


    void set_value(float value);


    void set_value(const char* value, unsigned int size);


    void set_value(const char* value);


    void move_value(char** value);


    void set_value(const std::string& value);


    friend std::ostream& operator<<(std::ostream& lhs, const Variable& rhs);

private:
    bool _equals(const Variable& rhs) const;

    void _copy(const Variable& rhs);

    void _destroy_string_if_string();
};

}
}
}

#endif //KOI_SCRIPTING_RUNTIME_VARIABLE_HPP
