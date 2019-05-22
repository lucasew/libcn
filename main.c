#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "./matriz/ops.c"
#include "./matriz/struct.c"
#include "./cholesky/ops.c"
#include "./alu/ops.c"
#include "./status.h"

#define THROW(cond, errmsg) \
    if (cond) { \
        printf("%s\n", errmsg); \
        return ERROR; \
    }

int cn_main__parse_matriz(struct cn_matriz *mtx, int argc, char **argv) {
    THROW(argc < 2, "ERRO: Parâmetros insuficientes. Esperado tam_i tam_j valores...");
    int tam_i = atoi(argv[0]);
    int tam_j = atoi(argv[1]);
    /* THROW(!tam_i && !tam_j, "ERRO: Valores inválidos fornecidos para tamanho."); */
    argc -= 2;
    argv += 2;
    cn_matriz__init(mtx, tam_i, tam_j);
    int i;
    for (i = 0; i < tam_i*tam_j; i++) {
        THROW(argc == 0, "Valores insuficientes para preencher a matriz.");
        double vlr = atof(argv[0]);
        /* THROW(vlr == 0.0, "ERRO: Valor inválido fornecido para a matriz."); */
        mtx->vet[i] = vlr;
        argc--;
        argv++;
    }
    return SUCESS;
}

int main(int argc, char **argv) {
    /* for (int i = 0; i < argc; i++) */
    /*     printf("ARGV: %s\n", argv[i]); */
    struct cn_matriz mtx, res;
    mtx.vet = NULL;
    THROW(argc < 2, "ERRO: Argumentos insuficientes");
    char *op = argv[1];
    printf("%s\n", op);
    cn_main__parse_matriz(&mtx, argc - 2, argv + 2);
    if (!strncmp(op, "cholesky", 1)) {
        THROW(cn_cholesky__calc(&mtx, &res) == ERROR, "Erro ao calcular cholesky: Critérios podem não ter sido satisfeitos\n");
        cn_matriz__prettyprint(&res);
        cn_matriz__destroy(&mtx);
        cn_matriz__destroy(&res);
    }
    if (!strncmp(op, "lu", 1)) {
        struct cn_matriz l;
        struct cn_matriz u;
        int res = cn_lu__calc(&mtx, &l, &u) == ERROR;
        THROW(res, "Erro ao calcular LU: Critérios podem não ter sido satisfeitos\n");
        printf("L:\n");
        cn_matriz__prettyprint(&l);
        printf("U:\n");
        cn_matriz__prettyprint(&u);
        cn_matriz__destroy(&mtx);
        cn_matriz__destroy(&l);
        cn_matriz__destroy(&u);
    }
    if (!strncmp(op, "print", 1)) {
        cn_matriz__prettyprint(&mtx);
        cn_matriz__destroy(&mtx);
    }
    return SUCESS;
}
