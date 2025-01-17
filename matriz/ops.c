#ifndef CN_MATRIZ_OPS
#define CN_MATRIZ_OPS
#include <stdio.h>
#include "../status.h"
#include <stdlib.h>
#include "./struct.c"

int
cn_matriz__copy(
        struct cn_matriz *from,
        struct cn_matriz *to
) {
    if (cn_matriz__init(to, from->tam_i, from->tam_j) == ERROR)
        return ERROR;
    int i;
    for (i = 0; i < from->tam_i*from->tam_j; i++) {
        to->vet[i] = from->vet[i];
    }
    return SUCESS;
}

int
cn_matriz__transpose(
        struct cn_matriz *from, 
        struct cn_matriz *to
) {
    cn_matriz__init(to, from->tam_j, from->tam_i);
    int i, j;
    for (i = 0; i < from->tam_i; i++)
        for (j = 0; j < from->tam_j; j++) {
            to->vet[j*to->tam_i + i] = from->vet[i*from->tam_i + j];
        }
    return SUCESS;
}

int
cn_matriz__check_bound(struct cn_matriz *this, int i, int j) {
    return i > this->tam_i || j > this->tam_j
        ? ERROR
        : SUCESS;
}

int
cn_matriz__is_quadrada(struct cn_matriz *this) {
    return this->tam_i == this->tam_j;
}

int
cn_matriz__is_simetrica(struct cn_matriz *this) {
    if (!cn_matriz__is_quadrada(this))
        return 0;
    int i, j;
    for (i = 0; i < this->tam_i; i++)
        for (j = 0; j < this->tam_i; j++) {
           if (this->vet[i*this->tam_i + j] != this->vet[j*this->tam_i + i])
                return 0;
        }
    return 1;
}

int
cn_matriz__get_determinante(struct cn_matriz *this, double *res) {
    if (!cn_matriz__is_quadrada(this))
        return ERROR;
    if (this->tam_i == 1) { // Não preciso verificar os dois por que ambos são iguais
        *res = this->vet[0];
        return SUCESS;
    }
    if (this->tam_i == 2) {
        *res = this->vet[0] * this->vet[3] - this->vet[1] * this->vet[2];
        return SUCESS;
    }
    if (this->tam_i == 3) { // Fazendo a conta do determinante na mão
        // TODO: Melhorar um pouco isso ai
#define idx(i, j) this->vet[i*3 + j]
        *res = (
                    (idx(0, 0) * idx(1,1) * idx(2,2))
                    + (idx(0, 1) * idx(1,2) * idx(2, 0)) 
                    + (idx(0, 2) * idx(1,0) * idx(2, 1))
                ) - (
                    idx(0,2) * idx(1,1) * idx(2,0)
                    + idx(0,0) * idx(1,2) * idx(2, 1)
                    + idx(0,1) * idx(1,0) * idx(2,2)
                );
// evitar conflitos
#undef  idx
        return SUCESS;
    }
    return ERROR;
}

int
cn_matriz__get_menor_principal(struct cn_matriz *this, struct cn_matriz *ret, int ordem) {
    if (!cn_matriz__is_quadrada(this))
        return ERROR;
    if (cn_matriz__init(ret, ordem, ordem) == ERROR)
        return ERROR;
    int i, j;
    for (i = 0; i < ordem; i++)
        for (j = 0; j < ordem; j++) {
            ret->vet[i*ordem + j] = this->vet[i*this->tam_i + j];
        }
    return SUCESS;
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
        new->vet[i] = this->vet[i] + that->vet[i];
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
        new->vet[i] = this->vet[i] - that->vet[i];
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
                    new->vet[i*new->tam_i + j] +
                                this->vet[i*this->tam_i + k] * that->vet[k*that->tam_i + j];
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
        double *f
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
        double f
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
            printf("%lf", this->vet[i*this->tam_i + j]);
        }
        printf("\n");
    }
    printf("\n");
    return SUCESS;
}

#endif
