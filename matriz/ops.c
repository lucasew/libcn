#ifndef CN_MATRIZ_OPS
#define CN_MATRIZ_OPS
#include "../status.h"
#include <stdio.h>
#include <stdlib.h>
#include "../fracao/struct.c"
#include "../fracao/ops.c"
#include "./struct.c"

int
cn_matriz__check_bound(struct cn_matriz *this, int i, int j) {
    return i > this->tam_i || j > this->tam_j
        ? ERROR
        : SUCESS;
}

int
cn_matriz__is_same_shape(
    struct cn_matriz *this,
    struct cn_matriz *that
) {
    return this->tam_i == that->tam_i && this->tam_j == that->tam_j;
}

int
cn_matriz__sum(
        struct cn_matriz *this,
        struct cn_matriz *that,
        struct cn_matriz *new
) {
    if (!cn_matriz__is_same_shape(this,that)) {
        return ERROR;
    }
    int i;
    cn_matriz__init(new, this->tam_i, this->tam_j);
    for (i = 0; i < this->tam_i*this->tam_j; i++) {
        new->vet[i] = cn_fracao__sum(this->vet[i], that->vet[i]);
    }
    return SUCESS;
}

int
cn_matriz__sub(
        struct cn_matriz *this,
        struct cn_matriz *that,
        struct cn_matriz *new
) {
    if (!cn_matriz__is_same_shape(this,that)) {
        return ERROR;
    }
    int i;
    cn_matriz__init(new, this->tam_i, this->tam_j);
    for (i = 0; i < this->tam_i*this->tam_j; i++) {
        new->vet[i] = cn_fracao__sub(this->vet[i], that->vet[i]);
    }
    return SUCESS;
}

int
cn_matriz__mul(
        struct cn_matriz *this,
        struct cn_matriz *that,
        struct cn_matriz *new
) {
    if (!(this->tam_i == that->tam_j)) {
        return ERROR;
    }
    cn_matriz__init(new, this->tam_i, that->tam_j);
    int i, j, k;
    for (i = 0; i < new->tam_i; i++) {
        for (j = 0; j < new->tam_j; j++) {
            for (k = 0; k < new->tam_j; k++) {
                new->vet[i*new->tam_i + j] = 
                    cn_fracao__sum(new->vet[i*new->tam_i + j],
                            cn_fracao__mul(
                                this->vet[i*this->tam_i + k],
                                that->vet[k*that->tam_i + j]
                            )
                    );
            }
        }
    }
    return SUCESS;
}

int
cn_matriz__get(
        struct cn_matriz *this,
        int i,
        int j,
        struct cn_fracao *f
) {
    if (cn_matriz__check_bound(this, i, j) == ERROR)
        return ERROR;
    *f = this->vet[i*this->tam_i + j];
    return SUCESS;
}

int
cn_matriz__set(
        struct cn_matriz *this,
        int i,
        int j,
        struct cn_fracao f
) {
    if(cn_matriz__check_bound(this, i, j) == ERROR) {
        return ERROR;
    }
    this->vet[i*this->tam_i + j] = f;
    return SUCESS;
}

int cn_matriz__prettyprint(
        struct cn_matriz *this
) {
    int i, j;
    for (i = 0; i < this->tam_i; i++) {
        for (j = 0; j < this->tam_j; j++) {
            printf("\t");
            struct cn_fracao fracao;
            if (cn_matriz__get(this, i, j, &fracao) == ERROR)
                return ERROR;
            cn_fracao__prettyprint(fracao);
        }
        printf("\n");
    }
    printf("\n");
    return SUCESS;
}

#endif
