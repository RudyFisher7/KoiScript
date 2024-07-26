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


#ifndef KOI_SCRIPTING_KOI_SCRIPT_HPP
#define KOI_SCRIPTING_KOI_SCRIPT_HPP


#include "scripting/runtime/error.hpp"
#include "scripting/runtime/environment.hpp"
#include "scripting/runtime/data/variant.hpp"

#include <string>
#include <memory>
#include <vector>


namespace Koi {
namespace Scripting {

class KoiScript {
public:

    static Runtime::Error function(int id, const Runtime::Environment& environment);


    static Runtime::Error identifier(const std::string& identifier_text, std::vector<Runtime::Variant>& args, Runtime::Variant& out_result);


    static Runtime::Error variable(int id, std::vector<Runtime::Variant>& args, Runtime::Variant& out_result);


    static Runtime::Error assign(int id, const Runtime::Variant& source);


    static Runtime::Error execute(const std::string& key, const Runtime::Environment& environment, const std::vector<std::shared_ptr<const Runtime::Variable>>& arguments, Runtime::Variable& out_result);


    static Runtime::Error reference(int id, std::vector<Runtime::Variant>& args, int& out_result);


    static Runtime::Error value(int id, std::vector<Runtime::Variant>& args, Runtime::Variant& out_result);
};

} // Scripting
} // Koi


#endif //KOI_SCRIPTING_KOI_SCRIPT_HPP
