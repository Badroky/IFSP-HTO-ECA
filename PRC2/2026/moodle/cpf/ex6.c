#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARQUIVO  260
#define TAM_LINHA     64
#define TAM_CPF       11

// TODAS as funções do programa
int  validar_cpf(const char *cpf);   // retorna 1 se valido, 0 caso contrario
void pular_bom(FILE *f);             // ignora o BOM UTF-8 se existir no inicio do arquivo
void limpar_linha(char *s);          // remove \r\n do final (arquivos Windows têm \r\n)
void limpar_buffer(void);
void pausar(void);
void limpar_tela(void);              // para ficar bonitinho :)

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
    char nome_arquivo[MAX_ARQUIVO];
    char linha[TAM_LINHA];
    char melhor_cpf[TAM_CPF + 1] = "";
    int  melhor_nota              = -1;
    int  total_lidos              = 0;
    int  total_validos            = 0;

    limpar_tela();
    printf("================================================\n");
    printf("  EX 6 - CPF COM A MAIOR NOTA (CPFs VALIDOS)\n");
    printf("================================================\n");

    printf("\nDigite o nome do arquivo de entrada: ");
    while (scanf("%259s", nome_arquivo) != 1) {
        printf("[ERRO] Entrada invalida. Digite novamente: ");
        limpar_buffer();
    }
    limpar_buffer();

    FILE *f = fopen(nome_arquivo, "r");
    if (!f) {
        printf("\n[ERRO] Nao foi possivel abrir o arquivo '%s'.\n", nome_arquivo);
        pausar();
        return 1;
    }

    pular_bom(f);

    printf("\n------------------------------------------------\n");

    while (fgets(linha, sizeof(linha), f)) {
        limpar_linha(linha);
        if (linha[0] == '\0') continue; // linha vazia, pula
        total_lidos++;

        char *sep = strchr(linha, ';');
        if (!sep) continue; // formato inesperado, pula

        int  tam_cpf = (int)(sep - linha);
        char cpf[TAM_CPF + 1];

        if (tam_cpf > TAM_CPF) continue;

        strncpy(cpf, linha, tam_cpf);
        cpf[tam_cpf] = '\0';

        int nota = atoi(sep + 1);

        if (!validar_cpf(cpf)) continue; // CPF invalido, ignora
        total_validos++;

        if (nota > melhor_nota) {
            melhor_nota = nota;
            strcpy(melhor_cpf, cpf);
        }
    }

    fclose(f);

    if (total_validos == 0) {
        printf("[INFO] Nenhum CPF valido encontrado no arquivo.\n");
    } else {
        printf("[RESULTADO] CPF com a maior nota entre os validos:\n\n");
        printf("  CPF:  %s\n", melhor_cpf);
        printf("  Nota: %d\n", melhor_nota);
    }

    printf("\n------------------------------------------------\n");
    printf("[INFO] %d linha(s) lida(s) | %d CPF(s) valido(s)\n", total_lidos, total_validos);

    pausar();
    return 0;
}
