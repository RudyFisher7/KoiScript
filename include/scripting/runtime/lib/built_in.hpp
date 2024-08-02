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


#ifndef KOI_SCRIPTING_RUNTIME_BUILT_IN_HPP
#define KOI_SCRIPTING_RUNTIME_BUILT_IN_HPP


#include "scripting/runtime/lib/i_library.hpp"

#include "scripting/runtime/error.hpp"
#include "scripting/runtime/variant/array.hpp"
#include "scripting/runtime/variant/function.hpp"
#include "scripting/runtime/variant/variable.hpp"


namespace Koi {
namespace Scripting {
namespace Runtime {

class BuiltIn final: public ILibrary {
public:
    void import(std::shared_ptr<Environment> environment) const override;

private:
    // control
    static Error cif(std::shared_ptr<Environment> environment, const Args<Variable>& args, Ret<Variable>& ret);
    static Error cwhile(std::shared_ptr<Environment> environment, const Args<Variable>& args, Ret<Variable>& ret);

    // logical
    static Error land(const Args<Variable>& args, Ret<Variable>& ret);
    static Error lor(const Args<Variable>& args, Ret<Variable>& ret);
    static Error lnot(const Args<Variable>& args, Ret<Variable>& ret);
    static Error eq(const Args<Variable>& args, Ret<Variable>& ret);
    static Error gt(const Args<Variable>& args, Ret<Variable>& ret);
    static Error lt(const Args<Variable>& args, Ret<Variable>& ret);
    static Error ge(const Args<Variable>& args, Ret<Variable>& ret);
    static Error le(const Args<Variable>& args, Ret<Variable>& ret);

    // arithmetic, unary
    static Error abs(const Args<Variable>& args, Ret<Variable>& ret);
    static Error neg(const Args<Variable>& args, Ret<Variable>& ret);
    static Error flr(const Args<Variable>& args, Ret<Variable>& ret);
    static Error rnd(const Args<Variable>& args, Ret<Variable>& ret);
    static Error ceil(const Args<Variable>& args, Ret<Variable>& ret);

    // arithmetic, multary
    static Error add(const Args<Variable>& args, Ret<Variable>& ret);
    static Error sub(const Args<Variable>& args, Ret<Variable>& ret);
    static Error mul(const Args<Variable>& args, Ret<Variable>& ret);
    static Error div(const Args<Variable>& args, Ret<Variable>& ret);
    static Error mod(const Args<Variable>& args, Ret<Variable>& ret);

    // bitwise, unary
    static Error bshl(const Args<Variable>& args, Ret<Variable>& ret);
    static Error bshr(const Args<Variable>& args, Ret<Variable>& ret);

    // bitwise, multary
    static Error bor(const Args<Variable>& args, Ret<Variable>& ret);
    static Error bxor(const Args<Variable>& args, Ret<Variable>& ret);
    static Error band(const Args<Variable>& args, Ret<Variable>& ret);
    static Error bnot(const Args<Variable>& args, Ret<Variable>& ret);

    // arrays
    static Error append(std::shared_ptr<Environment> environment, const Args<Variable>& args, Ret<Variable>& ret);
    static Error insert(std::shared_ptr<Environment> environment, const Args<Variable>& args, Ret<Variable>& ret);

    // variable and function info
    static Error size(std::shared_ptr<Environment> environment, const Args<Variable>& args, Ret<Variable>& ret);

    // special
    static Error print(const Args<Variable>& args, Ret<Variable>& ret);
};

} // Runtime
} // Scripting
} // Koi


#endif //KOI_SCRIPTING_RUNTIME_BUILT_IN_HPP
