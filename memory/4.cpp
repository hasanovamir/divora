#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------------------------------------

int 
main ()
{
    int n = 3, m = 3;

    int matrix[3][3] = { { 1, 0, 1},
                         {-1, 0, 1},
                         { 0, 0, 0}, };
                          
    int** ptr     = nullptr;
    int   status  = 0;
    int   size    = 0;

    for (int i = 0; i < 3; i++) {
        status = 0;
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] < 0) {
                status = 1;
            }
        }

        if (status == 0) {
            if (ptr == NULL) {
                size = 1;

                ptr  = (int**) calloc (1, sizeof (int*));

                ptr[size - 1] = (int*) calloc (3, sizeof (int));
            }
            else {
                size++;

                ptr = (int**) realloc (ptr, size * sizeof (int*));

                ptr[size - 1] = (int*) calloc (3, sizeof (int));
            }

            for (int k = 0; k < 3; k++) {
                ptr[size - 1][k] = matrix[i][k];
            }
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 3; j++) {
            printf ("%d", ptr[i][j]);
        }
        printf ("\n");
    }

    for (int i = 0; i < size; i++) {
        free (ptr[i]);
    }

    free (ptr);

    return 0;
}

//--------------------------------------------------------------------------------