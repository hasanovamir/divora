#include "tree.h"

//--------------------------------------------------------------------------------

void 
PrintNodeInOrder (tree_node_t* node)
{
    DEBUG_ASSERT (node != NULL);

    printf ("(");

    if (node->left_node)
        PrintNodeInOrder (node->left_node);
    
    printf ("%lf", node->node_data);

    if (node->right_node)
        PrintNodeInOrder (node->right_node);
    
    printf (")");
}

//--------------------------------------------------------------------------------

void
PrintNodePreOrder (tree_node_t* node)
{
    DEBUG_ASSERT (node != nullptr);

    printf ("(%lf", node->node_data);

    if (node->left_node) {
        PrintNodePreOrder (node->left_node);
    }

    if (node->right_node) {
        PrintNodePreOrder (node->right_node);
    }

    printf (")");
}

//--------------------------------------------------------------------------------

void
PrintNodePostOrder (tree_node_t* node)
{
    DEBUG_ASSERT (node != nullptr);

    printf ("(");

    if (node->left_node) {
        PrintNodePostOrder (node->left_node);
    }

    if (node->right_node) {
        PrintNodePostOrder (node->right_node);
    }

    printf ("%lf)", node->node_data);
}

//--------------------------------------------------------------------------------

tree_err_t 
FillDotFile (tree_node_t* tree_node, const char* file_name)
{
    DEBUG_ASSERT (file_name != NULL);

    FILE* dot_file = fopen (file_name, "w");
    
    if (dot_file == NULL)
    {
        PRINTERR (TREE_OPEN_FILE_ERR);
        return   (TREE_OPEN_FILE_ERR);
    }

    DotDumpTitle (dot_file);
    DotDumpNode  (dot_file, tree_node);
    DotDumpEdge  (dot_file, tree_node);
    
    fprintf (dot_file, "}\n");

    fclose (dot_file);

    return TREE_SUCCESS;
}

//--------------------------------------------------------------------------------

void 
DotDumpTitle (FILE* dot_file)
{
    DEBUG_ASSERT (dot_file != NULL);

    char title[] = 

R"(digraph ListDump {
    rankdir=TB;
    node [shape=Mrecord, color=black, fontname="Courier"];

    graph [splines=ortho]
    overlap=false;
    
)";

    fprintf (dot_file, "%s", title);
}

//--------------------------------------------------------------------------------

void
DotDumpNode (FILE* dot_file, tree_node_t* node)
{
    DEBUG_ASSERT (dot_file != NULL);
    DEBUG_ASSERT (node     != NULL);

    fprintf (dot_file, "\tnode%d [label=\"{", node->idx);

    fprintf (dot_file, "<VAL> VAL = %lf |", node->node_data);

    fprintf (dot_file, " <ptr> ptr:%p | {<left_node> left_node=%p | <right_node> right_node=%p } }\", color=black, style=filled, fillcolor=lime];\n", 
        node, node->left_node, node->right_node);

    if (node->left_node)
        DotDumpNode (dot_file, node->left_node);
    if (node->right_node)
        DotDumpNode (dot_file, node->right_node);
}

//--------------------------------------------------------------------------------

void 
DotDumpEdge (FILE* dot_file, tree_node_t* node)
{
    DEBUG_ASSERT (dot_file != NULL);

    if (node == NULL)
        return;

    if (node->left_node) {
        fprintf (dot_file, "\tnode%d -> node%d [color=green];\n", node->idx, node->left_node->idx);
        DotDumpEdge (dot_file, node->left_node);
    }

    if (node->right_node) {
        fprintf (dot_file, "\tnode%d -> node%d [color=green];\n", node->idx, node->right_node->idx);
        DotDumpEdge (dot_file, node->right_node);
    }
}

//--------------------------------------------------------------------------------

tree_err_t 
TreeDump (tree_node_t* tree_node)
{
    tree_context.num_calls++;

    char dot_file_name[MAXFILENAMESIZE];
    char svg_file_name[MAXFILENAMESIZE];
    char command[MAXCOMMANDSIZE];
    
    snprintf (dot_file_name, MAXFILENAMESIZE, "dump/dot/%s_%d.dot", "call", tree_context.num_calls);
    snprintf (svg_file_name, MAXFILENAMESIZE, "dump/svg/%s_%d.svg", "call", tree_context.num_calls);
    
    if (FillDotFile (tree_node, dot_file_name))
    {
        return TREE_OPEN_FILE_ERR;
    }

    printf ("\nGenerated DOT file:  %s\n", dot_file_name);
    
    snprintf (command, sizeof(command), "dot -Tsvg %s -o %s", dot_file_name, svg_file_name);
    
    if (system(command) == 0)
    {
        printf ("Generated SVG image: %s\n", svg_file_name);
    }
    else
    {
        PRINTERR (TREE_SYS_FUNC_ERR);
        return   (TREE_SYS_FUNC_ERR);
    }

    if (TreeFillHtml (svg_file_name))
        return TREE_OPEN_FILE_ERR;

    return TREE_SUCCESS;
}

//--------------------------------------------------------------------------------

tree_err_t 
TreeStartFillHtml (void)
{
    FILE* html_file = fopen ("dump/tree_dump.html", "w");

    if (html_file == NULL)
    {
        PRINTERR (TREE_OPEN_FILE_ERR);
        return   (TREE_OPEN_FILE_ERR);
    }

    fprintf (html_file, "<!DOCTYPE html>\n<html>\n<head>\n\t<title>LIST DUMP</title>\n</head>\n<body>\n");

    fclose (html_file);

    return TREE_SUCCESS;
}

//--------------------------------------------------------------------------------

tree_err_t 
TreeFillHtml (const char* file_name)
{
    FILE* html_file = fopen ("dump/tree_dump.html", "a");

    if (html_file == NULL)
    {
        PRINTERR (TREE_OPEN_FILE_ERR);
        return   (TREE_OPEN_FILE_ERR);
    }

    char string[MAXSTRINGSIZE] = "";

    snprintf (string, MAXSTRINGSIZE, "\t<h2>CALL = #%d</h2>\n\t<p>HEAD = %p</p>\n\t<img src=\"%s\">\n\n", 
        tree_context.num_calls, tree_context.head, file_name);

    fprintf (html_file, "%s", string);

    fclose (html_file);

    return TREE_SUCCESS;
}

//--------------------------------------------------------------------------------

tree_err_t 
TreeEndFillHtml (void)
{
    FILE* html_file = fopen ("dump/tree_dump.html", "a");

    if (html_file == NULL)
    {
        PRINTERR (TREE_OPEN_FILE_ERR);
        return   (TREE_OPEN_FILE_ERR);
    }

    fprintf (html_file, "</body>\n</html>");

    fclose (html_file);

    return TREE_SUCCESS;
}

//--------------------------------------------------------------------------------

int 
GetPriority (math_oper_t op)
{
    switch (op) {
        case addition_op:       return 1;
        case difference_op:     return 1;
        case multiplication_op: return 2;
        case division_op:       return 2;
        case exponentiation_op: return 3;
        default:                return 0;
    }
}

//--------------------------------------------------------------------------------