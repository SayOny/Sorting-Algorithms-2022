//
//  sort.c
//  Sorting
//
//  Created by 세연 on 2022/04/10.
//

#include "sort.h"



// main.c파일에서 선언한 전역변수들 가져오기
extern int numOfElements;
extern Arr* arr;

// 구조체 배열의 v값들에 랜덤 값 넣어주는 함수
void initArray(Arr* arr){
    int i;
    
    for (i = 0; i <  numOfElements; i++) {
        arr[i].v = rand()&100;
    }
}

void printArray(Arr* arr, int n){
    int i;
    
    for (i=0; i<n; i++) {
        printf("%d ", arr[i].v);
    }
    printf("\n\n");
}



// ---------------------------------------------Exchange Sort
void ExchangeSort(Arr* arr){
    int i, j;
    Arr tmp;
    
// 한 원소와 모든 원소가 비교되면서 가장 작은 값부터 정렬된다.
    for (i=0; i<numOfElements; i++) {
        for (j=0; j<numOfElements; j++) {
            if (arr[j].v > arr[i].v) {
                tmp.v = arr[i].v;
                arr[i].v = arr[j].v;
                arr[j].v = tmp.v;
            }
        }
    }
}



// ---------------------------------------------Merge Sort
void uMerge(Arr* left, Arr* right, Arr* arr, int h, int m){
    int i=0, j=0, k=0;

// 왼쪽 배열과 오른쪽 배열을 앞의 원소부터 비교하면서 하나의 배열에 합친다.
    while (i < h && j < m) {
        if (left[i].v < right[j].v){
            arr[k].v = left[i].v;
            i++;
        }else{
            arr[k].v = right[j].v;
            j++;
        }
        k++;
    }
//    만약 왼쪽이나 오른쪽 배열의 길이가 달라서 아직 정렬되지 않은 원소들이 있다면 그들은 이미 정렬 된 상태이므로 그대로 배열에 넣어준다.
    if (i >= h) {
        while(j <= m) {
            arr[k].v = right[j].v;
            j++;
            k++;
        }
    }else{
        while (i <= h) {
            arr[k].v = left[i].v;
            i++;
            k++;
        }
    }
}

void MergeSort(Arr* arr, int n){
//    정렬하고자 하는 배열을 매개변수로 입력 받아서 두 개의 배열로 나눈다.
    if (n > 1) {
        int i, j, h=(n/2), m=(n-h);
        Arr* leftArr = (Arr*)malloc(sizeof(Arr)*h);
        Arr* rightArr = (Arr*)malloc(sizeof(Arr)*m);

        for (i=0; i<h; i++) {
            leftArr[i].v  = arr[i].v;
        }
        for (j=0; j<m; j++) {
            rightArr[j].v = arr[j+h].v;
        }
// 나눈 왼쪽 배열과 오른쪽 배열 또한 MergeSort()함수를 통해 정렬한 뒤, 그 정렬된 두 배열을 합친다.
        MergeSort(leftArr, h);
        MergeSort(rightArr, m);
        uMerge(leftArr, rightArr, arr, h, m);

//        free(leftArr);
//        free(rightArr);
    }
    
}




// ---------------------------------------------Quick Sort
void partition(int low, int high, int* pivotPoint){
    int i, j;
    int pivotItem;
    int tmp;
    
//    피봇 인덱스의 값 바로 다음값과 맨 오른쪽 값의 간격을 서로 좁혀가면서 왼쪽 보다 작은 값을 발견하면 바꾸는 것을 반복한다. 둘이 엇갈리면 피봇과 그 값을 바꾼다.
    pivotItem = arr[low].v;
    j = low;
    for (i=low; i<high; i++) {
        if (arr[i].v < pivotItem) {
            j++;
            tmp = arr[i].v;
            arr[i].v = arr[j].v;
            arr[j].v = tmp;
        }
    }
    *pivotPoint = j;
    tmp = arr[low].v;
    arr[low].v = arr[*pivotPoint].v;
    arr[*pivotPoint].v = tmp;
}

void QuickSort(int low, int high){
    int pivotPoint;
    
//    partition()을 통해 피봇을 기준으로 작은 값과 큰값으로 나누고 그 왼쪽 오른쪽 배열을 또 QuickSort()를 한다.
    if (high > low) {
        partition(low, high, &pivotPoint);
        QuickSort(low, pivotPoint-1);
        QuickSort(pivotPoint+1, high);
    }
}



// ---------------------------------------------Heap Sort
// 힙의 루트값을 자식들과 비교하면서 초기 루트 값의 자리를 잡도록 하는 함수
void siftdown(Heap *H, int i){
    int parent, largerChild;
    int siftKey;
    int spotFound;
    
    siftKey = H->arr[i].v;
    parent = i;
    spotFound = 0;
    while (2*parent < (*H).heapSize && !spotFound) {
        if (2*parent < (*H).heapSize && H->arr[2*parent].v < H->arr[2*parent+1].v) {
            largerChild = 2*parent+1;
        }
        else{
            largerChild = 2*parent;
        }
        if (siftKey < H->arr[largerChild].v) {
            H->arr[parent].v = H->arr[largerChild].v;
            parent = largerChild;
        }
        else spotFound = 1;
    }
    H->arr[parent].v = siftKey;
}

void makeHeap(int n, Heap* H){
    int i;
    (*H).heapSize = n;
    for (i=(n/2); i>=0; i--) {
        siftdown(H, i);
    }
}

// 루트 값을 빼내는 함수
int root(Heap * H){
    int keyOut;
    
    keyOut = H->arr[0].v;
    H->arr[0].v = H->arr[(*H).heapSize].v;
    (*H).heapSize = ((*H).heapSize)-1;
    siftdown(H, 0);
    return keyOut;
}

void removeKeys(int n, Heap* H, Arr* arr){
    int i;
// 루트에 있는 값을 하나씩 빼가면서 재정렬한다.
    for (i = n; i >= 0; i--) {
        arr[i].v = root(H);
    }
}

void HeapSort(int n, Heap* H){
//    최대 힙의 구조를 만든다.
    makeHeap(n, H);
// 값을 하나씩 뺀다.
    removeKeys(n, H, (*H).arr);
}



// ---------------------------------------------Radix Sort
// 이중 연결 리스트 초기화하는 함수
LIST *initList(void) {
    NODE* nodePointer = malloc (sizeof (NODE));
    LIST* list = malloc (sizeof (LIST));
    
    nodePointer -> left = nodePointer;
    nodePointer -> right = nodePointer;
    
    list -> head = nodePointer;
    list -> cnt = 0;
    
    return (list);
}

// list를 받아서 새 노드를 연결하는 함수
void insertRight (LIST *list, int x) {
    NODE* nodePointer = malloc (sizeof (NODE));

    nodePointer -> key = x;
//     head와 head right의 값 사이에 넣는 느낌
    nodePointer -> left = list -> head;
    nodePointer -> right = list -> head -> right;
    nodePointer -> right -> left = nodePointer;
    
    list -> head -> right = nodePointer;
    list -> cnt++;
}

// 왼쪽 끝의 노드를 삭제하는 함수
int deleteLeft (LIST*list) {
    
    list -> head -> left = list -> head -> left -> left;
    int x = list -> head -> left -> right -> key;
    
    free (list -> head -> left -> right);
    
    list -> head -> left -> right = list -> head;
    list -> cnt--;
    
    return (x);
}

void printList(LIST* list){
    int i, n;
    printf("\n");
    for (i = 0; i < (*list).cnt; i++) {
        n = deleteLeft(list);
        printf ("%d ", n);
        insertRight(list,n);
    }
    printf("\n");
}

void freeList (LIST* list) {
    NODE *nodePointer = list -> head -> left -> left;
    while (nodePointer != list -> head) {
        free (nodePointer -> right);
        nodePointer = nodePointer -> left;
    }
    if (nodePointer -> right != nodePointer) {
        free (nodePointer -> right);
    }
    free (nodePointer);
    return;
}

void RadixSort(LIST* list, LIST** listOfList){
    int flag = 0, i = 0, j, n, m;
    
    while (!flag) {
        flag = 1;
        
        while((*list).cnt != 0) {
            m = deleteLeft(list);
            n = (m / ((int)pow(10,i))) % 10;
            insertRight(listOfList[n], m);

            if ((m / ((int)pow(10,i))) > 0) {
                flag = 0;
            }
        }

        for (j = 0; j < numOfElements; j++) {
            while ((*listOfList[j]).cnt != 0) {
                m = deleteLeft(listOfList[j]);
                insertRight(list,m);
            }
        }

        i++;
    }
}
