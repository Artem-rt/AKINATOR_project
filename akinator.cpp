#include <stdio.h>
#include <fcntl.h>
#include "tree_func.cpp"
#include "tree.h"
#include "akinator.h"
#include "akinator_func.cpp"

int main ()
{
    int akin_file = 0;
    FILE* re_akin_file = NULL;
    Tree akin_tree = { };

    if ((akin_file = open (PREORDER_FILE, O_RDONLY)) == 0)
        assert (0 && "problem with preorder_file\n");

    akin_tree.root_node = parse_preorder_tree (akin_file);

    dump_tree (&akin_tree);

    close (akin_file);

    if((re_akin_file = fopen (PREORDER_FILE, "w")) == NULL)
        assert (0 && "problem with preorder_file\n");

    // guessing_mode (akin_tree.root_node);

    choose_mode (&akin_tree);

    print_tree_preorder (akin_tree.root_node, re_akin_file);

    dump_tree (&akin_tree);

    fclose (re_akin_file);
}
