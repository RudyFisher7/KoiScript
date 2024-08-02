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


#include "scripting/runtime/variant/variable.hpp"

#include "scripting/log/log.hpp"

#include <cmath>
#include <cstring>
#include <limits>


namespace Koi {
namespace Scripting {
namespace Runtime {

const unsigned int Variable::SIMPLE_SIZE = 1u;
const unsigned int Variable::MAX_SIZE = 64u;//fixme:: build configuration or similar since this depends on token size
const std::string Variable::VOID_STRING("\"<void>\"");


Variable::Variable():
        _size(0u),
        _type(SCRIPTING_RUNTIME_BASIC_TYPE_VOID),
        _value_bool(false) {

}


Variable::Variable(BasicType in_type) {
    switch (in_type) {
        case SCRIPTING_RUNTIME_BASIC_TYPE_VOID:
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_BOOL:
            set_value(false);
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_INT:
            set_value(0);
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_FLOAT:
            set_value(0.0f);
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_TEXT:
            set_value("");
            break;
        default:
            KOI_LOG("Invalid BasicType for Variable: " + std::to_string(in_type));
            break;
    }
}


Variable::Variable(char in_value):
        _size(SIMPLE_SIZE),
        _type(SCRIPTING_RUNTIME_BASIC_TYPE_TEXT) {
    set_value(&in_value, 1u);
}


Variable::Variable(int in_value):
        _size(SIMPLE_SIZE),
        _type(SCRIPTING_RUNTIME_BASIC_TYPE_INT),
        _value_int(in_value) {

}


Variable::Variable(float in_value):
        _size(SIMPLE_SIZE),
        _type(SCRIPTING_RUNTIME_BASIC_TYPE_FLOAT),
        _value_float(in_value) {

}


Variable::Variable(const char* in_value):
        _type(SCRIPTING_RUNTIME_BASIC_TYPE_TEXT),
        _value_text(nullptr) {
    set_value(in_value);
}


Variable::Variable(const char* in_value, unsigned int size):
        _type(SCRIPTING_RUNTIME_BASIC_TYPE_TEXT),
        _value_text(nullptr) {
    set_value(in_value, size);
}


Variable::Variable(const char* in_value, unsigned int size, BasicType in_type):
        _type(in_type),
        _value_text(nullptr) {
    set_id(in_value, size);
}


Variable::Variable(const std::string& in_value):
        _type(SCRIPTING_RUNTIME_BASIC_TYPE_TEXT),
        _value_text(nullptr) {
    set_value(in_value);
}


Variable::Variable(const Variable& rhs) {
    _copy(rhs);
}


Variable::Variable(Variable&& rhs) noexcept {
    switch (rhs.get_type()) {
        case SCRIPTING_RUNTIME_BASIC_TYPE_VOID:
            set_value_void();
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_BOOL:
            set_value(rhs.get_bool());
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_INT:
            set_value(rhs.get_int());
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_FLOAT:
            set_value(rhs.get_float());
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_TEXT:
        case SCRIPTING_RUNTIME_BASIC_TYPE_KEY:
            move_value(&rhs._value_text);
            break;
        default:
            KOI_LOG("Variable isn't of recognized type.");
            break;
    }
}


Variable::~Variable() {
    _destroy_string_if_string();
}


Variable& Variable::operator=(const Variable& rhs) {
    if (this != &rhs) {
        _copy(rhs);
    }

    return *this;
}


Variable& Variable::operator=(Variable&& rhs) noexcept {
    if (this != &rhs) {
        switch (rhs.get_type()) {
            case SCRIPTING_RUNTIME_BASIC_TYPE_VOID:
                set_value_void();
                break;
            case SCRIPTING_RUNTIME_BASIC_TYPE_BOOL:
                set_value(rhs.get_bool());
                break;
            case SCRIPTING_RUNTIME_BASIC_TYPE_INT:
                set_value(rhs.get_int());
                break;
            case SCRIPTING_RUNTIME_BASIC_TYPE_FLOAT:
                set_value(rhs.get_float());
                break;
            case SCRIPTING_RUNTIME_BASIC_TYPE_TEXT:
                move_value(&rhs._value_text);
                break;
            case SCRIPTING_RUNTIME_BASIC_TYPE_KEY:
                move_id(&rhs._value_text);
                break;
            default:
                KOI_LOG("Variable isn't of recognized type.");
                break;
        }
    }

    return *this;
}


bool Variable::operator==(const Variable& rhs) const {
    return _equals(rhs);
}


bool Variable::operator!=(const Variable& rhs) const {
    bool result = false;

    result = !(*this == rhs);

    return result;
}


Variable::operator bool() const {
    return get_bool();
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


Variable::operator const char*() const {
    return get_c_string();
}


Variable::operator std::string() const {
    return get_string();
}


BasicType Variable::get_type() const {
    return _type;
}


unsigned int Variable::get_size() const {
    return _size;
}


bool Variable::get_bool() const {
    bool result = false;

    switch (_type) {
        case SCRIPTING_RUNTIME_BASIC_TYPE_VOID:
            // handled above
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_BOOL:
            result = _value_bool;
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_INT:
            result = static_cast<bool>(_value_int);
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_FLOAT:
            result = static_cast<bool>(_value_float);
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_TEXT:
        case SCRIPTING_RUNTIME_BASIC_TYPE_KEY:
            result = _size > 0u;
            break;
        default:
        KOI_LOG("Variable isn't of recognized type.");
            break;
    }

    return result;
}


char Variable::get_char() const {
    char result = '\0';

    switch (_type) {
        case SCRIPTING_RUNTIME_BASIC_TYPE_VOID:
            // handled above
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_BOOL:
            result = static_cast<char>(_value_bool);
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_INT:
            result = static_cast<char>(_value_int);
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_FLOAT:
            result = static_cast<char>(_value_float);
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_TEXT:
        case SCRIPTING_RUNTIME_BASIC_TYPE_KEY:
            if (_size > 0u) {
                result = _value_text[0u];
            }
            break;
        default:
        KOI_LOG("Variable isn't of recognized type.");
            break;
    }

    return result;
}


int Variable::get_int() const {
    int result = 0;

    switch (_type) {
        case SCRIPTING_RUNTIME_BASIC_TYPE_VOID:
            // handled above
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_BOOL:
            result = static_cast<int>(_value_bool);
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_INT:
            result = _value_int;
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_FLOAT:
            result = static_cast<int>(_value_float);
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_TEXT:
        case SCRIPTING_RUNTIME_BASIC_TYPE_KEY:
            if (_size > 0u) {
                result = static_cast<int>(static_cast<unsigned char>(_value_text[0u]));
            }
            break;
        default:
        KOI_LOG("Variable isn't of recognized type.");
            break;
    }

    return result;
}


float Variable::get_float() const {
    float result = 0.0f;

    switch (_type) {
        case SCRIPTING_RUNTIME_BASIC_TYPE_VOID:
            // handled above
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_BOOL:
            result = static_cast<float>(_value_bool);
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_INT:
            result = static_cast<float>(_value_int);
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_FLOAT:
            result = _value_float;
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_TEXT:
        case SCRIPTING_RUNTIME_BASIC_TYPE_KEY:
            if (_size > 0u) {
                result = static_cast<float>(static_cast<unsigned char>(_value_text[0u]));
            }
            break;
        default:
        KOI_LOG("Variable isn't of recognized type.");
            break;
    }

    return result;
}


const char* Variable::get_c_string() const {
    const char* result = nullptr;

    switch (_type) {
        case SCRIPTING_RUNTIME_BASIC_TYPE_VOID:
        case SCRIPTING_RUNTIME_BASIC_TYPE_BOOL:
        case SCRIPTING_RUNTIME_BASIC_TYPE_INT:
        case SCRIPTING_RUNTIME_BASIC_TYPE_FLOAT:
        KOI_LOG("Variable text is considered nullptr.");
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_TEXT:
        case SCRIPTING_RUNTIME_BASIC_TYPE_KEY:
            result = _value_text;
            break;
        default:
        KOI_LOG("Variable isn't of recognized type.");
            break;
    }

    return result;
}


std::string Variable::get_string() const {
    std::string result;

    switch (_type) {
        case SCRIPTING_RUNTIME_BASIC_TYPE_VOID:
            result = VOID_STRING;
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_BOOL:
            result = _value_bool ? "true" : "false";
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_INT:
            result = std::to_string(_value_int);
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_FLOAT:
            result = std::to_string(_value_float);
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_TEXT:
        case SCRIPTING_RUNTIME_BASIC_TYPE_KEY:
            result = _value_text;
            break;
        default:
        KOI_LOG("Variable isn't of recognized type.");
            break;
    }

    return result;
}


bool Variable::is_same_type(const Variable& other) const {
    return get_type() == other.get_type();
}


void Variable::set_value_void() {
    _destroy_string_if_string();
    _size = 0u;
    _type = SCRIPTING_RUNTIME_BASIC_TYPE_VOID;
    _value_bool = false;
}


void Variable::set_value(bool value) {
    _destroy_string_if_string();
    _size = SIMPLE_SIZE;
    _type = SCRIPTING_RUNTIME_BASIC_TYPE_BOOL;
    _value_bool = value;
}


void Variable::set_value(char value) {
    _destroy_string_if_string();
    set_value(&value, SIMPLE_SIZE);
}


void Variable::set_value(int value) {
    _destroy_string_if_string();
    _size = SIMPLE_SIZE;
    _type = SCRIPTING_RUNTIME_BASIC_TYPE_INT;
    _value_int = value;
}


void Variable::set_value(float value) {
    _destroy_string_if_string();
    _size = SIMPLE_SIZE;
    _type = SCRIPTING_RUNTIME_BASIC_TYPE_FLOAT;
    _value_float = value;
}


void Variable::set_value(const char* value, unsigned int size) {
    _destroy_string_if_string();
    _size = size;
    _type = SCRIPTING_RUNTIME_BASIC_TYPE_TEXT;
    _value_text = new char[size + 1u];
    std::memcpy(_value_text, value, size);
    _value_text[size] = '\0';
}


void Variable::set_id(const char* value, unsigned int size) {//fixme:: remove duplicate code
    _destroy_string_if_string();
    _size = size;
    _type = SCRIPTING_RUNTIME_BASIC_TYPE_KEY;
    _value_text = new char[size + 1u];
    std::memcpy(_value_text, value, size);
    _value_text[size] = '\0';
}


void Variable::set_value(const char* value) {
    unsigned int size = strnlen(value, MAX_SIZE);
    set_value(value, size);
}


void Variable::move_value(char** value) {
    _size = strnlen(*value, MAX_SIZE);
    _type = SCRIPTING_RUNTIME_BASIC_TYPE_TEXT;
    _value_text = *value;
    *value = nullptr;
}


void Variable::move_id(char** value) {
    _size = strnlen(*value, MAX_SIZE);
    _type = SCRIPTING_RUNTIME_BASIC_TYPE_KEY;
    _value_text = *value;
    *value = nullptr;
}


void Variable::set_value(const std::string& value) {
    set_value(value.c_str(), value.size());
}


void Variable::set_id(const std::string& value) {
    set_id(value.c_str(), value.size());
}


std::ostream& operator<<(std::ostream& lhs, const Variable& rhs) {
    lhs << "{\"_class:\": \"Variant\", \"_size\": "
    << std::to_string(rhs._size)
    << ", \"_type\": "
    << std::to_string(rhs._type)
    << ", \"_value\":";

    if (rhs._type == SCRIPTING_RUNTIME_BASIC_TYPE_TEXT) {
        lhs << "\"" << rhs.get_string() << "\"";
    } else {
        lhs << rhs.get_string();
    }

    lhs << "}";

    return lhs;
}


bool Variable::_equals(const Variable& rhs) const {
    bool result = false;

    result = get_type() == rhs.get_type();

    if (result) {
        switch (rhs.get_type()) {
            case SCRIPTING_RUNTIME_BASIC_TYPE_VOID:
                // handled above, since there is no value
                break;
            case SCRIPTING_RUNTIME_BASIC_TYPE_BOOL:
                result = get_bool() == rhs.get_bool();
                break;
            case SCRIPTING_RUNTIME_BASIC_TYPE_INT:
                result = get_int() == rhs.get_int();
                break;
            case SCRIPTING_RUNTIME_BASIC_TYPE_FLOAT:
                result = std::fabs(get_float() - rhs.get_float()) < std::numeric_limits<float>::epsilon();
                break;
            case SCRIPTING_RUNTIME_BASIC_TYPE_TEXT:
                result = _value_text == rhs.get_string();
                break;
            default:
            KOI_LOG("Variable isn't of recognized type.");
                break;
        }
    }

    return result;
}


void Variable::_copy(const Variable& rhs) {
    switch (rhs.get_type()) {
        case SCRIPTING_RUNTIME_BASIC_TYPE_VOID:
            set_value_void();
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_BOOL:
            set_value(rhs.get_bool());
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_INT:
            set_value(rhs.get_int());
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_FLOAT:
            set_value(rhs.get_float());
            break;
        case SCRIPTING_RUNTIME_BASIC_TYPE_TEXT:
            set_value(rhs.get_c_string());
            break;
        default:
            KOI_LOG("Variable isn't of recognized type.");
            break;
    }
}


void Variable::_destroy_string_if_string() {
    bool needs_freeing = (
            (_type == SCRIPTING_RUNTIME_BASIC_TYPE_TEXT || _type == SCRIPTING_RUNTIME_BASIC_TYPE_KEY)
            && _size > 0u
            && _value_text != nullptr
    );

    if (needs_freeing) {
        std::free(_value_text);
        _value_text = nullptr;
    }
}

}
}
}