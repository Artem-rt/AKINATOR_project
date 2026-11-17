#ifndef AKINATOR_H
#define AKINATOR_H

#include <stdio.h>
#include "tree.h"

void guessing_mode (Tree_Node* cur_node);
void expansion_akin_tree (Tree_Node* cur_node);
int determiner_mode (Tree_Node* cur_node, char* find_data);
void choose_mode (Tree* tree);

#endif
