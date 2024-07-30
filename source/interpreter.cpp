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

    std::shared_ptr<Runtime::Variable> value_variable;
    std::shared_ptr<Runtime::Function> value_function;
    std::shared_ptr<Runtime::Array> value_array;

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
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_ASN_VAR:
                result = environment->assign_var(current_instruction->key, *current_instruction->value_variable);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_ASN_ARR:
                result = environment->assign_var(current_instruction->key, *current_instruction->value_variable, current_instruction->index);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_ASN_RUN:
                result = environment->assign_fun(current_instruction->key, *current_instruction->value_function);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_LIB_KOI:
                result = _make_library(environment, current_instruction->key);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_VAL_VAR:
                value_variable = environment->get_var_val(current_instruction->key);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_VAL_FUN:
                value_function = environment->get_fun_val(current_instruction->key);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_REF_VAR:
                value_variable = environment->get_var_ref(current_instruction->key);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_REF_ARR:
                value_array = environment->get_arr_ref(current_instruction->key);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_REF_FUN:
                value_function = environment->get_fun_ref(current_instruction->key);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_EXE:
                result = _execute(environment, current_instruction->key, out_result);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_IMP_NATIVE:
                result = _import_library(environment, current_instruction->key, out_result);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_IMP_KOI:
                result = _import_library(environment, current_instruction->key, current_instruction->path, out_result);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_REM:
                result = _remove(environment, current_instruction->key);
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


Runtime::Error Interpreter::_make_array(
        const std::shared_ptr<Runtime::Environment>& environment,
        const std::string& key,
        Runtime::BasicType type
) const {
    Runtime::Error result = Runtime::SCRIPTING_RUNTIME_ERROR_OK;

    result = environment->declare_arr(key, type);

    return result;
}


Runtime::Error Interpreter::_make_function(
        const std::shared_ptr<Runtime::Environment>& environment,
        const std::string& key,
        Runtime::BasicType return_type,
        const std::vector<Runtime::BasicType>& parameter_types
) const {
    Runtime::Error result = Runtime::SCRIPTING_RUNTIME_ERROR_OK;

    result = environment->declare_fun(key, return_type, parameter_types);

    return result;
}


Runtime::Error Interpreter::_make_library(std::shared_ptr<Runtime::Environment> environment, std::string key) const {
    std::cout << "todo:: implement Interpreter::_make_library" << std::endl;
    return Runtime::SCRIPTING_RUNTIME_ERROR_OK;
}

} // Scripting
} // Koi