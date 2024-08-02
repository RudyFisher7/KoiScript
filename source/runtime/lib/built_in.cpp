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
                    {SCRIPTING_RUNTIME_BASIC_TYPE_TEXT},
                    4u
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
                    },
                    11u
            )
    );

    environment->declare_fun(
            "insert",
            SCRIPTING_RUNTIME_BASIC_TYPE_BOOL,
            {
                    SCRIPTING_RUNTIME_BASIC_TYPE_KEY,
                    SCRIPTING_RUNTIME_BASIC_TYPE_DYNAMIC,
                    SCRIPTING_RUNTIME_BASIC_TYPE_INT,
            }
    );

    environment->assign_fun(
            "insert",
            Function(
                    std::bind(BuiltIn::insert, environment, std::placeholders::_1, std::placeholders::_2),
                    SCRIPTING_RUNTIME_BASIC_TYPE_BOOL,
                    {
                            SCRIPTING_RUNTIME_BASIC_TYPE_KEY,
                            SCRIPTING_RUNTIME_BASIC_TYPE_DYNAMIC,
                            SCRIPTING_RUNTIME_BASIC_TYPE_INT,
                    },
                    16u
            )
    );

    environment->declare_fun(
            "size",
            SCRIPTING_RUNTIME_BASIC_TYPE_INT,
            {
                    SCRIPTING_RUNTIME_BASIC_TYPE_KEY,
            }
    );

    environment->assign_fun(
            "size",
            Function(
                    std::bind(BuiltIn::insert, environment, std::placeholders::_1, std::placeholders::_2),
                    SCRIPTING_RUNTIME_BASIC_TYPE_INT,
                    {
                            SCRIPTING_RUNTIME_BASIC_TYPE_KEY,
                    },
                    25u
            )
    );

    environment->declare_fun(
            "and",
            SCRIPTING_RUNTIME_BASIC_TYPE_BOOL,
            {
                    SCRIPTING_RUNTIME_BASIC_TYPE_VAR_ARGS,
            }
    );

    environment->assign_fun(
            "and",
            Function(
                    std::bind(BuiltIn::land, environment, std::placeholders::_1, std::placeholders::_2),
                    SCRIPTING_RUNTIME_BASIC_TYPE_BOOL,
                    {
                            SCRIPTING_RUNTIME_BASIC_TYPE_VAR_ARGS,
                    },
                    25u
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
    std::shared_ptr<Array> array_ref = environment->get_arr_ref(args.at(0u)->get_c_string());

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


Error BuiltIn::insert(std::shared_ptr<Environment> environment, const Args<Variable>& args, Ret<Variable>& ret) {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;
    std::shared_ptr<Array> array_ref = environment->get_arr_ref(args.at(0u)->get_c_string());

    if (array_ref) {
        if (array_ref->size() <= static_cast<unsigned int>(args.at(2u)->get_int())) {
            result = SCRIPTING_RUNTIME_ERROR_INDEX_OUT_OF_BOUNDS;
        } else if (array_ref->get_type() != args.at(1u)->get_type()) {
            result = SCRIPTING_RUNTIME_ERROR_TYPE_MISMATCH;
        } else {
            auto it = array_ref->cbegin() + args.at(2u)->get_int();
            array_ref->insert(it, *args.at(1u));
            ret->set_value(true);
        }
    } else {
        result = SCRIPTING_RUNTIME_ERROR_NOT_YET_DECLARED;
    }

    if (result != SCRIPTING_RUNTIME_ERROR_OK) {
        ret->set_value(false);
    }

    return result;
}


Error BuiltIn::size(std::shared_ptr<Environment> environment, const Args<Variable>& args, Ret<Variable>& ret) {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;

    std::shared_ptr<Variable> variable_ref;
    std::shared_ptr<Array> array_ref;
    std::shared_ptr<Function> function_ref;
    switch (environment->get_declaration_type(args.at(0u)->get_c_string())) {
        case Environment::SCRIPTING_ENVIRONMENT_DECLARATION_TYPE_VAR:
            variable_ref = environment->get_var_ref(args.at(0u)->get_c_string());
            ret->set_value(static_cast<int>(variable_ref->get_size()));
            break;
        case Environment::SCRIPTING_ENVIRONMENT_DECLARATION_TYPE_ARR:
            array_ref = environment->get_arr_ref(args.at(0u)->get_c_string());
            ret->set_value(static_cast<int>(array_ref->size()));
            break;
        case Environment::SCRIPTING_ENVIRONMENT_DECLARATION_TYPE_FUN:
            function_ref = environment->get_fun_ref(args.at(0u)->get_c_string());
            ret->set_value(static_cast<int>(variable_ref->get_size()));
            break;
        default:
            ret->set_value(-1);
            break;
    }


    if (variable_ref) {
        ret->set_value(static_cast<int>(variable_ref->get_size()));
    } else {
        result = SCRIPTING_RUNTIME_ERROR_NOT_YET_DECLARED;
    }

    return result;
}


Error BuiltIn::land(std::shared_ptr<Environment> environment, const Args<Variable>& args, Ret<Variable>& ret) {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;

    bool is_true = true;

    auto it = args.cbegin();
    auto end = args.cend();
    while (is_true && it != end) {
        is_true = is_true && it->get()->get_bool();
        ++it;
    }

    ret->set_value(is_true);

    return result;
}

} // Runtime
} // Scripting
} // Koi