#include <stdio.h>

//--------------------------------------------------------------------------------

const int MAT_SIZE = 4;

//--------------------------------------------------------------------------------

int fact        (int num);
int fibonacci   (int num);
int Akkerman    (int n, int m);
int FourthTask  (int* array, int* end_of_array);
int PassingMaze (int array[20][20], int x, int y, int x_finish, int y_finish, int x_prev, int y_prev);
int determinant (int A[MAT_SIZE][MAT_SIZE], int n);
void hanoi      (int n, char from, char to, char sup); 

//--------------------------------------------------------------------------------

int main ()
{
    int array[20][20] = {
    {0,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1},
    {0,1,0,0,0,0,0,0,0,1,1,0,1,0,1,1,1,1,1,1},
    {0,0,0,1,1,1,1,1,0,0,0,1,1,0,0,0,0,1,1,1},
    {1,1,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,1,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0},
    {1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,0,0},
    {1,0,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
    {0,0,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1},
    {1,1,1,0,1,1,1,0,0,1,1,1,1,1,0,1,1,0,1,1},
    {1,1,0,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1},
    {1,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1},
    {1,1,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,1,1,1},
    {1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,0,0,0,1,1},
    {1,1,0,0,0,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1},
    {1,1,0,1,1,1,1,0,0,0,0,0,0,1,1,0,1,1,1,1},
    {0,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1}};

    //printf ("%d\n", FourthTask (array, array + 9));
    //printf ("%d", Akkerman (4, 1));
    // if (PassingMaze (array, 2, 2, 14, 12, -1, -1)) {
    //     printf ("mojno");
    // }
    // else {
    //     printf ("nelzya");
    // }
    //hanoi (3, 'A', 'C', 'B');
    int array_det[4][4] = 
    {
    {1,-7,34,12},
    {4,8,-14,23},
    {17,-34,3,8},
    {2,7,-7,6}
    };
    printf ("%d", determinant (array_det, 4));
}

//--------------------------------------------------------------------------------

int fact (int num)
{
    if (num == 0) {
        return 1;
    }

    return num * fact (num - 1);
}

//--------------------------------------------------------------------------------

int fibonacci (int num)
{
    if (num == 1) {
        return 0;
    }
    if (num == 2) {
        return 1;
    }

    return fibonacci (num - 1) + fibonacci (num - 2);
}

//--------------------------------------------------------------------------------

int Akkerman (int m, int n)
{
    if (m == 0) {
        return n + 1;
    }
    else if (n == 0) {
        return Akkerman (m - 1, 1);
    }
    else {
        return Akkerman (m - 1, Akkerman (m , n - 1));
    }
}

//--------------------------------------------------------------------------------

int FourthTask (int* array, int* end_of_array)
{
    if (array == end_of_array) {
        return *end_of_array;
    }

    int next_el = FourthTask (array + 1, end_of_array);

    return (*array < next_el) ? *array : next_el;
}

//--------------------------------------------------------------------------------

int PassingMaze (int array[20][20], int x, int y, int x_finish, int y_finish, int x_prev, int y_prev)
{
    if (x == x_finish && y == y_finish) {
        return 1;
    }

    if (x - 1 >= 0 && array[y][x - 1] == 0 && x - 1 != x_prev) {
        if (PassingMaze (array, x - 1, y, x_finish, y_finish, x, y)) {
            return 1;
        }
    }
    if (x + 1 <= 19 && array[y][x + 1] == 0 && x + 1 != x_prev) {
        if (PassingMaze (array, x + 1, y, x_finish, y_finish, x, y)) {
            return 1;
        }
    }
    if (y - 1 >= 0 && array[y - 1][x] == 0 && y - 1 != y_prev) {
        if (PassingMaze (array, x, y - 1, x_finish, y_finish, x, y)) {
            return 1;
        }
    }
    if (y + 1 <= 19 && array[y + 1][x] == 0 && y + 1 != y_prev) {
        if (PassingMaze (array, x, y + 1, x_finish, y_finish, x, y)) {
            return 1;
        }
    }

    return 0;
}

//--------------------------------------------------------------------------------

int determinant(int array[MAT_SIZE][MAT_SIZE], int n)
{
    if (n == 1) return array[0][0];
    if (n == 2) return array[0][0] * array[1][1] - array[0][1] * array[1][0];
    
    int det = 0;
    int minor[MAT_SIZE][MAT_SIZE];
    int y = 0, x = 0;
    
    for (int j = 0; j < n; j++) {
        y = 0;
        for (int i = 1; i < n; i++) {
            x = 0;
            for (int k = 0; k < n; k++) {
                if (k == j) continue;
                minor[y][x] = array[i][k];
                x++;
            }
            y++;
        }
        
        int sign = (j % 2 == 0) ? 1 : -1;
        det += sign * array[0][j] * determinant (minor, n-1);
    }

    return det;
}

//--------------------------------------------------------------------------------

void hanoi (int n, char from, char to, char sup) 
{
    if (n == 1) {
        printf ("disk 1 from %c to %c\n", from, to);
        return;
    }
    
    hanoi (n - 1, from, sup, to);
    
    printf ("disk %d from %c to %c\n", n, from, to);
    
    hanoi (n - 1, sup, to, from);
}

//--------------------------------------------------------------------------------