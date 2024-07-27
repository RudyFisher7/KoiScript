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


#include "scripting/runtime/meta/print.hpp"

#include "scripting/runtime/variant/variable.hpp"

#include <ostream>


namespace Koi {
namespace Scripting {
namespace Runtime {

std::string Print::get_key() const {
    return "print";
}


Error Print::run(IMeta::Args arguments, std::shared_ptr<IVariant>& out_result) {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;

    IMeta::Args empty_args;
    for (auto& argument: arguments) {//fixme::
        std::shared_ptr<IVariant> argument_result;
        result = argument->run(empty_args, argument_result);

        if (result == SCRIPTING_RUNTIME_ERROR_OK) {
            std::cout << argument_result->get_c_string();
        }
    }

    std::cout << std::endl;

    out_result = std::unique_ptr<Variable>();

    return result;
}

} // Runtime
} // Scripting
} // Koi