#include <string.h>
#include <stdio.h>
#include <time.h>

static inline int is_symbol(char c) {
    return c != '.' && c > ' ' && (c < '0' || c > '9');
}
static inline int is_digit(char c) {
    return c >= '0' && c <= '9';
}

static inline size_t number_from_start(int pos, char line[256]) {
    size_t number = 0;
    if (!is_digit(line[pos])) {
        return number;
    }

    while (pos > 0 && is_digit(line[pos-1])) {
        --pos;
    }
    sscanf(&line[pos], "%zu", &number);

    return number;
}

static inline size_t sum_around(int pos, char top[256], char cur[256], char bot[256]) {
    size_t sum = 0;

    sum += number_from_start(pos, top) 
        + ( top[pos] == '.' ? number_from_start(pos-1, top) + number_from_start(pos+1, top) : (size_t)0 );

    sum += number_from_start(pos-1, cur) + number_from_start(pos+1, cur);

    sum += number_from_start(pos, bot)
        + ( bot[pos] == '.' ? number_from_start(pos-1, bot) + number_from_start(pos+1, bot) : (size_t)0 ); 

    return sum;
}

void run(void) {
    char top[256] = "", cur[256] = "", bot[256] = "";
    int len = 0;
    size_t sum_parts = 0;

    FILE *f = fopen("aoc3.txt", "rb");
        fgets(top, 255, f);
        fgets(cur, 255, f);
        len = (int)strlen(cur);

        while (fgets(bot, 255, f) != 0) {
            for (int i = 0; i < len; ++i) {
                if (is_symbol(cur[i])) {
                    sum_parts += sum_around(i, top, cur, bot);
                }
            }

            memcpy(top, cur, 255);
            memcpy(cur, bot, 255);
        }

        printf("Sum of parts: %zu\n", sum_parts);

    fclose(f);
}

int main(void) {
    clock_t bench = clock();
    run();
    printf("\n runned in %.3f seconds \n", ((double)clock() - bench)/CLOCKS_PER_SEC);

    return 0;
}
