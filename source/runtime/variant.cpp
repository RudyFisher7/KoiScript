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


#include <utility>

#include "scripting/runtime/variant.hpp"


namespace Koi {
namespace Scripting {
namespace Runtime {

Variant::Variant(): _type(SCRIPTING_RUNTIME_VARIANT_TYPE_INVALID), _reference_value(-1) {
    //
}


Variant::Variant(int in_reference): _type(SCRIPTING_RUNTIME_VARIANT_TYPE_REF), _reference_value(in_reference) {
    //
}


Variant::Variant(Variable in_variable): _type(SCRIPTING_RUNTIME_VARIANT_TYPE_VAR), _variable_value(new Variable(std::move(in_variable))) {
    //
}


Variant::Variant(Array in_array): _type(SCRIPTING_RUNTIME_VARIANT_TYPE_ARR), _array_value(new Array(std::move(in_array))) {
    //
}


Variant::Variant(Function in_function): _type(SCRIPTING_RUNTIME_VARIANT_TYPE_FUN), _function_value(new Function(std::move(in_function))) {

}


Variant::~Variant() {
    switch (_type) {
        case SCRIPTING_RUNTIME_VARIANT_TYPE_VAR:
            delete _variable_value;
            break;
        case SCRIPTING_RUNTIME_VARIANT_TYPE_ARR:
            delete _array_value;
            break;
        case SCRIPTING_RUNTIME_VARIANT_TYPE_FUN:
            delete _function_value;
            break;
        default:
            // do nothing
            break;
    }
}


Variant::Type Variant::get_type() const {
    return _type;
}


int Variant::get_reference() const {
    return _reference_value;
}


Variable Variant::get_variable() const {
    return *_variable_value;
}


void Variant::get_variable_by_move(Variable& out_result) {

}


Variable& Variant::get_variable_by_reference() {
    return *_variable_value;
}


Array Variant::get_array() const {
    return *_array_value;
}


void Variant::get_array_by_move(Array& out_result) {

}


Array& Variant::get_array_by_reference() {
    return *_array_value;
}


Function Variant::get_function() const {
    return *_function_value;
}


void Variant::get_function_by_move(Function& out_result) {

}


Function& Variant::get_function_by_reference() {
    return *_function_value;
}
} // Runtime
} // Scripting
} // Koi