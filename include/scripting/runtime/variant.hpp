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


#ifndef KOI_SCRIPTING_RUNTIME_VARIANT_HPP
#define KOI_SCRIPTING_RUNTIME_VARIANT_HPP


#include "scripting/runtime/type_defs.hpp"
#include "scripting/runtime/array.hpp"
#include "scripting/runtime/function.hpp"
#include "scripting/runtime/variable.hpp"


namespace Koi {
namespace Scripting {
namespace Runtime {

class Variant final {
public:
    enum Type: int {
        SCRIPTING_RUNTIME_VARIANT_TYPE_MIN = 0,
        SCRIPTING_RUNTIME_VARIANT_TYPE_VAR = SCRIPTING_RUNTIME_VARIANT_TYPE_MIN,
        SCRIPTING_RUNTIME_VARIANT_TYPE_REF,
        SCRIPTING_RUNTIME_VARIANT_TYPE_ARR,
        SCRIPTING_RUNTIME_VARIANT_TYPE_FUN,
        SCRIPTING_RUNTIME_VARIANT_TYPE_SIZE
    };

private:
    Array _array_value;
    Function _function_value;
    Id _ref_value;
    Variable _variable_value;

public:
    //

};

} // Runtime
} // Scripting
} // Koi

#endif //KOI_SCRIPTING_RUNTIME_VARIANT_HPP
