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


AnonymousFunctionCreation : YY_FUNC FunctionSignature YY_BODY_START YY_OPERATOR_RETURN FunctionArgumentExpression YY_DELIMITER YY_BODY_END ;
FunctionSignature : ClassType YY_GROUPING_START YY_GROUPING_END ;

AnonymousVariableCreation : YY_VAR ClassType YY_BODY_START FunctionArguments YY_BODY_END ;

ClassType : YY_CLASS_OBJECT | YY_CLASS_BOOL | YY_CLASS_CHAR | YY_CLASS_INT
    | YY_CLASS_UINT | YY_CLASS_FLOAT | YY_CLASS_UFLOAT | YY_CLASS_STRING
    | YY_CLASS_TYPE_NAME ;

FunctionArgumentExpression : VariableAccess | FunctionCall | AnonymousVariableCreation ;

FunctionCall : YY_IDENTIFIER YY_GROUPING_START YY_GROUPING_END YY_DELIMITER
    | YY_IDENTIFIER YY_GROUPING_START FunctionArguments YY_GROUPING_END YY_DELIMITER
    | YY_IDENTIFIER YY_OPERATOR_MEMBER_ACCESS FunctionCall
    ;

FunctionArguments : FunctionArgumentExpression
    | FunctionArgumentExpression YY_SEPARATOR
    | FunctionArgumentExpression YY_SEPARATOR FunctionArguments
    ;

VariableAccess : YY_IDENTIFIER YY_DELIMITER
    | YY_OPERATOR_REFERENCE YY_IDENTIFIER YY_DELIMITER
    | YY_IDENTIFIER YY_OPERATOR_MEMBER_ACCESS VariableAccess
    | YY_OPERATOR_REFERENCE YY_IDENTIFIER YY_OPERATOR_MEMBER_ACCESS VariableAccess
    ;

%%
