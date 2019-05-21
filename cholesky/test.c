#ifndef CN_CHOLESKY_TEST
#define CN_CHOLESKY_TEST
#include "./ops.c"
#include "../matriz/ops.c"
#include "assert.h"

void teste_de_algum_slide() {
    struct cn_matriz mtx;
    cn_matriz__init(&mtx, 3,3);
    cn_matriz__set(&mtx, 0, 0, 4);
    cn_matriz__set(&mtx, 1, 0, 2);
    cn_matriz__set(&mtx, 2, 0, -4);
    cn_matriz__set(&mtx, 0, 1, 2);
    cn_matriz__set(&mtx, 1, 1, 10);
    cn_matriz__set(&mtx, 2, 1, 4);
    cn_matriz__set(&mtx, 0, 2, -4);
    cn_matriz__set(&mtx, 1, 2, 4);
    cn_matriz__set(&mtx, 2, 2, 9);
    assert(cn_cholesky__check(&mtx) == SUCESS);
    struct cn_matriz res;
    assert(cn_cholesky__calc(&mtx, &res) == SUCESS);
    cn_matriz__prettyprint(&mtx);
    cn_matriz__prettyprint(&res);
    cn_matriz__destroy(&mtx);
    cn_matriz__destroy(&res);
}

int main() {
    teste_de_algum_slide();
}

#endif

