#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//--------------------------------------------------------------------------------
void MakeHeapMin    (int*  heap, int   size);
int  HeapCtor       (int** src , int** heap);
void HeapDtor       (int*  src , int*  heap);
int  CheckHeapToMin (int*  heap, int   size);
void PrintArray     (int*  arr , int   size);
int  HeapDelete     (int*  heap, int*  size);
void HeapSort       (int*  src , int   size);
int  FillHeap       (int*  src , int*  heap , int size );
void CompForMin     (int*  heap, int   i    , int size );
void HeapAppend     (int*  heap, int*  size , int value);

//--------------------------------------------------------------------------------

int 
main ()
{
    int* src  = nullptr;
    int* heap = nullptr;

    int size = HeapCtor (&src, &heap);

    FillHeap (src, heap, size);

    PrintArray (src,  size);
    PrintArray (heap, size);

    printf ("MinStatus = %d\n", CheckHeapToMin (heap, size));

    HeapAppend (heap, &size, 4);

    PrintArray (heap, size);

    printf ("MinStatus = %d\n", CheckHeapToMin (heap, size));

    HeapSort (heap, size);

    PrintArray (heap, size);

    HeapDtor (src, heap);

    return 0;
}

//--------------------------------------------------------------------------------

int 
HeapCtor (int** src, int** heap)
{
    int size = 0;

    scanf ("%d", &size);

    *src  = (int*) calloc (size, sizeof (int));
    *heap = (int*) calloc (size, sizeof (int));

    if (*src == nullptr || *heap == nullptr) {
        return -1;
    }

    for (int i = 0; i < size; i++) {
        scanf ("%d", *src + i);
    }

    return size;
}


//--------------------------------------------------------------------------------

void 
MakeHeapMin (int* heap, int size)
{
    for (int i = size / 2 - 1; i >= 0; i--) {
        CompForMin (heap, i, size);
    }
}

//--------------------------------------------------------------------------------

int 
FillHeap (int* src, int* heap, int size)
{
    for (int i = 0; i < size; i++) {
        heap[i] = src[i];
    }

    MakeHeapMin (heap, size);

    return size;
}

//--------------------------------------------------------------------------------

void 
CompForMin (int* heap, int i, int size)
{
    int smallest = i;

    int left  = 2 * i + 1;
    int right = 2 * i + 2;

    
    if (left < size && heap[left] < heap[smallest]) {
        smallest = left;
    }

    
    if (right < size && heap[right] < heap[smallest]) {
        smallest = right;
    }

    
    if (smallest != i) {
        
        int temp = heap[i];

        heap[i] = heap[smallest];

        heap[smallest] = temp;

        CompForMin (heap, smallest, size);
    }
}

//--------------------------------------------------------------------------------

int 
CheckHeapToMin (int* heap, int size)
{
    for (int i = 0; i <= size / 2 - 1; i++) {

        int left  = 2 * i + 1;
        int right = 2 * i + 2;

        if (left  < size && heap[i] > heap[left] ) return false;
        if (right < size && heap[i] > heap[right]) return false;
    }

    return true;
}

//--------------------------------------------------------------------------------

void 
PrintArray (int* arr, int size)
{
    for (int i = 0; i < size; i++) {
        printf ("%d ", arr[i]);
    }

    printf ("\n");
}

//--------------------------------------------------------------------------------

void 
HeapAppend (int* heap, int* size, int value)
{
    *size += 1;

    int i = *size - 1; 

    heap[i] = value;
    
    MakeHeapMin (heap, *size);
}

//--------------------------------------------------------------------------------

int
HeapDelete (int* heap, int* size)
{   
    int min = *heap;

    if (*size == 1) {
        *size = 0;

        return *heap;
    }

    *size -= 1;

    heap[0] = heap[*size];
    
    MakeHeapMin (heap, *size);

    return min;
}

//--------------------------------------------------------------------------------

void HeapDtor (int* src , int* heap)
{
    free (src );
    free (heap);
}

//--------------------------------------------------------------------------------

void 
HeapSort (int* src, int size)
{
    int* heap = (int*) calloc (size, sizeof (int));

    int heap_size = size;

    FillHeap (src, heap, size);

    for (int i = 0; i < size; i++) {
        src[i] = HeapDelete (heap, &heap_size);
    }

    free (heap);
}

//--------------------------------------------------------------------------------