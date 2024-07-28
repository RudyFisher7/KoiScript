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


#include "scripting/runtime/variant/function.hpp"

#include <utility>


namespace Koi {
namespace Scripting {
namespace Runtime {

Function::Function(
        Fun<Variable, Variable> fn,
        BasicType in_return_type
):
        Fun<Variable, Variable>(std::move(fn)),
        _return_type(in_return_type),
        _parameter_types() {

}


Function::Function(
        BasicType in_return_type,
        std::vector<BasicType> in_parameter_types
):
        Fun<Variable, Variable>(
                [in_return_type](const Args<Variable>&, Ret<Variable>& ret) -> Error {
                    ret = make_ret<Variable>(Variable(in_return_type));
                    return SCRIPTING_RUNTIME_ERROR_OK;
                }
        ),
        _return_type(in_return_type),
        _parameter_types(std::move(in_parameter_types)) {

}


Function::Function(
        Fun<Variable, Variable> fn,
        BasicType in_return_type,
        std::vector<BasicType> in_parameter_types
):
        Fun<Variable, Variable>(std::move(fn)),
        _return_type(in_return_type),
        _parameter_types(std::move(in_parameter_types)) {

}


Error Function::operator()(const Args<Variable>& args, Ret<Variable>& ret) const {//fixme:: add more error info as this stack could be larger than 1
    Error result = SCRIPTING_RUNTIME_ERROR_OK;

    bool is_valid_call = args.size() == _parameter_types.size();//fixme:: support var args and dynamic
    if (!is_valid_call) {
        result = SCRIPTING_RUNTIME_ERROR_WRONG_NUM_ARGS;
    }

    if (is_valid_call && !ret) {
        result = SCRIPTING_RUNTIME_ERROR_RETURN_VARIABLE_NOT_INITIALIZED;
        is_valid_call = false;
    }

    if (is_valid_call) {
        is_valid_call = ret->get_type() == _return_type;

        unsigned int i = 0u;
        while (is_valid_call && i < args.size()) {
            is_valid_call = args.at(i)->get_type() == _parameter_types.at(i);
            ++i;
        }
    }

    if (!is_valid_call) {
        result = SCRIPTING_RUNTIME_ERROR_TYPE_MISMATCH;
    } else {
        result = Fun<Variable, Variable>::operator()(args, ret);
    }

    return result;
}


BasicType Function::get_return_type() const {
    return _return_type;
}


const std::vector<BasicType>& Function::get_parameter_types() const {
    return _parameter_types;
}


bool Function::is_same_type(const Function& other) const {
    bool result = false;

    result = (
            get_return_type() == other.get_return_type()
            && get_parameter_types() == other.get_parameter_types()
    );

    return result;
}

} // Runtime
} // Scripting
} // Koi