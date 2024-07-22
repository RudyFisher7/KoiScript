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


#include "../include/scripting/type.hpp"

#include <utility>
#include <string>


namespace Koi {
namespace Scripting {


Type::Type(): return_type(SCRIPTING_BASIC_TYPE_INVALID), parameter_types({}) {

}


Type::Type(BasicType in_return_type):
        return_type(in_return_type),
        array_dimensions(0u),
        parameter_types({}) {

}


Type::~Type() {

}


Type::Type(
        BasicType in_return_type,
        unsigned int in_array_dimensions,
        std::vector<BasicType>&& in_parameter_types
):
        return_type(in_return_type),
        array_dimensions(in_array_dimensions),
        parameter_types(std::move(in_parameter_types)) {

}


std::ostream& operator<<(std::ostream& lhs, const Type& rhs) {
    lhs << "{\"_class:\": \"Type\", \"return_type\": " << std::to_string(rhs.return_type) << ", \"array_dimensions\": " << std::to_string(rhs.array_dimensions) << ", \"parameter_types\": [";

    auto it = rhs.parameter_types.cbegin();
    auto end = rhs.parameter_types.cend();

    while (it != end) {
        lhs << std::to_string(*it);

        if ((it + 1u) != end) {
            lhs << ", ";
        }

        ++it;
    }

    lhs << "]}";

    return lhs;
}


TypeDecorator* TypeDecorator::get_next_return_type() const {
    return _return_type_decorator;
}

}
}
