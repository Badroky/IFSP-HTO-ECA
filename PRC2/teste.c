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
    printf("Digite o ID do sensor: "); scanf("%d", &a.id);
    printf("Digite o tipo de sensor: "); scanf("%s", a.tipo);
    a.status = 0;

    FILE *f = fopen("sensores.txt", "r");
    if (!f) {
        printf("Erro ao abrir o arquivo 'sensores.txt' para leitura.\n");
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

int main() {
    printf("Olá, ECA IFSP-HTO!\n");
        return 0;
}
