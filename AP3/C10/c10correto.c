#include <stdlib.h>
#include <stdio.h>

int main(void)
{
        int *p;
        while(1)
        {
                p = (int *) malloc(128);
                printf("%ld\n", (long)p);
                free(p);
        }
        return (0);
}