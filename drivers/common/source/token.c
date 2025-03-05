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


#include "drivers_common/token.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void koi_script_print_token(KoiScriptToken* token) {
    if (token == NULL) {
        printf("%s", "(null)");
        return;
    }

    printf("{type: %d, line_number: %d, text: %s}", token->type, token->line_number, token->text);
}


char koi_script_to_char(char* text) {
    return text[0u];
}


int koi_script_to_bool(char* text) {
    return atoi(text);
}


int koi_script_to_int(char* text) {
    return atoi(text);
}


unsigned int koi_script_to_uint(char* text) {
    char* end = NULL;
    unsigned int result = strtoul(text, &end, 10);

    return result;
}


float koi_script_to_float(char* text) {
    char* end = NULL;
    float result = strtof(text, &end);

    return result;
}


double koi_script_to_ufloat(char* text) {
    return atof(text);
}


char* koi_script_to_string(char* text) {
    char* result = NULL;

    unsigned int string_length = strlen(text);
    result = (char*)malloc(string_length + 1u);
    result = strcpy(result, text);

    return result;
}
