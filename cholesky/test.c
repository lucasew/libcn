#ifndef CN_CHOLESKY_TEST
#define CN_CHOLESKY_TEST
#include "./ops.c"
#include "../matriz/ops.c"
#include "assert.h"

int main() {
    struct cn_matriz mtx;
    cn_matriz__init(&mtx, 3,3);
    cn_matriz__set(&mtx, 0,0, cn_fracao__init(2,1));
    cn_matriz__set(&mtx, 1,0, cn_fracao__init(-1,1));
    cn_matriz__set(&mtx, 2,0, cn_fracao__init(0,1));
    cn_matriz__set(&mtx, 0,1, cn_fracao__init(-1,1));
    cn_matriz__set(&mtx, 1,1, cn_fracao__init(2,1));
    cn_matriz__set(&mtx, 2,1, cn_fracao__init(-1,1));
    cn_matriz__set(&mtx, 0,2, cn_fracao__init(0,1));
    cn_matriz__set(&mtx, 1,2, cn_fracao__init(-1,1));
    cn_matriz__set(&mtx, 2,2, cn_fracao__init(2,1));
    assert(cn_cholesky__check(&mtx));
}

#endif

