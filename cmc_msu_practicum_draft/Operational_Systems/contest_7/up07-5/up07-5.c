#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct line {
    char op, type;
    unsigned addr;
    unsigned size;
    int unit;
} LINE;

typedef struct random_access_memory {
    unsigned memory_size;
    unsigned cache_size;
    unsigned block_size;
    unsigned block_count;
    unsigned **cache;
} RAM;

int
main(int argc, char **argv)
{
    RAM ram;
    ram.memory_size = strtol(argv[1], NULL, 10);
    ram.cache_size = strtol(argv[2], NULL, 10);
    ram.block_size = strtol(argv[3], NULL, 10);
    ram.block_count = ram.cache_size / ram.block_size;
    ram.cache = calloc(ram.block_count, sizeof(*ram.cache));
    for (int i = 0; i < ram.block_count; ++i) {
        ram.cache[i] = calloc(2, sizeof(**ram.cache));
    }
    unsigned cache_block_num, memory_block_num;
    unsigned long long misses = 0;
    LINE cur;
    memset(&cur, 0, sizeof(cur));
    while (scanf("%c%c%x%u%d\n", &cur.op, &cur.type, &cur.addr, &cur.size, &cur.unit) > 4) {
        if (cur.addr >= ram.memory_size) {
            ++misses;
            continue;
        }
        memory_block_num = cur.addr / ram.block_size;
        cache_block_num = memory_block_num % ram.block_count;
        if (ram.cache[cache_block_num][0] == 0) {
            ++ram.cache[cache_block_num][0];
        } else {
            if (ram.cache[cache_block_num][1] != memory_block_num) {
                ++misses;
            }
        }
        ram.cache[cache_block_num][1] = memory_block_num;
    }
    for (int i = 0; i < ram.block_count; ++i) {
        free(ram.cache[i]);
    }
    free(ram.cache);
    printf("%llu\n", misses);
    return 0;
}