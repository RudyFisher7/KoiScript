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


#include "scripting/type.hpp"

#include <functional>
#include <ostream>
#include <string>


namespace Koi {
namespace Scripting {
namespace Runtime {

class Variable final {
private:
    BasicType _current_type = SCRIPTING_BASIC_TYPE_VOID;
    union {
        bool _value_bool = false;
        int _value_int;
        float _value_float;
        char* _value_text;
    };

public:
    static Variable from_char(char in_value);


    static Variable from_int(int in_value);


    static Variable from_float(float in_value);


    static Variable from_c_string(const char* in_value, size_t size);//todo::
    static Variable from_c_string(const char* in_value);// must be null-terminated //todo::

    static Variable from_string(const std::string& in_value);


    Variable();


    Variable(char in_value);


    Variable(int in_value);


    Variable(float in_value);


    Variable(const char* in_value, size_t size);


    Variable(const char* in_value); // must be null-terminated

    Variable(std::string in_value);


    Variable(const Variable& rhs);


    Variable(Variable&& rhs);


    Variable& operator=(const Variable& rhs);


    Variable& operator=(Variable&& rhs);


    ~Variable();


    bool operator==(const Variable& rhs) const;


    bool operator!=(const Variable& rhs) const;


    BasicType get_type() const;


    operator bool() const;


    operator char() const;


    operator int() const;


    operator float() const;


    operator char*() const;


    operator std::string() const;


    bool get_bool() const;


    /**
     * @brief Function that can be used to explicitly get the char
     * representation of the variant when there is ambiguity otherwise
     * such as the cases when interfacing with certain json libraries.
     * @return The char representation of this variant.
     */
    char get_char() const;


    int get_int() const;


    float get_float() const;


    std::string get_string() const;


    void set_value(bool value);


    void set_value(char value);


    void set_value(int value);


    void set_value(float value);


    void set_value(const char* value, size_t size);


    void set_value(const char* value);//must be null terminated


    void set_value(const std::string& value);


    void morph(BasicType in_type);


    friend std::ostream& operator<<(std::ostream& lhs, const Variable& rhs);


private:
    void _copy(const Variable& rhs);


    bool _set_string_value(const std::string& in_value);


    void _destroy_string_if_string();
};


//todo:: verify this hash is correct
// taken from https://stackoverflow.com/questions/19195183/how-to-properly-hash-the-custom-struct
// which supposedly uses the golden ratio
struct VariantHash {
public:
    size_t operator()(const Variable& in) const noexcept;


private:
    template<typename type>
    void combine_hash(const type& in, size_t& out) const noexcept;
};


std::string operator+(const Variable& lhs, const std::string& rhs);


std::string operator+(const std::string& lhs, const Variable& rhs);

}
}
}

#endif //KOI_SCRIPTING_RUNTIME_VARIABLE_HPP
