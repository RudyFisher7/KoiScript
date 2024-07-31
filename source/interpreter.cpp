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


Runtime::Error Interpreter::_evaluate_instructions(const std::shared_ptr<Runtime::Environment>& environment, Runtime::Instruction* instructions, std::shared_ptr<Runtime::Variable>& out_result) const {
    Runtime::Error result = Runtime::SCRIPTING_RUNTIME_ERROR_OK;

    //fixme:: these cached variables need to be used for something
    std::shared_ptr<Runtime::Variable> value_variable;
    std::shared_ptr<Runtime::Function> value_function;
    std::shared_ptr<Runtime::Array> value_array;

    Runtime::Instruction* current_instruction = instructions;

    while(result == Runtime::SCRIPTING_RUNTIME_ERROR_OK && current_instruction) {
        switch (current_instruction->get_type()) {
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_VAR: {
                auto instruction = static_cast<Runtime::VariableDeclaration*>(current_instruction);
                result = _make_variable(environment, instruction->get_key(), instruction->get_data_type());
            }
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_ARR: {
                auto instruction = static_cast<Runtime::ArrayDeclaration*>(current_instruction);
                result = _make_array(environment, instruction->get_key(), instruction->get_data_type());
            }
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_FUN: {
                auto instruction = static_cast<Runtime::FunctionDeclaration*>(current_instruction);
                result = _make_function(
                        environment, instruction->get_key(),
                        instruction->get_data_type(),
                        instruction->get_parameter_types()
                );
            }
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_ASN_VAR: {
                auto instruction = static_cast<Runtime::VariableAssignment*>(current_instruction);
                result = environment->assign_var(instruction->get_key(), *instruction->get_value());
            }
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_ASN_ARR: {
                auto instruction = static_cast<Runtime::ArrayElementAssignment*>(current_instruction);
                result = environment->assign_var(instruction->get_key(), *instruction->get_value(), instruction->get_index());
            }
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_ASN_FUN: {
                auto instruction = static_cast<Runtime::FunctionAssignment*>(current_instruction);
                result = environment->assign_fun(instruction->get_key(), *instruction->get_value());
            }
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_LIB_KOI:
                result = _make_library(environment, current_instruction->get_key());
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_VAL_VAR: //todo:: this value is needed for something...
                value_variable = environment->get_var_val(current_instruction->get_key());
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_VAL_FUN: //todo:: this value is needed for something...
                value_function = environment->get_fun_val(current_instruction->get_key());
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_REF_VAR: //todo:: this reference is needed for something...
                value_variable = environment->get_var_ref(current_instruction->get_key());
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_REF_ARR: //todo:: this reference is needed for something...
                value_array = environment->get_arr_ref(current_instruction->get_key());
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_REF_FUN: //todo:: this reference is needed for something...
                value_function = environment->get_fun_ref(current_instruction->get_key());
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_EXE_NATIVE: //todo:: the result here is needed for something...
                result = _execute_native(Runtime::Environment::make_child_environment(environment), current_instruction->get_key(), out_result);
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_EXE_KOI: //todo:: the result here is needed for something...
                result = _execute_koi(Runtime::Environment::make_child_environment(environment), current_instruction->get_key(), out_result);//todo:: this function enters the function's body and calls this function recursively
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_RET_VAR: //todo:: the result here is needed for something...
                //todo:: implement evaluation of return variable
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_RET_ARR: //todo:: the result here is needed for something... need to know return type of Function executing so can enter the correct evaluate_instructions() function
//                out_result = fixme::
                result = Runtime::SCRIPTING_RUNTIME_ERROR_UNSUPPORTED_INSTRUCTION;
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_RET_FUN: //todo:: the result here is needed for something...
//                out_result = fixme::
                result = Runtime::SCRIPTING_RUNTIME_ERROR_UNSUPPORTED_INSTRUCTION;
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_IMP_NATIVE:
                result = _import_library(environment, current_instruction->get_key());
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_IMP_KOI: {
                auto instruction = static_cast<Runtime::ImportLibraryKoi*>(current_instruction);
                result = _import_library(environment, instruction->get_key(), instruction->get_path());
            }
                break;
            case Runtime::Instruction::SCRIPTING_RUNTIME_INSTRUCTION_TYPE_META_REM:
                result = _remove(environment, current_instruction->get_key());
                break;
            default:
                result = Runtime::SCRIPTING_RUNTIME_ERROR_UNRECOGNIZED_INSTRUCTION;
                break;
        }

        current_instruction = current_instruction->get_next();
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