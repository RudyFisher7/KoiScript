/*
 * MIT License
 *
 * Copyright (c) 2024 kiyasui-hito
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#include "scripting/interpreter.hpp"


namespace Koi {
namespace Scripting {

Runtime::Error Interpreter::interpret(std::shared_ptr<Runtime::Environment> root_environment, std::shared_ptr<Runtime::Instruction> instructions, std::shared_ptr<Runtime::Variable>& out_result) const {
    return _evaluate_instructions(root_environment, instructions, out_result);
}


Runtime::Error Interpreter::_evaluate_instructions(const std::shared_ptr<Runtime::Environment>& environment, std::shared_ptr<Runtime::Instruction>& instructions, std::shared_ptr<Runtime::Variable>& out_result) const {
    Runtime::Error result = Runtime::SCRIPTING_RUNTIME_ERROR_OK;

    std::shared_ptr<Runtime::Instruction>& current_instruction = instructions;

    while(result == Runtime::SCRIPTING_RUNTIME_ERROR_OK && current_instruction) {
        switch (current_instruction->type) {
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_VAR:
                result = _make_variable(environment, current_instruction->key, current_instruction->data_type);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_ARR:
                result = _make_array(environment, current_instruction->key, current_instruction->data_type);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_FUN:
                result = _make_function(environment, current_instruction->key, current_instruction->data_type, current_instruction->parameter_types);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_LIB:
                result = _make_library(environment, current_instruction->key);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_VAL:
                result = _evaluate_get_value(environment, current_instruction, out_result);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_REF:
                result = _evaluate_get_reference(environment, current_instruction, out_result);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_ASN:
                result = _evaluate_assignment(environment, current_instruction);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_EXE:
                result = _execute(environment, current_instruction->key, out_result);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_IMP:
                result = _evaluate_import(environment, current_instruction);
                break;
            default:
                result = Runtime::SCRIPTING_RUNTIME_ERROR_UNRECOGNIZED_INSTRUCTION;
                break;
        }

        current_instruction = current_instruction->next;
    }

    return result;
}


Runtime::Error Interpreter::_make_variable(
        const std::shared_ptr<Runtime::Environment>& environment,
        const std::string& key,
        Runtime::BasicType type
) const {
    Runtime::Error result = Runtime::SCRIPTING_RUNTIME_ERROR_OK;

    result = environment->declare_var(key, type);

    return result;
}

} // Scripting
} // Koi