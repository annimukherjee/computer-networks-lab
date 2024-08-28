// Write a C program to check whether the Host machine is in Little Endian or Big Endian. Enter a
// number, print the content of each byte locationand Convert the Endianness of the same i.e. Little to
// Big Endianand vice-versa.


// UNSURE IF THIS CODE IS CORRECT OR NOT.....

#include <stdio.h>

void reverseBytes(int *num)
{
    char *ptr, temp;

    ptr = (char *)num;

    temp = *(ptr + 0);
    *(ptr + 0) = *(ptr + 3);
    *(ptr + 3) = temp;

    temp = *(ptr + 1);
    *(ptr + 1) = *(ptr + 2);
    *(ptr + 2) = temp;
}

int main()
{

    int num = 258;
    // int temp = num;
    // char LSB = num;
    // char ch = 'A';

    // printf("%d\n", LSB);
    // printf("%d\n", temp >> 8);
    // printf("%d\n", temp >> 16);
    // printf("%d\n", temp >> 24);
    // printf("temp: %d\n", temp);

    // char *ptr_1 = (char *)&num;
    char *ptr = (char *)&num;
    // char *ptr_2 = (char *)&num;
    printf("------\n");

    // int LSB_3 = *ptr;
    // int LSB_2 = *(ptr+1);
    // int LSB_1 = *(ptr+2);
    // int LSB_0 = *(ptr+3);

    // char *c;
    // c = ptr_1;
    // ptr_1 = *(ptr_1 + 3);
    // ptr_1 = c;

    // char* ptr;

    printf("%d\n", *ptr);
    printf("%d\n", *(ptr+1));
    printf("%d\n", *(ptr+2));
    printf("%d\n", *(ptr+3));

    printf("%x\n", num);
    reverseBytes(&num);

    printf("reversal done----\n");
    printf("%d\n", *ptr);
    printf("%d\n", *(ptr+1));
    printf("%d\n", *(ptr+2));
    printf("%d\n", *(ptr+3));

    printf("%x\n", num);
    printf("%d\n", num);
    return 0;

    // c=0;
    // c = LSB_1;
    // LSB_1 = LSB_2;
    // LSB_2 = c;

    // printf("%d\n", *ptr_1);
    // printf("%d\n", *(ptr_1 + 1));
    // printf("%d\n", *(ptr_1 + 2));
    // printf("%d\n", *(ptr_1 + 3));

    // printf("------\n");

    // printf("%d\n", *ptr_1);
    // printf("%d\n", *(ptr_1 + 1));
    // printf("%d\n", *(ptr_1 + 2));
    // printf("%d\n", *(ptr_1 + 3));

    // printf("------\n");

    // int c;
    // c = *(ptr)
    // ptr = *(ptr+3);
    // *(ptr+3) = c;

    // printf("\n");

    return 0;
}
