#include "./ops.c"
#include "./template.c"
#include <assert.h>

void transposta() {
    struct cn_matriz mtx;
    cn_matriz__init(&mtx, 2,2);
    cn_matriz__set(&mtx, 0, 0, -1);
    cn_matriz__set(&mtx, 0, 1, 8);
    cn_matriz__set(&mtx, 1, 0, 2);
    cn_matriz__set(&mtx, 1, 1, 5);
    struct cn_matriz res;
    cn_matriz__transpose(&mtx, &res);
    cn_matriz__prettyprint(&res);
    assert(res.vet[0]== -1);
    assert(res.vet[1]== 2);
    assert(res.vet[2]== 8);
    assert(res.vet[3]== 5);
    cn_matriz__destroy(&mtx);
    cn_matriz__destroy(&res);
}

void menor_principal() {
    struct cn_matriz mtx;
    struct cn_matriz res;
    cn_matriz__init(&mtx, 3, 3);
    cn_matriz__set(&mtx, 0, 0, 2);
    cn_matriz__set(&mtx, 0, 1, 3);
    cn_matriz__set(&mtx, 0, 2, 5);
    cn_matriz__set(&mtx, 1, 0, 8);
    cn_matriz__set(&mtx, 1, 1, 6);
    cn_matriz__set(&mtx, 1, 2, -1);
    cn_matriz__set(&mtx, 2, 0, 3);
    cn_matriz__set(&mtx, 2, 1, -5);
    cn_matriz__set(&mtx, 2, 2, 4);
    cn_matriz__get_menor_principal(&mtx, &res, 1); // Menor principal 1
    assert(res.tam_i == 1 && res.tam_j == 1);
    assert(res.vet[0] == 2);
    cn_matriz__destroy(&res);
    cn_matriz__get_menor_principal(&mtx, &res, 2); // Menor principal 2
    assert(res.vet[2] == 8);
    cn_matriz__destroy(&res);
}

void simetria() {
    struct cn_matriz mtx;
    cn_matriz__init(&mtx, 1,1); // Primeira ordem, garantida
    cn_matriz__set(&mtx, 0,0, 11);
    assert(cn_matriz__is_simetrica(&mtx));
    cn_matriz__destroy(&mtx);
    cn_matriz__init(&mtx, 1, 2); // Nem vou preencher, a ideia é reprovar mesmo :v
    assert(!cn_matriz__is_simetrica(&mtx));
    cn_matriz__destroy(&mtx);
    cn_matriz__init(&mtx, 2,2); // Por padrão é tudo zero, então é simétrica
    assert(cn_matriz__is_simetrica(&mtx));
    cn_matriz__destroy(&mtx);
    cn_matriz__init(&mtx, 2,2);
    cn_matriz__set(&mtx, 1,0,(double)2/(double)3); // Colocar um valor  vprovesmo
    assert(!cn_matriz__is_simetrica(&mtx));
    cn_matriz__destroy(&mtx);
}

void multest() {
    struct cn_matriz ma;
    cn_matriz__init(&ma, 2, 2);
    cn_matriz__set(&ma, 0, 0, 1);
    cn_matriz__set(&ma, 0, 1, 2);
    cn_matriz__set(&ma, 1, 0, 3);
    cn_matriz__set(&ma, 1, 1, 4);
    struct cn_matriz mb;
    cn_matriz__init(&mb, 2, 2);
    cn_matriz__set(&mb, 0, 0, -1);
    cn_matriz__set(&mb, 1, 0, 3);
    cn_matriz__set(&mb, 0, 1, 4);
    cn_matriz__set(&mb, 1, 1, 2);
    cn_matriz__prettyprint(&mb);
    struct cn_matriz mc;
    cn_matriz__mul(&ma, &mb, &mc);
    cn_matriz__prettyprint(&mc);
}

void determinante() {
    struct cn_matriz mtx;
    double res;
    // ordem 1
    cn_matriz__init(&mtx, 1,1);
    cn_matriz__set(&mtx, 0, 0, 2);
    assert(cn_matriz__get_determinante(&mtx, &res) == SUCESS);
    assert(res== 2);
    cn_matriz__destroy(&mtx);
    // ordem 2
    cn_matriz__init(&mtx, 2,2);
    cn_matriz__set(&mtx, 0, 0, 1);
    cn_matriz__set(&mtx, 1, 0, 5);
    cn_matriz__set(&mtx, 0, 1, 3);
    cn_matriz__set(&mtx, 1, 1, 4);
    assert(cn_matriz__get_determinante(&mtx, &res) == SUCESS);
    assert(res == -11);
    cn_matriz__destroy(&mtx);
    // ordem 3
    cn_matriz__init(&mtx, 3, 3);
    cn_matriz__set(&mtx, 0, 0, 2);
    cn_matriz__set(&mtx, 0, 1, 3);
    cn_matriz__set(&mtx, 0, 2, 5);
    cn_matriz__set(&mtx, 1, 0, 8);
    cn_matriz__set(&mtx, 1, 1, 6);
    cn_matriz__set(&mtx, 1, 2, -1);
    cn_matriz__set(&mtx, 2, 0, 3);
    cn_matriz__set(&mtx, 2, 1, -5);
    cn_matriz__set(&mtx, 2, 2, 4);
    cn_matriz__prettyprint(&mtx);
    assert(cn_matriz__get_determinante(&mtx, &res) == SUCESS);
    assert(res== -357);
    cn_matriz__destroy(&mtx);
}

int main() {
    struct cn_matriz ma;
    struct cn_matriz mb;
    cn_matriz__init_identity(2, &ma);
    cn_matriz__init(&mb, 2, 2);
    cn_matriz__set(&mb, 0, 0, 2);
    cn_matriz__set(&mb, 1, 1, 2);
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
    transposta();
}
