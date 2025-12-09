#include "q.h"

//--------------------------------------------------------------------------------

int
LineCtor (line_ctx_t** l_ctx)
{
    assert (l_ctx != nullptr);

    *l_ctx = (line_ctx_t*) calloc (1, sizeof (line_ctx_t));

    if (*l_ctx == nullptr) {
        fprintf (stderr, "Error. No memory to l_ctx (LineCtor)\n");
        return 1;
    }

    return 0;
}

//--------------------------------------------------------------------------------

line_node_t*
CreateNode (int value)
{
    line_node_t* node = (line_node_t*) calloc (1, sizeof (line_node_t));

    if (node == nullptr) {
        fprintf (stderr, "Error. No memory to newnode (CreateNode)\n");
        return nullptr;
    }

    node->data = value;

    return node;
}

//--------------------------------------------------------------------------------

void
LineDtor (line_ctx_t* l_ctx)
{
    if (l_ctx == nullptr) {
        return ;
    }

    line_node_t* cur_node  = l_ctx   ->first;

    if (l_ctx->count > 1) {
        line_node_t* next_node = cur_node->next;

        while (cur_node != nullptr) {
            next_node = cur_node->next;
            
            free (cur_node);

            cur_node = next_node;
        }
    }
    else {
        free (cur_node);
    }

    free (l_ctx);

    return ;
}

//--------------------------------------------------------------------------------