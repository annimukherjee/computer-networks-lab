// Write a C program to swap the content of 2 variables entered through the command line 
// using function and pointer.

#include <stdio.h>
#include <stdlib.h>

void valueSwap(int a, int b);
void refSwap(int *a, int *b);

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Enter 3 arguments");
		return 1;
	}

	int num1 = atoi(argv[1]);
	int num2 = atoi(argv[2]);

	printf("Num1 before swap: %d\n", num1);
	printf("Num2 before swap: %d\n", num2);

	valueSwap(num1, num2);

	printf("Num1 after value swap: %d \n", num1);
	printf("Num2 after value swap: %d \n", num2);

	refSwap(&num1, &num2);

	printf("Num1 after ref swap: %d\n", num1);
	printf("Num2 after ref swap:  %d\n", num2);

	return 0;
}

void valueSwap(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;

	printf("Value of num1: %d (Value swap) \n", a);
	printf("Value of num2: %d (Value swap) \n", b);
}

void refSwap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;

	printf("Value of num1: %d (Ref swap) \n", *a);
	printf("Value of num2: %d (Ref swap) \n", *b);
}