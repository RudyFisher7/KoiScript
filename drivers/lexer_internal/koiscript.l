/* decl.l */
/* Definition section */

%{

#include "lexer_internal/token_type.h"


int yyline_index = 1;
char yyfile_path[256];

%}

%%

##[^(##)\n]*##    return KOI_SCRIPT_TOKEN_TYPE_DOCUMENTATION_COMMENT;
#[^#\n]*#    return KOI_SCRIPT_TOKEN_TYPE_COMMENT;
[ \t\r]+         return KOI_SCRIPT_TOKEN_TYPE_WHITE_SPACE;
\n              { ++yyline_index; return KOI_SCRIPT_TOKEN_TYPE_NEW_LINE; }
<<EOF>>         return KOI_SCRIPT_TOKEN_TYPE_EOF;
null            return KOI_SCRIPT_TOKEN_TYPE_NULL_LITERAL;
false           return KOI_SCRIPT_TOKEN_TYPE_BOOL_FALSE_LITERAL;
true            return KOI_SCRIPT_TOKEN_TYPE_BOOL_TRUE_LITERAL;
\'[^\']*\'      return KOI_SCRIPT_TOKEN_TYPE_CHAR_LITERAL;
[-]?[0-9]+       return KOI_SCRIPT_TOKEN_TYPE_INT_LITERAL;
[0-9]+u                 return KOI_SCRIPT_TOKEN_TYPE_UINT_LITERAL;
[-]?[0-9]+\.[0-9]+       return KOI_SCRIPT_TOKEN_TYPE_FLOAT_LITERAL;
[0-9]+\.[0-9]+u         return KOI_SCRIPT_TOKEN_TYPE_UFLOAT_LITERAL;
\"[^\"\n]*\"              return KOI_SCRIPT_TOKEN_TYPE_STRING_LITERAL;
var         return KOI_SCRIPT_TOKEN_TYPE_VAR;
func        return KOI_SCRIPT_TOKEN_TYPE_FUNC;
class       return KOI_SCRIPT_TOKEN_TYPE_CLASS;
library     return KOI_SCRIPT_TOKEN_TYPE_LIBRARY;
object_t    return KOI_SCRIPT_TOKEN_TYPE_CLASS_OBJECT;
bool_t      return KOI_SCRIPT_TOKEN_TYPE_CLASS_BOOL;
char_t      return KOI_SCRIPT_TOKEN_TYPE_CLASS_CHAR;
number_t    return KOI_SCRIPT_TOKEN_TYPE_CLASS_NUMBER;
int_t       return KOI_SCRIPT_TOKEN_TYPE_CLASS_INT;
uint_t      return KOI_SCRIPT_TOKEN_TYPE_CLASS_UINT;
float_t     return KOI_SCRIPT_TOKEN_TYPE_CLASS_FLOAT;
ufloat_t    return KOI_SCRIPT_TOKEN_TYPE_CLASS_UFLOAT;
string_t    return KOI_SCRIPT_TOKEN_TYPE_CLASS_STRING;
[a-zA-Z\_][a-zA-Z0-9\_]*\_t return KOI_SCRIPT_TOKEN_TYPE_CLASS_TYPE_NAME;
\(                          return KOI_SCRIPT_TOKEN_TYPE_GROUPING_START;
\)                          return KOI_SCRIPT_TOKEN_TYPE_GROUPING_END;
\{                          return KOI_SCRIPT_TOKEN_TYPE_BODY_START;
\}                          return KOI_SCRIPT_TOKEN_TYPE_BODY_END;
\<                          return KOI_SCRIPT_TOKEN_TYPE_GENERIC_START;
\>                          return KOI_SCRIPT_TOKEN_TYPE_GENERIC_END;
\.                          return KOI_SCRIPT_TOKEN_TYPE_OPERATOR_MEMBER_ACCESS;
:                           return KOI_SCRIPT_TOKEN_TYPE_OPERATOR_INHERITANCE;
::                          return KOI_SCRIPT_TOKEN_TYPE_OPERATOR_SCOPE;
&                           return KOI_SCRIPT_TOKEN_TYPE_OPERATOR_REFERENCE;
return                      return KOI_SCRIPT_TOKEN_TYPE_OPERATOR_RETURN;
,                           return KOI_SCRIPT_TOKEN_TYPE_SEPARATOR;
;                           return KOI_SCRIPT_TOKEN_TYPE_DELIMITER;
[a-zA-Z\_][a-zA-Z0-9\_]*    return KOI_SCRIPT_TOKEN_TYPE_IDENTIFIER;
.                           return KOI_SCRIPT_TOKEN_TYPE_UNRECOGNIZED;

%%

/* User code section */
int yywrap() {
    yyline_index = 1;
    return KOI_SCRIPT_TOKEN_TYPE_EOF;
}
