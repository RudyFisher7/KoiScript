//
// Created by rfish on 12/28/2023.
//

#include "../include/scripting/variant.hpp"

#include <iostream>
#include <cstring>


namespace Koi {
namespace Scripting {

Variant Variant::from_char(char in_value) {
    return Variant(in_value);
}


Variant Variant::from_int(int in_value) {
    return Variant(in_value);
}


Variant Variant::from_float(float in_value) {
    return Variant(in_value);
}


Variant Variant::from_string(const std::string& in_value) {
    return Variant(in_value);
}


Variant::Variant() : _current_type(Type::SCRIPTING_VARIANT_TYPE_VOID), _value_bool(false) {

}


Variant::Variant(char in_value) : _current_type(Type::SCRIPTING_VARIANT_TYPE_TEXT) {
    set_value(&in_value, 1u);
}


Variant::Variant(int in_value) : _current_type(Type::SCRIPTING_VARIANT_TYPE_INT), _value_int(in_value) {

}


Variant::Variant(float in_value) : _current_type(Type::SCRIPTING_VARIANT_TYPE_FLOAT), _value_float(in_value) {

}


Variant::Variant(const char* in_value, size_t size) {
    set_value(in_value, size);
}


Variant::Variant(std::string in_value) : _current_type(Type::SCRIPTING_VARIANT_TYPE_TEXT), _value_text(nullptr) {
    set_value(in_value);
}


Variant::Variant(const Variant& rhs) {
    switch (rhs._current_type) {
        case SCRIPTING_VARIANT_TYPE_VOID:
            break;
        case SCRIPTING_VARIANT_TYPE_BOOL:
            break;
        case SCRIPTING_VARIANT_TYPE_INT:
            set_value(rhs._value_int);
            break;
        case SCRIPTING_VARIANT_TYPE_FLOAT:
            set_value(rhs._value_float);
            break;
        case SCRIPTING_VARIANT_TYPE_TEXT:
            set_value(rhs.get_string());
            break;
        case SCRIPTING_VARIANT_TYPE_REF:
            break;
        case SCRIPTING_VARIANT_TYPE_SIZE:
            break;
    }
}


Variant::Variant(Variant&& rhs) {
    switch (rhs._current_type) {
        case SCRIPTING_VARIANT_TYPE_VOID:
            break;
        case SCRIPTING_VARIANT_TYPE_BOOL:
            break;
        case SCRIPTING_VARIANT_TYPE_INT:
            set_value(rhs._value_int);
            break;
        case SCRIPTING_VARIANT_TYPE_FLOAT:
            set_value(rhs._value_float);
            break;
        case SCRIPTING_VARIANT_TYPE_TEXT:
            set_value(rhs.get_string());
            break;
        case SCRIPTING_VARIANT_TYPE_REF:
            break;
        case SCRIPTING_VARIANT_TYPE_SIZE:
            break;
    }
}


Variant& Variant::operator=(const Variant& rhs) {
    if (this != &rhs) {
        switch (rhs._current_type) {
            case SCRIPTING_VARIANT_TYPE_VOID:
                break;
            case SCRIPTING_VARIANT_TYPE_BOOL:
                break;
            case SCRIPTING_VARIANT_TYPE_INT:
                set_value(rhs._value_int);
                break;
            case SCRIPTING_VARIANT_TYPE_FLOAT:
                set_value(rhs._value_float);
                break;
            case SCRIPTING_VARIANT_TYPE_TEXT:
                set_value(rhs.get_string());
                break;
            case SCRIPTING_VARIANT_TYPE_REF:
                break;
            case SCRIPTING_VARIANT_TYPE_SIZE:
                break;
        }
    }

    return *this;
}


Variant& Variant::operator=(Variant&& rhs) {
    if (this != &rhs) {
        switch (rhs._current_type) {
            case SCRIPTING_VARIANT_TYPE_VOID:
                break;
            case SCRIPTING_VARIANT_TYPE_BOOL:
                break;
            case SCRIPTING_VARIANT_TYPE_INT:
                set_value(rhs._value_int);
                break;
            case SCRIPTING_VARIANT_TYPE_FLOAT:
                set_value(rhs._value_float);
                break;
            case SCRIPTING_VARIANT_TYPE_TEXT:
                set_value(rhs.get_string());
                break;
            case SCRIPTING_VARIANT_TYPE_REF:
                break;
            case SCRIPTING_VARIANT_TYPE_SIZE:
                break;
        }
    }

    return *this;
}


Variant::~Variant() {
    _destroy_string_if_string();
}


bool Variant::operator==(const Variant& rhs) const {
    bool result = false;
    result = (
//            _current_type == rhs._current_type
//          && get_string() == rhs.get_string()
            get_string() == rhs.get_string()//fixme:: optimize
    );

    return result;
}


bool Variant::operator!=(const Variant& rhs) const {
    bool result = false;

    result = !(*this == rhs);

    return result;
}


Variant::Type Variant::get_type() const {
    return _current_type;
}


Variant::operator char() const {
    return get_char();
}


Variant::operator int() const {
    return get_int();
}


Variant::operator float() const {
    return get_float();
}


Variant::operator std::string() const {
    return get_string();
}


char Variant::get_char() const {
    char result = '\0';
    switch (_current_type) {
        case SCRIPTING_VARIANT_TYPE_INT:
            result = char(_value_int);
            break;
        case SCRIPTING_VARIANT_TYPE_FLOAT:
            result = char(_value_float);
            break;
        case SCRIPTING_VARIANT_TYPE_SIZE:
            break;
    }

    return result;
}


int Variant::get_int() const {
    int result = 0;
    switch (_current_type) {
        case SCRIPTING_VARIANT_TYPE_INT:
            result = _value_int;
            break;
        case SCRIPTING_VARIANT_TYPE_FLOAT:
            result = int(_value_float);
            break;
        case SCRIPTING_VARIANT_TYPE_SIZE:
            break;
    }

    return result;
}


float Variant::get_float() const {
    float result = 0.0f;
    switch (_current_type) {
        case SCRIPTING_VARIANT_TYPE_INT:
            result = float(_value_int);
            break;
        case SCRIPTING_VARIANT_TYPE_FLOAT:
            result = _value_float;
            break;
        case SCRIPTING_VARIANT_TYPE_SIZE:
            break;
    }

    return result;
}


std::string Variant::get_string() const {
    std::string result;
    switch (_current_type) {
        case SCRIPTING_VARIANT_TYPE_VOID:
            result = "\"<void>\"";
            break;
        case SCRIPTING_VARIANT_TYPE_BOOL:
            result = _value_bool ? "true" : "false";
            break;
        case SCRIPTING_VARIANT_TYPE_INT:
            result = std::to_string(_value_int);
            break;
        case SCRIPTING_VARIANT_TYPE_FLOAT:
            result = std::to_string(_value_float);
            break;
        case SCRIPTING_VARIANT_TYPE_TEXT:
            result = _value_text;
            break;
        case SCRIPTING_VARIANT_TYPE_REF:
            break;
    }

    return result;
}


void Variant::set_value(char value) {
    _destroy_string_if_string();
}


void Variant::set_value(int value) {
    _destroy_string_if_string();
    _value_int = value;
    _current_type = Type::SCRIPTING_VARIANT_TYPE_INT;
}


void Variant::set_value(float value) {
    _destroy_string_if_string();
    _value_float = value;
    _current_type = Type::SCRIPTING_VARIANT_TYPE_FLOAT;
}


void Variant::set_value(const char* value, size_t size) {
    _destroy_string_if_string();
    _value_text = new char[size + 1u];
    std::memcpy(_value_text, value, size);
    _value_text[size] = '\0';
    _current_type = Type::SCRIPTING_VARIANT_TYPE_TEXT;
}


void Variant::set_value(const std::string& value) {
    _set_string_value(value);
    _current_type = Type::SCRIPTING_VARIANT_TYPE_TEXT;

}


void Variant::morph(Variant::Type in_type) {
    //todo::
}


std::ostream& operator<<(std::ostream& lhs, const Variant& rhs) {
    lhs << "{\"_class:\": \"Variant\", \"_current_type\": " << std::to_string(rhs._current_type) << ", \"_value\":";

    if (rhs._current_type == Variant::SCRIPTING_VARIANT_TYPE_TEXT) {
        lhs << "\"" << rhs.get_string() << "\"";
    } else {
        lhs << rhs.get_string();
    }

    lhs << "}";

    return lhs;
}


bool Variant::_set_string_value(const std::string& in_value) {
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


void Variant::_destroy_string_if_string() {
    if (_current_type == Type::SCRIPTING_VARIANT_TYPE_TEXT && _value_text != nullptr) {
        free(_value_text);
    }
}


size_t VariantHash::operator()(const Variant& in) const noexcept {
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


std::string operator+(const Variant& lhs, const std::string& rhs) {
    return lhs.get_string() + rhs;
}


std::string operator+(const std::string& lhs, const Variant& rhs) {
    return lhs + rhs.get_string();
}

}
}