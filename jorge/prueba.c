#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b;
    int *c = malloc(sizeof(int *));

    a = 31;
    b = 5;
    *c = a/b + (a%b > 0);
    printf("%d, %d", *c, a%b);

    return 0;
}