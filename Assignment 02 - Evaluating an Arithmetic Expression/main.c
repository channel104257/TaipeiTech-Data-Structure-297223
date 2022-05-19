#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define dot ','

// 定義建立堆疊與串列所需的結構 (Infix轉Postfix用)
typedef struct StackNode
{
    // 儲存讀入字元
    char value;
    // 判斷為數字或運算元
    int chardetect;
    // 儲存下一節點的指標
    struct StackNode *nextPtr;

} stacknode;

// 重新定義結構之一階指標的名稱
typedef struct StackNode *stackPtr;

// 插入串列尾端
void insertlist(stackPtr *nodePtr, char info, int mode);
// 輸出串列第一的元素
char poplist(stackPtr *topPtr);
// 輸入資料進入堆疊
void push(stackPtr *topPtr, char info);
// 輸出堆疊中最上層的元素
char pop(stackPtr *topPtr);
// 判斷堆疊是否為空
int isEmpty(stackPtr topPtr);
// 顯示串列的所有元素
void printlist(stackPtr currentPtr, int mode);
// 優先權判斷
int priority(char op);

// 定義建立堆疊所需的結構 (計算Postfix用)
typedef struct CalculateNode
{
    // 儲存待運算數值
    double value;
    // 儲存下一節點的指標
    struct CalculateNode *nextPtr;

} calculateNode;

// 重新定義結構之一階指標的名稱
typedef struct CalculateNode *calculatePtr;

// 輸入資料進入堆疊
void pushDouble(calculatePtr *topPtr, double info);
// 輸出堆疊中最上層的元素
double popDouble(calculatePtr *topPtr);
// 對堆疊中數字進行計算
void calculate(calculatePtr *topPtr, char sign);

int main()
{
    // 建立堆疊(儲存運算符號)
    stackPtr stackNodePtr = NULL;
    // 建立串列(儲存infix後的數字與符號)
    stackPtr infixHeadPtr = NULL;
    // 建立串列(儲存傳換成postfix後的數字與符號)
    stackPtr postfixHeadPtr = NULL;
    // 逐字讀取的容器
    char value;
    // 設定步數旗標
    int step = 1;
    char trush;

    // 系統輸出 "Please enter the formula : " 在 Console 上
    printf("Please enter the formula : \n");
    // 在讀取到換行符'\n'之前逐字讀取字元
    while ((value = getchar()) != '\n')
    {
        insertlist(&infixHeadPtr, value, 1);
    }

    // 將串列的首位指標設為當前指標位置(後指標)
    stackPtr currentPtr = infixHeadPtr->nextPtr;
    // 定義前個指標為空(前指標)
    stackPtr previousPtr = infixHeadPtr;

    // 當串列的兩指標到達最後一位之前
    while (currentPtr != NULL)
    {
        // 如果兩指標的字元性質相異
        if (currentPtr->chardetect != previousPtr->chardetect)
        {
            // 若前指標讀取到數字
            if (previousPtr->chardetect == 0)
            {
                // 在移動到後指標之前
                while (currentPtr != previousPtr)
                {
                    // 將讀取到的數字直接插入postfix串列
                    insertlist(&postfixHeadPtr, previousPtr->value, 0);
                    // 前指標移向下個字元
                    previousPtr = previousPtr->nextPtr;
                }
                // 以逗號區隔下個符號
                insertlist(&postfixHeadPtr, dot, 0);
                // 將後指標向下移動至下個字元
                currentPtr = currentPtr->nextPtr;
                step = 1;
            }
            // 若前指標讀取到運算符
            // 接下來每個case做的事情都一樣
            else
            {
                switch (previousPtr->value)
                {
                // 若讀入左括號
                case '(':
                    // 直接推入堆疊中
                    push(&stackNodePtr, previousPtr->value);
                    // 將前指標移動至後指標位置
                    previousPtr = currentPtr;
                    // 將後指標向下移動至下個字元
                    currentPtr = currentPtr->nextPtr;
                    break;

                // 若讀入右括號
                case ')':
                    // 在讀取到左括號前，依序pop出堆疊中的運算符
                    while (stackNodePtr->value != '(')
                    {
                        // 將運算符推入存postfix的串列中
                        insertlist(&postfixHeadPtr, pop(&stackNodePtr), 0);
                        // 以逗號區隔下個符號
                        insertlist(&postfixHeadPtr, dot, 0);
                    }

                    // 建立零時容器吸收不須輸出的左括號
                    trush = pop(&stackNodePtr);
                    // 將前指標移動至後指標位置
                    previousPtr = currentPtr;
                    // 將後指標向下移動至下個字元
                    currentPtr = currentPtr->nextPtr;
                    break;

                case '+':
                case '-':
                case '/':
                case '%':
                case '^':
                    // 若堆疊內不是空的
                    if (!isEmpty(stackNodePtr))
                    {
                        // 若串列中的符號優先權大於讀入的 或 串列中的符號為左括號
                        if (priority(previousPtr->value) < priority(stackNodePtr->value) || stackNodePtr->value == '(')
                        {
                            // 直接推入堆疊中
                            push(&stackNodePtr, previousPtr->value);
                            // 將前指標移動至後指標位置
                            previousPtr = currentPtr;
                            // 將後指標向下移動至下個字元
                            currentPtr = currentPtr->nextPtr;
                            // 重製步數旗標
                            step = 1;
                            break;
                        }
                        else
                        {
                            // 先將運算符推入存postfix的串列中
                            insertlist(&postfixHeadPtr, pop(&stackNodePtr), 0);
                            // 以逗號區隔下個符號
                            insertlist(&postfixHeadPtr, dot, 0);
                            // 再將讀入的運算符直接推入堆疊中
                            push(&stackNodePtr, previousPtr->value);
                            // 將前指標移動至後指標位置
                            previousPtr = currentPtr;
                            // 將後指標向下移動至下個字元
                            currentPtr = currentPtr->nextPtr;
                            // 重製步數旗標
                            step = 1;
                            break;
                        }
                    }
                    else
                    {
                        // 直接推入堆疊中
                        push(&stackNodePtr, previousPtr->value);
                        // 將前指標移動至後指標位置
                        previousPtr = currentPtr;
                        // 將後指標向下移動至下個字元
                        currentPtr = currentPtr->nextPtr;
                        // 重製步數旗標
                        step = 1;
                        break;
                    }
                case '*':
                    // 若讀取到的運算符為兩個字元
                    if (step == 2)
                    {
                        // 若堆疊內不是空的
                        if (!isEmpty(stackNodePtr))
                        {
                            // 若串列中的符號優先權大於讀入的 或 串列中的符號為左括號
                            if (priority('p') < priority(stackNodePtr->value) || stackNodePtr->value == '(')
                            {
                                // 直接推入堆疊中
                                push(&stackNodePtr, 'p');
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                            else
                            {
                                // 先將運算符推入存postfix的串列中
                                insertlist(&postfixHeadPtr, pop(&stackNodePtr), 0);
                                // 以逗號區隔下個符號
                                insertlist(&postfixHeadPtr, dot, 0);
                                // 再將讀入的運算符直接推入堆疊中
                                push(&stackNodePtr, 'p');
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                        }
                        else
                        {
                            // 直接推入堆疊中
                            push(&stackNodePtr, 'p');
                            // 將前指標移動至後指標位置
                            previousPtr = currentPtr;
                            // 將後指標向下移動至下個字元
                            currentPtr = currentPtr->nextPtr;
                            // 重製步數旗標
                            step = 1;
                            break;
                        }
                    }
                    else
                    {
                        // 若堆疊內不是空的
                        if (!isEmpty(stackNodePtr))
                        {
                            // 若串列中的符號優先權大於讀入的 或 串列中的符號為左括號
                            if (priority(previousPtr->value) < priority(stackNodePtr->value) || stackNodePtr->value == '(')
                            {
                                // 直接推入堆疊中
                                push(&stackNodePtr, previousPtr->value);
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                            else
                            {
                                // 先將運算符推入存postfix的串列中
                                insertlist(&postfixHeadPtr, pop(&stackNodePtr), 0);
                                // 以逗號區隔下個符號
                                insertlist(&postfixHeadPtr, dot, 0);
                                // 再將讀入的運算符直接推入堆疊中
                                push(&stackNodePtr, previousPtr->value);
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                        }
                        else
                        {
                            // 直接推入堆疊中
                            push(&stackNodePtr, previousPtr->value);
                            // 將前指標移動至後指標位置
                            previousPtr = currentPtr;
                            // 將後指標向下移動至下個字元
                            currentPtr = currentPtr->nextPtr;
                            // 重製步數旗標
                            step = 1;
                            break;
                        }
                    }
                case '>':
                    // 若讀取到的運算符為兩個字元
                    if (step == 2)
                    {
                        // 若堆疊內不是空的
                        if (!isEmpty(stackNodePtr))
                        {
                            // 若串列中的符號優先權大於讀入的 或 串列中的符號為左括號
                            if (priority('r') < priority(stackNodePtr->value) || stackNodePtr->value == '(')
                            {
                                // 直接推入堆疊中
                                push(&stackNodePtr, 'r');
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                            else
                            {
                                // 先將運算符推入存postfix的串列中
                                insertlist(&postfixHeadPtr, pop(&stackNodePtr), 0);
                                // 以逗號區隔下個符號
                                insertlist(&postfixHeadPtr, dot, 0);
                                // 再將讀入的運算符直接推入堆疊中
                                push(&stackNodePtr, 'r');
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                        }
                        else
                        {
                            // 直接推入堆疊中
                            push(&stackNodePtr, 'r');
                            // 將前指標移動至後指標位置
                            previousPtr = currentPtr;
                            // 將後指標向下移動至下個字元
                            currentPtr = currentPtr->nextPtr;
                            // 重製步數旗標
                            step = 1;
                            break;
                        }
                    }
                    else
                    {
                        // 若堆疊內不是空的
                        if (!isEmpty(stackNodePtr))
                        {
                            // 若串列中的符號優先權大於讀入的 或 串列中的符號為左括號
                            if (priority(previousPtr->value) < priority(stackNodePtr->value) || stackNodePtr->value == '(')
                            {
                                // 直接推入堆疊中
                                push(&stackNodePtr, previousPtr->value);
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                            else
                            {
                                // 先將運算符推入存postfix的串列中
                                insertlist(&postfixHeadPtr, pop(&stackNodePtr), 0);
                                // 以逗號區隔下個符號
                                insertlist(&postfixHeadPtr, dot, 0);
                                // 再將讀入的運算符直接推入堆疊中
                                push(&stackNodePtr, previousPtr->value);
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                        }
                        else
                        {
                            // 直接推入堆疊中
                            push(&stackNodePtr, previousPtr->value);
                            // 將前指標移動至後指標位置
                            previousPtr = currentPtr;
                            // 將後指標向下移動至下個字元
                            currentPtr = currentPtr->nextPtr;
                            // 重製步數旗標
                            step = 1;
                            break;
                        }
                    }
                case '<':
                    // 若讀取到的運算符為兩個字元
                    if (step == 2)
                    {
                        // 若堆疊內不是空的
                        if (!isEmpty(stackNodePtr))
                        {
                            // 若串列中的符號優先權大於讀入的 或 串列中的符號為左括號
                            if (priority('l') < priority(stackNodePtr->value) || stackNodePtr->value == '(')
                            {
                                // 直接推入堆疊中
                                push(&stackNodePtr, 'l');
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                            else
                            {
                                // 先將運算符推入存postfix的串列中
                                insertlist(&postfixHeadPtr, pop(&stackNodePtr), 0);
                                // 以逗號區隔下個符號
                                insertlist(&postfixHeadPtr, dot, 0);
                                // 再將讀入的運算符直接推入堆疊中
                                push(&stackNodePtr, 'l');
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                        }
                        else
                        {
                            // 直接推入堆疊中
                            push(&stackNodePtr, 'l');
                            // 將前指標移動至後指標位置
                            previousPtr = currentPtr;
                            // 將後指標向下移動至下個字元
                            currentPtr = currentPtr->nextPtr;
                            // 重製步數旗標
                            step = 1;
                            break;
                        }
                    }
                    else
                    {
                        // 若堆疊內不是空的
                        if (!isEmpty(stackNodePtr))
                        {
                            // 若串列中的符號優先權大於讀入的 或 串列中的符號為左括號
                            if (priority(previousPtr->value) < priority(stackNodePtr->value) || stackNodePtr->value == '(')
                            {
                                // 直接推入堆疊中
                                push(&stackNodePtr, previousPtr->value);
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                            else
                            {
                                // 先將運算符推入存postfix的串列中
                                insertlist(&postfixHeadPtr, pop(&stackNodePtr), 0);
                                // 以逗號區隔下個符號
                                insertlist(&postfixHeadPtr, dot, 0);
                                // 再將讀入的運算符直接推入堆疊中
                                push(&stackNodePtr, previousPtr->value);
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                        }
                        else
                        {
                            // 直接推入堆疊中
                            push(&stackNodePtr, previousPtr->value);
                            // 將前指標移動至後指標位置
                            previousPtr = currentPtr;
                            // 將後指標向下移動至下個字元
                            currentPtr = currentPtr->nextPtr;
                            // 重製步數旗標
                            step = 1;
                            break;
                        }
                    }
                case '&':
                    // 若讀取到的運算符為兩個字元
                    if (step == 2)
                    {
                        // 若堆疊內不是空的
                        if (!isEmpty(stackNodePtr))
                        {
                            // 若串列中的符號優先權大於讀入的 或 串列中的符號為左括號
                            if (priority('a') < priority(stackNodePtr->value) || stackNodePtr->value == '(')
                            {
                                // 直接推入堆疊中
                                push(&stackNodePtr, 'a');
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                            else
                            {
                                // 先將運算符推入存postfix的串列中
                                insertlist(&postfixHeadPtr, pop(&stackNodePtr), 0);
                                // 以逗號區隔下個符號
                                insertlist(&postfixHeadPtr, dot, 0);
                                // 再將讀入的運算符直接推入堆疊中
                                push(&stackNodePtr, 'a');
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                        }
                        else
                        {
                            // 直接推入堆疊中
                            push(&stackNodePtr, 'a');
                            // 將前指標移動至後指標位置
                            previousPtr = currentPtr;
                            // 將後指標向下移動至下個字元
                            currentPtr = currentPtr->nextPtr;
                            // 重製步數旗標
                            step = 1;
                            break;
                        }
                    }
                    else
                    {
                        // 若堆疊內不是空的
                        if (!isEmpty(stackNodePtr))
                        {
                            // 若串列中的符號優先權大於讀入的 或 串列中的符號為左括號
                            if (priority(previousPtr->value) < priority(stackNodePtr->value) || stackNodePtr->value == '(')
                            {
                                // 直接推入堆疊中
                                push(&stackNodePtr, previousPtr->value);
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                            else
                            {
                                // 先將運算符推入存postfix的串列中
                                insertlist(&postfixHeadPtr, pop(&stackNodePtr), 0);
                                // 以逗號區隔下個符號
                                insertlist(&postfixHeadPtr, dot, 0);
                                // 再將讀入的運算符直接推入堆疊中
                                push(&stackNodePtr, previousPtr->value);
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                        }
                        else
                        {
                            // 直接推入堆疊中
                            push(&stackNodePtr, previousPtr->value);
                            // 將前指標移動至後指標位置
                            previousPtr = currentPtr;
                            // 將後指標向下移動至下個字元
                            currentPtr = currentPtr->nextPtr;
                            // 重製步數旗標
                            step = 1;
                            break;
                        }
                    }
                case '|':
                    // 若讀取到的運算符為兩個字元
                    if (step == 2)
                    {
                        // 若堆疊內不是空的
                        if (!isEmpty(stackNodePtr))
                        {
                            // 若串列中的符號優先權大於讀入的 或 串列中的符號為左括號
                            if (priority('o') < priority(stackNodePtr->value) || stackNodePtr->value == '(')
                            {
                                // 直接推入堆疊中
                                push(&stackNodePtr, 'o');
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                            else
                            {
                                // 先將運算符推入存postfix的串列中
                                insertlist(&postfixHeadPtr, pop(&stackNodePtr), 0);
                                // 以逗號區隔下個符號
                                insertlist(&postfixHeadPtr, dot, 0);
                                // 再將讀入的運算符直接推入堆疊中
                                push(&stackNodePtr, 'o');
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                        }
                        else
                        {
                            // 直接推入堆疊中
                            push(&stackNodePtr, 'o');
                            // 將前指標移動至後指標位置
                            previousPtr = currentPtr;
                            // 將後指標向下移動至下個字元
                            currentPtr = currentPtr->nextPtr;
                            // 重製步數旗標
                            step = 1;
                            break;
                        }
                    }
                    else
                    {
                        // 若堆疊內不是空的
                        if (!isEmpty(stackNodePtr))
                        {
                            // 若串列中的符號優先權大於讀入的 或 串列中的符號為左括號
                            if (priority(previousPtr->value) < priority(stackNodePtr->value) || stackNodePtr->value == '(')
                            {
                                // 直接推入堆疊中
                                push(&stackNodePtr, previousPtr->value);
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                            else
                            {
                                // 先將運算符推入存postfix的串列中
                                insertlist(&postfixHeadPtr, pop(&stackNodePtr), 0);
                                // 以逗號區隔下個符號
                                insertlist(&postfixHeadPtr, dot, 0);
                                // 再將讀入的運算符直接推入堆疊中
                                push(&stackNodePtr, previousPtr->value);
                                // 將前指標移動至後指標位置
                                previousPtr = currentPtr;
                                // 將後指標向下移動至下個字元
                                currentPtr = currentPtr->nextPtr;
                                // 重製步數旗標
                                step = 1;
                                break;
                            }
                        }
                        else
                        {
                            // 直接推入堆疊中
                            push(&stackNodePtr, previousPtr->value);
                            // 將前指標移動至後指標位置
                            previousPtr = currentPtr;
                            // 將後指標向下移動至下個字元
                            currentPtr = currentPtr->nextPtr;
                            // 重製步數旗標
                            step = 1;
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            // 將後指標向後移動
            currentPtr = currentPtr->nextPtr;
            // 運算符長度+1
            step++;
        }
    }

    // 若已掃描完畢還未有數字未讀出
    while (previousPtr != NULL)
    {
        // 將讀取到的數字直接插入postfix串列
        insertlist(&postfixHeadPtr, previousPtr->value, 0);
        // 移向下個指標
        previousPtr = previousPtr->nextPtr;
    }
    // 以逗號區隔下個符號
    insertlist(&postfixHeadPtr, dot, 0);

    // 讀取結束後，將堆疊中的運算符全部依序輸出
    while (stackNodePtr != NULL)
    {
        // 將讀取到的運算符直接插入postfix串列
        insertlist(&postfixHeadPtr, pop(&stackNodePtr), 0);
        // 以逗號區隔下個符號
        insertlist(&postfixHeadPtr, dot, 0);
    }

    printlist(postfixHeadPtr, 0);

    // 建立堆疊 (計算postfix算式)
    calculatePtr calculateTop = NULL;
    // 建立暫存數字
    int numtemp = 0;

    // 當讀取到的串列位址為空前，不停進行計算
    while (postfixHeadPtr != NULL)
    {
        // 建立暫存容器，讀取從postfix串列輸出的字元
        char temp = poplist(&postfixHeadPtr);

        // 判斷字元為數字或字元為
        switch (temp)
        {
        // 若讀取到 dot 直接略過
        case dot:
        case '(':
        case ')':
            break;

        // 字元為運算符
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '>':
        case '<':
        case '&':
        case '|':
        case '^':
        case 'a':
        case 'o':
        case 'p':
        case 'r':
        case 'l':
            // 將堆疊中的數字進行相對應的運算
            calculate(&calculateTop, temp);
            break;

        // 字元為數字
        default:

            // 在讀取到 dot 前，進行連續讀取
            while (temp != dot)
            {
                // 數字掃描迴圈
                for (int i = 48; i <= 57; i++)
                {
                    // 若讀入的數字符合該數字的ascii碼
                    if ((int)temp == i)
                    {
                        // 將數字算出再加上前個數字乘以10
                        numtemp = numtemp * 10 + (i - 48);
                        break;
                    }
                }
                // 讀取下個數字
                temp = poplist(&postfixHeadPtr);
            }

            // 將結果強制轉型後存入堆疊
            pushDouble(&calculateTop, (double)numtemp);
            // 重置暫存數字
            numtemp = 0;
            break;
        }
    }

    // 在 console 上輸出答案
    printf("\n%.13lf", popDouble(&calculateTop));
}

void insertlist(stackPtr *headPtr, char info, int mode)
{
    // 建立新的節點
    stackPtr newPtr = (stackPtr)malloc(sizeof(stacknode));

    // 記憶體擁有足夠的空間
    if (newPtr != NULL)
    {
        // 若使用模式 '1'
        // 會幫讀入的字元區分為數字或字元
        if (mode)
        {
            // 若讀入為數字
            if ((int)info >= 48 /* 0 */ && (int)info <= 57 /* 9 */)
            {
                // 將其字元在chardetect表示為'0'(數字)
                newPtr->chardetect = 0;
            }
            else if (info == '(' || info == ')')
            {
                // 將其字元在chardetect表示為'2'(括號)
                newPtr->chardetect = 2;
            }
            // 若讀入為符號
            else
            {
                // 將其字元在chardetect表示為'1'(符號)
                newPtr->chardetect = 1;
            }
        }

        // 將欲插入的字元存入節點中
        newPtr->value = info;
        // 將指向下的節點的指標指為空
        newPtr->nextPtr = NULL;

        // 將串列的首位指標設為當前指標位置
        stackPtr currentPtr = *headPtr;
        // 定義前個指標為空
        stackPtr previousPtr = NULL;

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
        printf("%c not inserted. No memory available.\n", info);
    }
}

char poplist(stackPtr *topPtr)
{
    // 建立暫存指標指向串列的頭
    stackPtr tempPtr = *topPtr;

    // 讀取串列頭所儲存的元素
    char output = tempPtr->value;
    // 將串列頭的指標指向串列的下一個元素
    *topPtr = (*topPtr)->nextPtr;
    // 釋放串列頭的記憶體空間
    free(tempPtr);

    // 輸出串列頭所儲存的元素
    return output;
}

void push(stackPtr *topPtr, char info)
{
    // 建立新的節點
    stackPtr newPtr = (stackPtr)malloc(sizeof(stacknode));

    // 若還有記憶體空間
    if (newPtr != NULL)
    {
        // 將欲插入的字元存入新節點中
        newPtr->value = info;
        // 將新節點所指向的下個位置指向當前堆疊的頂端
        newPtr->nextPtr = *topPtr;
        // 將堆疊的頂端位置指向剛建立的節點
        *topPtr = newPtr;
    }
    // 記憶體空間不足
    else
    {
        printf("%c not inserted. No memory available.\n", info);
    }
}

// pushDouble 函式只是推入堆疊的資料改成 double 型態，其運作內容相同於 push 函式
void pushDouble(calculatePtr *topPtr, double info)
{
    calculatePtr newPtr = (calculatePtr)malloc(sizeof(calculateNode));

    if (newPtr != NULL)
    {
        newPtr->value = info;
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
    }
    else
    {
        printf("%lf not inserted. No memory available.\n", info);
    }
}

char pop(stackPtr *topPtr)
{
    // 建立暫存指標指向堆疊的頂端
    stackPtr tempPtr = *topPtr;

    // 讀取堆疊頂端所儲存的元素
    char popValue = (*topPtr)->value;
    // 將堆疊頂端的指標指向堆疊內的下一個元素
    *topPtr = (*topPtr)->nextPtr;
    // 釋放堆疊頂端節點的記憶體空間
    free(tempPtr);

    // 輸出堆疊頂端所儲存的元素
    return popValue;
}

// popDouble 函式只是推入堆疊的資料改成 double 型態，其運作內容相同於 pop 函式
double popDouble(calculatePtr *topPtr)
{
    calculatePtr tempPtr = *topPtr;

    double popValue = (*topPtr)->value;
    *topPtr = (*topPtr)->nextPtr;
    free(tempPtr);

    return popValue;
}

int isEmpty(stackPtr topPtr)
{
    // 檢查串列頂端是否為空
    return topPtr == NULL;
}

void printlist(stackPtr currentPtr, int mode)
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
            switch (mode)
            {
            case 0:
                // 輸出該串列元素
                printf("%c", currentPtr->value);
                // 將當前串列位置往後移
                currentPtr = currentPtr->nextPtr;
                break;

            case 1:
                // 輸出該串列元素
                printf("%d", currentPtr->chardetect);
                // 將當前串列位置往後移
                currentPtr = currentPtr->nextPtr;
                break;
            }
        }
    }
}

int priority(char op)
{
    // 檢查該運符之優先權
    switch (op)
    {
    case 'p': // 次方 power
        return 3;

    case '*': // 乘法
    case '/': // 除法
    case '%': // 取mod
        return 5;

    case '+': // 加法
    case '-': // 減法
        return 6;

    case 'r': // 位元右移
    case 'l': // 位元左移
        return 7;

    case '>': // 大於
    case '<': // 小於
        return 8;

    case '&': // 位元 and
        return 10;

    case '^': // 位元 xor
        return 11;

    case '|': // 位元 or
        return 12;

    case 'a': // 邏輯 and
        return 13;

    case 'o': // 邏輯 or
        return 14;

    default:
        return 0;
    }
}

void calculate(calculatePtr *topPtr, char sign)
{
    // 分別讀出堆疊中的頂端兩組數字
    double temp2 = popDouble(topPtr);
    double temp1 = popDouble(topPtr);

    // 對不同運算符對兩數字進行相對應的運算
    switch (sign)
    {
    // 加法
    case '+':
        pushDouble(topPtr, temp1 + temp2);
        break;

    // 減法
    case '-':
        pushDouble(topPtr, temp1 - temp2);
        break;

    // 乘法
    case '*':
        pushDouble(topPtr, temp1 * temp2);
        break;

    // 除法
    case '/':
        pushDouble(topPtr, temp1 / temp2);
        break;

    // 取mod
    case '%':
        pushDouble(topPtr, (double)((int)temp1 % (int)temp2));
        break;

    // 大於
    case '>':
        pushDouble(topPtr, temp1 > temp2);
        break;

    // 小於
    case '<':
        pushDouble(topPtr, temp1 < temp2);
        break;

    // 位元 and
    case '&':
        pushDouble(topPtr, (double)((int)temp1 & (int)temp2));
        break;

    // 位元 xor
    case '^':
        pushDouble(topPtr, (double)((int)temp1 ^ (int)temp2));
        break;

    // 位元 or
    case '|':
        pushDouble(topPtr, (double)((int)temp1 | (int)temp2));
        break;

    // 次方 power
    case 'p':
        pushDouble(topPtr, pow(temp1, temp2));
        break;

    // 位元右移
    case 'r':
        pushDouble(topPtr, (double)((int)temp1 >> (int)temp2));
        break;

    // 位元左移
    case 'l':
        pushDouble(topPtr, (double)((int)temp1 << (int)temp2));
        break;

    // 邏輯 and
    case 'a':
        pushDouble(topPtr, (double)((int)temp1 && (int)temp2));
        break;

    // 邏輯 or
    case 'o':
        pushDouble(topPtr, (double)((int)temp1 || (int)temp2));
        break;

    default:
        break;
    }
}
