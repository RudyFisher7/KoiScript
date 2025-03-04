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


#ifndef KOISCRIPT_TOKEN_TREE_H
#define KOISCRIPT_TOKEN_TREE_H


#include "drivers_common/token.h"


typedef struct koi_script_token_tree_node_t {
    unsigned long uid;
    unsigned int child_count;
    unsigned int child_capacity;
    struct koi_script_token_tree_node_t** children;
    KoiScriptToken token;
} KoiScriptTokenTreeNode;


KoiScriptTokenTreeNode* koi_script_create_empty_token_tree(void);
void koi_script_free_token_tree(KoiScriptTokenTreeNode* tree_root);

void koi_script_token_tree_append_child(KoiScriptTokenTreeNode* parent, KoiScriptTokenTreeNode* child);

void koi_script_print_token_tree(KoiScriptTokenTreeNode* tree_root);


#endif //KOISCRIPT_TOKEN_TREE_H
