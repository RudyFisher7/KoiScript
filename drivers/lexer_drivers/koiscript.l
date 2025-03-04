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

/* Definition section */

%{

#include "y.tab.h"


int yyline_index = 1;
char yyfile_path[256];

%}

%option noinput
%option nounput

%%

##[^(##)\n]*##    return YY_DOCUMENTATION_COMMENT;
#[^#\n]*#    return YY_COMMENT;
[ \t\r]+         /* return YY_WHITE_SPACE; */
\n              { ++yyline_index; /* return YY_NEW_LINE; */ }
null            return YY_NULL_LITERAL;
false           return YY_BOOL_FALSE_LITERAL;
true            return YY_BOOL_TRUE_LITERAL;
\'[^\']*\'      return YY_CHAR_LITERAL;
[-]?[0-9]+       return YY_INT_LITERAL;
[0-9]+u                 return YY_UINT_LITERAL;
[-]?[0-9]+\.[0-9]+       return YY_FLOAT_LITERAL;
[0-9]+\.[0-9]+u         return YY_UFLOAT_LITERAL;
\"[^\"\n]*\"              return YY_STRING_LITERAL;
var         return YY_VAR;
func        return YY_FUNC;
class       return YY_CLASS;
library     return YY_LIBRARY;
object_t    return YY_CLASS_OBJECT;
bool_t      return YY_CLASS_BOOL;
char_t      return YY_CLASS_CHAR;
number_t    return YY_CLASS_NUMBER;
int_t       return YY_CLASS_INT;
uint_t      return YY_CLASS_UINT;
float_t     return YY_CLASS_FLOAT;
ufloat_t    return YY_CLASS_UFLOAT;
string_t    return YY_CLASS_STRING;
[a-zA-Z\_][a-zA-Z0-9\_]*\_t return YY_CLASS_TYPE_NAME;
\(                          return YY_GROUPING_START;
\)                          return YY_GROUPING_END;
\{                          return YY_BODY_START;
\}                          return YY_BODY_END;
\<                          return YY_GENERIC_START;
\>                          return YY_GENERIC_END;
\.                          return YY_OPERATOR_MEMBER_ACCESS;
:                           return YY_OPERATOR_INHERITANCE;
::                          return YY_OPERATOR_SCOPE;
&                           return YY_OPERATOR_REFERENCE;
return                      return YY_OPERATOR_RETURN;
,                           return YY_SEPARATOR;
;                           return YY_DELIMITER;
[a-zA-Z\_][a-zA-Z0-9\_]*    return YY_IDENTIFIER;
.                           return YY_UNRECOGNIZED;

%%

/* User code section */
int yywrap() {
    yyline_index = 1;
    return YY_EOF;
}
