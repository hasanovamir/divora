#include "tree.h"
#include "general_io_file_func.h"


//--------------------------------------------------------------------------------

tree_err_t 
TreeReadDataBase (const char* FileName)
{
    DEBUG_ASSERT (FileName    != NULL);

    int size = get_file_size (FileName);

    if (size == -1) {
        PRINTERR (TREE_SYS_FUNC_ERR);
        return   TREE_SYS_FUNC_ERR;
    }

    char* buffer = (char*) calloc (size, sizeof (char));
    
    if (buffer == nullptr) {
        PRINTERR (TREE_ALLOC_ERR);
        return TREE_ALLOC_ERR;
    }

    if (ReadBuffer (buffer, FileName, size)) {
        return TREE_OPEN_FILE_ERR;
    }

    int pos = 0;

    tree_context.head = TreeReadNode (nullptr, buffer, &pos);

    return TREE_SUCCESS;
}

//--------------------------------------------------------------------------------

tree_err_t 
ReadBuffer (char* buffer, const char* FileName, int size)
{
    DEBUG_ASSERT (buffer   != NULL);
    DEBUG_ASSERT (FileName != NULL);

    FILE* file = fopen (FileName, "r");

    if (file == NULL) {
        PRINTERR (TREE_OPEN_FILE_ERR);
        return   TREE_OPEN_FILE_ERR;
    }

    int read_size = ( int ) fread ( buffer, sizeof ( char ), size, file );

    if ( read_size != size ) {
        PRINTERR (TREE_INVALID_FILE_SIZE);
        return TREE_INVALID_FILE_SIZE;
    }

    fclose (file);

    return TREE_SUCCESS;
}

//--------------------------------------------------------------------------------

tree_node_t* 
TreeReadNode (tree_node_t* parent_node, char* buffer, int* pos)
{
    DEBUG_ASSERT (buffer != nullptr);

    int    oper_num   = 0;
    double data_value = 0;

    if (buffer[(*pos)++] == '(') {
        tree_node_t* new_node = nullptr;

        MakeNode (&new_node);

        new_node->prev_node = parent_node;

        MyAtof (buffer + *pos, &data_value);

        new_node->node_data = data_value;

        while (isdigit(buffer[*pos]) || buffer[*pos] == '.') {
            (*pos)++;
        }

        (*pos)++;

        return new_node;
    }

    if (strncmp (buffer + *pos, "nil", 3) == 0) {
        (*pos) += 3;
    }

    return NULL;
}

//--------------------------------------------------------------------------------

int 
MyAtof (const char* buffer, double* value)
{
    *value = atof (buffer);

    int pos = 0;

    if (*value == 0) {
        while (buffer[pos] == ' ' && pos < strlen (buffer)) {
            pos++;
        }

        if (buffer[pos] == 0) {
            return 0;
        }

        return 1;
    }

    return 0;
}

//--------------------------------------------------------------------------------

void 
SkipSpace (const char* buffer, int* pos)
{
    DEBUG_ASSERT (buffer != nullptr);

    while (buffer[*pos] == ' ') {
        (*pos)++;
    }
}

//--------------------------------------------------------------------------------

void 
DebugPrint (const char* buffer, int pos, int size)
{
    for (int i = 0; i < pos; i++) {
        fprintf (stderr, COLOR_GREEN "%c" COLOR_RESET, buffer[i]);
    }

    fprintf (stderr, COLOR_RED "|%c|", buffer[pos]);

    for (int i = pos + 1; i < size; i++) {
        fprintf (stderr, COLOR_YELLOW "%c" COLOR_RESET, buffer[i]);
    }

    fprintf (stderr, "\n\n");
}

//--------------------------------------------------------------------------------