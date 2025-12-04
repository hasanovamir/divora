#include "tree.h"

//--------------------------------------------------------------------------------

int
main ()
{
    TreeInit ();

    int tree_size = 0;

    scanf ("%d", &tree_size);

    for (int i = 0; i < tree_size; i++) {
        int tree_val = 0;
        scanf ("%d", &tree_val);
        TreeInsert (tree_val);
    }

    TreeDump (tree_context.head);

    UseTree ();

    TreeDestroy ();

    return EXIT_SUCCESS;
}

//--------------------------------------------------------------------------------