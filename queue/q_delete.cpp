#include "q.h"

//--------------------------------------------------------------------------------

line_data_t
LinePop (line_ctx_t* l_ctx)
{
    assert (l_ctx != nullptr);

    if (l_ctx->first == nullptr) {
        fprintf (stderr, "Error. No element to POP\n");
        return 0;
    }

    line_node_t* first_node = l_ctx->first;

    line_data_t  value = first_node->data;

    if (l_ctx->count != 1) {
    l_ctx->first->next->prev = nullptr;

    l_ctx->first = l_ctx->first->next;
    }
    else {
        l_ctx->first = nullptr;
        l_ctx->last  = nullptr;
    }
    free (first_node);

    l_ctx->count--;

    return value;
}

//--------------------------------------------------------------------------------