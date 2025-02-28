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


#include <utility>

#include "scripting/runtime/meta/main.hpp"


namespace Koi {
namespace Scripting {
namespace Runtime {

std::string Main::get_key() const {
    return "main";
}


Error Main::run(IMeta::Args arguments, std::shared_ptr<IVariant>& out_result) {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;

    IMeta::Args cmdln_args;
    if (arguments.size() == 2u) {
        cmdln_args.push_back(arguments.at(0u));
        result = arguments.at(1u)->run(cmdln_args, out_result);

//        IMeta::Args empty_args;
//        Variant commandline_arguments;
//        result = arguments.at(0u)->run(empty_args, commandline_arguments);
//        _environment.register_declaration("cmdln_args");
//        _environment.register_assignment("cmdln_args", std::make_shared<const LitVal>(commandline_arguments));
//
//        ++i;
    } else if (arguments.size() == 1u) {
        result = arguments.at(0u)->run(cmdln_args, out_result);
    }

    return result;
}

} // Runtime
} // Scripting
} // Koi