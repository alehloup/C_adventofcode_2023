#include <stdio.h>
#include <time.h>
#include <string.h>

static void run(void) {
    int game;
    size_t sum = 0;

    FILE *f = fopen("aoc2.txt", "r");
    while (fscanf(f, " Game %d: ", &game) == 1) {
        char color[8] = "";
        unsigned int qty = 0;
        char end = ',';

        printf("\nGame %d: ", game);
        while (end != '\n' && fscanf(f, " %u %6s ", &qty, color) == 2) {
            size_t len = strlen(color) - 1;
            end = color[len];

            sum += (size_t)game;

            switch(end) {
                case ',': 
                    color[len] = '\0';
                    printf("%u %s, ", qty, color);
                break;

                case ';': 
                    color[len] = '\0';
                    printf("%u %s || ", qty, color);
                break;
                
                default: 
                    printf("%u %s\n", qty, color);
                end='\n';
            }
        }
    }
    fclose(f);

    printf("\n%zu\n", sum);
}

int main(void) {
    clock_t bench = clock();
    run();
    printf("\nrunned in %.3f seconds.\n", (double)(clock() - bench)/CLOCKS_PER_SEC);

    return 0;
}
