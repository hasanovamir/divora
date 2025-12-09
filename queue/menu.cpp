#include "q.h"

//--------------------------------------------------------------------------------

void
UseLine (line_ctx_t* l_ctx)
{
    int action = 0; 
    int val = 0;

    while (1) {
        PrintMenu ();
        scanf ("%d", &action);
        switch (action) {
            case 1:
                scanf ("%d", &val);
                LinePush (l_ctx, val);
                break;
            case 2:
                printf ("Deleted %d\n", LinePop (l_ctx));
                break;
            case 3:
                PrintLine (l_ctx);
                break;
            case 4:
                printf ("line empty status %d\n", CheckEmptyLine (l_ctx));
                break;
            case 5:
                PrintNodeCount (l_ctx);
                break;
            case 6:
                scanf ("%d", &val);
                SearchPosToStayAlive (val);
                break;
            case 7:
                Task_3 ();
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
    printf ("1 - Push\n2 - Pop\n3 - Print line\n4 - Check line to empty\n"
            "5 - Print cur node count\n6 - Pos to stay alive\n7 - Line cat\n8 - end\n");
}

//--------------------------------------------------------------------------------