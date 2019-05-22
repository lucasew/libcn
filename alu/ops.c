#ifndef CN_ALU_OPS
#define CN_ALU_OPS
#include "../matriz/ops.c"
#include "../matriz/struct.c"
#include "../matriz/template.c"
#include "./ops.c"

int cn_lu__check(struct cn_matriz *this) {
    if (!cn_matriz__is_quadrada(this))
        return ERROR;
    int i;
    struct cn_matriz menor_principal;
    for (i = 1; i < this->tam_i; i++) {
        double res;
        cn_matriz__get_menor_principal(this, &menor_principal, i);
        int detres = cn_matriz__get_determinante(&menor_principal, &res);
        cn_matriz__destroy(&menor_principal);
        if (detres == ERROR)
            return ERROR;
        if (res == 0.0)
            return ERROR;
    }
    return SUCESS;
}

int cn_lu__calc(
        struct cn_matriz *a,
        struct cn_matriz *l,
        struct cn_matriz *u
        ) {
    if (cn_lu__check(a) == ERROR)
        return ERROR;
    int n = a->tam_i;
    int i, j, k;
    cn_matriz__copy(a, u);
    cn_matriz__init_identity(l, a->tam_i);
    for (j = 0; j < n - 1; j++) {
        for (i = j + 1; i < n; i++) {
            l->vet[i*n + j] = u->vet[i*n + j]/u->vet[j*n + j];
            for (k = j + 1; k < n; k++) {
                u->vet[i*n + k] -= l->vet[i*n + j]*u->vet[j*n + k];
            }
            u->vet[i*n + j] = 0;
        }
    }

    return SUCESS;
}


#endif
