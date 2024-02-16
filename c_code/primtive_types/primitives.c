#include <stdio.h>

int main() {
    char c = 'a';
    unsigned char uc = 12;
    int i = 123;
    unsigned int ui = 123;
    short s = 123;
    unsigned short us = 123;
    long l = 123;
    unsigned long ul = 123;

    printf("%d    %ld\n", c, sizeof(c));
    printf("%d    %ld\n", uc, sizeof(uc));
    printf("%d    %ld\n", i, sizeof(i));
    printf("%d    %ld\n", ui, sizeof(ui));
    printf("%d    %ld\n", s, sizeof(s));
    printf("%d    %ld\n", us, sizeof(us));
    printf("%ld    %ld\n", l, sizeof(l));
    printf("%ld    %ld\n", ul, sizeof(ul));
    return 0;
}