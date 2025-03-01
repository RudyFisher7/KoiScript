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


#include "scripting/lexer.hpp"

extern "C" {
#include "lexer_drivers/lexer_driver.h"
#include "../drivers/common/include/drivers_common/token_type.h"
}

#include <iostream>


namespace Koi { namespace Scripting {

Lexer::Error Lexer::lex(const char* script_path, std::vector<Token>& out_tokens) const {
    if (koi_script_lexer_load_script(script_path) != 0) {
        return SCRIPTING_LEXER_ERROR_FAILED_TO_LOAD_FILE;
    }

    Error result = SCRIPTING_LEXER_ERROR_OK;

    int token_type = KOI_SCRIPT_TOKEN_TYPE_INVALID;
    while ((token_type = koi_script_lexer_next()) != KOI_SCRIPT_TOKEN_TYPE_EOF) {

        out_tokens.emplace_back(static_cast<KoiScriptTokenType>(token_type), koi_script_lexer_get_text(), koi_script_lexer_get_file_path(), koi_script_lexer_get_line_index());
    }

    return result;
}


std::string Lexer::get_token_type_name(KoiScriptTokenType type) const {
    return koi_script_lexer_get_token_type_name(type);
}

} // Scripting
} // Koi