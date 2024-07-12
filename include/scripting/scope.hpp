//
// Created by rfish on 7/11/2024.
//

#ifndef KOI_SCRIPTING_SCOPE_HPP
#define KOI_SCRIPTING_SCOPE_HPP


#include "scripting/variant.hpp"


#include <string>
#include <unordered_map>
#include <vector>


namespace Koi {
namespace Scripting {

class Scope {
protected:
    unsigned int _next_available_id = 0u;
    std::vector<Scope*> _params;
    std::vector<Scope*> _children;
    std::unordered_map<std::string, unsigned int> _id_map;

    Variant _return_value;

public:
    void add_declaration();//todo::
};

} // Scripting
} // Koi


#endif //KOI_SCRIPTING_SCOPE_HPP
