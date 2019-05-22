#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "./matriz/ops.c"
#include "./matriz/struct.c"
#include "./cholesky/ops.c"
#include "./alu/ops.c"
#include "./status.h"

int teve_erro = 0;

#define THROW(cond, errmsg...) \
    if (cond) { \
        printf(errmsg); \
        printf("\n"); \
        teve_erro = 1; \
        cn_main__print_help(); \
    }
void cn_main__print_help() {
    printf("Como usar o programa: \n");
    printf("./programa comando tam_i tam_j valores...\n");
    printf("    Comandos disponíveis: lu, print, cholesky.\n");
    printf("    Apenas a primeira letra é necessária, as outras são opcionais!\n");
}

char *cn_main__parse_matriz(struct cn_matriz *mtx, int argc, char **argv) {
    THROW(argc < 2, "ERRO: Parâmetros insuficientes. Esperado tam_i tam_j valores...");
    int tam_i = atoi(argv[0]);
    int tam_j = atoi(argv[1]);
    THROW(tam_i < 1 && tam_j < 1, "ERRO: Valores inválidos fornecidos para tamanho.");
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
        if (teve_erro)
            return "Valores insuficientes";
    }
    return SUCESS;
}

int main(int argc, char **argv) {
    /* for (int i = 0; i < argc; i++) */
    /*     printf("ARGV: %s\n", argv[i]); */
    struct cn_matriz mtx, res;
    mtx.vet = NULL;
    THROW(argc < 2, "ERRO: Argumentos insuficientes");
    if (teve_erro)
        return ERROR;
    char *op = argv[1];
    /* printf("%s\n", op); */
    cn_main__parse_matriz(&mtx, argc - 2, argv + 2);
    if (!strncmp(op, "cholesky", 1)) {
        char *calc_res = cn_cholesky__calc(&mtx, &res);
        THROW(calc_res, "Erro ao calcular cholesky:\n\t Critérios podem não ter sido satisfeitos: %s\n", calc_res);
        if (!teve_erro)
            cn_matriz__prettyprint(&res);
        cn_matriz__destroy(&mtx);
        cn_matriz__destroy(&res);
    }
    if (!strncmp(op, "lu", 1)) {
        struct cn_matriz l;
        struct cn_matriz u;
        char *res = cn_lu__calc(&mtx, &l, &u);
        THROW(res, "Erro ao calcular LU:\n\t Critérios podem não ter sido satisfeitos: %s\n", res);
        if (!teve_erro) {
            printf("L:\n");
            cn_matriz__prettyprint(&l);
            printf("U:\n");
            cn_matriz__prettyprint(&u);
            cn_matriz__destroy(&l);
            cn_matriz__destroy(&u);
        }
        cn_matriz__destroy(&mtx);
    }
    if (!strncmp(op, "print", 1)) {
        if (!teve_erro)
            cn_matriz__prettyprint(&mtx);
        cn_matriz__destroy(&mtx);
    }
    return SUCESS;
}
