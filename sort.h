//
//  sort.h
//  Sorting
//
//  Created by 세연 on 2022/04/10.
//

#ifndef sort_h
#define sort_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct arr{
    int v;
}Arr;

typedef struct heap{
    Arr* arr;
    int heapSize;
}Heap;

typedef struct node {
    int key;
    struct node* left;
    struct node* right;
} NODE;

typedef struct list {
    int cnt;
    NODE *head;
} LIST;

void initArray(Arr*);
void printArray(Arr*, int);

void ExchangeSort(Arr*);
void uMerge(Arr*, Arr*, Arr*, int, int);
void MergeSort(Arr*, int);

void partition(int, int, int*);
void QuickSort(int, int);

void siftdown(Heap *, int);
void makeHeap(int, Heap*);
int root(Heap *);
void removeKeys(int, Heap*, Arr*);
void HeapSort(int, Heap*);

LIST *initList(void);
void insertRight (LIST *, int);
int deleteLeft (LIST*);
void printList(LIST*);
void freeList (LIST*);
void RadixSort(LIST*, LIST**);

#endif /* sort_h */
