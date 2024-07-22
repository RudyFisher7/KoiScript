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


#include "scripting/runtime/type_defs.hpp"
#include "scripting/variant.hpp"

#include <string>
#include <vector>


namespace Koi {
namespace Scripting {

class KoiScript {
public:
    enum Error: int {
        SCRIPTING_KOI_SCRIPT_ERROR_UNKNOWN = -1,
        SCRIPTING_KOI_SCRIPT_ERROR_MIN = 0,
        SCRIPTING_KOI_SCRIPT_ERROR_OK = SCRIPTING_KOI_SCRIPT_ERROR_MIN,
        SCRIPTING_KOI_SCRIPT_ERROR_SIZE
    };

    static Error function(Id id, std::vector<Variant>& args, Variant& out_result);
    static Error identifier(const std::string& identifier_text, std::vector<Variant>& args, Id& out_result);
    static Error variable(Id id, std::vector<Variant>& args, Variant& out_result);

    static Error assign(Id id, const Variant& source);

    static Error execute(Id id, std::vector<Variant>& args, Variant& out_result);
    static Error reference(Id id, std::vector<Variant>& args, Id& out_result);
    static Error value(Id id, std::vector<Variant>& args, Variant& out_result);
};

} // Scripting
} // Koi


#endif //KOI_SCRIPTING_KOI_SCRIPT_HPP
