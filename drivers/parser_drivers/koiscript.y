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

%{
#include "lex.yy.c"
#include <stdio.h>

void yyerror(char * msg);

%}

%token YY_UNRECOGNIZED 257
%token YY_INVALID 258
%token YY_MIN 259
%token YY_VAR 260
%token YY_FUNC 261
%token YY_CLASS 262
%token YY_LIBRARY 263
%token YY_IDENTIFIER 264
%token YY_SEPARATOR 265
%token YY_DELIMITER 266
%token YY_CLASS_OBJECT 267
%token YY_CLASS_BOOL 268
%token YY_CLASS_CHAR 269
%token YY_CLASS_NUMBER 270
%token YY_CLASS_INT 271
%token YY_CLASS_UINT 272
%token YY_CLASS_FLOAT 273
%token YY_CLASS_UFLOAT 274
%token YY_CLASS_STRING 275
%token YY_CLASS_TYPE_NAME 276
%token YY_NULL_LITERAL 277
%token YY_BOOL_FALSE_LITERAL 278
%token YY_BOOL_TRUE_LITERAL 279
%token YY_CHAR_LITERAL 280
%token YY_INT_LITERAL 281
%token YY_UINT_LITERAL 282
%token YY_FLOAT_LITERAL 283
%token YY_UFLOAT_LITERAL 284
%token YY_STRING_LITERAL 285
%token YY_GROUPING_START 286
%token YY_GROUPING_END 287
%token YY_BODY_START 288
%token YY_BODY_END 289
%token YY_GENERIC_START 290
%token YY_GENERIC_END 291
%token YY_OPERATOR_MEMBER_ACCESS 292
%token YY_OPERATOR_INHERITANCE 293
%token YY_OPERATOR_SCOPE 294
%token YY_OPERATOR_REFERENCE 295
%token YY_OPERATOR_RETURN 296
%token YY_COMMENT 297
%token YY_DOCUMENTATION_COMMENT 298
%token YY_WHITE_SPACE 299
%token YY_NEW_LINE 300
%token YY_EOF 301
%token YY_SIZE 302

%%

/*fixme:: ScriptBody */

Script : LibraryDefinition
    | ClassDefinition
    | GenericClassDefinition
    | VariableCreation
    | FunctionCreation
    | FunctionCall
    | VariableAccess
    | Script VariableCreation
    | Script FunctionCreation
    | Script FunctionCall
    | Script VariableAccess
    ;

LibraryDefinition : YY_LIBRARY YY_CLASS_TYPE_NAME YY_BODY_START LibraryBody YY_BODY_END YY_DELIMITER ;
LibraryBody : VariableCreation
    | LibraryBody VariableCreation
    | FunctionCreation
    | LibraryBody FunctionCreation
    | ClassDefinition
    | LibraryBody ClassDefinition
    ;


ClassDefinition : YY_CLASS YY_CLASS_TYPE_NAME YY_OPERATOR_INHERITANCE ClassType YY_BODY_START ClassBody YY_BODY_END YY_DELIMITER ;
ClassBody : VariableCreation
    | ClassBody VariableCreation
    ;

FunctionCreation : YY_FUNC YY_IDENTIFIER FunctionSignature YY_BODY_START FunctionBody YY_OPERATOR_RETURN FunctionArgumentExpression YY_DELIMITER YY_BODY_END YY_DELIMITER ;
AnonymousFunctionCreation : YY_FUNC FunctionSignature YY_BODY_START FunctionBody YY_OPERATOR_RETURN FunctionArgumentExpression YY_DELIMITER YY_BODY_END ;
FunctionBody : VariableAccess
    | FunctionCall
    | FunctionBody VariableAccess
    | FunctionBody FunctionCall
    ;

FunctionArgumentExpression : VariableAccess | FunctionCall | AnonymousVariableCreation | AnonymousFunctionCreation ;
FunctionSignature : AnyType YY_GROUPING_START FunctionParameters YY_GROUPING_END ;
FunctionParameters : AnyType YY_IDENTIFIER
    | MoreFunctionParameters
    ;
MoreFunctionParameters : AnyType YY_IDENTIFIER YY_SEPARATOR
    | MoreFunctionParameters AnyType YY_IDENTIFIER YY_SEPARATOR
    ;

VariableCreation : YY_VAR YY_IDENTIFIER AnyType YY_BODY_START VariableInitializer YY_BODY_END YY_DELIMITER ;
AnonymousVariableCreation : YY_VAR AnyType YY_BODY_START VariableInitializer YY_BODY_END ;
VariableInitializer : VariableInitializerExpression
    | MoreVariableInitializerExpressions
    ;

VariableInitializerExpression : VariableAccess
    | FunctionCall
    | AnonymousVariableCreation
    ;
MoreVariableInitializerExpressions : VariableAccess YY_SEPARATOR
    | FunctionCall YY_SEPARATOR
    | AnonymousVariableCreation YY_SEPARATOR
    | MoreVariableInitializerExpressions VariableAccess YY_SEPARATOR
    | MoreVariableInitializerExpressions FunctionCall YY_SEPARATOR
    | MoreVariableInitializerExpressions AnonymousVariableCreation YY_SEPARATOR
    ;

FunctionCall : ClassMemberAccess YY_GROUPING_START YY_GROUPING_END YY_DELIMITER
    | ClassMemberAccess YY_GROUPING_START FunctionArguments YY_GROUPING_END YY_DELIMITER
    ;

FunctionArguments : FunctionArgumentExpression
    | MoreFunctionArguments FunctionArgumentExpression
    | MoreFunctionArguments
    ;
MoreFunctionArguments : FunctionArgumentExpression YY_SEPARATOR
    | MoreFunctionArguments FunctionArgumentExpression YY_SEPARATOR
    ;

VariableAccess : ClassMemberAccess YY_DELIMITER
    | YY_OPERATOR_REFERENCE ClassMemberAccess YY_DELIMITER
    ;
ClassMemberAccess : YY_IDENTIFIER
    | ClassMemberAccess YY_OPERATOR_MEMBER_ACCESS YY_IDENTIFIER
    ;

AnyType : ClassType
    | ClassType YY_OPERATOR_SCOPE ClassType
    | ClassType YY_OPERATOR_REFERENCE
    | ClassType YY_OPERATOR_SCOPE ClassType YY_OPERATOR_REFERENCE
    | FunctionType
    | FunctionType YY_OPERATOR_REFERENCE
    | ClassType YY_OPERATOR_SCOPE FunctionType
    | ClassType YY_OPERATOR_SCOPE FunctionType YY_OPERATOR_REFERENCE
    ;

FunctionType : ClassType YY_GROUPING_START YY_GROUPING_END
    | ClassType YY_GROUPING_START AnonymousFunctionParameters YY_GROUPING_END
    ;

AnonymousFunctionParameters : AnyType
    | MoreAnonymousFunctionParameters
    ;
MoreAnonymousFunctionParameters : AnyType YY_SEPARATOR
    | MoreAnonymousFunctionParameters AnyType YY_SEPARATOR
    ;

ClassType : YY_CLASS_OBJECT
    | YY_CLASS_BOOL
    | YY_CLASS_CHAR
    | YY_CLASS_INT
    | YY_CLASS_UINT
    | YY_CLASS_FLOAT
    | YY_CLASS_UFLOAT
    | YY_CLASS_STRING
    | YY_CLASS_TYPE_NAME
    ;

GenericClassDefinition : YY_CLASS YY_CLASS_TYPE_NAME YY_GENERIC_START GenericClassTypeParameters YY_GENERIC_END YY_OPERATOR_INHERITANCE GenericClassType YY_BODY_START GenericClassBody YY_BODY_END YY_DELIMITER ;
GenericClassBody : VariableCreation
    | YY_IDENTIFIER YY_IDENTIFIER YY_DELIMITER
    | GenericClassBody VariableCreation
    | GenericClassBody YY_IDENTIFIER YY_IDENTIFIER YY_DELIMITER
    ;

GenericClassTypeParameters : YY_IDENTIFIER
    | YY_IDENTIFIER YY_OPERATOR_INHERITANCE AnyType
    | MoreGenericClassTypeParameters
    ;
MoreGenericClassTypeParameters : YY_IDENTIFIER YY_SEPARATOR
    | YY_IDENTIFIER YY_OPERATOR_INHERITANCE AnyType YY_SEPARATOR
    | MoreGenericClassTypeParameters YY_IDENTIFIER YY_SEPARATOR
    | MoreGenericClassTypeParameters YY_IDENTIFIER YY_OPERATOR_INHERITANCE AnyType YY_SEPARATOR
    ;

GenericClassType : ClassType
    | YY_CLASS_TYPE_NAME YY_GENERIC_START GenericClassTypeArguments YY_GENERIC_END
    ;
GenericClassTypeArguments : GenericClassType
    | MoreGenericClassTypeArguments
    ;
MoreGenericClassTypeArguments : GenericClassType YY_SEPARATOR
    | MoreGenericClassTypeArguments GenericClassType YY_SEPARATOR
    ;

%%

void yyerror(char * msg) {
  fprintf(stderr, msg);
}