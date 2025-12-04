#include "tree.h"

//--------------------------------------------------------------------------------

tree_err_t 
MakeNode (tree_node_t** node)
{
    *node = MyAlloc ();

    if (*node == NULL) {
        return TREE_ALLOC_ERR;
    }

    return TREE_SUCCESS;
}

//--------------------------------------------------------------------------------

void 
TreeDeleteBranch (tree_node_t* node)
{
    if (node->left_node) {
        TreeDeleteBranch (node->left_node);
    }

    if (node->right_node) {
        TreeDeleteBranch (node->right_node);
    }

    if (node->prev_node->left_node  == node) node->prev_node->left_node  = nullptr;
    if (node->prev_node->right_node == node) node->prev_node->right_node = nullptr;

    MyFree (node);
}

//--------------------------------------------------------------------------------

tree_err_t 
TreeInsert (tree_data_t val)
{
    if (tree_context.size == 0) {
        tree_node_t* NewNode = MyAlloc ();

        if (NewNode == NULL) {
            PRINTERR (TREE_ALLOC_ERR);
            return   (TREE_ALLOC_ERR);
        }

        NewNode->node_data = val;
        tree_context.head = NewNode;
    }
    else {
        if (TreeAddNode (tree_context.head, val))
            return TREE_ALLOC_ERR;
    }

    return TREE_SUCCESS;
}

//--------------------------------------------------------------------------------

tree_err_t 
TreeAddNode (tree_node_t* Node, tree_data_t val)
{
    DEBUG_ASSERT (Node != NULL);

    if (val <= Node->node_data) {
        if (Node->left_node) {
            TreeAddNode (Node->left_node, val);
        }
        else {
            tree_node_t* NewNode = MyAlloc ();

            if (NewNode == NULL) {
                PRINTERR (TREE_ALLOC_ERR);
                return   (TREE_ALLOC_ERR);
            }

            NewNode->node_data = val;
            NewNode->idx = tree_context.size;
            Node->left_node = NewNode;
            tree_context.size++;
            NewNode->prev_node = Node;
        }
    }
    else {
        if (Node->right_node) {
            TreeAddNode (Node->right_node, val);
        }
        else {
            tree_node_t* NewNode = MyAlloc ();

            if (NewNode == NULL) {
                PRINTERR (TREE_ALLOC_ERR);
                return   (TREE_ALLOC_ERR);
            }

            NewNode->node_data = val;
            NewNode->idx = tree_context.size;
            Node->right_node = NewNode;
            tree_context.size++;
            NewNode->prev_node = Node;
        }
    }

    return TREE_SUCCESS;
}

//--------------------------------------------------------------------------------

void
TreeDelete (tree_data_t val)
{
    tree_node_t* node = SearchNode (tree_context.head, val);

    TreeDeleteBranch (node);
}

//--------------------------------------------------------------------------------