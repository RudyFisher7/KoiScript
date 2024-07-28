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


#ifndef KOI_SCRIPTING_RUNTIME_ENVIRONMENT_HPP
#define KOI_SCRIPTING_RUNTIME_ENVIRONMENT_HPP


#include "scripting/runtime/error.hpp"
#include "scripting/runtime/basic_type.hpp"
#include "scripting/runtime/variant/array.hpp"
#include "scripting/runtime/variant/variable.hpp"
#include "scripting/runtime/function.hpp"
#include "scripting/runtime/meta/i_meta.hpp"

#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>


namespace Koi {
namespace Scripting {
namespace Runtime {

class Environment {
protected:
    std::set<std::string> _all_declarations;
    std::map<std::string, std::shared_ptr<Variable>> _variables;
    std::map<std::string, std::shared_ptr<Array>> _arrays;
    std::map<std::string, std::shared_ptr<Function>> _functions;
    std::shared_ptr<Environment> _parent;

public:
    static std::shared_ptr<Environment> make_child_environment(const std::shared_ptr<Environment>& in_parent);

    Environment() = default;
    explicit Environment(const std::shared_ptr<Environment>& in_parent);

    Environment(const Environment& rhs) = default;
    Environment(Environment&& rhs) = default;

    ~Environment() = default;

    Environment& operator=(const Environment& rhs) = default;
    Environment& operator=(Environment&& rhs) = default;

    std::shared_ptr<Variable> get_var_val(const std::string& key) const;
    std::shared_ptr<Variable> get_var_ref(const std::string& key);

    std::shared_ptr<Variable> get_var_val(const std::string& key, int index) const;
    std::shared_ptr<Array> get_arr_ref(const std::string& key);

    std::shared_ptr<Function> get_fun_val(const std::string& key) const;
    std::shared_ptr<Function> get_fun_ref(const std::string& key);

    Error declare_var(const std::string& key, BasicType type);
    Error declare_arr(const std::string& key, BasicType type);
    Error declare_fun(const std::string& key, BasicType return_type, const std::vector<BasicType>& parameter_types);

    Error assign_var(const std::string& key, const Variable& value);
    Error assign_var(const std::string& key, const Variable& value, int index);
    Error assign_fun(const std::string& key, const Function& value);

    Error execute_fun(const std::string& key, Ret<Variable>& ret, const Args<Variable>& args = {});


    void set_parent_environment(std::shared_ptr<Environment> in_parent);

protected:
    bool _has_key(const std::string& key) const;
    std::shared_ptr<Environment> _resolve(const std::string& key) const;
};

} // Runtime
} // Scripting
} // Koi


#endif //KOI_SCRIPTING_RUNTIME_ENVIRONMENT_HPP
