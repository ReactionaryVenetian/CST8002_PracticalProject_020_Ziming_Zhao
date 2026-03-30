/**
 * CST8002 Programming Language Research Project
 * Practical Project Part 02 – Project Review I
 *
 * Author: Ziming Zhao 041166304
 * Professor: Stanley Pieda
 * Due Date: 2026-02-22
 *
 * Description:
 * Implements pseudo UUID generation for filename uniqueness. Based on the time, just like a lot of RNG stuff. Not totally
 * random but good enough for this project.
 *
 * References:
 * [1] Stack Overflow, "Generating a random UUID in C," Stack Overflow, 2018.
 *     [Online]. Available: https://stackoverflow.com/questions/51053568/generating-a-random-uuid-in-c
 *     [Accessed: Feb. 22, 2026]. So I got the idea from this, but man I am confused to the implementation of UUIDs in C.
 *
 * [2] cppreference.com, "rand," C standard library reference.
 *     [Online]. Available: https://en.cppreference.com/w/c/numeric/random/rand
 *     [Accessed: Feb. 22, 2026]. Used for pseudo-random numbers in the UUID-like string.
 *
 * [3] cppreference.com, "srand," C standard library reference.
 *     [Online]. Available: https://en.cppreference.com/w/c/numeric/random/srand
 *     [Accessed: Feb. 22, 2026]. Seeds the RNG once so the sequence differs between runs.
 *
 * [4] cppreference.com, "time," C standard library reference.
 *     [Online]. Available: https://en.cppreference.com/w/c/chrono/time
 *     [Accessed: Feb. 22, 2026]. Used as part of the RNG seed.
 *
 * [5] cppreference.com, "clock," C standard library reference.
 *     [Online]. Available: https://en.cppreference.com/w/c/chrono/clock
 *     [Accessed: Feb. 22, 2026]. Mixed into the seed to reduce repeat chance within the same second.
 *
 * [6] cppreference.com, "Integer types (stdint.h) and uintptr_t," C standard library reference.
 *     [Online]. Available: https://en.cppreference.com/w/c/types/integer
 *     [Accessed: Feb. 22, 2026]. Used for uintptr_t to safely mix pointer values into the seed.
 */
 

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Misc.h"

/**
 * Generates a pseudo-random UUID v4-style string. Uh.... I just realized that it's random, not unique
 * Well w/e it's like stastically unique enough for this project, and it's not like I'm generating millions of them or anything.
 * Output format is 36 chars + null terminator (requires out_size >= 37).
 *
 * @param out Output buffer to store the UUID string.
 * @param out_size Size of the output buffer (must be at least 37).
 * @return 0 on success, non-zero on failure.
 */

int uuid_generate_v4(char *out, size_t out_size) {
    if (out == NULL || out_size < 37) {
        return 1;
    }

    static int seeded = 0;
    static unsigned long counter = 0;

    if (!seeded) {
        /* Mix several changing values for a better seed across runs */
        unsigned int seed =
            (unsigned int)time(NULL) ^
            (unsigned int)clock() ^
            (unsigned int)(uintptr_t)&seeded ^
            (unsigned int)(uintptr_t)out;

        srand(seed);
        seeded = 1;
    }

    counter++;

    /* Mix counter to avoid repeats inside a single program run */
    unsigned int a = (unsigned int)rand() ^ (unsigned int)counter;
    unsigned int b = (unsigned int)rand();
    unsigned int c = ((unsigned int)rand() & 0x0FFFu) | 0x4000u;          /* version 4 */
    unsigned int d = ((unsigned int)rand() & 0x3FFFu) | 0x8000u;          /* variant */
    unsigned int e = (unsigned int)rand() ^ (unsigned int)(counter << 16);

    snprintf(out, out_size,
             "%08x-%04x-%04x-%04x-%012x",
             a,
             b & 0xFFFFu,
             c,
             d,
             e);

    return 0;
}