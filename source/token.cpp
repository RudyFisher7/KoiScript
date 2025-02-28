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


#include "../include/scripting/token.hpp"

#include <cstring>


#define NAMEOF(arg) #arg


namespace Koi { namespace Scripting {

const char* Token::TRUE_BOOL = "True";


Token Token::from(Type in_type, const char* in_value_string) {
    switch (in_type) {
        case SCRIPTING_TOKEN_TYPE_BOOL:
            return Token(in_type, in_value_string == TRUE_BOOL);
        case SCRIPTING_TOKEN_TYPE_INT:
            return Token(in_type, std::atoi(in_value_string));
        case SCRIPTING_TOKEN_TYPE_FLOAT:
            return Token(in_type, static_cast<float>(std::atof(in_value_string)));
        default:
            return Token(in_type, in_value_string);
    }
}


Token Token::from(Type in_type, const std::string& in_value_string) {
    return from(in_type, in_value_string.c_str());
}


Token::Token(Type in_type, bool in_value):
        _type(in_type),
        _internal_type(SCRIPTING_TOKEN_INTERNAL_TYPE_BOOL),
        _value_bool(in_value) {

}


Token::Token(Type in_type, int in_value):
        _type(in_type),
        _internal_type(SCRIPTING_TOKEN_INTERNAL_TYPE_INT),
        _value_int(in_value) {

}


Token::Token(Type in_type, float in_value):
        _type(in_type),
        _internal_type(SCRIPTING_TOKEN_INTERNAL_TYPE_FLOAT),
        _value_float(in_value) {

}


Token::Token(Type in_type, const char* in_value):
        _type(in_type),
        _internal_type(SCRIPTING_TOKEN_INTERNAL_TYPE_STRING),
        _string_size(std::strlen(in_value) + 1u){
    _value_string = new char[_string_size];
    std::strcpy(_value_string, in_value);
    _value_string[_string_size - 1u] = '\0';
}


Token::Token(Type in_type, const std::string& in_value):
        _type(in_type),
        _internal_type(SCRIPTING_TOKEN_INTERNAL_TYPE_STRING),
        _string_size(in_value.size() + 1u){
    _value_string = new char[_string_size];
    std::strcpy(_value_string, in_value.c_str());
    _value_string[in_value.size()] = '\0';
}


Token::Token(const Token& rhs): _type(rhs._type), _internal_type(rhs._internal_type), _string_size(rhs._string_size) {
    switch (_internal_type) {
        case SCRIPTING_TOKEN_INTERNAL_TYPE_BOOL:
            _value_bool = rhs._value_bool;
            break;
        case SCRIPTING_TOKEN_INTERNAL_TYPE_INT:
            _value_int = rhs._value_int;
            break;
        case SCRIPTING_TOKEN_INTERNAL_TYPE_FLOAT:
            _value_float = rhs._value_float;
            break;
        case SCRIPTING_TOKEN_INTERNAL_TYPE_STRING:
            _value_string = new char[_string_size];
            std::strcpy(_value_string, rhs._value_string);
            break;
        default:
            //todo:: should be impossible to be here
            break;
    }
}


Token::Token(Token&& rhs) noexcept {
    _type = rhs._type;
    _internal_type = rhs._internal_type;
    _string_size = rhs._string_size;
    switch (_internal_type) {
        case SCRIPTING_TOKEN_INTERNAL_TYPE_BOOL:
            _value_bool = rhs._value_bool;
            break;
        case SCRIPTING_TOKEN_INTERNAL_TYPE_INT:
            _value_int = rhs._value_int;
            break;
        case SCRIPTING_TOKEN_INTERNAL_TYPE_FLOAT:
            _value_float = rhs._value_float;
            break;
        case SCRIPTING_TOKEN_INTERNAL_TYPE_STRING:
            _value_string = new char[_string_size];
            std::memmove(_value_string, rhs._value_string, _string_size);
            break;
        default:
            //todo:: should be impossible to be here
            break;
    }
}


Token::~Token() {
    if (_internal_type == SCRIPTING_TOKEN_INTERNAL_TYPE_STRING) {
        std::free(_value_string);
    }
}


Token& Token::operator=(const Token& rhs) {
    _copy(rhs);
    return *this;
}


Token& Token::operator=(Token&& rhs) noexcept {
    _type = rhs._type;
    _internal_type = rhs._internal_type;
    _string_size = rhs._string_size;
    switch (_internal_type) {
        case SCRIPTING_TOKEN_INTERNAL_TYPE_BOOL:
            _value_bool = rhs._value_bool;
            break;
        case SCRIPTING_TOKEN_INTERNAL_TYPE_INT:
            _value_int = rhs._value_int;
            break;
        case SCRIPTING_TOKEN_INTERNAL_TYPE_FLOAT:
            _value_float = rhs._value_float;
            break;
        case SCRIPTING_TOKEN_INTERNAL_TYPE_STRING:
            _value_string = new char[_string_size];
            std::memmove(_value_string, rhs._value_string, _string_size);
            break;
        default:
            //todo:: should be impossible to be here
            break;
    }

    return *this;
}


Token::Type Token::get_type() const {
    return _type;
}


Token::InternalType Token::get_internal_type() const {
    return _internal_type;
}


bool Token::get_value_bool() const {
    return _value_bool;
}


int Token::get_value_int() const {
    return _value_int;
}


float Token::get_value_float() const {
    return _value_float;
}


std::string Token::get_value_string() const {
    switch (_internal_type) {
        case SCRIPTING_TOKEN_INTERNAL_TYPE_BOOL:
            if (_value_bool) {
                return "true";
            } else {
                return "false";
            }
        case SCRIPTING_TOKEN_INTERNAL_TYPE_INT:
            return std::to_string(_value_int);
        case SCRIPTING_TOKEN_INTERNAL_TYPE_FLOAT:
            return std::to_string(_value_float);
        case SCRIPTING_TOKEN_INTERNAL_TYPE_STRING:
            return _value_string;
        default:
            return "";
    }
}


std::string Token::_get_name_of_type(Token::Type in_type) {
    std::string result;

    switch (in_type) {
        case SCRIPTING_TOKEN_TYPE_INVALID:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_INVALID);
            break;
        case SCRIPTING_TOKEN_TYPE_SPECIFIER_VOID:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_SPECIFIER_VOID);
            break;
        case SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_SPECIFIER_BOOL);
            break;
        case SCRIPTING_TOKEN_TYPE_SPECIFIER_INT:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_SPECIFIER_INT);
            break;
        case SCRIPTING_TOKEN_TYPE_SPECIFIER_FLOAT:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_SPECIFIER_FLOAT);
            break;
        case SCRIPTING_TOKEN_TYPE_SPECIFIER_TEXT:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_SPECIFIER_TEXT);
            break;
        case SCRIPTING_TOKEN_TYPE_GROUPING_START:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_GROUPING_START);
            break;
        case SCRIPTING_TOKEN_TYPE_GROUPING_END:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_GROUPING_END);
            break;
        case SCRIPTING_TOKEN_TYPE_SCOPE_START:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_SCOPE_START);
            break;
        case SCRIPTING_TOKEN_TYPE_SCOPE_END:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_SCOPE_END);
            break;
        case SCRIPTING_TOKEN_TYPE_ID_START:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_ID_START);
            break;
        case SCRIPTING_TOKEN_TYPE_ID_END:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_ID_END);
            break;
        case SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_VERBATIM_BOOKEND);
            break;
        case SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_COMMENT_BOOKEND);
            break;
        case SCRIPTING_TOKEN_TYPE_COMBINER:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_COMBINER);
            break;
        case SCRIPTING_TOKEN_TYPE_DELIMITER:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_DELIMITER);
            break;
        case SCRIPTING_TOKEN_TYPE_RESULTER:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_RESULTER);
            break;
        case SCRIPTING_TOKEN_TYPE_BOOL:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_BOOL);
            break;
        case SCRIPTING_TOKEN_TYPE_INT:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_INT);
            break;
        case SCRIPTING_TOKEN_TYPE_FLOAT:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_FLOAT);
            break;
        case SCRIPTING_TOKEN_TYPE_TEXT:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_TEXT);
            break;
        case SCRIPTING_TOKEN_TYPE_ID:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_ID);
            break;
        case SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_START);
            break;
        case SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_ARRAY_SIZE_END);
            break;
        case SCRIPTING_TOKEN_TYPE_SEPARATOR:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_SEPARATOR);
            break;
        case SCRIPTING_TOKEN_TYPE_RESERVED_ID:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_RESERVED_ID);
            break;
        case SCRIPTING_TOKEN_TYPE_SIZE:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_SIZE);
            break;
        case SCRIPTING_TOKEN_TYPE_VAR_META:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_VAR_META);
            break;
        case SCRIPTING_TOKEN_TYPE_FUN_META:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_FUN_META);
            break;
        case SCRIPTING_TOKEN_TYPE_EXE_META:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_EXE_META);
            break;
        case SCRIPTING_TOKEN_TYPE_VAL_META:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_VAL_META);
            break;
        case SCRIPTING_TOKEN_TYPE_REF_META:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_REF_META);
            break;
        case SCRIPTING_TOKEN_TYPE_LIB_META:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_LIB_META);
            break;
        case SCRIPTING_TOKEN_TYPE_IMP_META:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_IMP_META);
            break;
        case SCRIPTING_TOKEN_TYPE_EOF:
            result = NAMEOF(SCRIPTING_TOKEN_TYPE_EOF);
            break;
        default:
            result = "Unknown. How did you do this?";
            break;
    }

    return result;
}


std::string Token::_get_name_of_internal_type(InternalType in_internal_type) {
    std::string result;

    switch (in_internal_type) {
        case SCRIPTING_TOKEN_INTERNAL_TYPE_INVALID:
            result = NAMEOF(SCRIPTING_TOKEN_INTERNAL_TYPE_INVALID);
            break;
        case SCRIPTING_TOKEN_INTERNAL_TYPE_BOOL:
            result = NAMEOF(SCRIPTING_TOKEN_INTERNAL_TYPE_BOOL);
            break;
        case SCRIPTING_TOKEN_INTERNAL_TYPE_INT:
            result = NAMEOF(SCRIPTING_TOKEN_INTERNAL_TYPE_INT);
            break;
        case SCRIPTING_TOKEN_INTERNAL_TYPE_FLOAT:
            result = NAMEOF(SCRIPTING_TOKEN_INTERNAL_TYPE_FLOAT);
            break;
        case SCRIPTING_TOKEN_INTERNAL_TYPE_STRING:
            result = NAMEOF(SCRIPTING_TOKEN_INTERNAL_TYPE_STRING);
            break;
        case SCRIPTING_TOKEN_INTERNAL_TYPE_SIZE:
            result = NAMEOF(SCRIPTING_TOKEN_INTERNAL_TYPE_SIZE);
            break;
        default:
            result = "Unknown. How did you do this?";
            break;
    }

    return result;
}


bool Token::operator==(const Token& rhs) const {
    bool result = false;
    result = _type == rhs._type;

    switch (_type) {
        case SCRIPTING_TOKEN_TYPE_BOOL:
            result = result && get_value_bool() == get_value_bool();
            break;
        case SCRIPTING_TOKEN_TYPE_INT:
            result = result && get_value_int() == get_value_int();
            break;
        case SCRIPTING_TOKEN_TYPE_FLOAT:
            result = result && get_value_float() == get_value_float();
            break;
        default:
            result = result && get_value_string() == get_value_string();
            break;
    }

    return result;
}


bool Token::operator!=(const Token& rhs) const {
    return !(*this == rhs);
}


Token::operator std::string() const {
    if (_internal_type == SCRIPTING_TOKEN_INTERNAL_TYPE_STRING) {
        return std::string(
                R"({"_value": ")"
                + get_value_string()
                + R"(", "_internal_type": )"
                + std::to_string(_internal_type)
                + R"(, "_type": )"
                + std::to_string(_type)
                + R"(})"
        );
    } else {
        return std::string(
                R"({"_value": )"
                + get_value_string()
                + R"(, "_internal_type": )"
                + std::to_string(_internal_type)
                + R"(, "_type": )"
                + std::to_string(_type)
                + R"(})"
        );
    }
}


std::ostream& operator<<(std::ostream& lhs, const Token& rhs) {
    lhs << R"({"_value": ")"
    << rhs.get_value_string()
    << R"(", "_internal_type": ")"
    << Token::_get_name_of_internal_type(rhs._internal_type)
    << R"(", "_type": ")"
    << Token::_get_name_of_type(rhs._type)
    << R"("})";

    return lhs;
}


void Token::_copy(const Token& rhs) {
    if (&rhs != this) {
        _type = rhs._type;
        _internal_type = rhs._internal_type;
        _string_size = rhs._string_size;
        switch (_internal_type) {
            case SCRIPTING_TOKEN_INTERNAL_TYPE_BOOL:
                _value_bool = rhs._value_bool;
                break;
            case SCRIPTING_TOKEN_INTERNAL_TYPE_INT:
                _value_int = rhs._value_int;
                break;
            case SCRIPTING_TOKEN_INTERNAL_TYPE_FLOAT:
                _value_float = rhs._value_float;
                break;
            case SCRIPTING_TOKEN_INTERNAL_TYPE_STRING:
                std::free(_value_string);
                _value_string = new char[_string_size];
                std::strcpy(_value_string, rhs._value_string);
                break;
            default:
                //todo:: should be impossible to be here
                break;
        }
    }
}

}
}
