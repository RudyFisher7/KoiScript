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


#include "scripting/runtime/variant/i_variant.hpp"


namespace Koi {
namespace Scripting {
namespace Runtime {

IVariant::IVariant(IVariant::Type in_type): _variant_type(in_type) {

}


bool IVariant::operator==(const IVariant& rhs) const {
    return _equals(rhs);
}


bool IVariant::operator!=(const IVariant& rhs) const {
    return !_equals(rhs);
}


IVariant::operator bool() const {
    return get_bool();
}


IVariant::operator char() const {
    return get_char();
}


IVariant::operator int() const {
    return get_int();
}


IVariant::operator float() const {
    return get_float();
}


IVariant::operator const char*() const {
    return get_c_string();
}


IVariant::operator std::string() const {
    return get_string();
}


IVariant::Type IVariant::get_variant_type() const {
    return _variant_type;
}


BasicType IVariant::get_type() const {
    return _type;
}

} // Runtime
} // Scripting
} // Koi