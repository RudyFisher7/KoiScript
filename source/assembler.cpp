//
// Created by rfish on 7/20/2024.
//

#include "scripting/assembler.hpp"


namespace Koi {
namespace Scripting {

Assembler::Error Assembler::assemble(
        const std::shared_ptr<AstNode> ast_tree,
        std::map<std::string, Koi::Scripting::Id>& out_memory_map,
        std::vector<std::shared_ptr<Koi::Scripting::AstNode>>& out_memory
) const {
    Error result = SCRIPTING_ASSEMBLER_ERROR_OK;



    return result;
}

} // Scripting
} // Koi