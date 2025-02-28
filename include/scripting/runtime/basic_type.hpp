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


#ifndef KOI_SCRIPTING_TYPE_HPP
#define KOI_SCRIPTING_TYPE_HPP


#include <iostream>
#include <vector>


namespace Koi {
namespace Scripting {
namespace Runtime {

enum BasicType : int {
    SCRIPTING_RUNTIME_BASIC_TYPE_INVALID = -1,
    SCRIPTING_RUNTIME_BASIC_TYPE_MIN = 0,
    SCRIPTING_RUNTIME_BASIC_TYPE_VOID = SCRIPTING_RUNTIME_BASIC_TYPE_MIN,
    SCRIPTING_RUNTIME_BASIC_TYPE_BOOL,
    SCRIPTING_RUNTIME_BASIC_TYPE_INT,
    SCRIPTING_RUNTIME_BASIC_TYPE_FLOAT,
    SCRIPTING_RUNTIME_BASIC_TYPE_TEXT,
    SCRIPTING_RUNTIME_BASIC_TYPE_KEY,//fixme:: remove this, handled only by meta functions
    SCRIPTING_RUNTIME_BASIC_TYPE_NUMERIC,
    SCRIPTING_RUNTIME_BASIC_TYPE_DYNAMIC,
    SCRIPTING_RUNTIME_BASIC_TYPE_ANY,
    SCRIPTING_RUNTIME_BASIC_TYPE_VAR_ARGS,
    SCRIPTING_RUNTIME_BASIC_TYPE_SIZE,
};

}
}
}


#endif //KOI_SCRIPTING_TYPE_HPP
