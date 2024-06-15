#include <stdio.h>
#include <time.h>
#include <string.h>

enum { REDC = 12, GREENC = 13, BLUEC = 14 };

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
        case 'r': return qty > REDC;
        case 'g': return qty > GREENC;
        case 'b': return qty > BLUEC;
        default: return 1;
    }
}

static void run(void) {
    int game;
    size_t sum_valid_games = 0;
    size_t sum_power_mincubes = 0;

    FILE *f = fopen("aoc2.txt", "r");
        while (fscanf(f, /* Game 5: */ " Game %d: ", &game) == 1) {
            unsigned int qty = 0; char color[8] = "";

            int valid_game = 1;

            unsigned int maxred = 0, maxgreen = 0, maxblue = 0;

            while (fscanf(f, /* 1 red, 2 blue; 5 red, 3 green; 8 red\n */ " %u %6s ", &qty, color) == 2) {
                valid_game = valid_game && !is_invalid(qty, color[0]);
                
                update_max(&maxred, &maxgreen, &maxblue, qty, color[0]);
            }

            sum_valid_games += valid_game ? (size_t)game : 0;

            sum_power_mincubes += (maxred*maxgreen*maxblue);
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
