//
// Created by rfish on 7/17/2024.
//


#include "../include/scripting/type.hpp"


namespace Koi {
namespace Scripting {


Type::Type(): return_type(SCRIPTING_BASIC_TYPE_INVALID), parameter_types({}) {

}


Type::Type(BasicType in_return_type):
        return_type(in_return_type),
        parameter_types({}) {

}


Type::~Type() {

}


Type::Type(BasicType in_return_type, std::vector<BasicType>&& in_parameter_types):
        return_type(in_return_type),
        parameter_types(std::move(in_parameter_types)) {

}


TypeDecorator* TypeDecorator::get_next_return_type() const {
    return _return_type_decorator;
}
}
}
