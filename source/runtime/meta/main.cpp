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


#include "scripting/runtime/meta/main.hpp"


namespace Koi {
namespace Scripting {
namespace Runtime {

Main::Main(std::vector<std::shared_ptr<const IMeta>> body_meta_instructions):
        _body_meta_instructions(body_meta_instructions) {
}


std::string Main::get_key() const {
    return "main";
}


Error Main::run(std::shared_ptr<const Environment> environment, Variant& out_result) const {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;

    auto it = _body_meta_instructions.cbegin();
    auto end = _body_meta_instructions.cend();
    while (result == SCRIPTING_RUNTIME_ERROR_OK && it != end) {
        result = it->get()->run(environment, out_result);
        ++it;
    }

    out_result = Variant(Variable(0));

    return result;
}

} // Runtime
} // Scripting
} // Koi