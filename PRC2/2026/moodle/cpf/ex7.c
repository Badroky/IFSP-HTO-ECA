#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARQUIVO   260
#define TAM_LINHA      64
#define TAM_CPF        11
#define ARQUIVO_SAIDA "sem_duplicatas.txt"

// TODAS as funções do programa
int  validar_cpf(const char *cpf);                                   // retorna 1 se valido, 0 caso contrario
int  ja_registrado(const char *lista, int total, const char *cpf);  // 'const' para somente leitura
void pular_bom(FILE *f);                                             // ignora o BOM UTF-8 se existir no inicio
void limpar_linha(char *s);                                          // remove \r\n do final (Windows tem \r\n)
void limpar_buffer(void);
void pausar(void);
void limpar_tela(void);                                              // para ficar bonitinho :)

int validar_cpf(const char *cpf) {
    if ((int)strlen(cpf) != TAM_CPF) return 0;

    for (int i = 0; i < TAM_CPF; i++) {
        if (cpf[i] < '0' || cpf[i] > '9') return 0;
    }

    // CPF com todos os dígitos iguais é inválido (111.111.111-11, 222.222.222-22, etc.)
    int todos_iguais = 1;
    for (int i = 1; i < TAM_CPF; i++) {
        if (cpf[i] != cpf[0]) { todos_iguais = 0; break; }
    }
    if (todos_iguais) return 0;

    // Primeiro dígito verificador
    int soma = 0;
    for (int i = 0; i < 9; i++) soma += (cpf[i] - '0') * (10 - i);
    int resto = (soma * 10) % 11;
    if (resto == 10 || resto == 11) resto = 0;
    if (resto != cpf[9] - '0') return 0;

    // Segundo dígito verificador
    soma = 0;
    for (int i = 0; i < 10; i++) soma += (cpf[i] - '0') * (11 - i);
    resto = (soma * 10) % 11;
    if (resto == 10 || resto == 11) resto = 0;
    if (resto != cpf[10] - '0') return 0;

    return 1;
}

int ja_registrado(const char *lista, int total, const char *cpf) {
    // Array plano: cada slot ocupa (TAM_CPF + 1) bytes
    for (int i = 0; i < total; i++) {
        if (strcmp(lista + i * (TAM_CPF + 1), cpf) == 0) return 1;
    }
    return 0;
}

void pular_bom(FILE *f) {
    // Pula o BOM UTF-8 (EF BB BF) se estiver no início (o Windows adora colocar isso)
    unsigned char bom[3];
    if (fread(bom, 1, 3, f) == 3 && bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF) return;
    rewind(f); // sem BOM, volta pro início
}

void limpar_linha(char *s) {
    int len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) s[--len] = '\0';
}

void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar(void) {
    printf("\n[SISTEMA] Pressione ENTER para encerrar...");
    getchar();
}

void limpar_tela(void) {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

int main() {
    char  nome_entrada[MAX_ARQUIVO];
    char  linha[TAM_LINHA];
    int   total_lidos   = 0;
    int   total_validos = 0;
    int   total_unicos  = 0;
    int   total_duplic  = 0;
    int   capacidade    = 1;

    // Array dinâmico plano pra guardar os CPFs já vistos (cada slot = TAM_CPF + 1 bytes)
    char *cpfs_vistos = malloc(1 * (TAM_CPF + 1));
    if (!cpfs_vistos) {
        printf("[ERRO CRITICO] Falha ao iniciar a memoria do sistema.\n");
        return 1;
    }

    limpar_tela();
    printf("==================================================\n");
    printf("  EX 7 - REMOVER CPFs DUPLICADOS (CPFs VALIDOS)\n");
    printf("==================================================\n");

    printf("\nDigite o nome do arquivo de entrada: ");
    while (scanf("%259s", nome_entrada) != 1) {
        printf("[ERRO] Entrada invalida. Digite novamente: ");
        limpar_buffer();
    }
    limpar_buffer();

    FILE *entrada = fopen(nome_entrada, "r");
    if (!entrada) {
        printf("\n[ERRO] Nao foi possivel abrir o arquivo '%s'.\n", nome_entrada);
        free(cpfs_vistos);
        pausar();
        return 1;
    }

    FILE *saida = fopen(ARQUIVO_SAIDA, "w");
    if (!saida) {
        printf("\n[ERRO] Nao foi possivel criar o arquivo '%s'.\n", ARQUIVO_SAIDA);
        fclose(entrada);
        free(cpfs_vistos);
        pausar();
        return 1;
    }

    pular_bom(entrada);

    printf("\n--------------------------------------------------\n");

    while (fgets(linha, sizeof(linha), entrada)) {
        limpar_linha(linha);
        if (linha[0] == '\0') continue; // linha vazia, pula
        total_lidos++;

        char cpf[TAM_LINHA];
        strncpy(cpf, linha, TAM_LINHA - 1);
        cpf[TAM_LINHA - 1] = '\0';

        if (!validar_cpf(cpf)) continue; // CPF invalido (comprimento ou checksum), ignora
        total_validos++;

        if (ja_registrado(cpfs_vistos, total_unicos, cpf)) {
            total_duplic++;
            continue; // duplicata, pula
        }

        // Expande o array se necessário (dobra a capacidade, igual ao realloc do professor :D)
        if (total_unicos >= capacidade) {
            int   nova_capacidade = capacidade * 2;
            char *temp = realloc(cpfs_vistos, nova_capacidade * (TAM_CPF + 1));

            if (!temp) {
                printf("\n[ERRO] Falha ao expandir memoria. Operacao cancelada.\n");
                break;
            }

            cpfs_vistos = temp;
            capacidade  = nova_capacidade;
        }

        strcpy(cpfs_vistos + total_unicos * (TAM_CPF + 1), cpf);
        total_unicos++;
        fprintf(saida, "%s\n", cpf);
    }

    fclose(entrada);
    fclose(saida);
    free(cpfs_vistos); // Libera a memória alocada pelo malloc/realloc (muito importante!!)

    printf("[SUCESSO] Arquivo '%s' gerado com sucesso.\n", ARQUIVO_SAIDA);
    printf("\n--------------------------------------------------\n");
    printf("[INFO] Linhas lidas:  %d\n", total_lidos);
    printf("[INFO] CPFs validos:  %d\n", total_validos);
    printf("[INFO] CPFs unicos:   %d\n", total_unicos);
    printf("[INFO] Duplicatas:    %d\n", total_duplic);

    pausar();
    return 0;
}
