#include <stdlib.h>
 #include <stdio.h>

 #define MAX 2000

 int main(void) {

 for (long int k = 0; k < MAX; ++k) {
 for (long int j = k * k; j > 0; --j) {
 putchar('0' + rand() % 10);
 }
 putchar('\n');
 }
 return EXIT_SUCCESS;
 }
