#include "pch.h"
#include <stdio.h>
#include <stdlib.h>

#define max_stack_size 3

typedef struct stack
{
	char element;
	//stack* nextptr;
};

stack* CreareS(int max_size);
bool IsFull(stack Stack[], int max_size);
void push(stack Stack[], char element, int max_size, int* top);
char Delete(stack Stack[], int* top);
void printStack(stack Stack[], int max_size);

int main()
{
	stack* Stack = CreareS(max_stack_size);

	Stack[0].element = 'a';
	Stack[1].element = 'b';
	Stack[2].element = 'c';

	int top = 2;

	printStack(Stack, max_stack_size);

	while (true)
	{
		printf("Select the function\n");
		printf("(1)push (2)pop : ");

		int select;

		scanf_s("%d", &select);

		if (select == 1)
		{
			getchar();
			char element;
			printf("Please enter the element : ");
			scanf_s("%c", &element);

			push(Stack, element, max_stack_size, &top);
		}
		else
		{
			printf("We pop %c\n", Delete(Stack, &top));
		}

		printStack(Stack, max_stack_size);
	}
	
	return 0;
}

stack* CreareS(int max_size)
{
	stack* newStack = (stack*)malloc(max_size*(sizeof(stack)));

	for (size_t i = 0; i < max_size; i++)
	{
		newStack[i].element = NULL;
	}

	return newStack;
}

bool IsFull(stack Stack[], int max_size)
{	
	return Stack[max_size - 1].element != NULL;
}

void push(stack Stack[], char element, int max_size, int* top)
{
	if (IsFull(Stack, max_size))
	{
		printf("The stack is Full.");
	}
	else
	{
		(*top)++;
		Stack[*top].element = element;
	}

}

bool IsEmpty(stack Stack[])
{
	return Stack[0].element == NULL;
}

char Delete(stack Stack[], int* top)
{
	if (IsEmpty(Stack))
	{
		printf("The stack is EMPTY.");
	}
	else
	{
		char temp = Stack[*top].element;

		Stack[*top].element = NULL;
		(*top)--;

		return temp;
	}
}

void printStack(stack Stack[], int max_size)
{
	for (size_t i = 0; i < max_size; i++)
	{
		if (Stack[i].element == NULL)
		{
			break;
		}
		printf("%5c", Stack[i].element);
	}

	printf("\n");
}
