//
// Created by rfish on 12/28/2023.
//

#include "../include/scripting/variant.hpp"

#include <cstdlib>
#include <iostream>


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


Variant Variant::from_double(double in_value) {
    return Variant(in_value);
}


Variant Variant::from_string(const std::string& in_value) {
    return Variant(in_value);
}


Variant Variant::from_variant(const Variant& rhs) {
    return Variant(rhs);
}


Variant::Variant() : _current_type(Type::SCRIPTING_VARIANT_TYPE_CHAR), _value_char('A') {

}


Variant::Variant(char in_value) : _current_type(Type::SCRIPTING_VARIANT_TYPE_CHAR), _value_char(in_value) {

}


Variant::Variant(int in_value) : _current_type(Type::SCRIPTING_VARIANT_TYPE_INT), _value_int(in_value) {

}


Variant::Variant(float in_value) : _current_type(Type::SCRIPTING_VARIANT_TYPE_FLOAT), _value_float(in_value) {

}


Variant::Variant(double in_value) : _current_type(Type::SCRIPTING_VARIANT_TYPE_DOUBLE), _value_double(in_value) {

}


Variant::Variant(const char* in_value, size_t size) {
    set_value(in_value, size);
}


Variant::Variant(std::string in_value) : _current_type(Type::SCRIPTING_VARIANT_TYPE_STRING), _value_string(nullptr) {
    set_value(in_value);
}


Variant::Variant(const Variant& rhs) {
    switch (rhs._current_type) {
        case SCRIPTING_VARIANT_TYPE_CHAR:
            set_value(rhs._value_char);
            break;
        case SCRIPTING_VARIANT_TYPE_INT:
            set_value(rhs._value_int);
            break;
        case SCRIPTING_VARIANT_TYPE_FLOAT:
            set_value(rhs._value_float);
            break;
        case SCRIPTING_VARIANT_TYPE_DOUBLE:
            set_value(rhs._value_double);
            break;
        case SCRIPTING_VARIANT_TYPE_STRING:
            set_value(rhs.get_string());
            break;
        case SCRIPTING_VARIANT_TYPE_SIZE:
            break;
    }
}


Variant::Variant(Variant&& rhs) {
    switch (rhs._current_type) {
        case SCRIPTING_VARIANT_TYPE_CHAR:
            set_value(rhs._value_char);
            break;
        case SCRIPTING_VARIANT_TYPE_INT:
            set_value(rhs._value_int);
            break;
        case SCRIPTING_VARIANT_TYPE_FLOAT:
            set_value(rhs._value_float);
            break;
        case SCRIPTING_VARIANT_TYPE_DOUBLE:
            set_value(rhs._value_double);
            break;
        case SCRIPTING_VARIANT_TYPE_STRING:
            set_value(rhs.get_string());
            break;
        case SCRIPTING_VARIANT_TYPE_SIZE:
            break;
    }
}


Variant& Variant::operator=(const Variant& rhs) {
    if (this != &rhs) {
        switch (rhs._current_type) {
            case SCRIPTING_VARIANT_TYPE_CHAR:
                set_value(rhs._value_char);
                break;
            case SCRIPTING_VARIANT_TYPE_INT:
                set_value(rhs._value_int);
                break;
            case SCRIPTING_VARIANT_TYPE_FLOAT:
                set_value(rhs._value_float);
                break;
            case SCRIPTING_VARIANT_TYPE_DOUBLE:
                set_value(rhs._value_double);
                break;
            case SCRIPTING_VARIANT_TYPE_STRING:
                set_value(rhs.get_string());
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
            case SCRIPTING_VARIANT_TYPE_CHAR:
                set_value(rhs._value_char);
                break;
            case SCRIPTING_VARIANT_TYPE_INT:
                set_value(rhs._value_int);
                break;
            case SCRIPTING_VARIANT_TYPE_FLOAT:
                set_value(rhs._value_float);
                break;
            case SCRIPTING_VARIANT_TYPE_DOUBLE:
                set_value(rhs._value_double);
                break;
            case SCRIPTING_VARIANT_TYPE_STRING:
                set_value(rhs.get_string());
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


int Variant::get_type() const {
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


Variant::operator double() const {
    return get_double();
}


Variant::operator std::string() const {
    return get_string();
}


char Variant::get_char() const {
    char result = '\0';
    switch (_current_type) {
        case SCRIPTING_VARIANT_TYPE_CHAR:
            result = _value_char;
            break;
        case SCRIPTING_VARIANT_TYPE_INT:
            result = char(_value_int);
            break;
        case SCRIPTING_VARIANT_TYPE_FLOAT:
            result = char(_value_float);
            break;
        case SCRIPTING_VARIANT_TYPE_DOUBLE:
            result = char(_value_double);
            break;
        case SCRIPTING_VARIANT_TYPE_STRING:
            result = _value_string[0u];
            break;
        case SCRIPTING_VARIANT_TYPE_SIZE:
            break;
    }

    return result;
}


int Variant::get_int() const {
    int result = 0;
    switch (_current_type) {
        case SCRIPTING_VARIANT_TYPE_CHAR:
            result = int(_value_char);
            break;
        case SCRIPTING_VARIANT_TYPE_INT:
            result = _value_int;
            break;
        case SCRIPTING_VARIANT_TYPE_FLOAT:
            result = int(_value_float);
            break;
        case SCRIPTING_VARIANT_TYPE_DOUBLE:
            result = int(_value_double);
            break;
        case SCRIPTING_VARIANT_TYPE_STRING:
            result = atoi(_value_string);
            break;
        case SCRIPTING_VARIANT_TYPE_SIZE:
            break;
    }

    return result;
}


float Variant::get_float() const {
    float result = 0.0f;
    switch (_current_type) {
        case SCRIPTING_VARIANT_TYPE_CHAR:
            result = float(_value_char);
            break;
        case SCRIPTING_VARIANT_TYPE_INT:
            result = float(_value_int);
            break;
        case SCRIPTING_VARIANT_TYPE_FLOAT:
            result = _value_float;
            break;
        case SCRIPTING_VARIANT_TYPE_DOUBLE:
            result = float(_value_double);
            break;
        case SCRIPTING_VARIANT_TYPE_STRING:
            result = atof(_value_string);
            break;
        case SCRIPTING_VARIANT_TYPE_SIZE:
            break;
    }

    return result;
}


double Variant::get_double() const {
    double result = 0.0;
    switch (_current_type) {
        case SCRIPTING_VARIANT_TYPE_CHAR:
            result = double(_value_char);
            break;
        case SCRIPTING_VARIANT_TYPE_INT:
            result = double(_value_int);
            break;
        case SCRIPTING_VARIANT_TYPE_FLOAT:
            result = double(_value_float);
            break;
        case SCRIPTING_VARIANT_TYPE_DOUBLE:
            result = _value_double;
            break;
        case SCRIPTING_VARIANT_TYPE_STRING:
            result = atof(_value_string);
            break;
        case SCRIPTING_VARIANT_TYPE_SIZE:
            break;
    }

    return result;
}


std::string Variant::get_string() const {
    std::string result;
    switch (_current_type) {
        case SCRIPTING_VARIANT_TYPE_CHAR:
            result = _value_char;//todo:: verify this is correct
            break;
        case SCRIPTING_VARIANT_TYPE_INT:
            result = std::to_string(_value_int);
            break;
        case SCRIPTING_VARIANT_TYPE_FLOAT:
            result = std::to_string(_value_float);
            break;
        case SCRIPTING_VARIANT_TYPE_DOUBLE:
            result = std::to_string(_value_double);
            break;
        case SCRIPTING_VARIANT_TYPE_STRING:
            result = _value_string;
            break;
        case SCRIPTING_VARIANT_TYPE_SIZE:
            break;
    }

    return result;
}


void Variant::set_value(char value) {
    _destroy_string_if_string();
    _value_char = value;
    _current_type = Type::SCRIPTING_VARIANT_TYPE_CHAR;
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


void Variant::set_value(double value) {
    _destroy_string_if_string();
    _value_double = value;
    _current_type = Type::SCRIPTING_VARIANT_TYPE_DOUBLE;
}


void Variant::set_value(const char* value, size_t size) {
    _value_string = new char[size + 1u];
    memcpy(_value_string, value, size);
    _value_string[size] = '\0';
    _current_type = Type::SCRIPTING_VARIANT_TYPE_STRING;
}


void Variant::set_value(const std::string& value) {
    _set_string_value(value);
    _current_type = Type::SCRIPTING_VARIANT_TYPE_STRING;

}


void Variant::morph(Variant::Type in_type) {
    //todo::
}


bool Variant::_set_string_value(const std::string& in_value) {
    bool result = false;

    _destroy_string_if_string();

    _value_string = new char[in_value.size() + 1];

    size_t size = in_value.copy(_value_string, in_value.size());
    _value_string[in_value.size()] = '\0';

    result = size == in_value.size();

    if (!result) {
        std::cout << "Variant::_set_string_value() error. Characters copied: " << size << ", expected: "
                  << in_value.size()
                  << " Resulting string: " << _value_string << ", original string: " << in_value << std::endl;
    }

    return result;
}


void Variant::_destroy_string_if_string() {
    if (_current_type == Type::SCRIPTING_VARIANT_TYPE_STRING && _value_string != nullptr) {
        free(_value_string);
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


std::ostream& operator<<(std::ostream& lhs, const Variant& rhs) {
    switch (rhs.get_type()) {
        case Variant::SCRIPTING_VARIANT_TYPE_CHAR:
            lhs << rhs.get_char();
            break;
        case Variant::SCRIPTING_VARIANT_TYPE_INT:
            lhs << rhs.get_int();
            break;
        case Variant::SCRIPTING_VARIANT_TYPE_FLOAT:
            lhs << rhs.get_float();
            break;
        case Variant::SCRIPTING_VARIANT_TYPE_DOUBLE:
            lhs << rhs.get_double();
            break;
        case Variant::SCRIPTING_VARIANT_TYPE_STRING:
            lhs << rhs.get_string();
            break;
        case Variant::SCRIPTING_VARIANT_TYPE_SIZE:
            break;
    }

    return lhs;
}


std::string operator+(const Variant& lhs, const std::string& rhs) {
    return lhs.get_string() + rhs;
}


std::string operator+(const std::string& lhs, const Variant& rhs) {
    return lhs + rhs.get_string();
}

}
}