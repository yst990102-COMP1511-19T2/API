#include <stdio.h>

int main(int argc, char *argv[]) {
    int ch = getchar();
    while (ch != EOF) {
        printf("%d\n", ch);
        ch = getchar();
    }
    return 0;
}
