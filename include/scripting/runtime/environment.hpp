//
// Created by rfish on 7/20/2024.
//

#ifndef KOI_SCRIPTING_RUNTIME_ENVIRONMENT_HPP
#define KOI_SCRIPTING_RUNTIME_ENVIRONMENT_HPP


#include "type_defs.hpp"

#include <map>
#include <memory>
#include <string>


namespace Koi {
namespace Scripting {
namespace Runtime {

class Environment {
public:
    std::shared_ptr<Environment> parent_environment;
    std::map<std::string, Id> declarations;
    std::map<Id, Id> locals;//fixme::
};

} // Runtime
} // Scripting
} // Koi


#endif //KOI_SCRIPTING_RUNTIME_ENVIRONMENT_HPP
