#include <stdio.h>
#include <time.h>
#include <string.h>

static const char *const spelled[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
static const size_t  spelled_len[9] = {  3,     3,      5,       4,      4,     3,      5,       5,      4};

enum { use_only_digit = 1, use_literals = 0};

static inline char number(char line[256], size_t idx, size_t len, int only_digit) {
    size_t remaining = len - idx;

    if (line[idx] >= '0' && line[idx] <= '9') {
        return line[idx] - '0';
    }

    if (only_digit == use_only_digit) {
        return 0;
    }

    for (unsigned int i = 0; i < 9; ++i) {
        if (remaining >= spelled_len[i] && memcmp(&line[idx], spelled[i], spelled_len[i])==0) {
            return (char)i+1;
        }
    }

    return 0;
}

static inline void run(void) {
    size_t sum_digits = 0, sum_literals = 0;
    char line[256];
    FILE *f = fopen("aoc1.txt", "r");
        while (fgets(line, 256, f) != 0) {
            char first = 0, last = 0;
            size_t len = strlen(line);
            
            for (size_t i = 0; i < len; ++i) {
                char n = number(line, i, len, use_only_digit);
                if (n != 0) {
                    first = n;
                    break;
                }
            }
            for (size_t i = 1; i <= len; ++i) {
                size_t idx = len - i;
                char n = number(line, idx, len, use_only_digit);
                if (n != 0) {
                    last = n;
                    break;
                }
            }
            sum_digits += (size_t)first*10 + (size_t)last;


            for (size_t i = 0; i < len; ++i) {
                char n = number(line, i, len, use_literals);
                if (n != 0) {
                    first = n;
                    break;
                }
            }
            for (size_t i = 1; i <= len; ++i) {
                size_t idx = len - i;
                char n = number(line, idx, len, use_literals);
                if (n != 0) {
                    last = n;
                    break;
                }
            }
            sum_literals += (size_t)first*10 + (size_t)last;
        }

        printf("using digits: %zu using literals: %zu\n", sum_digits, sum_literals);
    fclose(f);
}

int main(void) {
    clock_t start = clock();
    run();
    printf("runned in %f seconds\n", (double)(clock() - start) / (double)CLOCKS_PER_SEC);

    return 0;
}
