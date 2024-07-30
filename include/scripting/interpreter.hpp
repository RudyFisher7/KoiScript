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


#ifndef KOI_SCRIPTING_INTERPRETER_HPP
#define KOI_SCRIPTING_INTERPRETER_HPP


#include "scripting/runtime/basic_type.hpp"
#include "scripting/runtime/error.hpp"
#include "scripting/runtime/environment.hpp"
#include "scripting/runtime/instruction.hpp"
#include "scripting/runtime/variant/array.hpp"
#include "scripting/runtime/variant/function.hpp"
#include "scripting/runtime/variant/variable.hpp"

#include <memory>
#include <string>
#include <vector>


namespace Koi {
namespace Scripting {

class Interpreter {
public:
    Interpreter() = default;

    Interpreter(const Interpreter& rhs) = default;
    Interpreter(Interpreter&& rhs) = default;

    ~Interpreter() = default;

    Interpreter& operator=(const Interpreter& rhs) = default;
    Interpreter& operator=(Interpreter&& rhs) = default;


    Runtime::Error interpret(std::shared_ptr<Runtime::Environment> root_environment, std::shared_ptr<Runtime::Instruction> instructions, std::shared_ptr<Runtime::Variable>& out_result) const;


protected:
    Runtime::Error _evaluate_instructions(const std::shared_ptr<Runtime::Environment>& environment, std::shared_ptr<Runtime::Instruction>& instructions, std::shared_ptr<Runtime::Variable>& out_result) const;

    Runtime::Error _make_variable(const std::shared_ptr<Runtime::Environment>& environment, const std::string& key, Runtime::BasicType type) const;
    Runtime::Error _make_array(std::shared_ptr<Runtime::Environment> environment, std::string key, Runtime::BasicType type) const;
    Runtime::Error _make_function(std::shared_ptr<Runtime::Environment> environment, std::string key, Runtime::BasicType return_type, std::vector<Runtime::BasicType> parameter_types) const;
    Runtime::Error _make_library(std::shared_ptr<Runtime::Environment> environment, std::string key) const;

    Runtime::Error _evaluate_get_value(std::shared_ptr<Runtime::Environment> environment, std::shared_ptr<Runtime::Instruction>& instruction, std::shared_ptr<Runtime::Variable>& out_value) const;
    Runtime::Error _get_value(std::shared_ptr<Runtime::Environment> environment, std::string key, std::shared_ptr<Runtime::Variable>& out_value) const;
    Runtime::Error _get_value(std::shared_ptr<Runtime::Environment> environment, std::string key, int index, std::shared_ptr<Runtime::Variable>& out_value) const;
    Runtime::Error _get_value(std::shared_ptr<Runtime::Environment> environment, std::string key, std::shared_ptr<Runtime::Function>& out_value) const;

    Runtime::Error _evaluate_get_reference(std::shared_ptr<Runtime::Environment> environment, std::shared_ptr<Runtime::Instruction>& instruction, std::shared_ptr<Runtime::Variable>& out_reference) const;
    Runtime::Error _get_reference(std::shared_ptr<Runtime::Environment> environment, std::string key, std::shared_ptr<Runtime::Variable>& out_reference) const;
    Runtime::Error _get_reference(std::shared_ptr<Runtime::Environment> environment, std::string key, std::shared_ptr<Runtime::Array>& out_reference) const;
    Runtime::Error _get_reference(std::shared_ptr<Runtime::Environment> environment, std::string key, std::shared_ptr<Runtime::Function>& out_reference) const;

    Runtime::Error _execute(std::shared_ptr<Runtime::Environment> environment, std::string key, std::shared_ptr<Runtime::Variable>& out_result) const;

    Runtime::Error _evaluate_assignment(std::shared_ptr<Runtime::Environment> environment, std::shared_ptr<Runtime::Instruction>& instruction) const;
    Runtime::Error _assign(std::shared_ptr<Runtime::Environment> environment, std::string key, std::shared_ptr<Runtime::Variable> value) const;
    Runtime::Error _assign(std::shared_ptr<Runtime::Environment> environment, std::string key, int index, std::shared_ptr<Runtime::Variable> value) const;
    Runtime::Error _assign(std::shared_ptr<Runtime::Environment> environment, std::string key, std::shared_ptr<Runtime::Array> value) const;
    Runtime::Error _assign(std::shared_ptr<Runtime::Environment> environment, std::string key, std::shared_ptr<Runtime::Function> value) const;

    Runtime::Error _evaluate_import(std::shared_ptr<Runtime::Environment> environment, std::shared_ptr<Runtime::Instruction>& instruction) const;
    Runtime::Error _import_library(std::shared_ptr<Runtime::Environment> environment, std::string key, std::shared_ptr<Runtime::Variable>& out_result) const;
    Runtime::Error _import_library(std::shared_ptr<Runtime::Environment> environment, std::string key, std::string path, std::shared_ptr<Runtime::Variable>& out_result) const;

    Runtime::Error _remove(std::shared_ptr<Runtime::Environment> environment, std::string key, std::shared_ptr<Runtime::Variable>& out_result) const;
};

} // Scripting
} // Koi

#endif //KOI_SCRIPTING_INTERPRETER_HPP
