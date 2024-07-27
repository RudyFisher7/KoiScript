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


#include "scripting/runtime/meta/var.hpp"

#include <utility>


namespace Koi {
namespace Scripting {
namespace Runtime {

Var::Var(std::string in_key, std::shared_ptr<Environment> in_environment):
        IEnv(std::move(in_key), std::move(in_environment)) {
}


std::string Var::get_key() const {
    return _key;
}


Error Var::run(IMeta::Args arguments, Variant& out_result) const {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;

    bool declaration_result = _environment->register_declaration(_key);

    if (!declaration_result) {
        result = SCRIPTING_RUNTIME_ERROR_ALREADY_EXISTS;
    }

    return result;
}

} // Runtime
} // Scripting
} // Koi