#include "q.h"

//--------------------------------------------------------------------------------

void
LineCat (line_ctx_t* src_1, line_ctx_t* src_2)
{
    if (src_1 == nullptr || src_2 == nullptr) {
        return ;
    }

    line_node_t* cur_node_1  = src_1->first;
    line_node_t* cur_node_2  = src_2->first;

    line_node_t* next_node_1 = cur_node_1->next;
    line_node_t* next_node_2 = cur_node_2->next;

    while (src_2->count) {
        for (int i = 0; i < src_1->count; i++) { fprintf (stderr, "i = %d CUR1 = %p CUR2 = %p src2 count %d\n", i, cur_node_1, cur_node_2, src_2->count);
            if (cur_node_2->data > cur_node_1->data && cur_node_1->next) {
                cur_node_1 = cur_node_1->next;
            }
            else if (cur_node_1->next == nullptr) {
                cur_node_1->next = cur_node_2;
                cur_node_2->prev = cur_node_1;
                next_node_2 = cur_node_2->next;
                cur_node_2->next = nullptr;
                cur_node_2 = next_node_2;
                src_1->count++;
                src_2->count--;
                break;
            }
            else {
                if (cur_node_1 != src_1->first) {
                cur_node_1->prev->next = cur_node_2;
                cur_node_2->prev = cur_node_1->prev;
                }
                else {
                    cur_node_2->prev = nullptr;
                    src_1->first = cur_node_2;
                }
                next_node_2 = cur_node_2->next;
                cur_node_2->next = cur_node_1;
                cur_node_1->prev = cur_node_2;
                src_1->count++;
                src_2->count--;
                cur_node_2 = next_node_2;
                cur_node_1 = src_1->first;
                break;
            }
        }
    }

    free (src_2);

    line_node_t* cur_node = src_1->first;

    for (int i = 0; i < src_1->count - 1; i++) {
        cur_node = cur_node->next;
    }

    src_1->last = cur_node;

    return ;
}

//--------------------------------------------------------------------------------

void
Task_3 (void)
{
    line_ctx_t* src_1 = nullptr;
    line_ctx_t* src_2 = nullptr;

    LineCtor (&src_1);
    LineCtor (&src_2);

    int count_1 = 0;
    int count_2 = 0;

    printf ("Entre node_count to 1 and 2\n");

    scanf ("%d %d", &count_1, &count_2);

    int val = 0;

    for (int i = 0; i < count_1; i++) {
        printf ("Enter %d elem to src_1\n", i + 1);
        scanf ("%d", &val);
        LinePush (src_1, val);
    }

    for (int i = 0; i < count_2; i++) {
        printf ("Enter %d elem to src_2\n", i + 1);
        scanf ("%d", &val);
        LinePush (src_2, val);
    }

    LineCat (src_1, src_2);

    PrintLine (src_1);

    LineDtor (src_1);

    return ;
}

//--------------------------------------------------------------------------------