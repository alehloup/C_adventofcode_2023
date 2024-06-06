#include <stdio.h>
#include <time.h>
#include <string.h>

#define REDC 12
#define GREENC 13
#define BLUEC 14

static void update_max(unsigned int *red, unsigned int *green, unsigned int *blue, unsigned int qty, char color) {
    switch (color) {
        case 'r': *red = qty > *red ? qty : *red; return;
        case 'g': *green = qty > *green ? qty : *green; return;
        case 'b': *blue = qty > *blue ? qty : *blue; return;
        default: return;
    }
}

static int is_invalid(unsigned int qty, char color) {
    switch (color) {
        case 'r': return qty > REDC; break;
        case 'g': return qty > GREENC; break;
        case 'b': return qty > BLUEC; break;
        default: return 1;
    }
}

static void run(void) {
    int game;
    size_t sum_valid_games = 0;
    size_t sum_power_mincubes = 0;

    FILE *f = fopen("aoc2.txt", "r");
    while (fscanf(f, " Game %d: ", &game) == 1) {
        size_t power_cube = 1;
        int valid_game = 1; 
        char end = ' ';

        char color[8] = "";
        unsigned int qty = 0;

        unsigned int maxred = 0, maxgreen = 0, maxblue = 0;

        while (end != '\n' && fscanf(f, " %u %6s ", &qty, color) == 2) {
            size_t len = strlen(color) - 1;
            end = color[len];
            end = end == ',' || end == ';' ? end : '\n';
            color[len] = end == '\n' ? color[len] : '\0';

            update_max(&maxred, &maxgreen, &maxblue, qty, color[0]);

            if (valid_game && is_invalid(qty, color[0])) {
                //printf("Invalid Game %d: [%u %s]\n", game, qty, color);
                valid_game = 0;
            }
        }

        if (valid_game) {
            sum_valid_games += (size_t)game;
        }

        power_cube = (maxred*maxgreen*maxblue);
        sum_power_mincubes += power_cube;
        //printf("Game %d: %zu\n", game, power_cube);
    }
    fclose(f);

    printf("\nsum_valid_games: %zu, sum_power_mincubes: %zu\n", sum_valid_games, sum_power_mincubes);
}

int main(void) {
    clock_t bench = clock();
    run();
    printf("\nrunned in %.3f seconds.\n", (double)(clock() - bench)/CLOCKS_PER_SEC);

    return 0;
}
