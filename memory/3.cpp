#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------------------------------------

int 
main ()
{
    int n = 5, m = 10;

    int (*ptr_1)[10] = (int (*)[10]) malloc (sizeof (int) * n * m);

    int** ptr_2 = (int**) malloc (sizeof (int*) * n);

    for (int i = 0; i < n; i++) {
        ptr_2[i] = (int*) malloc (sizeof (int) * m); 
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ptr_1[i][j] = i * m + j;
            ptr_2[i][j] = i * m + j;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf ("elem #%d ptr_1 = %p *ptr_1 = %d ptr_2 = %p *ptr_2 = %d\n",
                i * m + j, ptr_1[i] + j, ptr_1[i][j], ptr_2[i] + j, ptr_2[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        free (ptr_2[i]);
    }
    free (ptr_1);
    free (ptr_2);

    return 0;
}

//--------------------------------------------------------------------------------