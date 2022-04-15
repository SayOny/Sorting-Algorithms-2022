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
    Heap H;
    LIST *list = initList();
    
    printf("Enter the number of numbers to sort\n:");
    scanf("%d", &numOfElements);
    
    arr = (Arr*)malloc(sizeof(Arr)*numOfElements);
    initArray(arr);

    printf("------------Select a sort algorithm");
    printf("\n1.Exchange Sort\n2.Merge Sort\n3.Quick Sort\n4.Heap Sort\n5.Radix Sort\n:");
    scanf("%d", &s);
    
    printf("\n------------An array before sorting\n");
    
    start = clock();

    switch (s) {
        case 1:
            printArray(arr, numOfElements);
            ExchangeSort(arr);
            printf("\n------------The result of Exchange Sort\n");
            printArray(arr, numOfElements);
            break;
        case 2:
            printArray(arr, numOfElements);
            MergeSort(arr, numOfElements);
            printf("\n------------The result of Merge Sort\n");
            printArray(arr, numOfElements);
            break;
        case 3:
            printArray(arr, numOfElements);
            QuickSort(0, numOfElements);
            printf("\n------------The result of Quick Sort\n");
            printArray(arr, numOfElements);
            break;
        case 4:
            printArray(arr, numOfElements);
            H.arr = arr;
            H.heapSize = numOfElements-1;
            HeapSort(numOfElements-1, &H);
            printf("\n------------The result of Heap Sort\n");
            printArray(arr, numOfElements);
            break;
        case 5:
            for (i = 0; i<numOfElements; i++) {
                insertRight(list, rand()%100);
            }
            
            LIST *listOfList[numOfElements];
            for (i = 0; i < numOfElements; i++) {
                listOfList[i] = initList();
            }
            
            printList(list);
            
            RadixSort(list, listOfList);
            
            printf("------------The result of Radix Sort\n");
            printList(list);
            
            freeList(list);
            for (i = 0; i < numOfElements; i++) {
                freeList(listOfList[i]);
            }
            break;
    }
    
    end = clock();

    printf("\nThe time is %.4lf\n\n", (double)(end-start));
    
    free(arr);
    
    return 0;
}

