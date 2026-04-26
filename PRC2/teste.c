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
        printf("Limite de Sensores cadastrados atingidos.\n");
        return;
    }
    sensor a;
    printf("Digite o ID do sensor: "); scanf("%d", &a.id);
    printf("Digite o tipo de sensor: "); scanf("%s", a.tipo);

    a.status = 0;
}

int main() {
    printf("Olá, ECA IFSP-HTO!\n");
        return 0;
}
