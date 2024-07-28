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


#include "scripting/runtime/function.hpp"

#include <utility>


namespace Koi {
namespace Scripting {
namespace Runtime {

Function::Function(Body in_body, Ret in_ret): _body(std::move(in_body)), _ret(std::move(in_ret)) {

}


Function::Function(const Function& rhs) {
    //
}


Function::Function(Function&& rhs) noexcept {
    //
}


Function& Function::operator=(const Function& rhs) {
    //
    return *this;
}


Function& Function::operator=(Function&& rhs) noexcept {
    //
    return *this;
}


Error Function::operator()(const Args& arguments, IMeta& out_result) const {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;

    while (result == SCRIPTING_RUNTIME_ERROR_OK)

    return result;
}


BasicType Function::get_return_type() const {
    return SCRIPTING_RUNTIME_BASIC_TYPE_VOID;
}


//const std::vector<BasicType>& Function::get_parameter_types() const {
//    return _parameter_types;
//}

} // Runtime
} // Scripting
} // Koi