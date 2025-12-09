#ifndef Q_H
#define Q_H

//————————————————————————————————————————————————————————————————————————————————

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "assert.h"

//————————————————————————————————————————————————————————————————————————————————

typedef int line_data_t;

//————————————————————————————————————————————————————————————————————————————————

struct line_node_t {
    line_data_t  data;
    line_node_t* next;
    line_node_t* prev;
};

//————————————————————————————————————————————————————————————————————————————————

struct line_ctx_t {
    int count;
    line_node_t* first;
    line_node_t* last;
};

//————————————————————————————————————————————————————————————————————————————————

int
LineCtor (line_ctx_t** l_ctx);
line_node_t*
CreateNode (int value);
int
LinePush (line_ctx_t* l_ctx, int value);
line_data_t
LinePop (line_ctx_t* l_ctx);
void
PrintLine (line_ctx_t* l_ctx);
bool
CheckEmptyLine (line_ctx_t* l_ctx);
void
PrintNodeCount (line_ctx_t* l_ctx);
void
LineDtor (line_ctx_t* l_ctx);
void
UseLine (line_ctx_t* l_ctx);
void
PrintMenu (void);
void
SearchPosToStayAlive (int count);
void
Task_3 (void);
void
LineCat (line_ctx_t* src_1, line_ctx_t* src_2);

//————————————————————————————————————————————————————————————————————————————————

#endif //Q_H