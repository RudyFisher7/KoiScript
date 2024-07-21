//
// Created by rfish on 7/20/2024.
//

#include "scripting/assembler.hpp"


namespace Koi {
namespace Scripting {

Assembler::Error Assembler::assemble(
        const std::shared_ptr<Ast::Node> ast_tree,
        std::map<std::string, Runtime::Id>& out_memory_map,
        std::vector<std::shared_ptr<Ast::Node>>& out_memory
) const {
    Error result = SCRIPTING_ASSEMBLER_ERROR_OK;



    return result;
}

} // Scripting
} // Koi