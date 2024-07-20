//
// Created by rfish on 7/17/2024.
//


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
