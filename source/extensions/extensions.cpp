//
// Created by rfish on 7/17/2024.
//

#include "scripting/extensions/extensions.hpp"


namespace Koi {
namespace Scripting {

std::ostream& operator<<(std::ostream& lhs, const std::vector<Token>& rhs) {
    for (const Token& token : rhs) {
        lhs << token << '\n';
    }

    return lhs;
}

} // Scripting
} // Koi