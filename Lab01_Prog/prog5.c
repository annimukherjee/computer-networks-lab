#include <stdio.h>

struct pkt
{
    unsigned char ch1;
    unsigned char ch2[2];
    unsigned char ch3;
};

typedef struct pkt Byte;

int main()
{
    Byte b;

    unsigned int num;

    printf("Enter a number: ");
    scanf("%u", &num);

    b.ch1 = (num & 0xFF);
    b.ch2[0] = ((num >> 8) & 0xFF);
    b.ch2[1] = ((num >> 16) & 0xFF);
    b.ch3 = ((num >> 24) & 0xFF);

    printf("Byte 1: %x\n", b.ch1);
    printf("Byte 2: %x \n", b.ch2[0]);
    printf("Byte 3: %x \n", b.ch2[1]);
    printf("Byte 4: %x \n", b.ch3);

    unsigned int aggregate = 0;

    aggregate |= b.ch1;
    aggregate |= (b.ch2[0] << 8);
    aggregate |= (b.ch2[1] << 16);
    aggregate |= (b.ch3 << 24);

    printf("Aggregate number: %u \n", aggregate);

    return 0;
}