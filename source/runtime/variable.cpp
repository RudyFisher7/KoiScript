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


#include "scripting/runtime/variable.hpp"

#include <iostream>
#include <cstring>


namespace Koi {
namespace Scripting {
namespace Runtime {

Variable Variable::from_char(char in_value) {
    return Variable(in_value);
}


Variable Variable::from_int(int in_value) {
    return Variable(in_value);
}


Variable Variable::from_float(float in_value) {
    return Variable(in_value);
}


Variable Variable::from_string(const std::string& in_value) {
    return Variable(in_value);
}


Variable::Variable() : _current_type(SCRIPTING_BASIC_TYPE_VOID), _value_bool(false) {

}


Variable::Variable(char in_value) : _current_type(SCRIPTING_BASIC_TYPE_TEXT) {
    set_value(&in_value, 1u);
}


Variable::Variable(int in_value) : _current_type(SCRIPTING_BASIC_TYPE_INT), _value_int(in_value) {

}


Variable::Variable(float in_value) : _current_type(SCRIPTING_BASIC_TYPE_FLOAT), _value_float(in_value) {

}


Variable::Variable(const char* in_value, size_t size) {
    set_value(in_value, size);
}


Variable::Variable(std::string in_value) : _current_type(SCRIPTING_BASIC_TYPE_TEXT), _value_text(nullptr) {
    set_value(in_value);
}


Variable::Variable(const Variable& rhs) {
    switch (rhs._current_type) {
        case SCRIPTING_BASIC_TYPE_VOID:
            break;
        case SCRIPTING_BASIC_TYPE_BOOL:
            break;
        case SCRIPTING_BASIC_TYPE_INT:
            set_value(rhs._value_int);
            break;
        case SCRIPTING_BASIC_TYPE_FLOAT:
            set_value(rhs._value_float);
            break;
        case SCRIPTING_BASIC_TYPE_TEXT:
            set_value(rhs.get_string());
            break;
        case SCRIPTING_BASIC_TYPE_REF:
            break;
        case SCRIPTING_BASIC_TYPE_SIZE:
            break;
    }
}


Variable::Variable(Variable&& rhs) {
    switch (rhs._current_type) {
        case SCRIPTING_BASIC_TYPE_VOID:
            break;
        case SCRIPTING_BASIC_TYPE_BOOL:
            break;
        case SCRIPTING_BASIC_TYPE_INT:
            set_value(rhs._value_int);
            break;
        case SCRIPTING_BASIC_TYPE_FLOAT:
            set_value(rhs._value_float);
            break;
        case SCRIPTING_BASIC_TYPE_TEXT:
            set_value(rhs.get_string());
            break;
        case SCRIPTING_BASIC_TYPE_REF:
            break;
        case SCRIPTING_BASIC_TYPE_SIZE:
            break;
    }
}


Variable& Variable::operator=(const Variable& rhs) {
    if (this != &rhs) {
        switch (rhs._current_type) {
            case SCRIPTING_BASIC_TYPE_VOID:
                break;
            case SCRIPTING_BASIC_TYPE_BOOL:
                break;
            case SCRIPTING_BASIC_TYPE_INT:
                set_value(rhs._value_int);
                break;
            case SCRIPTING_BASIC_TYPE_FLOAT:
                set_value(rhs._value_float);
                break;
            case SCRIPTING_BASIC_TYPE_TEXT:
                set_value(rhs.get_string());
                break;
            case SCRIPTING_BASIC_TYPE_REF:
                break;
            case SCRIPTING_BASIC_TYPE_SIZE:
                break;
        }
    }

    return *this;
}


Variable& Variable::operator=(Variable&& rhs) {
    if (this != &rhs) {
        switch (rhs._current_type) {
            case SCRIPTING_BASIC_TYPE_VOID:
                break;
            case SCRIPTING_BASIC_TYPE_BOOL:
                break;
            case SCRIPTING_BASIC_TYPE_INT:
                set_value(rhs._value_int);
                break;
            case SCRIPTING_BASIC_TYPE_FLOAT:
                set_value(rhs._value_float);
                break;
            case SCRIPTING_BASIC_TYPE_TEXT:
                set_value(rhs.get_string());
                break;
            case SCRIPTING_BASIC_TYPE_REF:
                break;
            case SCRIPTING_BASIC_TYPE_SIZE:
                break;
        }
    }

    return *this;
}


Variable::~Variable() {
    _destroy_string_if_string();
}


bool Variable::operator==(const Variable& rhs) const {
    bool result = false;
    result = (
//            _current_type == rhs._current_type
//          && get_string() == rhs.get_string()
            get_string() == rhs.get_string()//fixme:: optimize
    );

    return result;
}


bool Variable::operator!=(const Variable& rhs) const {
    bool result = false;

    result = !(*this == rhs);

    return result;
}


BasicType Variable::get_type() const {
    return _current_type;
}


Variable::operator char() const {
    return get_char();
}


Variable::operator int() const {
    return get_int();
}


Variable::operator float() const {
    return get_float();
}


Variable::operator std::string() const {
    return get_string();
}


char Variable::get_char() const {
    char result = '\0';
    switch (_current_type) {
        case SCRIPTING_BASIC_TYPE_INT:
            result = char(_value_int);
            break;
        case SCRIPTING_BASIC_TYPE_FLOAT:
            result = char(_value_float);
            break;
        case SCRIPTING_BASIC_TYPE_SIZE:
            break;
    }

    return result;
}


int Variable::get_int() const {
    int result = 0;
    switch (_current_type) {
        case SCRIPTING_BASIC_TYPE_INT:
            result = _value_int;
            break;
        case SCRIPTING_BASIC_TYPE_FLOAT:
            result = int(_value_float);
            break;
        case SCRIPTING_BASIC_TYPE_SIZE:
            break;
    }

    return result;
}


float Variable::get_float() const {
    float result = 0.0f;
    switch (_current_type) {
        case SCRIPTING_BASIC_TYPE_INT:
            result = float(_value_int);
            break;
        case SCRIPTING_BASIC_TYPE_FLOAT:
            result = _value_float;
            break;
        case SCRIPTING_BASIC_TYPE_SIZE:
            break;
    }

    return result;
}


std::string Variable::get_string() const {
    std::string result;
    switch (_current_type) {
        case SCRIPTING_BASIC_TYPE_VOID:
            result = "\"<void>\"";
            break;
        case SCRIPTING_BASIC_TYPE_BOOL:
            result = _value_bool ? "true" : "false";
            break;
        case SCRIPTING_BASIC_TYPE_INT:
            result = std::to_string(_value_int);
            break;
        case SCRIPTING_BASIC_TYPE_FLOAT:
            result = std::to_string(_value_float);
            break;
        case SCRIPTING_BASIC_TYPE_TEXT:
            result = _value_text;
            break;
        case SCRIPTING_BASIC_TYPE_REF:
            break;
    }

    return result;
}


void Variable::set_value(char value) {
    _destroy_string_if_string();
}


void Variable::set_value(int value) {
    _destroy_string_if_string();
    _value_int = value;
    _current_type = SCRIPTING_BASIC_TYPE_INT;
}


void Variable::set_value(float value) {
    _destroy_string_if_string();
    _value_float = value;
    _current_type = SCRIPTING_BASIC_TYPE_FLOAT;
}


void Variable::set_value(const char* value, size_t size) {
    _destroy_string_if_string();
    _value_text = new char[size + 1u];
    std::memcpy(_value_text, value, size);
    _value_text[size] = '\0';
    _current_type = SCRIPTING_BASIC_TYPE_TEXT;
}


void Variable::set_value(const std::string& value) {
    _set_string_value(value);
    _current_type = SCRIPTING_BASIC_TYPE_TEXT;

}


void Variable::morph(BasicType in_type) {
    //todo::
}


std::ostream& operator<<(std::ostream& lhs, const Variable& rhs) {
    lhs << "{\"_class:\": \"Variant\", \"_current_type\": " << std::to_string(rhs._current_type) << ", \"_value\":";

    if (rhs._current_type == SCRIPTING_BASIC_TYPE_TEXT) {
        lhs << "\"" << rhs.get_string() << "\"";
    } else {
        lhs << rhs.get_string();
    }

    lhs << "}";

    return lhs;
}


bool Variable::_set_string_value(const std::string& in_value) {
    bool result = false;

    _destroy_string_if_string();

    _value_text = new char[in_value.size() + 1];

    size_t size = in_value.copy(_value_text, in_value.size());
    _value_text[in_value.size()] = '\0';

    result = size == in_value.size();

    if (!result) {
        std::cout << "Variant::_set_string_value() error. Characters copied: " << size << ", expected: "
                  << in_value.size()
                  << " Resulting string: " << _value_text << ", original string: " << in_value << std::endl;
    }

    return result;
}


void Variable::_destroy_string_if_string() {
    if (_current_type == SCRIPTING_BASIC_TYPE_TEXT && _value_text != nullptr) {
        free(_value_text);
    }
}


size_t VariantHash::operator()(const Variable& in) const noexcept {
    size_t result = 0u;
//    combine_hash<int>(in.get_type(), result);
    combine_hash<std::string>(in.get_string(), result);
    return result;
}


template<typename type>
void VariantHash::combine_hash(const type& in, size_t& out) const noexcept {
    std::hash<type> hash;
    out ^= hash(in) + 0x9e3779b9 + (out << 6) + (out >> 2);
}


std::string operator+(const Variable& lhs, const std::string& rhs) {
    return lhs.get_string() + rhs;
}


std::string operator+(const std::string& lhs, const Variable& rhs) {
    return lhs + rhs.get_string();
}

}
}
}