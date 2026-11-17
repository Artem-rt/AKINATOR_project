#ifndef AKINATOR_FUNC_CPP
#define AKINATOR_FUNC_CPP

#include <stdio.h>
#include "tree.h"
#include <assert.h>
#include <string.h>
#include "akinator.h"

void choose_mode (Tree* tree)
{
    assert (tree);
    int flag_mode = -1;

    printf ("Hello! It's me - Akinator, who know all about you thoughts!\n");
    printf ("Now you must choose, how I'll work with you. If you want to play, press keys: [p] && [Enter]. If you want to"
            " get a definition of the subject, press keys: [d] && [Enter] and then write the name of your subject.\n");
    while (flag_mode == -1)
    {
        char mode [512] = { } ;

        printf ("Choice:__\b\b");
        scanf ("%s", mode);

        if (!strcmp (mode, "p"))
        {
            guessing_mode (tree -> root_node);
            flag_mode = 1;
        } else if (!strcmp (mode, "d"))
        {
            char subject [512] = { } ;
            int stop_trying = 0;
            printf ("Your subject:_____\b\b\b\b\b");
            scanf ("%s", subject);
            while (!determiner_mode (tree -> root_node, subject))
            {
                if (stop_trying) scanf ("%s", subject);
                stop_trying ++ ;
                if (stop_trying == 5) break;
                printf ("I don't no it, try, again\n");
                printf ("Your subject:_____\b\b\b\b\b");
            }
            flag_mode = 1;
        } else
        {
            printf ("I SAD: [p] OR [d]!!! I AM VERY ANGRY!!! TRY AGAIN, silly leather sack!!!\n");
        }
    }
}

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

int determiner_mode (Tree_Node* cur_node, char* find_data)
{
    assert (cur_node);
    assert (find_data);
    int left_child = -1;
    int right_child = -1;

    if (!strcmp(cur_node -> data, find_data))
    {
        int child_print = 1;
        while (cur_node -> parent_node != NULL)
        {
            if (!child_print)
                printf ("[not %s] <-", cur_node -> data);
            else
                printf ("[%s] <-", cur_node -> data);

            if (cur_node == cur_node -> parent_node -> right_child_node)
                child_print = 0;
            else
                child_print = 1;
            cur_node = cur_node -> parent_node;
        }

        if (!child_print)
            printf ("[not %s]\n", cur_node -> data);
        else
            printf ("[%s]\n", cur_node -> data);

        return 1;
    } else
    {
        if (cur_node -> left_child_node)
            left_child = determiner_mode (cur_node -> left_child_node, find_data);

        if (cur_node -> right_child_node)
            right_child = determiner_mode (cur_node -> right_child_node, find_data);
    }

    if (left_child == 1) return 1;
    if (right_child == 1) return 1;
    return 0;

}

#endif
