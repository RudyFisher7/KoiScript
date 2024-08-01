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


#include "scripting/runtime/environment.hpp"

#include <utility>


namespace Koi {
namespace Scripting {
namespace Runtime {

std::shared_ptr<Environment> Environment::make_child_environment(const std::shared_ptr<Environment>& in_parent) {
    std::shared_ptr<Environment> result = std::make_shared<Environment>(in_parent);
    return result;
}


Environment::Environment(const std::shared_ptr<Environment>& in_parent):
        _all_declarations(),
        _variables(),
        _arrays(),
        _functions(),
        _parent(in_parent) {

}


std::shared_ptr<Variable> Environment::get_var_val(const std::string& key) const {
    std::shared_ptr<Variable> result;

    if (_variables.find(key) != _variables.end()) {
        result = std::make_shared<Variable>(*_variables.at(key));
    } else {
        std::shared_ptr<Environment> environment = _resolve(key);

        if (environment) {
            result = environment->get_var_val(key);
        }
    }

    return result;
}


std::shared_ptr<Variable> Environment::get_var_ref(const std::string& key) {
    std::shared_ptr<Variable> result;

    if (_variables.find(key) != _variables.end()) {
        result = _variables.at(key);
    } else {
        std::shared_ptr<Environment> environment = _resolve(key);

        if (environment) {
            result = environment->get_var_ref(key);
        }
    }

    return result;
}


std::shared_ptr<Variable> Environment::get_var_val(const std::string& key, unsigned int index) const {
    std::shared_ptr<Variable> result;

    if (_arrays.find(key) != _arrays.end() && _arrays.at(key)->size() > index) {
        result = std::make_shared<Variable>(_arrays.at(key)->at(index));
    } else {
        std::shared_ptr<Environment> environment = _resolve(key);

        if (environment) {
            result = environment->get_var_val(key);
        }
    }

    return result;
}


std::shared_ptr<Array> Environment::get_arr_ref(const std::string& key) {
    std::shared_ptr<Array> result;

    if (_arrays.find(key) != _arrays.end()) {
        result = _arrays.at(key);
    } else {
        std::shared_ptr<Environment> environment = _resolve(key);

        if (environment) {
            result = environment->get_arr_ref(key);
        }
    }

    return result;
}


std::shared_ptr<Function> Environment::get_fun_val(const std::string& key) const {
    std::shared_ptr<Function> result;

    if (_functions.find(key) != _functions.end()) {
        result = std::make_shared<Function>(*_functions.at(key));
    } else {
        std::shared_ptr<Environment> environment = _resolve(key);

        if (environment) {
            result = environment->get_fun_val(key);
        }
    }

    return result;
}


std::shared_ptr<Function> Environment::get_fun_ref(const std::string& key) {
    std::shared_ptr<Function> result;

    if (_functions.find(key) != _functions.end()) {
        result = _functions.at(key);
    } else {
        std::shared_ptr<Environment> environment = _resolve(key);

        if (environment) {
            result = environment->get_fun_ref(key);
        }
    }

    return result;
}


Error Environment::declare_var(const std::string& key, BasicType type) {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;

    if (!_all_declarations.emplace(key, SCRIPTING_ENVIRONMENT_DECLARATION_TYPE_VAR).second) {
        result = SCRIPTING_RUNTIME_ERROR_ALREADY_EXISTS;
    } else {
        _variables.emplace(key, std::make_shared<Variable>(type));
    }

    return result;
}


Error Environment::declare_arr(const std::string& key, BasicType type) {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;

    if (!_all_declarations.emplace(key, SCRIPTING_ENVIRONMENT_DECLARATION_TYPE_ARR).second) {
        result = SCRIPTING_RUNTIME_ERROR_ALREADY_EXISTS;
    } else {
        _arrays.emplace(key, std::make_shared<Array>(type));
    }

    return result;
}


Error Environment::declare_fun(
        const std::string& key,
        BasicType return_type,
        const std::vector<BasicType>& parameter_types
) {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;

    if (!_all_declarations.emplace(key, SCRIPTING_ENVIRONMENT_DECLARATION_TYPE_FUN).second) {
        result = SCRIPTING_RUNTIME_ERROR_ALREADY_EXISTS;
    } else {
        _functions.emplace(
                key,
                std::make_shared<Function>(return_type, parameter_types)
        );
    }

    return result;
}


Error Environment::assign_var(const std::string& key, const Variable& value) {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;

    std::shared_ptr<Variable> variable = get_var_ref(key);

    if (variable) {
        if (variable->is_same_type(value)) {
            *variable = value;
        } else {
            result = SCRIPTING_RUNTIME_ERROR_TYPE_MISMATCH;
        }
    } else {
        result = SCRIPTING_RUNTIME_ERROR_NOT_YET_DECLARED;
    }

    return result;
}


Error Environment::assign_var(const std::string& key, const Variable& value, unsigned int index) {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;

    std::shared_ptr<Array> array = get_arr_ref(key);

    if (!array) {
        result = SCRIPTING_RUNTIME_ERROR_NOT_YET_DECLARED;
    } else if (array->size() <= index) {
        result = SCRIPTING_RUNTIME_ERROR_INDEX_OUT_OF_BOUNDS;
    } else if (array->get_type() != value.get_type()) {
        result = SCRIPTING_RUNTIME_ERROR_TYPE_MISMATCH;
    }

    if (result == SCRIPTING_RUNTIME_ERROR_OK) {
        array->at(index) = value;
    }

    return result;
}


Error Environment::assign_fun(const std::string& key, const Function& value) {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;

    std::shared_ptr<Function> function = get_fun_ref(key);

    if (function) {
        if (function->is_same_type(value)) {
            *function = value;
        } else {
            result = SCRIPTING_RUNTIME_ERROR_TYPE_MISMATCH;
        }
    } else {
        result = SCRIPTING_RUNTIME_ERROR_NOT_YET_DECLARED;
    }

    return result;
}


Error Environment::remove(const std::string& key) {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;

    if (_has_key(key)) {
        switch (_all_declarations.at(key)) {
            case SCRIPTING_ENVIRONMENT_DECLARATION_TYPE_VAR:
                _variables.erase(key);
                break;
            case SCRIPTING_ENVIRONMENT_DECLARATION_TYPE_ARR:
                _arrays.erase(key);
                break;
            case SCRIPTING_ENVIRONMENT_DECLARATION_TYPE_FUN:
                _functions.erase(key);
                break;
            default:
                result = SCRIPTING_RUNTIME_ERROR_TYPE_UNRECOGNIZED;
                break;
        }
    } else {
        std::shared_ptr<Environment> environment = _resolve(key);

        if (environment) {
            result = environment->remove(key);
        }
    }

    return result;
}


void Environment::set_parent_environment(std::shared_ptr<Environment> in_parent) {
    _parent = std::move(in_parent);
}


bool Environment::_has_key(const std::string& key) const {
    bool result = false;

    result = _all_declarations.find(key) != _all_declarations.cend();

    return result;
}


Error Environment::execute_fun(const std::string& key, Ret<Variable>& ret, const Args<Variable>& args) {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;
    std::shared_ptr<Function> function = get_fun_ref(key);

    if (!function) {
        result = SCRIPTING_RUNTIME_ERROR_NOT_YET_DECLARED;
    } else {
        result = (*function)(args, ret);
    }

    return result;
}


std::shared_ptr<Environment> Environment::_resolve(const std::string& key) const {
    std::shared_ptr<Environment> result = _parent;

    while (result && !result->_has_key(key)) {
        result = result->_parent;
    }

    return result;
}

} // Runtime
} // Scripting
} // Koi