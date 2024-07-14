//
// Created by rfish on 7/13/2024.
//

#ifndef KOI_SCRIPTING_KOI_SCRIPT_HPP
#define KOI_SCRIPTING_KOI_SCRIPT_HPP


#include "scripting/type_defs.hpp"
#include "scripting/variant.hpp"

#include <string>
#include <vector>


namespace Koi {
namespace Scripting {

class KoiScript {
public:
    enum Error: int {
        SCRIPTING_KOI_SCRIPT_ERROR_UNKNOWN = -1,
        SCRIPTING_KOI_SCRIPT_ERROR_MIN = 0,
        SCRIPTING_KOI_SCRIPT_ERROR_OK = SCRIPTING_KOI_SCRIPT_ERROR_MIN,
        SCRIPTING_KOI_SCRIPT_ERROR_SIZE
    };

    static Error function(Id id, std::vector<Variant>& args, Variant& out_result);
    static Error identifier(const std::string& identifier_text, std::vector<Variant>& args, Id& out_result);
    static Error variable(Id id, std::vector<Variant>& args, Variant& out_result);

    static Error assign(Id id, const Variant& source);

    static Error execute(Id id, std::vector<Variant>& args, Variant& out_result);
    static Error reference(Id id, std::vector<Variant>& args, Id& out_result);
    static Error value(Id id, std::vector<Variant>& args, Variant& out_result);
};

} // Scripting
} // Koi


#endif //KOI_SCRIPTING_KOI_SCRIPT_HPP
