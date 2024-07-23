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


#include "scripting/runtime/global_environment.hpp"

#include "scripting/log/log.hpp"

#include <ostream>
#include <string>


namespace Koi {
namespace Scripting {
namespace Runtime {

Error GlobalEnvironment::exe(const std::string& key, const std::vector<std::shared_ptr<Ast::Node>>& args) const {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;

    if (key == "print") {
        Runtime::Variable arg;
    }

    return result;
}


Error GlobalEnvironment::print(const Runtime::Variable& value) const {
    Error result = SCRIPTING_RUNTIME_ERROR_OK;

    if (
            value.get_type() == BasicType::SCRIPTING_BASIC_TYPE_VOID
            || value.get_type() == BasicType::SCRIPTING_BASIC_TYPE_INVALID
    ) {
        result = SCRIPTING_RUNTIME_ERROR_TYPE_MISMATCH;
    }

    if (result == SCRIPTING_RUNTIME_ERROR_OK) {
        std::cout << value << std::endl;
    }

    KOI_LOG_IF_NOT(
            result == SCRIPTING_RUNTIME_ERROR_OK,
            std::string("Variant of type: ")
            + std::to_string(value.get_type())
            + std::string(" is invalid for native print() function.")
    );

    return result;
}

} // Runtime
} // Scripting
} // Koi