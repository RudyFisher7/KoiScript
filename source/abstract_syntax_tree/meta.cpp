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


#include "scripting/abstract_syntax_tree/meta.hpp"


namespace Koi {
namespace Scripting {
namespace Ast {

ExecuteMeta::ExecuteMeta() : executing_key(), args({}) {

}


ExecuteMeta::ExecuteMeta(std::string in_executing_key) :
        executing_key(std::move(in_executing_key)),
        args({}) {

}


ExecuteMeta::ExecuteMeta(std::string in_executing_key, TypeDecorator in_type) :
        executing_key(std::move(in_executing_key)),
        args({}) {

}


void ExecuteMeta::print(std::ostream& lhs) const {
    lhs << "{\"_class\": \"Execute\", \"executing_key\": \"" << executing_key << "\", \"args\": [";

    auto it = args.cbegin();
    auto end = args.cend();

    while (it != end) {
        (*it)->print(lhs);
        if ((it + 1u) != end) {
            lhs << ", ";
        }

        ++it;
    }

    lhs << "]}";
}


Runtime::Error ExecuteMeta::evaluate(Variant& out_result) {
    Runtime::Error result = Runtime::SCRIPTING_RUNTIME_ERROR_OK;

    //todo:: get function associated with executing key

    return result;
}


ValueMeta::ValueMeta(Variant in_value) : value(std::move(in_value)) {

}


void ValueMeta::print(std::ostream& lhs) const {
    lhs << "{\"_class\": \"Value\", \"value\": " << value << " todo::}";
}


Runtime::Error ValueMeta::evaluate(Variant& out_result) {
    return Runtime::SCRIPTING_RUNTIME_ERROR_OK;
}

} // Ast
} // Scripting
} // Koi