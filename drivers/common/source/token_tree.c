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


#include "drivers_common/token_tree.h"

#include <stdlib.h>
#include <stdio.h>


void koi_script_print_token_tree_recursive(KoiScriptTokenTreeNode* tree_root, unsigned int level);


KoiScriptTokenTreeNode* koi_script_create_empty_token_tree(void) {
    KoiScriptTokenTreeNode* result = (KoiScriptTokenTreeNode*)malloc(sizeof(KoiScriptTokenTreeNode));

    result->uid = 0ul;
    result->child_count = 0u;
    result->child_capacity = 0u;
    result->children = NULL;
    result->token = (KoiScriptToken){0ul, 0u, NULL};

    return result;
}


void koi_script_free_token_tree(KoiScriptTokenTreeNode* tree_root) {
    if (tree_root == NULL) {
        return;
    }

    for (unsigned int i = 0u; i < tree_root->child_capacity; ++i) {
        koi_script_free_token_tree(tree_root->children[i]);
    }

    free((KoiScriptTokenTreeNode*)tree_root);
    tree_root = NULL;
}


void koi_script_token_tree_append_child(KoiScriptTokenTreeNode* parent, KoiScriptTokenTreeNode* child) {
    if (parent->child_count >= parent->child_capacity) {
        unsigned int new_capacity = ((parent->child_count * 2u) + 1u);
        unsigned int new_size = sizeof(KoiScriptTokenTreeNode*) * new_capacity;

        parent->children = (KoiScriptTokenTreeNode**)realloc(parent->children, new_size);
        parent->child_capacity = new_capacity;

        for (unsigned int i = parent->child_count; i < parent->child_capacity; ++i) {
            parent->children[i] = NULL;
        }
    }

    parent->children[parent->child_count] = child;
    ++parent->child_count;
}


void koi_script_print_token_tree(KoiScriptTokenTreeNode* tree_root) {
    if (tree_root == NULL) {
        printf("%s", "(null tree)");
        return;
    }

    koi_script_print_token(&tree_root->token);

    for (unsigned int i = 0u; i < tree_root->child_count; ++i) {
        koi_script_print_token_tree_recursive(tree_root->children[i], 0u);
    }
}


void koi_script_print_token_tree_recursive(KoiScriptTokenTreeNode* tree_root, unsigned int level) {
    for (unsigned int i = 0u; i < level; ++i) {
        printf("-");
    }

    if (tree_root == NULL) {
        printf("%s", "(null tree)");
        return;
    }

    koi_script_print_token(&tree_root->token);

    for (unsigned int i = 0u; i < tree_root->child_count; ++i) {
        koi_script_print_token_tree_recursive(tree_root->children[i], level + 1u);
    }
}
