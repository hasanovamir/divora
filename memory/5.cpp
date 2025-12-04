#include <stdio.h>
#include <stdlib.h>

int 
distance_between(int* distances, int n, int start, int end) 
{
    int dist = 0;
    int current = start;

    while (current != end) {
        dist += distances[current];
        current = (current + 1) % n;
    }
    
    int dist_counter = 0;

    current = end;

    while (current != start) {
        dist_counter += distances[current];
        current = (current + 1) % n;
    }
    
    return (dist < dist_counter) ? dist : dist_counter;
}

int 
total_path_length(int* distances, int n, int a, int b, int c) 
{
    int ab = distance_between(distances, n, a, b);
    int bc = distance_between(distances, n, b, c);
    int ac = distance_between(distances, n, a, c);
    
    return ab + bc + ac - (ab > bc ? (ab > ac ? ab : ac) : (bc > ac ? bc : ac));
}

int 
main()
{
    int n;
    
    scanf("%d", &n);
    
    int* distances = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        printf("between %d & %d: ", i, (i+1)%n);
        scanf("%d", &distances[i]);
    }
    
    int min_path = INT_MAX;
    int best_a = -1, best_b = -1, best_c = -1;
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                int path = total_path_length(distances, n, i, j, k);
                
                if (path < min_path) {
                    min_path = path;
                    best_a = i;
                    best_b = j;
                    best_c = k;
                }
            }
        }
    }
    
    printf("PLOSHAD: %d, %d, %d\n", best_a, best_b, best_c);
    printf("LEN: %d\n", min_path);
    
    free(distances);
    
    return 0;
}