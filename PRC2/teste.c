#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char tipo [25];
    float valor_atual;
    float limite_maximo;
    float limite_minimo;
    int status; // 0 - normal, 1 - alerta, 2 - crítico.
} sensor;

sensor sensores[10];
int sensores_cadastrados = 0;

void cadastrar (sensor v[], int *sensores_cadastrados) {
    if (*sensores_cadastrados >= 10) {
        printf("\nLimite de Sensores cadastrados atingidos.\n");
        return;
    }
    sensor a;
    printf("\nDigite o ID do sensor: "); scanf("%d", &a.id);
    printf("\nDigite o tipo de sensor: "); scanf("%s", a.tipo);
    a.status = 0;

    FILE *f = fopen("sensores.txt", "r");
    if (!f) {
        printf("\nErro ao abrir o arquivo 'sensores.txt' para leitura.\n");
        return;
    }

    int encontrado = 0;
    int id_arquivo;
    float valor_atual_arquivo, limite_maximo_arquivo, limite_minimo_arquivo;

    while (fscanf(f, "%d %f %f %f", &id_arquivo, &valor_atual_arquivo, &limite_maximo_arquivo, &limite_minimo_arquivo) == 4) {
        if (id_arquivo == a.id) {
            a.valor_atual = valor_atual_arquivo;
            a.limite_maximo = limite_maximo_arquivo;
            a.limite_minimo = limite_minimo_arquivo;
            encontrado = 1;
            break;
        }
    }
    fclose(f);

    if (!encontrado) {
        printf("ID %d nao encontrado no arquivo 'sensores.txt'.\n", a.id);
        return;
    }

    v[*sensores_cadastrados] = a;
    (*sensores_cadastrados)++;
    printf("Sensor cadastrado com sucesso.\n");
}

void atualizar_status(sensor *a) {
    float valor = a -> valor_atual;
    float maximo = a -> limite_maximo;
    float minimo = a -> limite_minimo;

    if (valor > maximo * 1.20 || valor < minimo * 0.80) {
        a -> status = 2; //é crítico
    }
    else if (valor > maximo || valor < minimo) {
        a -> status = 1; // é alerta
    }
    else {
        a -> status = 0; // é normal
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
    printf("\nDigite o ID do sensor para atualizar a leitura: ");
    scanf("%d", &id);

    int idx = buscar_id(v, sensores_cadastrados, id);
    if (idx == -1) {
        printf("Sensor com ID %d nao encontrado.\n", id);
        return;
    }

    // busca o novo valor no arquivo
    FILE *f = fopen("sensores.txt", "r");
    if (!f) {
        printf("\nErro ao abrir o arquivo 'sensores.txt' para leitura.\n");
        return;
    }

    int encontrado = 0;
    int id_arquivo;
    float valor_atual_arquivo, limite_maximo_arquivo, limite_minimo_arquivo;

    while(fscanf(f, "%d %f %f %f", &id_arquivo, &valor_atual_arquivo, &limite_maximo_arquivo, &limite_minimo_arquivo) == 4) {
        if (id_arquivo == id) {
            v[idx].valor_atual = valor_atual_arquivo;
            v[idx].limite_maximo = limite_maximo_arquivo;
            v[idx].limite_minimo = limite_minimo_arquivo;
            encontrado = 1;
            break;
        }
    }
    fclose(f);

    if (!encontrado) {
        printf("ID %d nao encontrado no arquivo 'sensores.txt'.\n", id);
        return;
    }

    atualizar_status(&v[idx]);
    printf("Leitura do sensor ID %d atualizada com sucesso.\n", id);
}

void exibir_sensores(sensor v[], int sensores_cadastrados) {
    if (sensores_cadastrados ==  0) {
        printf("\nNenhum sensor cadastrado.\n");
        return;
    }

    char *nomes[] = {"Normal", "Alerta", "Critico"};

    for (int i=0; i < sensores_cadastrados; i++) {
        printf(" ID: %d | Tipo: %s | Valor atual: %.2f | Status: %s\n", v[i].id, v[i].tipo, v[i].valor_atual, nomes[v[i].status]);
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

void salvar(sensor v[], int sensores_cadastrados) {
    FILE *f = fopen("sensores.dat", "wb");
    if (!f) {
        printf("\nErro ao salvar os sensores no arquivo 'sensores.dat'.\n");
        return;
    }

    fwrite(&sensores_cadastrados, sizeof(int), 1, f); // "escreve 1 elemento do tamanho de um int a partir de &sensores_cadastrados"
    fwrite(v, sizeof(sensor), sensores_cadastrados, f);  // "escreve sensores_cadastrados elementos do tamanho de Sensor a partir de v"
    fclose(f);
    printf("\nSensores salvos com sucesso em 'sensores.dat'.\n");
}

void carregar(sensor v[], int *sensores_cadastrados) {
    FILE *f = fopen ("sensores.dat", "rb");
    if (!f) {
        printf("\nNenhum dado salvo encontrado em 'sensores.dat'.\n");
        return;
    }

    fread(sensores_cadastrados,sizeof(int), 1, f);
    fread(v, sizeof(sensor), *sensores_cadastrados, f);
    fclose(f);
    printf("\nDados carregados com sucesso de 'sensores.dat'.\n");
}

void remover(sensor v[], int *sensores_cadastrados) {
    int id;
    printf("\nDigite o ID do sensor que deseja remover: ");
    scanf("%d", &id);

    int idx = buscar_id(v, *sensores_cadastrados, id);
    if (idx == -1) {
        printf("\nSensor com ID %d nao encontrado.\n", id);
        return;
    }

    for (int i = idx; i < *sensores_cadastrados - 1; i++) {
        v[i] = v[i + 1];
    }

    (*sensores_cadastrados)--;
    printf("\nSensor com ID %d removido com sucesso.\n", id);
}

int main() {
    printf("Olá, ECA IFSP-HTO!\n");
        return 0;
}
