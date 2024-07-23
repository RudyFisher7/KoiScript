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


#ifndef KOI_SCRIPTING_GLOBAL_ENVIRONMENT_HPP
#define KOI_SCRIPTING_GLOBAL_ENVIRONMENT_HPP


#include "scripting/runtime/environment.hpp"

#include "scripting/runtime/error.hpp"
#include "scripting/type.hpp"
#include "variable.hpp"


namespace Koi {
namespace Scripting {
namespace Runtime {

class GlobalEnvironment: public Environment {
public:
    Error exe(const std::string& key, const std::vector<std::shared_ptr<Ast::Node>>& args) const;

protected:
    Error print(const Runtime::Variable& value) const;

};

} // Runtime
} // Scripting
} // Koi

#endif //KOI_SCRIPTING_GLOBAL_ENVIRONMENT_HPP
