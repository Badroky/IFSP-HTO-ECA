#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARQUIVO   260
#define TAM_LINHA      64
#define TAM_CPF        11
#define ARQUIVO_SAIDA "saida_idades.txt"

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
    int  ano_corrente;
    char nome_arquivo[MAX_ARQUIVO];
    char linha[TAM_LINHA];
    int  total_lidos     = 0;
    int  total_maiores   = 0;
    int  total_menores   = 0;
    int  total_invalidos = 0;

    limpar_tela();
    printf("==============================================\n");
    printf("  EX 8 - CLASSIFICACAO DE IDADE POR CPF\n");
    printf("==============================================\n");

    printf("\nDigite o ano corrente: ");
    while (scanf("%d", &ano_corrente) != 1 || ano_corrente <= 0) {
        printf("[ERRO] Ano invalido. Digite novamente: ");
        limpar_buffer();
    }
    limpar_buffer();

    printf("Digite o nome do arquivo de entrada: ");
    while (scanf("%259s", nome_arquivo) != 1) {
        printf("[ERRO] Entrada invalida. Digite novamente: ");
        limpar_buffer();
    }
    limpar_buffer();

    FILE *entrada = fopen(nome_arquivo, "r");
    if (!entrada) {
        printf("\n[ERRO] Nao foi possivel abrir o arquivo '%s'.\n", nome_arquivo);
        pausar();
        return 1;
    }

    FILE *saida = fopen(ARQUIVO_SAIDA, "w");
    if (!saida) {
        printf("\n[ERRO] Nao foi possivel criar o arquivo '%s'.\n", ARQUIVO_SAIDA);
        fclose(entrada);
        pausar();
        return 1;
    }

    pular_bom(entrada);

    printf("\n----------------------------------------------\n");

    while (fgets(linha, sizeof(linha), entrada)) {
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

        int ano_nascimento = atoi(sep + 1);

        if (!validar_cpf(cpf)) {
            fprintf(saida, "%s => null\n", cpf); // CPF inválido
            total_invalidos++;
            continue;
        }

        int idade = ano_corrente - ano_nascimento;

        if (idade >= 18) {
            fprintf(saida, "%s => maior de idade\n", cpf);
            total_maiores++;
        } else {
            fprintf(saida, "%s => menor de idade\n", cpf);
            total_menores++;
        }
    }

    fclose(entrada);
    fclose(saida);

    printf("[SUCESSO] Arquivo '%s' gerado com sucesso.\n", ARQUIVO_SAIDA);
    printf("\n----------------------------------------------\n");
    printf("[INFO] Linhas processadas:  %d\n", total_lidos);
    printf("[INFO] Maiores de idade:    %d\n", total_maiores);
    printf("[INFO] Menores de idade:    %d\n", total_menores);
    printf("[INFO] CPFs invalidos:      %d\n", total_invalidos);

    pausar();
    return 0;
}
