#include <stdlib.h>
#include <assert.h>

void array_facts(int size, int array[]);

#undef main
int main(int argc, char *argv[]) {
    int array[argc];
    for (int i = 1; i < argc; i++) {
        array[i - 1] = atoi(argv[i]);
    }
    array_facts(argc - 1, array);
    return 0;
}
