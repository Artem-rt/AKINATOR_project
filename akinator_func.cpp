#ifndef AKINATOR_FUNC_CPP
#define AKINATOR_FUNC_CPP

#include <stdio.h>
#include "tree.h"
#include <assert.h>
#include <string.h>
#include "akinator.h"

void guessing_mode (Tree_Node* cur_node)
{
    assert (cur_node);

    int flag_stop = -1;

    while (flag_stop != 1)
    {
        char answer [512] = { };

        printf ("Is it: %s?\n", cur_node -> data);
        printf ("answer: ___\b\b\b");
        scanf ("%s", answer);

        if (cur_node -> left_child_node == NULL && cur_node -> right_child_node == NULL)
        {
            flag_stop = 1;
            if (!strcasecmp (answer, "yes"))
            {
                printf ("I've done it! You're so predictable :)\n");

            } else if (!strcasecmp (answer, "no"))
            {
                printf ("You're so unpredictable and stuffy\n");
                expansion_akin_tree (cur_node);
            } else
            {
                printf ("you gave uncorrectable answer, try again\n");
            }
        } else
        {
            if (!strcasecmp (answer, "yes"))
            {
                printf ("Hahaha, I knew it!\n");
                cur_node = cur_node -> left_child_node;

            } else if (!strcasecmp (answer, "no"))
            {
                printf ("Well, of course, surprise me.\n");
                cur_node = cur_node -> right_child_node;
            } else
            {
                printf ("you gave uncorrectable answer, try again\n");
            }
        }
    }
}

void expansion_akin_tree (Tree_Node* cur_node)
{
    assert (cur_node);

    char new_elem [512] = { };
    char difference [512] = { };
    Tree_Node* new_node = NULL;
    Tree_Node* old_node = NULL;

    printf ("Ok, say me, who was it? ___\b\b\b");
    while (getchar () != '\n');
    fgets (new_elem, 512, stdin);
    new_elem [strlen(new_elem) - 1] = '\0';

    create_node (&new_node, new_elem);
    create_node (&old_node, cur_node -> data);

    printf ("very interesting (no). And How does %s differ from %s? ___\b\b\b", old_node -> data, new_node -> data);

    fgets (difference, 512, stdin);
    difference [strlen(difference) - 1] = '\0';

    for (int i = 0; cur_node -> data [i] != '\0'; i ++)
    {
        cur_node -> data [i] = '\0';
    }

    strcpy (cur_node -> data, difference);

    cur_node -> left_child_node = new_node;
    cur_node -> right_child_node = old_node;

    new_node -> parent_node = cur_node;
    old_node -> parent_node = cur_node;

    printf ("You're so great! You won't deceive me next time!\n");
}

#endif
