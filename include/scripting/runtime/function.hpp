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
#include "scripting/runtime/variant/variable.hpp"
#include "scripting/runtime/meta/i_meta.hpp"
#include "scripting/runtime/basic_type.hpp"

#include <functional>
#include <memory>
#include <vector>


namespace Koi {
namespace Scripting {
namespace Runtime {

class Function final {
public:
    typedef std::vector<std::shared_ptr<const IMeta>> Args;
    typedef std::vector<std::shared_ptr<const IMeta>> Body;
    typedef std::shared_ptr<const IMeta> Ret;


private:
    Body _body;
    Ret _ret;

    //todo:: statements

public:
    Function() = default;
    Function(Body in_body, Ret in_ret);

    ~Function() = default;


    //todo:: implement
    Function(const Function& rhs);
    Function(Function&& rhs) noexcept;

    Function& operator=(const Function& rhs);
    Function& operator=(Function&& rhs) noexcept;


    Error operator()(const Args& arguments, IMeta& out_result) const;


    BasicType get_return_type() const;//fixme::

//fixme::
//    const std::vector<BasicType>& get_parameter_types() const;

};


} // Runtime
} // Scripting
} // Koi

#endif //KOI_SCRIPTING_RUNTIME_FUNCTION_HPP
