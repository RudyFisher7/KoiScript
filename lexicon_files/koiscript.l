/* decl.l */
/*  Definition section  */

%{
#include "token.h"

int yyline_index = 1;

%}

%%

   /* Rules section  */
[\t ]+         /* ignore whitespace */
var     return KOI_SCRIPT_TOKEN_TYPE_VAR;
func    return KOI_SCRIPT_TOKEN_TYPE_FUNC;
class   return KOI_SCRIPT_TOKEN_TYPE_CLASS;
object_t     return KOI_SCRIPT_TOKEN_TYPE_CLASS_OBJECT;
bool_t     return KOI_SCRIPT_TOKEN_TYPE_CLASS_BOOL;
char_t     return KOI_SCRIPT_TOKEN_TYPE_CLASS_CHAR;
number_t    return KOI_SCRIPT_TOKEN_TYPE_CLASS_NUMBER;
int_t   return KOI_SCRIPT_TOKEN_TYPE_CLASS_INT;
uint_t   return KOI_SCRIPT_TOKEN_TYPE_CLASS_UINT;
float_t   return KOI_SCRIPT_TOKEN_TYPE_CLASS_FLOAT;
ufloat_t   return KOI_SCRIPT_TOKEN_TYPE_CLASS_UFLOAT;
string_t   return KOI_SCRIPT_TOKEN_TYPE_CLASS_STRING;
[a-zA-Z\_][a-zA-Z0-9\_]*\_t return KOI_SCRIPT_TOKEN_TYPE_CLASS_TYPE_NAME;
\'\'      return KOI_SCRIPT_TOKEN_TYPE_CHAR_LITERAL;
\"\"      return KOI_SCRIPT_TOKEN_TYPE_STRING_LITERAL;
\(      return KOI_SCRIPT_TOKEN_TYPE_GROUPING_START;
\)      return KOI_SCRIPT_TOKEN_TYPE_GROUPING_END;
\{      return KOI_SCRIPT_TOKEN_TYPE_BODY_START;
\}      return KOI_SCRIPT_TOKEN_TYPE_BODY_END;
\<      return KOI_SCRIPT_TOKEN_TYPE_GENERIC_START;
\>      return KOI_SCRIPT_TOKEN_TYPE_GENERIC_END;
\.       return KOI_SCRIPT_TOKEN_TYPE_OPERATOR_MEMBER_ACCESS;
:       return KOI_SCRIPT_TOKEN_TYPE_OPERATOR_INHERITANCE;
::       return KOI_SCRIPT_TOKEN_TYPE_OPERATOR_SCOPE;
&       return KOI_SCRIPT_TOKEN_TYPE_OPERATOR_REFERENCE;
return       return KOI_SCRIPT_TOKEN_TYPE_OPERATOR_RETURN;
,       return KOI_SCRIPT_TOKEN_TYPE_SEPARATOR;
;       return KOI_SCRIPT_TOKEN_TYPE_DELIMITER;
\n      ++yyline_index;
<<EOF>> return KOI_SCRIPT_TOKEN_TYPE_EOF;
[a-zA-Z\_][a-zA-Z0-9\_]* return KOI_SCRIPT_TOKEN_TYPE_IDENTIFIER;
%%

/* User code section */
int yywrap() {
    yyline_index = 1;
    return KOI_SCRIPT_TOKEN_TYPE_EOF;
}
