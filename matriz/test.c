#include "./ops.c"
#include "./template.c"
#include <assert.h>

void menor_principal() {
    struct cn_matriz mtx;
    struct cn_matriz res;
    cn_matriz__init(&mtx, 3, 3);
    cn_matriz__set(&mtx, 0, 0, cn_fracao__init(2, 1));
    cn_matriz__set(&mtx, 0, 1, cn_fracao__init(3, 1));
    cn_matriz__set(&mtx, 0, 2, cn_fracao__init(5, 1));
    cn_matriz__set(&mtx, 1, 0, cn_fracao__init(8, 1));
    cn_matriz__set(&mtx, 1, 1, cn_fracao__init(6, 1));
    cn_matriz__set(&mtx, 1, 2, cn_fracao__init(-1, 1));
    cn_matriz__set(&mtx, 2, 0, cn_fracao__init(3, 1));
    cn_matriz__set(&mtx, 2, 1, cn_fracao__init(-5, 1));
    cn_matriz__set(&mtx, 2, 2, cn_fracao__init(4, 1));
    cn_matriz__get_menor_principal(&mtx, &res, 1); // Menor principal 1
    assert(res.tam_i == 1 && res.tam_j == 1);
    assert(cn_fracao__cmp(res.vet[0], cn_fracao__init(2,1)));
    cn_matriz__destroy(&res);
    cn_matriz__get_menor_principal(&mtx, &res, 2); // Menor principal 2
    assert(cn_fracao__cmp(res.vet[2], cn_fracao__init(8,1)));
    cn_matriz__destroy(&res);
}

void simetria() {
    struct cn_matriz mtx;
    cn_matriz__init(&mtx, 1,1); // Primeira ordem, garantida
    cn_matriz__set(&mtx, 0,0, cn_fracao__init(11,3));
    assert(cn_matriz__is_simetrica(&mtx));
    cn_matriz__destroy(&mtx);
    cn_matriz__init(&mtx, 1, 2); // Nem vou preencher, a ideia é reprovar mesmo :v
    assert(!cn_matriz__is_simetrica(&mtx));
    cn_matriz__destroy(&mtx);
    cn_matriz__init(&mtx, 2,2); // Por padrão é tudo zero, então é simétrica
    assert(cn_matriz__is_simetrica(&mtx));
    cn_matriz__destroy(&mtx);
    cn_matriz__init(&mtx, 2,2);
    cn_matriz__set(&mtx, 1,0, cn_fracao__init(3,2)); // Colocar um valor nada a ver pra reprovar mesmo
    assert(!cn_matriz__is_simetrica(&mtx));
    cn_matriz__destroy(&mtx);
}

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
    cn_matriz__set(&mb, 1, 0, cn_fracao__init(3, 1));
    cn_matriz__set(&mb, 0, 1, cn_fracao__init(4, 1));
    cn_matriz__set(&mb, 1, 1, cn_fracao__init(2, 1));
    cn_matriz__prettyprint(&mb);
    struct cn_matriz mc;
    cn_matriz__mul(&ma, &mb, &mc);
    cn_matriz__prettyprint(&mc);
}

void determinante() {
    struct cn_matriz mtx;
    struct cn_fracao res;
    // ordem 1
    cn_matriz__init(&mtx, 1,1);
    cn_matriz__set(&mtx, 0, 0, cn_fracao__init(2, 1));
    assert(cn_matriz__get_determinante(&mtx, &res) == SUCESS);
    assert(res.numerador == 2);
    cn_matriz__destroy(&mtx);
    // ordem 2
    cn_matriz__init(&mtx, 2,2);
    cn_matriz__set(&mtx, 0, 0, cn_fracao__init(1,1));
    cn_matriz__set(&mtx, 1, 0, cn_fracao__init(5,1));
    cn_matriz__set(&mtx, 0, 1, cn_fracao__init(3,1));
    cn_matriz__set(&mtx, 1, 1, cn_fracao__init(4,1));
    assert(cn_matriz__get_determinante(&mtx, &res) == SUCESS);
    assert(res.numerador == -11);
    cn_matriz__destroy(&mtx);
    // ordem 3
    cn_matriz__init(&mtx, 3, 3);
    cn_matriz__set(&mtx, 0, 0, cn_fracao__init(2, 1));
    cn_matriz__set(&mtx, 0, 1, cn_fracao__init(3, 1));
    cn_matriz__set(&mtx, 0, 2, cn_fracao__init(5, 1));
    cn_matriz__set(&mtx, 1, 0, cn_fracao__init(8, 1));
    cn_matriz__set(&mtx, 1, 1, cn_fracao__init(6, 1));
    cn_matriz__set(&mtx, 1, 2, cn_fracao__init(-1, 1));
    cn_matriz__set(&mtx, 2, 0, cn_fracao__init(3, 1));
    cn_matriz__set(&mtx, 2, 1, cn_fracao__init(-5, 1));
    cn_matriz__set(&mtx, 2, 2, cn_fracao__init(4, 1));
    cn_matriz__prettyprint(&mtx);
    assert(cn_matriz__get_determinante(&mtx, &res) == SUCESS);
    assert(res.numerador == -357);
    cn_matriz__destroy(&mtx);
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
    determinante();
    simetria();
    menor_principal();
}
