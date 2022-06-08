#include <stdio.h>
#include <stdlib.h>

typedef struct HeapNode
{
    int data;
    struct HeapNode *nextPtr;
} heapnode;

// ���s�w�q���c���@�����Ъ��W��
typedef struct HeapNode *heapPtr;

// ���J��C����
void insertlist(heapPtr *nodePtr, int info);
// ��ܦ�C���Ҧ�����
void printlist(heapPtr currentPtr);
//
int nodecount(heapPtr currentPtr);
//
heapPtr MoveToNode(heapPtr nodePtr, int num);
//
void swap(int *num1, int *num2);
//
void MinHeapComparison(heapPtr headPtr, int size, int No);
//
void HeapSort(heapPtr headPtr, int size);

int main()
{
    char value;
    int tempNum = 0;
    heapPtr heapNodeHead = NULL;

    printf("�п�J Heap �� Level-Order Traversal\n");
    printf("(�ХH�u�Ů�v�Ϲj�U��node)\n-> ");

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
        MinHeapComparison(heapNodeHead, nodecount(heapNodeHead), i);
    }

    printf("Min Heap\n");
    printlist(heapNodeHead);

    HeapSort(heapNodeHead, nodecount(heapNodeHead));
    printf("After HeapSort\n");
    printlist(heapNodeHead);
}

void insertlist(heapPtr *headPtr, int info)
{
    // �إ߷s���`�I
    heapPtr newPtr = (heapPtr)malloc(sizeof(heapPtr));

    // �O����֦��������Ŷ�
    if (newPtr != NULL)
    {
        // �N�����J���r���s�J�`�I��
        newPtr->data = info;
        // �N���V�U���`�I�����Ы�����
        newPtr->nextPtr = NULL;

        // �N��C��������г]����e���Ц�m
        heapPtr currentPtr = *headPtr;
        // �w�q�e�ӫ��Ь���
        heapPtr previousPtr = NULL;

        // �N��e���Ц�m���ʦܦ�C�̧���
        while (currentPtr != NULL)
        {
            // �N�e�ӫ��Ъ���m�]����e����
            previousPtr = currentPtr;
            // �N��e���Ц�m�V�U�Ӹ`�I����
            currentPtr = currentPtr->nextPtr;
        }

        // �Y��C���S���b�Ӥ���
        if (previousPtr == NULL)
        {
            // �N�s�`�I�ҫ��V���U�Ӫ̼Ц�m���VŪ�J��C���Y(NULL)
            newPtr->nextPtr = *headPtr;
            // �N����C����m�����s�`�I
            *headPtr = newPtr;
        }
        else
        {
            // �N�e�@�ӫ��Ъ��ҫ��V���U�Ӧ�m���V�s�W���`�I
            previousPtr->nextPtr = newPtr;
            // �N�s�`�I���ҫ��V���U�ӫ��Ы��V��e�`�I
            newPtr->nextPtr = currentPtr;
        }
    }
    // �O����Ŷ��κ�
    else
    {
        printf("%d not inserted. No memory available.\n", info);
    }
}

void printlist(heapPtr currentPtr)
{
    // �ˬd��e��C�O�_����
    if (currentPtr == NULL)
    {
        puts("The stack is empty.\n");
    }
    else
    {
        // �N��e��C��m���Ჾ�����F����
        while (currentPtr != NULL)
        {
            // ��X�Ӧ�C����
            printf("%d ", currentPtr->data);
            // �N��e��C��m���Ჾ
            currentPtr = currentPtr->nextPtr;
        }
        printf("\n");
    }
}

int nodecount(heapPtr currentPtr)
{
    // �ˬd��e��C�O�_����
    if (currentPtr == NULL)
    {
        return 0;
    }
    else
    {
        int nodeNum = 0;

        // �N��e��C��m���Ჾ�����F����
        while (currentPtr != NULL)
        {
            // �N��e��C��m���Ჾ
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
        // �N��e��C��m���Ჾ
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

void MinHeapComparison(heapPtr headPtr, int size, int No)
{
    int smallest = No;
    int left = 2 * No;
    int right = 2 * No + 1;

    // If left child is smaller than root
    if (left < size && MoveToNode(headPtr, left)->data < MoveToNode(headPtr, smallest)->data)
    {
        smallest = left;
    }
    if (right < size && MoveToNode(headPtr, right)->data < MoveToNode(headPtr, smallest)->data)
    {
        smallest = right;
    }
    if (smallest != No)
    {
        swap(&MoveToNode(headPtr, No)->data, &MoveToNode(headPtr, smallest)->data);
        MinHeapComparison(headPtr, size, smallest);
    }
}

void HeapSort(heapPtr headPtr, int size)
{
    for (size_t i = 1; i <= size; i++)
    {
        swap(&MoveToNode(headPtr, 1)->data, &MoveToNode(headPtr, size - i + 1)->data);

        MinHeapComparison(headPtr, size - i, 1);
    }
}