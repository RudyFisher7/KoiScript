//
// Created by rfish on 7/11/2024.
//

#ifndef KOI_SCRIPTING_SCOPE_HPP
#define KOI_SCRIPTING_SCOPE_HPP


#include <string>
#include <unordered_map>
#include <vector>


namespace Koi {
namespace Scripting {

class Closure {
protected:
    unsigned int _next_available_id = 0u;
    std::vector<Closure*> _params;
    std::vector<Closure*> _children;
    std::unordered_map<std::string, unsigned int> _id_map;

public:
    void add_declaration();//todo::
};

} // Scripting
} // Koi


#endif //KOI_SCRIPTING_SCOPE_HPP
