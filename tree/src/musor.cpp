#include "tree.h"

//--------------------------------------------------------------------------------

bool
CheckTreeEmpty (tree_node_t* node)
{
    if (node == nullptr) {
        return true;
    }

    return false;
}

//--------------------------------------------------------------------------------

int
SearchMinValue (tree_node_t* node)
{
    if (!node) {
        return -1;
    }
    
    if (!node->left_node && !node->right_node) {
        return node->node_data;
    }
    
    int min_left  = INT_MAX;
    int min_right = INT_MAX;
    
    if (node->left_node) {
        min_left = SearchMinValue (node->left_node);
    }
    
    if (node->right_node) {
        min_right = SearchMinValue (node->right_node);
    }
    
    return (min_left < min_right) ? min_left : min_right;
}

//--------------------------------------------------------------------------------

int
CountRightNode (tree_node_t* node)
{
    int count = 0;

    if (node->right_node) count++;

    if  (node->left_node ) count += CountRightNode (node->left_node );
    if  (node->right_node) count += CountRightNode (node->right_node);

    return count;
}

//--------------------------------------------------------------------------------

void
ReverseTree (tree_node_t* node)
{
    tree_node_t* left  = node->left_node;
    tree_node_t* right = node->right_node;

    if (node->left_node ) ReverseTree (node->left_node );
    if (node->right_node) ReverseTree (node->right_node);

    node->left_node  = right;
    node->right_node = left;
}

//--------------------------------------------------------------------------------

int
GetTreeDeep (tree_node_t* node, int deep)
{
    if (node == nullptr) return 0;

    deep++;
    
    int max_deep = deep;

    if (node->left_node) 
        max_deep = (max_deep > GetTreeDeep (node->left_node, deep)) ? max_deep : GetTreeDeep (node->left_node, deep); 
    if (node->right_node) 
        max_deep = (max_deep > GetTreeDeep (node->right_node, deep)) ? max_deep : GetTreeDeep (node->right_node, deep); 

    return max_deep;
}

//--------------------------------------------------------------------------------

bool
CheckToBalance (tree_node_t* node)
{
    if (node == nullptr) return true;

    int left_deep  = GetTreeDeep (node->left_node , 0);
    int right_deep = GetTreeDeep (node->right_node, 0);

    if (fabs (left_deep - right_deep) <= 1 && CheckToBalance (node->left_node) && CheckToBalance (node->right_node))
        return true;
    return false;
}

//--------------------------------------------------------------------------------

tree_node_t*
SearchNode (tree_node_t* node, tree_data_t val)
{
    if (node->node_data == val) 
        return node;
    else if (val <= node->node_data && node->left_node)
        return SearchNode (node->left_node, val);
    else if (val > node->node_data && node->right_node)
        return SearchNode (node->right_node, val);

    return nullptr;
}

//--------------------------------------------------------------------------------