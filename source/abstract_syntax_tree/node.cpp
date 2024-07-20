//
// Created by rfish on 7/17/2024.
//


#include "scripting/abstract_syntax_tree/node.hpp"

#include <utility>


namespace Koi {
namespace Scripting {
namespace Ast {


std::ostream& operator<<(std::ostream& lhs, const AstNode& rhs) {
    rhs.print(lhs);

    return lhs;
}


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
    lhs << "{\"_class:\": \"Execute\", \"executing_key\": \"" << executing_key << "\", \"args\": [";

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


ValueMeta::ValueMeta(Variant in_value) : value(std::move(in_value)) {

}


void ValueMeta::print(std::ostream& lhs) const {
    lhs << "{\"_class:\": \"Value\", \"value\": " << value << " todo::}";
}

} // Ast
} // Scripting
} // Koi