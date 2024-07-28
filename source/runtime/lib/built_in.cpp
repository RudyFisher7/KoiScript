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


#include "scripting/runtime/lib/built_in.hpp"

#include <functional>
#include <memory>
#include <string>


namespace Koi {
namespace Scripting {
namespace Runtime {

void BuiltIn::import(std::shared_ptr<Environment> environment) const {
    environment->declare_fun(
            "print",
            SCRIPTING_RUNTIME_BASIC_TYPE_VOID,
            {SCRIPTING_RUNTIME_BASIC_TYPE_TEXT}
    );

    environment->assign_fun(
            "print",
            Function(
                    BuiltIn::print,
                    SCRIPTING_RUNTIME_BASIC_TYPE_VOID,
                    {SCRIPTING_RUNTIME_BASIC_TYPE_TEXT}
            )
    );

    environment->declare_fun(
            "append",
            SCRIPTING_RUNTIME_BASIC_TYPE_VOID,
            {
                    SCRIPTING_RUNTIME_BASIC_TYPE_KEY,
                    SCRIPTING_RUNTIME_BASIC_TYPE_DYNAMIC,
            }
    );

    environment->assign_fun(
            "append",
            Function(
                    std::bind(BuiltIn::append, environment, std::placeholders::_1, std::placeholders::_2),
                    SCRIPTING_RUNTIME_BASIC_TYPE_VOID,
                    {
                            SCRIPTING_RUNTIME_BASIC_TYPE_KEY,
                            SCRIPTING_RUNTIME_BASIC_TYPE_DYNAMIC,
                    }
            )
    );
}


Error BuiltIn::print(const Args<Variable>& args, Ret<Variable>& ret) {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;
    std::cout << args.at(0u)->get_c_string() << std::endl;
    ret->set_value_void();
    return result;
}


Error BuiltIn::append(std::shared_ptr<Environment> environment, const Args<Variable>& args, Ret<Variable>& ret) {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;
    std::shared_ptr<Array> array_ref = environment->get_arr_ref(args.at(0u)->get_string());

    if (array_ref) {
        if (array_ref->get_type() == args.at(1u)->get_type()) {
            array_ref->emplace_back(*args.at(1u));
        } else {
            result = SCRIPTING_RUNTIME_ERROR_TYPE_MISMATCH;
        }
    } else {
        result = SCRIPTING_RUNTIME_ERROR_NOT_YET_DECLARED;
    }

    ret->set_value_void();
    return result;
}

} // Runtime
} // Scripting
} // Koi