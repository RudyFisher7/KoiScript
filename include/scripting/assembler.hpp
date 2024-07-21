//
// Created by rfish on 7/20/2024.
//


#ifndef KOI_SCRIPTING_ASSEMBLER_HPP
#define KOI_SCRIPTING_ASSEMBLER_HPP


#include "scripting/abstract_syntax_tree/node.hpp"
#include "scripting/runtime/type_defs.hpp"

#include <map>
#include <memory>
#include <vector>


namespace Koi {
namespace Scripting {

class Assembler {
public:
    enum Error : int {
        SCRIPTING_ASSEMBLER_ERROR_MIN = 0,
        SCRIPTING_ASSEMBLER_ERROR_OK = SCRIPTING_ASSEMBLER_ERROR_MIN,
        SCRIPTING_ASSEMBLER_ERROR_SIZE
    };

    Error assemble(
            const std::shared_ptr<Ast::Node> ast_tree,
            std::map<std::string, Runtime::Id>& out_memory_map,
            std::vector<std::shared_ptr<Ast::Node>>& out_memory
    ) const;
};

} // Scripting
} // Koi


#endif //KOI_SCRIPTING_ASSEMBLER_HPP
