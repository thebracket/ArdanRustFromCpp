#include <stdio.h>
#include <limits.h>

int main() {
   char a = 127;
   char add = 1;
   if (a > 0 && add > 0 && a > CHAR_MAX - add) {
      printf("Overflow detected\n");
      return 1;
   }
   a = a + add;
   printf("a = %d\n", a);
   return 0;
}
