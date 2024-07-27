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

#include "scripting/runtime/meta/exe.hpp"


namespace Koi {
namespace Scripting {
namespace Runtime {

Exe::Exe() {

}


Exe::Exe(std::string in_key, IExe::Body in_body_meta_instructions):
    _key(std::move(in_key)),
    _body_meta_instructions(std::move(in_body_meta_instructions)) {

}


Exe::~Exe() {

}


std::string Exe::get_key() const {
    return _key;
}



Error Exe::run(IMeta::Args arguments, IMeta& out_result) const {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;

    IMeta::Args empty_args;

    unsigned int i = 0u;
//    while (result == SCRIPTING_RUNTIME_ERROR_OK && i < arguments.size()) {
//        result = arguments.at(i)->run(empty_args, *arg_results.at(i));
//        ++i;
//    }

    i = 0u;
    while (result == SCRIPTING_RUNTIME_ERROR_OK && i < _body_meta_instructions.size()) {
        IMeta temp_result;
        result = _body_meta_instructions.at(i)->run(arguments, temp_result);//fixme:: arguments passed in here is implementation detail
        ++i;

        if (i >= _body_meta_instructions.size()) {
            out_result = temp_result;
        }
    }

    return result;
}

} // Runtime
} // Scripting
} // Koi