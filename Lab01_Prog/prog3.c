// Write a C program to extract each byte from a given number and store them in separate character
// variables and print the content of those variables

#include <stdio.h>



int main()
{
    unsigned int num;
    unsigned char b1, b2, b3, b4;

    printf("Enter a number: ");
    scanf("%u", &num);

    b1 = (num & 0xFF);
    b2 = ((num >> 8) & 0xFF);
    b3 = ((num >> 16) & 0xFF);
    b4 = ((num >> 24) & 0xFF);

    printf("Byte 1: %x\n", b1);
    printf("Byte 2: %x \n", b2);
    printf("Byte 3: %x \n", b3);
    printf("Byte 4: %x \n", b4);

    return 0;
}