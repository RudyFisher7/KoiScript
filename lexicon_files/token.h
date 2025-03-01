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


#ifndef KOISCRIPT_TOKEN_H
#define KOISCRIPT_TOKEN_H

enum KoiScriptTokenType {
    KOI_SCRIPT_TOKEN_TYPE_INVALID = -1,
    KOI_SCRIPT_TOKEN_TYPE_MIN = 0,

    // statement starters
    KOI_SCRIPT_TOKEN_TYPE_VAR = KOI_SCRIPT_TOKEN_TYPE_MIN,
    KOI_SCRIPT_TOKEN_TYPE_FUNC,
    KOI_SCRIPT_TOKEN_TYPE_CLASS,

    // expression starter
    KOI_SCRIPT_TOKEN_TYPE_IDENTIFIER,

    // delimiter/separator
    KOI_SCRIPT_TOKEN_TYPE_DELIMITER,
    KOI_SCRIPT_TOKEN_TYPE_SEPARATOR,

    // built-in class types
    KOI_SCRIPT_TOKEN_TYPE_CLASS_OBJECT,
    KOI_SCRIPT_TOKEN_TYPE_CLASS_BOOL,
    KOI_SCRIPT_TOKEN_TYPE_CLASS_CHAR,
    KOI_SCRIPT_TOKEN_TYPE_CLASS_NUMBER,
    KOI_SCRIPT_TOKEN_TYPE_CLASS_INT,
    KOI_SCRIPT_TOKEN_TYPE_CLASS_UINT,
    KOI_SCRIPT_TOKEN_TYPE_CLASS_FLOAT,
    KOI_SCRIPT_TOKEN_TYPE_CLASS_UFLOAT,
    KOI_SCRIPT_TOKEN_TYPE_CLASS_STRING,
    KOI_SCRIPT_TOKEN_TYPE_CLASS_TYPE_NAME,

    // literal values
    KOI_SCRIPT_TOKEN_TYPE_CHAR_LITERAL,
    KOI_SCRIPT_TOKEN_TYPE_STRING_LITERAL,

    //
    KOI_SCRIPT_TOKEN_TYPE_GROUPING_START,
    KOI_SCRIPT_TOKEN_TYPE_GROUPING_END,
    KOI_SCRIPT_TOKEN_TYPE_BODY_START,
    KOI_SCRIPT_TOKEN_TYPE_BODY_END,

    // generics
    KOI_SCRIPT_TOKEN_TYPE_GENERIC_START,
    KOI_SCRIPT_TOKEN_TYPE_GENERIC_END,

    // operators
    KOI_SCRIPT_TOKEN_TYPE_OPERATOR_MEMBER_ACCESS,
    KOI_SCRIPT_TOKEN_TYPE_OPERATOR_INHERITANCE,
    KOI_SCRIPT_TOKEN_TYPE_OPERATOR_SCOPE,
    KOI_SCRIPT_TOKEN_TYPE_OPERATOR_REFERENCE,
    KOI_SCRIPT_TOKEN_TYPE_OPERATOR_RETURN,

    // special
    KOI_SCRIPT_TOKEN_TYPE_NEW_LINE,
    KOI_SCRIPT_TOKEN_TYPE_EOF,
    KOI_SCRIPT_TOKEN_TYPE_SIZE
};

struct KoiScriptToken {
    const char* text;
    enum KoiScriptTokenType type;
    const char* file_path;
    const unsigned long line_number;
    const unsigned long column_number;
};

#endif //KOISCRIPT_TOKEN_H
