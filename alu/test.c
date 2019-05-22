#ifndef CN_ALU_TEST
#define CN_ALU_TEST
#include <assert.h>
#include "../matriz/ops.c"
#include "./ops.c"

void test_validade() {
    struct cn_matriz mtx;
    cn_matriz__init(&mtx, 3, 3);
    cn_matriz__set(&mtx, 0, 0, 2);
    cn_matriz__set(&mtx, 1, 0, 1);
    cn_matriz__set(&mtx, 2, 0, 3);
    cn_matriz__set(&mtx, 0, 1, 0);
    cn_matriz__set(&mtx, 1, 1, -1);
    cn_matriz__set(&mtx, 2, 1, 1);
    cn_matriz__set(&mtx, 0, 2, 1);
    cn_matriz__set(&mtx, 1, 2, 0);
    cn_matriz__set(&mtx, 2, 2, 3);
    assert(cn_lu__check(&mtx) == SUCESS);
    cn_matriz__destroy(&mtx);
}

void test_decomposicao() {
    struct cn_matriz a, l, u;
    cn_matriz__init(&a, 3, 3);
    cn_matriz__set(&a, 0, 0, 2);
    cn_matriz__set(&a, 0, 1, 1);
    cn_matriz__set(&a, 0, 2, 3);
    cn_matriz__set(&a, 1, 0, 0);
    cn_matriz__set(&a, 1, 1, -1);
    cn_matriz__set(&a, 1, 2, 1);
    cn_matriz__set(&a, 2, 0, 1);
    cn_matriz__set(&a, 2, 1, 0);
    cn_matriz__set(&a, 2, 2, 3);
    /*assert(*/cn_lu__calc(&a, &l, &u)/* == SUCESS);*/;
    cn_matriz__prettyprint(&a);
    cn_matriz__prettyprint(&l);
    cn_matriz__prettyprint(&u);
    assert(l.vet[0] == 1);
    assert(l.vet[3] == 0);
    assert(l.vet[6] == 0.5);
    assert(u.vet[0] == 2);
    assert(u.vet[2] == 3);
    assert(u.vet[8] == 1);
    cn_matriz__destroy(&a);
    cn_matriz__destroy(&l);
    cn_matriz__destroy(&u);
}

int main() {
    test_validade();
    test_decomposicao();
}

#endif
