#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *buf;

int sum_to_n(int num)
{
    int i, sum = 0;
    for (i = 1; i <= num; i++)
        sum += i;
    return sum;
}

void printSum()
{
    char line[10];
    int len;
    printf("Enter a number:\n");
    fgets(line, 10, stdin);
    len = strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    buf = (char *) malloc(sizeof(char) * (strlen("sum=") + 10 + 1));
    if (buf == NULL) {
        fprintf(stderr, "Error: could not allocate memory for buf\n");
        exit(EXIT_FAILURE);
    }
    sprintf(buf, "sum=%d", sum_to_n(atoi(line)));
    printf("%s\n", buf);
    free(buf);
}

int main(void)
{
    printSum();
    return 0;
}