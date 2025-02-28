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


#include "scripting/runtime/basic_type.hpp"
#include "scripting/runtime/error.hpp"
#include "scripting/runtime/variant/variable.hpp"

#include <functional>
#include <memory>
#include <vector>


namespace Koi {
namespace Scripting {
namespace Runtime {

template<typename T>
using Args = std::vector<std::shared_ptr<T>>;


template<typename T>
using Ret = std::shared_ptr<T>;


template<typename ArgT, typename RetT>
using Fun = std::function<Error(const Args<ArgT>&, Ret<RetT>&)>;


class Function final: public Fun<Variable, Variable> {
private:
    unsigned int _size;
    BasicType _return_type = SCRIPTING_RUNTIME_BASIC_TYPE_VOID;
    std::vector<BasicType> _parameter_types;


public:
    template<typename T>
    static Ret<T> make_ret(const T& value) {
        return std::make_shared<T>(value);
    }

    Function() = default;
    Function(Fun<Variable, Variable> fn, BasicType  in_return_type, unsigned int in_size);
    Function(BasicType in_return_type, std::vector<BasicType> in_parameter_types);
    Function(Fun<Variable, Variable> fn, BasicType  in_return_type, std::vector<BasicType> in_parameter_types, unsigned int in_size);

    Function(const Function& rhs) = default;
    Function(Function&& rhs) = default;

    ~Function() = default;


    Function& operator=(const Function& rhs) = default;
    Function& operator=(Function&& rhs) = default;

    /**
     * @brief Implements the function call operator.
     * @remarks Hides this class' base class' function call operator.
     * Performs type checks before executing.
     * @param args
     * @param ret
     * @return
     */
    Error operator()(const Args<Variable>& args, Ret<Variable>& ret) const;

    unsigned int get_size() const;
    BasicType get_return_type() const;
    const std::vector<BasicType>& get_parameter_types() const;

    bool is_same_type(const Function& other) const;
};


} // Runtime
} // Scripting
} // Koi

#endif //KOI_SCRIPTING_RUNTIME_FUNCTION_HPP
