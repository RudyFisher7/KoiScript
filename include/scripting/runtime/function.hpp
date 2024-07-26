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


#ifndef KOI_SCRIPTING_RUNTIME_FUNCTION_HPP
#define KOI_SCRIPTING_RUNTIME_FUNCTION_HPP


#include "scripting/runtime/error.hpp"
#include "scripting/runtime/variable.hpp"
#include "scripting/type.hpp"

#include <functional>
#include <memory>
#include <vector>


namespace Koi {
namespace Scripting {
namespace Runtime {

class Function final {
private:
    bool _is_built_in = false;
    BasicType _return_type = SCRIPTING_BASIC_TYPE_VOID;
    std::vector<BasicType> _parameter_types;
    std::function<Error(const std::vector<std::shared_ptr<const Variable>>&, Variable&)> _function;

    //todo:: statements

public:
    Function() = default;
    Function(
            bool in_is_built_in,
            BasicType in_return_type,
            std::vector<BasicType> in_parameter_types,
            std::function<Error(const std::vector<std::shared_ptr<const Variable>>&, Variable&)> in_function
    );

    ~Function() = default;


    //todo:: implement
    Function(const Function& rhs);
    Function(Function&& rhs) noexcept;

    Function& operator=(const Function& rhs);
    Function& operator=(Function&& rhs) noexcept;


    Error operator()(const std::vector<std::shared_ptr<const Variable>>& arguments, Variable& out_result) const;

    bool is_built_in() const;


    BasicType get_return_type() const;


    const std::vector<BasicType>& get_parameter_types() const;

};


} // Runtime
} // Scripting
} // Koi

#endif //KOI_SCRIPTING_RUNTIME_FUNCTION_HPP
