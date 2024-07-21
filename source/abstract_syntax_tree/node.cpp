//
// Created by rfish on 7/17/2024.
//


#include "scripting/abstract_syntax_tree/node.hpp"


namespace Koi {
namespace Scripting {
namespace Ast {

std::ostream& operator<<(std::ostream& lhs, const Node& rhs) {
    rhs.print(lhs);

    return lhs;
}

} // Ast
} // Scripting
} // Koi