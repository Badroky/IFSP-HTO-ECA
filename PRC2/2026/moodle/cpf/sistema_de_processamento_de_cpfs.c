#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COR_NORMAL "\033[32m"
#define COR_ALERTA "\033[33m"
#define COR_CRITICO "\033[31m"
#define COR_RESET "\033[0m"

#ifdef _WIN32
    #define STRCASECMP _stricmp
#else
    #define STRCASECMP strcasecmp
#endif

// Estrutura para o Exercicio 6
typedef struct {
    char cpf[15];
    int nota;
} aluno;

// TODAS as funções do sistema
void limpar_buffer(void);
void pausar(void);
void limpar_tela(void); // para ficar bonitinho
int validar_cpf(const char *cpf); // Validador matemático do CPF
void exercicio_6(void);
void exercicio_7(void);
void exercicio_8(void);

// ====================================================
// FUNÇÕES DE UTILIDADE E VALIDAÇÃO
// ====================================================

void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar(void) {
    printf("\n[SISTEMA] Pressione ENTER para voltar ao menu...");
    getchar();
}

void limpar_tela(void) {
    #ifdef _WIN32
    system("cls");   // Comando para limpar terminal no Windows
    #else
    system("clear"); // Comando para limpar terminal no Linux/Mac
    #endif
}

int validar_cpf(const char *cpf) {
    // 1. Verifica tamanho e formatação
    if (strlen(cpf) != 11) return 0;
    
    int i, soma, peso, digito1, digito2;
    int todos_iguais = 1;

    // 2. Bloqueia CPFs com todos os números iguais (ex: 111.111.111-11)
    for (i = 1; i < 11; i++) {
        if (cpf[i] != cpf[0]) {
            todos_iguais = 0;
            break;
        }
    }
    if (todos_iguais) return 0;

    // 3. Validação do primeiro dígito verificador
    soma = 0;
    peso = 10;
    for (i = 0; i < 9; i++) {
        if (cpf[i] < '0' || cpf[i] > '9') return 0; // garante que só tem número
        soma += (cpf[i] - '0') * peso--;
    }
    digito1 = 11 - (soma % 11);
    if (digito1 >= 10) digito1 = 0;
    
    if (cpf[9] - '0' != digito1) return 0;

    // 4. Validação do segundo dígito verificador
    soma = 0;
    peso = 11;
    for (i = 0; i < 10; i++) {
        soma += (cpf[i] - '0') * peso--;
    }
    digito2 = 11 - (soma % 11);
    if (digito2 >= 10) digito2 = 0;
    
    if (cpf[10] - '0' != digito2) return 0;

    return 1; // CPF passou em todos os testes
}

// ====================================================
// exercicios do prof
// ====================================================

void exercicio_6(void) {
    char nome_arquivo[50];
    printf("\n[Ex 6] Informe o nome do arquivo com as notas (ex: ex6.txt): ");
    while (scanf("%49s", nome_arquivo) != 1) {
        printf("[ERRO] Entrada invalida. Digite novamente: ");
        limpar_buffer();
    }
    limpar_buffer();

    FILE *f = fopen(nome_arquivo, "r");
    if (!f) {
        printf("[ERRO] Arquivo '%s' nao encontrado.\n", nome_arquivo);
        return;
    }

    aluno melhor_aluno;
    melhor_aluno.nota = -1; // Inicializa com valor baixo
    strcpy(melhor_aluno.cpf, "");

    char cpf_temp[15];
    int nota_temp;
    int alunos_lidos = 0;

    // Lê linha a linha ignorando o separador ';'
    while (fscanf(f, "%11[^;];%d\n", cpf_temp, &nota_temp) == 2) {
        alunos_lidos++;
        if (validar_cpf(cpf_temp)) {
            if (nota_temp > melhor_aluno.nota) {
                melhor_aluno.nota = nota_temp;
                strcpy(melhor_aluno.cpf, cpf_temp);
            }
        }
    }
    fclose(f);

    if (alunos_lidos == 0) {
        printf("\n[AVISO] Nenhum dado lido do arquivo.\n");
    } else if (melhor_aluno.nota == -1) {
        printf("\n[AVISO] Nenhum CPF valido foi encontrado no arquivo.\n");
    } else {
        printf("\n[SUCESSO] Analise concluida!");
        printf("\n  Maior Nota: %s%d%s", COR_NORMAL, melhor_aluno.nota, COR_RESET);
        printf("\n  CPF do Aluno: %s%s%s\n", COR_NORMAL, melhor_aluno.cpf, COR_RESET);
    }
}

void exercicio_7(void) {
    char nome_arquivo_in[50], nome_arquivo_out[50];
    
    printf("\n[Ex 7] Informe o nome do arquivo de origem (ex: ex7.txt): ");
    while (scanf("%49s", nome_arquivo_in) != 1) {
        printf("[ERRO] Entrada invalida. Digite novamente: ");
        limpar_buffer();
    }
    limpar_buffer();

    printf("[Ex 7] Informe o nome do arquivo de saida (ex: unicos.txt): ");
    while (scanf("%49s", nome_arquivo_out) != 1) {
        printf("[ERRO] Entrada invalida. Digite novamente: ");
        limpar_buffer();
    }
    limpar_buffer();

    FILE *f_in = fopen(nome_arquivo_in, "r");
    if (!f_in) {
        printf("[ERRO] Arquivo de origem '%s' nao encontrado.\n", nome_arquivo_in);
        return;
    }

    FILE *f_out = fopen(nome_arquivo_out, "w");
    if (!f_out) {
        printf("[ERRO] Nao foi possivel criar o arquivo '%s'.\n", nome_arquivo_out);
        fclose(f_in);
        return;
    }

    // Gerenciamento de memória dinâmico para os CPFs (do jeito que você gosta)
    int capacidade          = 10;
    int cpfs_cadastrados    = 0;
    char **cpfs_unicos      = malloc(capacidade * sizeof(char*));
    
    if (!cpfs_unicos) {
        printf("[ERRO CRITICO] Falha ao alocar memoria.\n");
        fclose(f_in);
        fclose(f_out);
        return;
    }

    char cpf_temp[15];
    int duplicado = 0;

    printf("\nProcessando arquivo...\n");

    while (fscanf(f_in, "%11s\n", cpf_temp) == 1) {
        if (validar_cpf(cpf_temp)) {
            duplicado = 0;
            
            // Checa se já existe no array
            for (int i = 0; i < cpfs_cadastrados; i++) {
                if (strcmp(cpfs_unicos[i], cpf_temp) == 0) {
                    duplicado = 1;
                    break;
                }
            }

            if (!duplicado) {
                // Expansão dinâmica se necessário
                if (cpfs_cadastrados >= capacidade) {
                    capacidade *= 2;
                    char **temp = realloc(cpfs_unicos, capacidade * sizeof(char*));
                    if (!temp) {
                        printf("[ERRO] Falha na expansão de memoria!\n");
                        break; 
                    }
                    cpfs_unicos = temp;
                }

                cpfs_unicos[cpfs_cadastrados] = malloc(12 * sizeof(char));
                strcpy(cpfs_unicos[cpfs_cadastrados], cpf_temp);
                cpfs_cadastrados++;
                
                fprintf(f_out, "%s\n", cpf_temp);
            }
        }
    }

    fclose(f_in);
    fclose(f_out);

    // Libera a memória alocada (muito importante!!!!!!!!!)
    for (int i = 0; i < cpfs_cadastrados; i++) {
        free(cpfs_unicos[i]);
    }
    free(cpfs_unicos);

    printf("[SUCESSO] Foram salvos %d CPFs unicos e validos em '%s'.\n", cpfs_cadastrados, nome_arquivo_out);
}

void exercicio_8(void) {
    int ano_corrente;
    char nome_arquivo_in[50], nome_arquivo_out[50];

    printf("\n[Ex 8] Digite o ano corrente (apenas numeros): ");
    while (scanf("%d", &ano_corrente) != 1 || ano_corrente <= 0) {
        printf("[ERRO] Entrada invalida. Digite um ano valido: ");
        limpar_buffer();
    }
    limpar_buffer();

    printf("[Ex 8] Informe o nome do arquivo de origem (ex: ex8.txt): ");
    while (scanf("%49s", nome_arquivo_in) != 1) {
        printf("[ERRO] Entrada invalida. Digite novamente: ");
        limpar_buffer();
    }
    limpar_buffer();

    printf("[Ex 8] Informe o nome do arquivo de saida (ex: idades.txt): ");
    while (scanf("%49s", nome_arquivo_out) != 1) {
        printf("[ERRO] Entrada invalida. Digite novamente: ");
        limpar_buffer();
    }
    limpar_buffer();

    FILE *f_in = fopen(nome_arquivo_in, "r");
    if (!f_in) {
        printf("[ERRO] Arquivo '%s' nao encontrado.\n", nome_arquivo_in);
        return;
    }

    FILE *f_out = fopen(nome_arquivo_out, "w");
    if (!f_out) {
        printf("[ERRO] Nao foi possivel criar o arquivo '%s'.\n", nome_arquivo_out);
        fclose(f_in);
        return;
    }

    char cpf_temp[15];
    int ano_nascimento;
    int processados = 0;

    while (fscanf(f_in, "%11[^;];%d\n", cpf_temp, &ano_nascimento) == 2) {
        if (!validar_cpf(cpf_temp)) {
            fprintf(f_out, "%s => null\n", cpf_temp);
        } else {
            int idade = ano_corrente - ano_nascimento;
            if (idade >= 18) {
                fprintf(f_out, "%s => maior de idade\n", cpf_temp);
            } else {
                fprintf(f_out, "%s => menor de idade\n", cpf_temp);
            }
        }
        processados++;
    }

    fclose(f_in);
    fclose(f_out);

    if (processados == 0) {
        printf("\n[AVISO] Nenhum dado processado. Verifique o formato do arquivo.\n");
    } else {
        printf("\n[SUCESSO] Relatorio de idades exportado para '%s'.\n", nome_arquivo_out);
    }
}

// ====================================================
// daqui pra baixo é o menu
// ====================================================

int main() {
    int opcao;

    do {
        limpar_tela();

        printf("\n====================================================\n");
        printf("         SISTEMA DE PROCESSAMENTO DE CPFS           \n");
        printf("====================================================\n");
        printf("  1. Exercicio 6 (Maior nota lida do arquivo)\n");
        printf("  2. Exercicio 7 (Remover CPFs duplicados)\n");
        printf("  3. Exercicio 8 (Calcular maioridade)\n");
        printf("  4. Sair\n");
        printf("----------------------------------------------------\n");
        printf(" Selecione a opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            limpar_tela();
            printf("\n[ERRO] Entrada invalida. Digite apenas numeros.\n");
            limpar_buffer();
            pausar();
            continue; // Volta pro começo do menu
        }
        limpar_buffer();
            
        limpar_tela();
        printf("\n----------------------------------------------------\n");

        switch (opcao) {
            case 1: exercicio_6(); break;
            case 2: exercicio_7(); break;
            case 3: exercicio_8(); break;
            case 4: printf("[INFO] Encerrando o sistema...\n"); break;
            default: printf("[AVISO] Opcao invalida.\n"); break;
        }

        if (opcao != 4) {
            pausar();
        }

    } while (opcao != 4);

    return 0;
}