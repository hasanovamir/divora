#include "q.h"

//--------------------------------------------------------------------------------

void
SearchPosToStayAlive (int count)
{
    line_ctx_t* l_ctx = nullptr;

    LineCtor (&l_ctx);

    for (int i = 0; i < count; i++) {
        LinePush (l_ctx, i + 1);
    }

    while (l_ctx->count > 2) {
        line_data_t first_alive  = LinePop (l_ctx);
        line_data_t second_alive = LinePop (l_ctx);

        LinePop (l_ctx);

        LinePush (l_ctx, first_alive );
        LinePush (l_ctx, second_alive);
    }

    if (l_ctx->count == 2) {
        printf ("Positions to stay alive:\nFirst - %d\nSecond - %d\n", LinePop (l_ctx), LinePop (l_ctx));
    }
    else {
        printf ("Position to stay alive - %d\n", LinePop (l_ctx));
    }

    LineDtor (l_ctx);

    return ;
}

//--------------------------------------------------------------------------------