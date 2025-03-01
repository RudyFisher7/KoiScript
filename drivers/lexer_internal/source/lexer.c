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


#include "lexer_internal/lexer.h"
#include "lexer_internal/token_type.h"

#include "lex.yy.c"

#include <string.h>


#ifndef NAME_OF
#define WAS_NOT_DEFINED 1
#define NAME_OF(x) #x
#endif


int koi_script_lexer_load_script(const char* script_path) {
    int result = -1;

    FILE* script = fopen(script_path, "r");
    if (script != NULL) {
        strcpy(yyfile_path, script_path);
        yyin = script;
        result = 0;
    }

    return result;
}


int koi_script_lexer_next(void) {
    return yylex();
}


const char* koi_script_lexer_get_text(void) {
    return yytext;
}


const char* koi_script_lexer_get_file_path(void) {
    return yyfile_path;
}


int koi_script_lexer_get_line_index(void) {
    return yyline_index;
}


char* koi_script_lexer_get_token_type_name(int type) {
    char buffer[256];
    char* result = buffer;

    enum KoiScriptTokenType t = (enum KoiScriptTokenType)type;

    switch (t) {
        case KOI_SCRIPT_TOKEN_TYPE_UNRECOGNIZED:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_UNRECOGNIZED));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_INVALID:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_INVALID));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_VAR:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_VAR));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_FUNC:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_FUNC));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_CLASS:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_CLASS));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_LIBRARY:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_LIBRARY));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_IDENTIFIER:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_IDENTIFIER));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_SEPARATOR:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_SEPARATOR));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_DELIMITER:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_DELIMITER));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_CLASS_OBJECT:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_CLASS_OBJECT));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_CLASS_BOOL:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_CLASS_BOOL));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_CLASS_CHAR:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_CLASS_CHAR));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_CLASS_NUMBER:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_CLASS_NUMBER));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_CLASS_INT:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_CLASS_INT));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_CLASS_UINT:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_CLASS_UINT));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_CLASS_FLOAT:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_CLASS_FLOAT));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_CLASS_UFLOAT:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_CLASS_UFLOAT));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_CLASS_STRING:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_CLASS_STRING));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_CLASS_TYPE_NAME:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_CLASS_TYPE_NAME));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_NULL_LITERAL:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_NULL_LITERAL));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_BOOL_FALSE_LITERAL:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_BOOL_FALSE_LITERAL));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_BOOL_TRUE_LITERAL:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_BOOL_TRUE_LITERAL));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_CHAR_LITERAL:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_CHAR_LITERAL));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_INT_LITERAL:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_INT_LITERAL));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_UINT_LITERAL:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_UINT_LITERAL));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_FLOAT_LITERAL:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_FLOAT_LITERAL));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_UFLOAT_LITERAL:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_UFLOAT_LITERAL));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_STRING_LITERAL:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_STRING_LITERAL));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_GROUPING_START:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_GROUPING_START));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_GROUPING_END:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_GROUPING_END));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_BODY_START:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_BODY_START));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_BODY_END:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_BODY_END));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_GENERIC_START:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_GENERIC_START));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_GENERIC_END:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_GENERIC_END));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_OPERATOR_MEMBER_ACCESS:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_OPERATOR_MEMBER_ACCESS));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_OPERATOR_INHERITANCE:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_OPERATOR_INHERITANCE));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_OPERATOR_SCOPE:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_OPERATOR_SCOPE));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_OPERATOR_REFERENCE:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_OPERATOR_REFERENCE));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_OPERATOR_RETURN:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_OPERATOR_RETURN));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_COMMENT:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_COMMENT));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_DOCUMENTATION_COMMENT:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_DOCUMENTATION_COMMENT));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_WHITE_SPACE:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_WHITE_SPACE));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_NEW_LINE:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_NEW_LINE));
            break;
        case KOI_SCRIPT_TOKEN_TYPE_EOF:
            strcpy(result, NAME_OF(KOI_SCRIPT_TOKEN_TYPE_EOF));
            break;
        default:
            strcpy(result, "Note a token type");
            break;
    }

    return result;
}

#if WAS_NOT_DEFINED
#undef NAME_OF
#undef WAS_NOT_DEFINED
#endif
