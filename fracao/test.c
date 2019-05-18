#include "assert.h"
#include <stdio.h>
#include "./struct.c"
#include "./ops.c"
#include "./ops_sqrt.c"

#define div(a,b) cn_fracao__div(a, b)
#define mul(a,b) cn_fracao__mul(a, b)
#define sum(a,b) cn_fracao__sum(a, b)
#define sub(a,b) cn_fracao__sub(a, b)
#define cmp(a,b) cn_fracao__cmp(a, b)
#define init(a,b) cn_fracao__init(a, b)
#define pri(a) cn_fracao__prettyprint(a)
#define frsqrt(a) cn_fracao__sqrt(a)
#define dbl(a) cn_fracao__as_double(a)

void test(struct cn_fracao a, struct cn_fracao b) {
    if (!cmp(a, b)) {
        pri(a);
        printf(" does not equal ");
        pri(b);
    } else { \
        pri(a);
        printf(" == ");
        pri(b);
        printf("  OK!");
    } \
    printf("\n");

}

int main() {
    struct cn_fracao a = init(2,3);
    struct cn_fracao b = init(2,3);
    assert(cmp(a, b));
    test(sum(init(1,2), init(3,4)), init(10, 8));
    test(sub(init(1,2), init(3,4)), init(-2, 8));
    test(mul(init(2,3), init(5,7)), init(10, 21));
    test(div(init(9,2), init(7,3)), init(27, 14));
    assert((dbl(frsqrt(init(16, 25))) - dbl(init(4,5))) < 0.001);
    assert(((dbl(frsqrt(init(225, 100))) - dbl(init(150, 100)))) < 0.001);
}
