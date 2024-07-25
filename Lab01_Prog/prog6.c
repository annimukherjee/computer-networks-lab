#include <stdio.h>

struct pkt
{
    char ch[8];
    int num1;
    int num2;
};

struct pkt1
{
    char ch1;
    char ch2;
};

int main()
{
    struct pkt pkt;

    pkt.ch[0] = 'a';
    pkt.ch[1] = 'b';
    pkt.ch[2] = 'c';
    pkt.ch[3] = 'd';
    pkt.ch[4] = 'e';
    pkt.ch[5] = 'f';
    pkt.ch[6] = 'g';
    pkt.ch[7] = 'h';
    pkt.num1 = 12;
    pkt.num2 = 34;

    struct pkt1 pkt1;
    char *p = (char *)&pkt;
    int i;
    for (i = 0; i < 16; i += 2)
    {
        pkt1.ch1 = *(p + i);
        pkt1.ch2 = *(p + i + 1);
        if (i < 8)
        {
            printf("Extracted 2 bytes: %c %c\n", pkt1.ch1, pkt1.ch2);
        }
        else
        {
            int *num_ptr = (int *)(p + i);
            int num = *num_ptr;
            printf("Extracted 2 bytes: %d\n", num);
        }
    }

    return 0;
}