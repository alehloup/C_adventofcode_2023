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

static inline void numbers_around(int pos, char * lines[3], size_t out_numbers[9]) {
    size_t count = 0;

    for (int i = 0; i < 3; ++i) {
        char * line = lines[i];

        if (is_digit(line[pos])) {
            out_numbers[count] = number_from_start(pos, line);
            count += out_numbers[count] > 0 ? 1 : 0;
        } else {
            out_numbers[count] = number_from_start(pos-1, line);
            count += out_numbers[count] > 0 ? 1 : 0;

            out_numbers[count] = number_from_start(pos+1, line);
            count += out_numbers[count] > 0 ? 1 : 0;
        }
    }
    out_numbers[count] = 0;
}

static inline size_t sum_around(int pos, char * lines[3]) {
    size_t sum = 0;
    size_t numbers[9] = {0};
    
    numbers_around(pos, lines, numbers);
    for (int i = 0; numbers[i] != 0; ++i) {
        sum += numbers[i];
    }

    return sum;
}

static inline size_t mult_around(int pos, char * lines[3]) {
    size_t numbers[9] = {0};
    numbers_around(pos, lines, numbers);

    return numbers[2] == 0 ? numbers[0] * numbers[1] : 0;
}

static void run(void) {
    char top[256] = "", cur[256] = "", bot[256] = "";
    char * lines[3] = {top, cur, bot};

    size_t sum_parts = 0, sum_mult_parts = 0;

    int len = 0;

    FILE *f = fopen("aoc3.txt", "rb");
        fgets(top, 255, f);
        fgets(cur, 255, f);
        len = (int)strlen(cur);

        while (fgets(bot, 255, f) != 0) {
            for (int i = 0; i < len; ++i) {
                if (is_symbol(cur[i])) {
                    sum_parts += sum_around(i, lines);
                }
                if (cur[i] == '*') {
                    sum_mult_parts += mult_around(i, lines);
                }
            }

            memcpy(top, cur, 255);
            memcpy(cur, bot, 255);
        }

        printf("Sum of parts: %zu, Sum of multparts: %zu \n", sum_parts, sum_mult_parts);

    fclose(f);
}

int main(void) {
    clock_t bench = clock();
    run();
    printf("\n runned in %.3f seconds \n", (double)(clock() - bench)/CLOCKS_PER_SEC);

    return 0;
}
