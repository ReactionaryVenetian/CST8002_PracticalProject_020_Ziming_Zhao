/*
Author: Ziming Zhao 041166304
Sources: now done in IEEE style in the source code! :)

This is the business layer

[1] T. Newman, “Unit testing basics: 6 best practices to get up to speed,” Stackify, Mar. 6, 2018. [Online]. 
Available: https://stackify.com/unit-testing-basics-best-practices/ [Accessed: Feb. 10, 2026]. Talks a lot about what Unit testing isn’t to isolate what it is.

[2] Throw The Switch, “Unity: Getting Started Guide,” Unity C Unit Testing Framework Documentation, 2024. [Online]. 
Available: https://raw.githubusercontent.com/ThrowTheSwitch/Unity/master/docs/UnityGettingStartedGuide.md [Accessed: Feb. 10, 2026]. 
I installed this for testing, so I might as well read the documentation.
 
[3] “Assert in C and C++,” YouTube, Jul. 2022. [Online]. Available: https://www.youtube.com/watch?v=iXIuOe1agH4 [
Accessed: Feb. 14, 2026]. Talks abut asserts in C, with some good examples.

*/

#include <stdio.h>
#include <assert.h>
#include "Processor.h"

int add(int a, int b);   /* forward declaration - guarantees compiler knows add() */

int add(int a, int b) {
    return a + b;
}

/* Test should PASS */
void do_positive_test(void) {
    printf("Positive test: add(2, 3) == 5\n");
    assert(add(2, 3) == 5);
    printf("Positive test passed.\n\n");
}

/*
    Negative-input test (still PASSES).
    “Negative” here means using negative numbers, not failing on purpose.
*/
void do_negative_test(void) {
    printf("Negative-input test: add(-2, 3) == 1\n");
    assert(add(-2, 3) == 1);
    printf("Negative-input test passed.\n\n");
}

/*
    Optional: demonstration of an assert FAIL.
    Call this only if you WANT the program to abort.
*/
void do_demo_fail_test(void) {
    printf("Demo fail test: add(2, 3) == 6 (this will abort)\n");
    assert(add(2, 3) == 6);
    printf("This line will never print.\n");
}

void clear_input_line(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* discard */
    }
}
