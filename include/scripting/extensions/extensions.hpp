//
// Created by rfish on 7/17/2024.
//

#ifndef KOI_SCRIPTING_EXTENSIONS_HPP
#define KOI_SCRIPTING_EXTENSIONS_HPP


#include "scripting/token.hpp"

#include <iostream>
#include <vector>


namespace Koi {
namespace Scripting {


std::ostream& operator<<(std::ostream& lhs, const std::vector<Token>& rhs);


} // Scripting
} // Koi

#endif //KOI_SCRIPTING_EXTENSIONS_HPP
