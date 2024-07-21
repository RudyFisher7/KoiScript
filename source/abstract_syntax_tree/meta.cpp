//
// Created by rfish on 7/20/2024.
//

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