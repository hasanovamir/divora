#include "q.h"

//--------------------------------------------------------------------------------

void
PrintLine (line_ctx_t* l_ctx)
{
    if (l_ctx == nullptr) return;

    line_node_t* cur_node = l_ctx->first;

    while (cur_node != nullptr) {
        printf ("%d", cur_node->data);

        cur_node = cur_node->next;

        if (cur_node != nullptr) {
            printf (" -> ");
        }
    }

    printf ("\n");

    return ;
}

//--------------------------------------------------------------------------------

bool
CheckEmptyLine (line_ctx_t* l_ctx)
{
    if (l_ctx == nullptr) {
        return true;
    }

    if (l_ctx->first == nullptr || l_ctx->last == nullptr) {
        return true;
    }

    return false;
}

//--------------------------------------------------------------------------------

void
PrintNodeCount (line_ctx_t* l_ctx)
{
    if (l_ctx == nullptr) {
        return ;
    }

    line_node_t* cur_node = l_ctx->first;

    int node_count = 0;

    while (cur_node != nullptr) {
        node_count++;
        cur_node = cur_node->next;
    }

    if (node_count != l_ctx->count) {
        fprintf (stderr, "ERROR. Invalid node count\n");
    }

    printf ("Current node count is %d\n", node_count);

    return ;
}

//--------------------------------------------------------------------------------