//
//  main.c
//  Sorting
//
//  Created by 세연 on 2022/04/10.
//

#include "sort.h"

int numOfElements;
Arr* arr;

int main(int argc, const char * argv[]) {
    clock_t start, end;
    int s, i;
    
    
    printf("Enter the number of numbers to sort\n:");
    scanf("%d", &numOfElements);
    
    arr = (Arr*)malloc(sizeof(Arr)*numOfElements);
    initArray(arr);
    
    Heap H;
    
    LIST *list = initList();
    for (i = 0; i<numOfElements; i++) {
        insertRight(list, rand()%100);
    }
    LIST *listOfList[numOfElements];
    for (i = 0; i < numOfElements; i++) {
        listOfList[i] = initList();
    }
    
    
    printf("------------Select a sort algorithm");
    printf("\n1.Exchange Sort\n2.Merge Sort\n3.Quick Sort\n4.Heap Sort\n5.Radix Sort\n:");
    scanf("%d", &s);
    
    printf("\n------------An array before sorting\n");
    
    switch (s) {
        case 1 ... 3:
            printArray(arr, numOfElements);
            break;
        case 4:
            printArray(arr, numOfElements);
            H.arr = arr;
            H.heapSize = numOfElements-1;
            break;
        case 5:
            printList(list);
            break;
    }
    
    
    start = clock();
    switch (s) {
        case 1:
            ExchangeSort(arr);
            printf("\n------------The result of Exchange Sort\n");
            break;
        case 2:
            MergeSort(arr, numOfElements);
            printf("\n------------The result of Merge Sort\n");
            break;
        case 3:
            QuickSort(0, numOfElements);
            printf("\n------------The result of Quick Sort\n");
            break;
        case 4:
            HeapSort(numOfElements-1, &H);
            printf("\n------------The result of Heap Sort\n");
            break;
        case 5:
            RadixSort(list, listOfList);
            printf("------------The result of Radix Sort\n");
            break;
    }
    end = clock();
    
    
    switch (s) {
        case 1 ... 4:
            printArray(arr, numOfElements);
            break;
        case 5:
            printList(list);
            
            freeList(list);
            for (i = 0; i < numOfElements; i++) {
                freeList(listOfList[i]);
            }
            break;
    }

    
    printf("\nThe time is %.4lf\n\n", (double)(end-start));
    
    
    free(arr);
    
    
    return 0;
}

