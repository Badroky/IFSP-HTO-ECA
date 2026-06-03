#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

//#define ARQUIVO_TELEMETRIA "sensores.txt" - NÃO PRECISO MAIS, era utilizado na função "atualizar leitura"
#define COR_NORMAL "\033[32m"
#define COR_ALERTA "\033[33m"
#define COR_CRITICO "\033[31m"
#define COR_RESET "\033[0m"

#define ARQUIVO_SISTEMA "sensores.dat"
#define MARGEM_STATUS 0.20f
#define MAX_SENSORES 10

#ifdef _WIN32
    #define STRCASECMP _stricmp
#else
    #define STRCASECMP strcasecmp
#endif

typedef enum {
    NORMAL = 0,
    ALERTA = 1,
    CRITICO = 2
} status_sensor;

typedef struct {
    float valor_atual;
    float limite_maximo;
    float limite_minimo;
    int id;
    status_sensor status;
    time_t ultima_leitura;
    char tipo[25]; // no final para otimizar a memória
} sensor;

// TODAS as funções do sistema
void cadastrar(sensor **v, int *sensores_cadastrados, int *capacidade);
void atualizar_status(sensor *a);
int buscar_id(sensor v[], int sensores_cadastrados, int id);
void atualizar_leitura(sensor v[], int sensores_cadastrados);
void exibir_sensores(const sensor v[], int sensores_cadastrados); // 'const' para somente leitura (assim da pra garantir que ele n muda nada e ferra todo o fluxo eu acho :D )
void exibir_sensores_criticos(const sensor v[], int sensores_cadastrados); // 'const' para somente leitura
void media_por_tipo(const sensor v[], int sensores_cadastrados); // 'const'para somente leitura
void ordenar(sensor v[], int sensores_cadastrados, int crescente);
void salvar(const sensor v[], int sensores_cadastrados); // 'const' para somente leitura
void carregar(sensor **v, int *sensores_cadastrados, int *capacidade);
void remover(sensor v[], int *sensores_cadastrados);
void limpar_buffer(void);
void pausar(void);
void limpar_tela(void); // para ficar bonitinho

void cadastrar (sensor **v, int *sensores_cadastrados, int *capacidade) {
    while (1) {
        // ---- DEFINIDO PELO PROFESSOR !!! ----
        if (*sensores_cadastrados >= MAX_SENSORES) {
            printf("\n[AVISO] Limite maximo de 10 sensores definido pelo sistema atingido.\n");
            break; 
        }
        // -------------------------------------

        sensor a;
        printf("\nDigite o ID do sensor (apenas numeros, '0' volta ao menu): "); 
        while (scanf("%d", &a.id) != 1) {
            printf("[ERRO] Entrada invalida. Digite o ID novamente: ");
            limpar_buffer();
        } 
        limpar_buffer();
        
        if (a.id == 0) break;

        if (a.id < 0) {
            printf("[ERRO] O ID deve ser um numero positivo.\n");
            continue;
        }

        if (buscar_id(*v, *sensores_cadastrados, a.id) != -1) {
            printf("[ERRO] Ja existe um sensor com o ID %d.\n", a.id);
            continue;
        }

        printf("\nDigite o tipo de sensor: ");
        while (scanf("%24s", a.tipo) != 1) {
            printf("[ERRO] Entrada invalida. Digite o tipo novamente: ");
            limpar_buffer();
        }
        limpar_buffer();

        printf("Digite o limite maximo (apenas numeros): ");
            while (scanf("%f", &a.limite_maximo) != 1) {
                printf("[ERRO] Entrada invalida. Digite o limite maximo novamente: ");
                limpar_buffer();
            }
            limpar_buffer();

        printf("Digite o limite minimo (apenas numeros): ");
            while (scanf("%f", &a.limite_minimo) != 1) {
                printf("[ERRO] Entrada invalida. Digite o limite minimo novamente: ");
                limpar_buffer();
            }
            limpar_buffer();

        if (a.limite_minimo >= a.limite_maximo) {
            printf("[ERRO] O limite maximo deve ser maior que o minimo.\n");
            continue;
                    
        }

        a.valor_atual = 0.0; // comeca zerado, a leitura vai ser atualizada depois
        a.ultima_leitura = 0;
        a.status = NORMAL;

        if (*sensores_cadastrados >= *capacidade) {
            int nova_capacidade = *capacidade * 2;
            sensor *temp = realloc(*v, nova_capacidade * sizeof(sensor));

            if (!temp) {
                printf("\n[Erro] Falha ao alocar memoria. Operação cancelada.\n");
                return;
            }

            *v = temp;
            *capacidade = nova_capacidade;
        }

        (*v)[*sensores_cadastrados] = a;
        (*sensores_cadastrados)++;
        printf("[SUCESSO] Sensor cadastrado com sucesso.\n");

    }
}

void atualizar_status(sensor *a) {
    float valor = a -> valor_atual;
    float maximo = a -> limite_maximo;
    float minimo = a -> limite_minimo;

    float margem_maxima = fabsf(maximo * MARGEM_STATUS);

    float margem_minima = fabsf(minimo * MARGEM_STATUS);

    if (valor > (maximo + margem_maxima) || valor < (minimo - margem_minima)) {
        a -> status = CRITICO;
    }
    else if (valor > maximo || valor < minimo) {
        a -> status = ALERTA;
    }
    else {
        a -> status = NORMAL;
    }
}

int buscar_id(sensor v[], int sensores_cadastrados, int id) {
    
    for (int i = 0; i < sensores_cadastrados; i++) {
        if (v[i].id == id) return i; // ID encontrado, retorna o índice
    }
    return -1; // ID não encontrado
}

void atualizar_leitura(sensor v[], int sensores_cadastrados) {
    int id;

    if (sensores_cadastrados == 0) {
        printf("[INFO] Nenhum sensor cadastrado.\n");
        return;
    }

    while (1) {
        printf("\nDigite o ID do sensor para simular a atualizacao de leitura ('0' volta ao menu): ");
        while (scanf("%d", &id) != 1) {
            printf("[ERRO] Entrada invalida. Digite o ID novamente: ");
            limpar_buffer();
        }
        limpar_buffer();

        if (id == 0) break;

        int idx = buscar_id(v, sensores_cadastrados, id);
        if (idx == -1) {
            printf("[ERRO] Sensor com ID %d nao encontrado.\n", id);
            continue;
        }

        float amplitude = v[idx].limite_maximo - v[idx].limite_minimo;
        if (amplitude == 0) amplitude = 10.0;

        float margem_sorteio = amplitude * 0.35;
        float minimo_sorteio = v[idx].limite_minimo - margem_sorteio;
        float maximo_sorteio = v[idx].limite_maximo + margem_sorteio;
        float range = maximo_sorteio - minimo_sorteio;

        v[idx].valor_atual = minimo_sorteio + ((float)rand() / RAND_MAX) * range;
        atualizar_status(&v[idx]);
        v[idx].ultima_leitura = time(NULL);
        printf("[SUCESSO] Nova leitura capturada: %.2f (Status Atualizado)\n", v[idx].valor_atual);
    }
}

void exibir_sensores(const sensor v[], int sensores_cadastrados) {
    if (sensores_cadastrados ==  0) {
        printf("\nNenhum sensor cadastrado.\n");
        return;
    }

    char *nomes[] = {"Normal", "Alerta", "Critico"};
    char *cores[] = {COR_NORMAL, COR_ALERTA, COR_CRITICO};

    for (int i=0; i < sensores_cadastrados; i++) {
        printf(" ID: %-4d | Tipo: %-12s | Valor atual: %-6.2f | Status: %s%s%s\n",
            v[i].id, v[i].tipo, v[i].valor_atual,
            cores[v[i].status], nomes[v[i].status], COR_RESET);

        if(v[i].ultima_leitura == 0) {
            printf("       Ultima leitura: Sem leitura\n");
        }
        else {
            char buf[20];
            strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M:%S", localtime(&v[i].ultima_leitura));
            printf("       Ultima leitura: %s\n", buf);
        }
    }
}

void exibir_sensores_criticos(const sensor v[], int sensores_cadastrados) {
    
    if (sensores_cadastrados == 0) {
        printf("[INFO] Nenhum sensor cadastrado.\n");
        return;
    }
    
    char *nomes[] = {"Normal", "Alerta", "Critico"};
    char *cores[] = {COR_NORMAL, COR_ALERTA, COR_CRITICO};
    int achou = 0;
    for (int i = 0; i < sensores_cadastrados; i++) {
        if (v[i].status == CRITICO) {
            printf("ID: %d | Tipo: %s | Valor: %.2f | Status: %s%s%s\n",
                v[i].id, v[i].tipo, v[i].valor_atual,
                cores[v[i].status], nomes[v[i].status], COR_RESET); achou = 1;
        }
    }

    if (achou == 0) printf("Nenhum sensor critico.\n");
}

void media_por_tipo(const sensor v[], int sensores_cadastrados) {
    char tipo[25];

    if (sensores_cadastrados == 0) {
        printf("[INFO] Nenhum sensor cadastrado.\n");
        return;
    }
    

    printf("Tipo: ");
    while (scanf("%24s", tipo) != 1) {
        printf("[ERRO] Entrada invalida. Digite o tipo novamente: ");
        limpar_buffer();
    }
    limpar_buffer();

    float soma = 0;
    int count  = 0;
    for (int i = 0; i < sensores_cadastrados; i++) {
        if (STRCASECMP(v[i].tipo, tipo) == 0) {
            soma += v[i].valor_atual;
            count++;
        }
    }

    if (count == 0) {
        printf("Nenhum sensor do tipo '%s'.\n", tipo);
    }
    else {
        printf("Media de '%s': %.2f\n", tipo, soma / count);
    }
}

void ordenar(sensor v[], int sensores_cadastrados, int crescente) {
    for (int i = 0; i < sensores_cadastrados - 1; i++) {
        for (int j = 0; j < sensores_cadastrados - i - 1; j++) {
            int condicao = crescente ? (v[j].valor_atual > v[j+1].valor_atual) : (v[j].valor_atual < v[j+1].valor_atual);

            if (condicao) {
                sensor temporario = v[j];
                v[j]              = v[j+1];
                v[j+1]            = temporario;
            }
        }
    }
}

void salvar(const sensor v[], int sensores_cadastrados) {

    FILE *f = fopen(ARQUIVO_SISTEMA, "wb");
    if (!f) {
        printf("\nErro ao salvar os sensores no arquivo do sistema.\n");
        return;
    }

    fwrite(&sensores_cadastrados, sizeof(int), 1, f); // "escreve 1 elemento do tamanho de um int a partir de &sensores_cadastrados"
    fwrite(v, sizeof(sensor), sensores_cadastrados, f);  // "escreve sensores_cadastrados elementos do tamanho de Sensor a partir de v"
    fclose(f);
    printf("\nSensores salvos com sucesso no arquivo do sistema.\n");
}

void carregar(sensor **v, int *sensores_cadastrados, int *capacidade) {
    FILE *f = fopen (ARQUIVO_SISTEMA, "rb");
    if (!f) {
        printf("\nNenhum dado salvo encontrado no arquivo do sistema.\n");
        return;
    }

    fread(sensores_cadastrados,sizeof(int), 1, f);

    if (*sensores_cadastrados < 0 || *sensores_cadastrados > MAX_SENSORES) {
        printf("[ERRO] Arquivo corrompido ou invalido.\n");
        fclose(f);
        *sensores_cadastrados = 0;
        return;
    }

    if (*sensores_cadastrados > *capacidade) {
        *capacidade = *sensores_cadastrados;
        sensor *temp = realloc(*v, *capacidade * sizeof(sensor));
        if (!temp) {
            printf("\nErro ao expandir memoria.\n");
            fclose(f); // ← veja o bug 2
            return;
        }
    *v = temp;
    }
    fread(*v, sizeof(sensor), *sensores_cadastrados, f);
    fclose(f);
    printf("\nDados carregados com sucesso do arquivo do sistema.\n");
}

void remover(sensor v[], int *sensores_cadastrados) {
    int id;

    while (1) {
        if (*sensores_cadastrados == 0) {
            printf("\n[INFO] Nao ha mais sensores cadastrados para remover.\n");
            break;
        }
        
        printf("\nDigite o ID do sensor que deseja remover (ou 0 para voltar ao menu): ");
        while (scanf("%d", &id) != 1) {
            printf("[ERRO] Entrada invalida. Digite novamente: ");
            limpar_buffer();
        }
        limpar_buffer();
    
        if (id == 0) break;

        int idx = buscar_id(v, *sensores_cadastrados, id);
        if (idx == -1) {
            printf("\nSensor com ID %d nao encontrado.\n", id);
            continue;
        }
    
        char confirm;
        printf("Confirma remocao do sensor ID %d? (s/n): ", id);
        scanf(" %c", &confirm);
        limpar_buffer();
        if (confirm != 's' && confirm != 'S') {
            printf("[INFO] Remocao cancelada.\n");
            continue;
        }

        for (int i = idx; i < *sensores_cadastrados - 1; i++) {
            v[i] = v[i + 1];
        }

        (*sensores_cadastrados)--;
        printf("[SUCESSO] Sensor com ID %d removido com sucesso.\n", id);
    }
}

void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar(void) {
    printf("\n[SISTEMA] Pressione ENTER para voltar ao menu...");
    getchar();
}

void limpar_tela(void) {
    // Isso é pra deixar o terminal mais limpo
    #ifdef _WIN32
    system("cls");   // Comando para limpar terminal no Windows
    #else
    system("clear"); // Comando para limpar terminal no Linux/Mac
    #endif
}


int main() {
    srand(time(NULL));

    int capacidade = 1;
    sensor *sensores = malloc(sizeof(sensor));
    int sensores_cadastrados = 0;
    int opcao;

    if (!sensores) {
        printf("[ERRO CRITICO] Falha ao iniciar a memoria do sistema.\n");
        return 1;
    }

    carregar(&sensores, &sensores_cadastrados, &capacidade);

    do {
        limpar_tela();

        printf("\n====================================================\n");
        printf("      SISTEMA DE MONITORAMENTO     [%d/%d sensores] \n", sensores_cadastrados, MAX_SENSORES);
        printf("====================================================\n");
        printf("  1. Cadastrar Novo Sensor\n");
        printf("  2. Atualizar leitura (simulacao)\n");
        printf("  3. Listar Todos os Sensores\n");
        printf("  4. Filtrar Sensores Criticos\n");
        printf("  5. Media por Tipo\n");
        printf("  6. Ordenar crescente\n");
        printf("  7. Ordenar decrescente\n");
        printf("  8. Remover sensor\n");
        printf("  9. Salvar e sair\n");
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
            case 1: cadastrar(&sensores, &sensores_cadastrados, &capacidade);                                        break;
            case 2: atualizar_leitura(sensores, sensores_cadastrados);                                               break;
            case 3: exibir_sensores(sensores, sensores_cadastrados);                                                 break;
            case 4: exibir_sensores_criticos(sensores, sensores_cadastrados);                                        break;
            case 5: media_por_tipo(sensores, sensores_cadastrados);                                                  break;
            case 6: ordenar(sensores, sensores_cadastrados, 1); exibir_sensores(sensores, sensores_cadastrados);     break;
            case 7: ordenar(sensores, sensores_cadastrados, 0); exibir_sensores(sensores, sensores_cadastrados);     break;
            case 8: remover(sensores, &sensores_cadastrados);                                                        break;
            case 9: salvar(sensores, sensores_cadastrados);                                                          break;
            default: printf("[AVISO] Opcao invalida.\n");                                                            break;
        }

        if (opcao != 9) {
            pausar();
        }

    } while (opcao != 9);

    free (sensores); // Libera a memória alocada pelo malloc/realloc (muito importante!!!!!!!!!)
    return 0;
}