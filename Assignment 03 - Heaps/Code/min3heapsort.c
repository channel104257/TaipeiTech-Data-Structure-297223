#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //for timeing

// 定義節點結構
typedef struct HeapNode
{
    int data;
    struct HeapNode *nextPtr;
} heapnode;

// 重新定義結構之一階指標的名稱
typedef struct HeapNode *heapPtr;

// 插入串列尾端
void insertlist(heapPtr *nodePtr, int info);
// 顯示串列的所有元素
void printlist(heapPtr currentPtr);
// 計算當前節點數量
int nodecount(heapPtr currentPtr);
// 移動堆積指標位置
heapPtr MoveToNode(heapPtr nodePtr, int num);
// 交換
void swap(int *num1, int *num2);
// 最小堆積比較
void MinHeapComparison(heapPtr headPtr, int size, int No);
// 堆積排序法
void HeapSort(heapPtr headPtr, int size);

// 主程式進入點
int main()
{
    // 定義輸入字元
    char value;
    // 定義字元數量旗標
    int tempNum = 0;
    // 定義首位堆積節點
    heapPtr heapNodeHead = NULL;
    // set up the variable for timing
    LARGE_INTEGER t1, t2, tc;

    printf("請輸入 Heap 的 Level-Order Traversal\n");
    printf("(請以「空格」區隔各個node)\n-> ");

    // 逐字讀取輸入字元直到'\n'
    while ((value = getchar()) != '\n')
    {
        switch (value)
        {
        // 以空白間隔表輸入完畢
        case ' ':
        {
            // 將該數字輸入初始堆積
            insertlist(&heapNodeHead, tempNum);
            // 重製字元數量旗標
            tempNum = 0;
            break;
        }
        default:
        {
            // 若輸入為數字
            if (value >= 48 && value <= 57)
            {
                // 將已讀取的數字累加
                tempNum = tempNum * 10 + (value - 48);
            }
            break;
        }
        }
    }

    // 將最後的數字推入初始堆積
    insertlist(&heapNodeHead, tempNum);

    // 輸出初始堆積
    printlist(heapNodeHead);

    // 逐節點訪問進行 Buttom-up
    for (int i = nodecount(heapNodeHead); i > 0; i--)
    {
        MinHeapComparison(heapNodeHead, nodecount(heapNodeHead), i);
    }

    // 輸出最小堆積
    printf("\n");
    printf("Min 3-Heap\n");
    printlist(heapNodeHead);

    // check the tick frequency
    QueryPerformanceFrequency(&tc);

    // start timing
    QueryPerformanceCounter(&t1);

    HeapSort(heapNodeHead, nodecount(heapNodeHead));
    
    // stop timing
    QueryPerformanceCounter(&t2);

    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    double time = ((double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart) * 1000;

    printf("After HeapSort\n");
    printlist(heapNodeHead);
    // 歷經時間
    printf("The elapsed time is %lf ms\n", time);
    printf("\n");
}

// 插入節點
void insertlist(heapPtr *headPtr, int info)
{
    // 建立新的節點
    heapPtr newPtr = (heapPtr)malloc(sizeof(heapPtr));

    // 記憶體擁有足夠的空間
    if (newPtr != NULL)
    {
        // 將欲插入的字元存入節點中
        newPtr->data = info;
        // 將指向下的節點的指標指為空
        newPtr->nextPtr = NULL;

        // 將串列的首位指標設為當前指標位置
        heapPtr currentPtr = *headPtr;
        // 定義前個指標為空
        heapPtr previousPtr = NULL;

        // 將當前指標位置移動至串列最尾端
        while (currentPtr != NULL)
        {
            // 將前個指標的位置設為當前指標
            previousPtr = currentPtr;
            // 將當前指標位置向下個節點移動
            currentPtr = currentPtr->nextPtr;
        }

        // 若串列中沒有半個元素
        if (previousPtr == NULL)
        {
            // 將新節點所指向的下個者標位置指向讀入串列的頭(NULL)
            newPtr->nextPtr = *headPtr;
            // 將元串列的位置指項新節點
            *headPtr = newPtr;
        }
        else
        {
            // 將前一個指標的所指向的下個位置指向新增的節點
            previousPtr->nextPtr = newPtr;
            // 將新節點的所指向的下個指標指向當前節點
            newPtr->nextPtr = currentPtr;
        }
    }
    // 記憶體空間用盡
    else
    {
        printf("%d not inserted. No memory available.\n", info);
    }
}

void printlist(heapPtr currentPtr)
{
    // 檢查當前串列是否為空
    if (currentPtr == NULL)
    {
        puts("The stack is empty.\n");
    }
    else
    {
        // 將當前串列位置往後移直到到達尾端
        while (currentPtr != NULL)
        {
            // 輸出該串列元素
            printf("%d ", currentPtr->data);
            // 將當前串列位置往後移
            currentPtr = currentPtr->nextPtr;
        }
        printf("\n");
    }
}

int nodecount(heapPtr currentPtr)
{
    // 檢查當前串列是否為空
    if (currentPtr == NULL)
    {
        return 0;
    }
    else
    {
        // 定義節點數量
        int nodeNum = 0;

        // 將當前串列位置往後移直到到達尾端
        while (currentPtr != NULL)
        {
            // 將當前串列位置往後移
            currentPtr = currentPtr->nextPtr;
            // 節點數量 +1 
            nodeNum++;
        }

        return nodeNum;
    }
}

heapPtr MoveToNode(heapPtr nodePtr, int num)
{
    for (size_t i = 0; i < num - 1; i++)
    {
        // 將當前串列位置往後移
        nodePtr = nodePtr->nextPtr;
    }

    return nodePtr;
}

// 交換
void swap(int *num1, int *num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void MinHeapComparison(heapPtr headPtr, int size, int No)
{
    //定義最小節點
    int smallest = No;
    // 定義 left child
    int left = 3 * No - 1;
    // 定義 medium child
    int medium = 3 * No;
    // 定義 right child
    int right = 3 * No + 1;

    // 若 left child 小於最小節點的值
    if (left <= size && MoveToNode(headPtr, left)->data < MoveToNode(headPtr, smallest)->data)
    {
        // 最小節點為 left child
        smallest = left;
    }
    // 若 medium child 小於最小節點的值
    if (medium <= size && MoveToNode(headPtr, medium)->data < MoveToNode(headPtr, smallest)->data)
    {
        // 最小節點為 medium child
        smallest = medium;
    }
    // 若 right child 小於最小節點的值
    if (right <= size && MoveToNode(headPtr, right)->data < MoveToNode(headPtr, smallest)->data)
    {
        // 最小節點為 right child
        smallest = right;
    }
    // 若最小節點不為 root
    if (smallest != No)
    {
        // 交換 root & 最小節點
        swap(&MoveToNode(headPtr, No)->data, &MoveToNode(headPtr, smallest)->data);
        // 向下層子樹遞迴
        MinHeapComparison(headPtr, size, smallest);
    }
}

// 堆積排序法
void HeapSort(heapPtr headPtr, int size)
{
    for (size_t i = 1; i <= size; i++)
    {
        // 將極值與 root 值交換
        swap(&MoveToNode(headPtr, 1)->data, &MoveToNode(headPtr, size - i + 1)->data);

        // 縮減區間進行heapify
        MinHeapComparison(headPtr, size - i, 1);
    }
}
