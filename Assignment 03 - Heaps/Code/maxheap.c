#include <stdio.h>
#include <stdlib.h>

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
//
int nodecount(heapPtr currentPtr);
//
heapPtr MoveToNode(heapPtr nodePtr, int num);
//
void swap(int *num1, int *num2);
//
void MaxHeapComparison(heapPtr headPtr, int size, int No);
//
void deleteHeapNode(heapPtr headPtr, int size, int No);
//
void insertHeapNode(heapPtr headPtr, int size, int input);

int main()
{
    char value;
    int tempNum = 0;
    heapPtr heapNodeHead = NULL;

    printf("請輸入 Heap 的 Level-Order Traversal\n");
    printf("(請以「空格」區隔各個node)\n-> ");

    while ((value = getchar()) != '\n')
    {
        switch (value)
        {
        case ' ':
        {
            insertlist(&heapNodeHead, tempNum);
            tempNum = 0;
            break;
        }
        default:
        {
            if (value >= 48 && value <= 57)
            {
                tempNum = tempNum * 10 + (value - 48);
            }
            break;
        }
        }
    }

    insertlist(&heapNodeHead, tempNum);

    printlist(heapNodeHead);

    for (int i = nodecount(heapNodeHead) / 2; i > 0; i--)
    {
        MaxHeapComparison(heapNodeHead, nodecount(heapNodeHead), i);
    }

    printf("\n");
    printf("Max Heap\n");
    printlist(heapNodeHead);

    int modeNum, input;

    printf("Choose the function : (1) insert (2) delete (3) exit\n-> ");
    scanf("%d", &modeNum);

    while (modeNum != 3)
    {
        switch (modeNum)
        {
        case 1:
            printf("Please enter the number you want to insert\n-> ");
            scanf("%d", &input);

            insertHeapNode(heapNodeHead, nodecount(heapNodeHead), input);
            printf("After insert %d to heap\n", input);
            printlist(heapNodeHead);
            printf("\n");

            printf("Choose the function : (1) insert (2) delete (3) exit\n-> ");
            scanf("%d", &modeNum);
            break;

        case 2:
            printf("Choose the node you what to remove (1 ~ %d)\n-> ", nodecount(heapNodeHead));
            scanf("%d", &input);

            deleteHeapNode(heapNodeHead, nodecount(heapNodeHead), input);
            printf("After delete the node NO.%d\n", input);
            printlist(heapNodeHead);
            printf("\n");

            printf("Choose the function : (1) insert (2) delete (3) exit\n-> ");
            scanf("%d", &modeNum);
            break;

        case 3:
            break;
        }
    }
}

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
        int nodeNum = 0;

        // 將當前串列位置往後移直到到達尾端
        while (currentPtr != NULL)
        {
            // 將當前串列位置往後移
            currentPtr = currentPtr->nextPtr;
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

void swap(int *num1, int *num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void MaxHeapComparison(heapPtr headPtr, int size, int No)
{
    int largest = No;
    int left = 2 * No;
    int right = 2 * No + 1;

    if (left <= size && MoveToNode(headPtr, left)->data > MoveToNode(headPtr, largest)->data)
    {
        largest = left;
    }
    if (right <= size && MoveToNode(headPtr, right)->data > MoveToNode(headPtr, largest)->data)
    {
        largest = right;
    }
    if (largest != No)
    {
        swap(&MoveToNode(headPtr, No)->data, &MoveToNode(headPtr, largest)->data);
        MaxHeapComparison(headPtr, size, largest);
    }
}

void deleteHeapNode(heapPtr headPtr, int size, int No)
{
    MoveToNode(headPtr, No)->data = MoveToNode(headPtr, size)->data;
    MoveToNode(headPtr, size - 1)->nextPtr = NULL;
    free(MoveToNode(headPtr, size));

    MaxHeapComparison(headPtr, size - 1, No);
}

void insertHeapNode(heapPtr headPtr, int size, int input)
{
    insertlist(&headPtr, input);

    for (int i = size; i > 0; i--)
    {
        MaxHeapComparison(headPtr, size + 1, i);
    }
}
