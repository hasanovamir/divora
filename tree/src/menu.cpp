#include "tree.h"

//--------------------------------------------------------------------------------

void
UseTree (void)
{
    int action = 0; 
    int val = 0;

    while (1) {
        PrintMenu ();
        scanf ("%d", &action);
        switch (action) {
            case 1:
                scanf ("%d", &val);
                TreeInsert (val);
                break;
            case 2:
                scanf ("%d", &val);
                TreeDelete (val);
                break;
            case 3:
                printf ("deep = %d\n", GetTreeDeep (tree_context.head, 0));
                break;
            case 4:
                printf ("min val = %d\n", SearchMinValue (tree_context.head));
                break;
            case 5:
                printf ("balance = %d\n", CheckToBalance (tree_context.head));
                break;
            case 6:
                ReverseTree (tree_context.head);
            case 7:
                TreeDump (tree_context.head);
                break;
            case 8:
                return ;
            default : ;
        }
    }
}

//--------------------------------------------------------------------------------

void
PrintMenu (void)
{
    printf ("1 - insert\n2 - delete\n3 - deep\n4 - min val\n5 - balance\n6 - reverse\n7 - dump\n8 - end\n");
}

//--------------------------------------------------------------------------------