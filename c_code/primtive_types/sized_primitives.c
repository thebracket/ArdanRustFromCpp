#include <stdio.h>
#include <stdint.h>

int main() {
    int8_t c = 'a';
    uint8_t uc = 12;
    int32_t i = 123;
    uint32_t ui = 123;
    int16_t s = 123;
    uint16_t us = 123;
    int64_t l = 123;
    uint64_t ul = 123;

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