#include <stdio.h>
#include <time.h>

static void run(void) {
    char line[256];
    FILE *f = fopen("aoc2.txt", "r");
    while (fgets(line, 256, f) != 0) {
        printf("%s", line);
    }
    fclose(f);
}

int main(void) {
    clock_t bench = clock();
    run();
    printf("\nrunned in %f seconds.\n", (double)(clock() - bench)/CLOCKS_PER_SEC);

    return 0;
}
