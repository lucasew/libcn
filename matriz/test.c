#include "./ops.c"
#include "./template.c"
#include <assert.h>

void multest() {
    struct cn_matriz ma;
    cn_matriz__init(&ma, 2, 2);
    cn_matriz__set(&ma, 0, 0, cn_fracao__init(1, 1));
    cn_matriz__set(&ma, 0, 1, cn_fracao__init(2, 1));
    cn_matriz__set(&ma, 1, 0, cn_fracao__init(3, 1));
    cn_matriz__set(&ma, 1, 1, cn_fracao__init(4, 1));
    struct cn_matriz mb;
    cn_matriz__init(&mb, 2, 2);
    cn_matriz__set(&mb, 0, 0, cn_fracao__init(-1, 1));
    cn_matriz__set(&mb, 0, 1, cn_fracao__init(3, 1));
    cn_matriz__set(&mb, 1, 0, cn_fracao__init(4, 1));
    cn_matriz__set(&mb, 1, 1, cn_fracao__init(2, 1));
    cn_matriz__prettyprint(&mb);
    struct cn_matriz mc;
    cn_matriz__mul(&ma, &mb, &mc);
    cn_matriz__prettyprint(&mc);
}

int main() {
    struct cn_matriz ma;
    struct cn_matriz mb;
    cn_matriz__init_identity(2, &ma);
    cn_matriz__init(&mb, 2, 2);
    cn_matriz__set(&mb, 0, 0, cn_fracao__init(2,1));
    cn_matriz__set(&mb, 1, 1, cn_fracao__init(2,1));
    cn_matriz__prettyprint(&ma);
    struct cn_matriz resmul;
    assert(!cn_matriz__mul(&ma, &mb, &resmul));
    cn_matriz__prettyprint(&resmul);
    cn_matriz__destroy(&ma);
    cn_matriz__destroy(&mb);
    multest();
}

