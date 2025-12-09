#include "q.h"

//--------------------------------------------------------------------------------

int
LinePush (line_ctx_t* l_ctx, int value)
{
    if (l_ctx == nullptr) {
        fprintf (stderr, "Invalid l_ctx pointer\n");
        return 1; 
    }

    line_node_t* new_node = CreateNode (value);

    if (new_node == nullptr) {
        return 1;
    }

    if (l_ctx->count == 0) {
        l_ctx->first = new_node;
        l_ctx->last  = new_node;
    }
    else {
        new_node->prev = l_ctx->last;

        l_ctx->last->next = new_node;

        l_ctx->last = new_node;
    }

    l_ctx->count++;

    return 0;
}

//--------------------------------------------------------------------------------