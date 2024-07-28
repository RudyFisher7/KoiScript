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


#ifndef KOI_SCRIPTING_RUNTIME_ARRAY_HPP
#define KOI_SCRIPTING_RUNTIME_ARRAY_HPP


#include "scripting/runtime/basic_type.hpp"
#include "scripting/runtime/variant/variable.hpp"

#include <string>
#include <vector>


namespace Koi {
namespace Scripting {
namespace Runtime {


class Array final: public std::vector<Variable> {
private:
    BasicType _type = SCRIPTING_RUNTIME_BASIC_TYPE_INVALID;

public:
    Array() = default;
    explicit Array(BasicType in_type);

    Array(const Array& rhs) = default;
    Array(Array&& rhs) = default;

    ~Array() = default;

    Array& operator=(const Array& rhs) = default;
    Array& operator=(Array&& rhs) = default;

    BasicType get_type() const;

};

} // Runtime
} // Scripting
} // Koi

#endif //KOI_SCRIPTING_RUNTIME_ARRAY_HPP
