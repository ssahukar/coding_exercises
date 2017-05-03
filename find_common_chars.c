/* Given two strings, find the common characters between the two
 * strings. For ex, "Hello world" and "woowrd" have "word" as common
 * characters.
 *
 * The solution below has O(n) complexity and is not case sensitive
 */

#include<stdio.h>

int main() {
    char a[] = "Hello world";
    char b[] = "woowrd";
    int x[26] = {0};
    int i;
    int index;

    for (i = 0; a[i] != '\0'; i++) {
        index = a[i] - 'a';
        if (index > 26) {
            //capital char
            index = a[i] - 'A';
        }
        x[index]++;
    }

    for (i = 0; b[i] != '\0'; i++) {
        index = b[i] - 'a';
        if (index > 26) {
            //capital char
            index = b[i] - 'A';
        }

        if (x[index] > 0)
            x[index] = -1;
    }

    printf("Common characters in '%s' and '%s' are ", a, b);
    for (i = 0; i < 26; i++) {
        if (x[i] < 0)
            printf("%c", 'a'+i);
    }
    printf("\n");
}
