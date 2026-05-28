#include <stdio.h>
#include <string.h>

typedef struct{
    int id;
    char tipo[25]; // Ex: "Temperatura", "Pressão", "Umidade"
    float valorAtual;
    float limiteMax;
    float limiteMin;
    int status; // 0 = normal, 1 = alerta, 2 = crítico
} Sensor;

void cadastrarSensor(Sensor sensores[], int *total);
void atualizarSensor(Sensor sensores[], int total);
void exibirTodos(Sensor sensores[], int total);
void exibirCriticos(Sensor sensores[], int total);
void calcularMediaTipo(Sensor sensores[], int total);
void ordenarSensores(Sensor sensores[], int total);
void removerSensor(Sensor sensores[], int *total);
void carregarSensores(Sensor sensores[], int *total);
int avaliarStatus(float valorAtual, float limiteMax, float limiteMin);
void ordenarSensoresDecrescente(Sensor sensores[], int total);
void ordenarSensoresCrescente(Sensor sensores[], int total);

int main(){
    Sensor sensores[10];
    int total = 0;
    int opcao;

    carregarSensores(sensores, &total);

    do {
        printf("1. Cadastrar Sensor\n");
        printf("2. Atualizar Sensor\n");
        printf("3. Exibir Todos os Sensores\n");
        printf("4. Exibir Sensores Críticos\n");
        printf("5. Calcular Média por Tipo\n");
        printf("6. Ordenar Sensores\n");
        printf("7. Remover Sensor\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 0:
                printf("\nSaindo...\n\n");
                break;
            case 1:
                cadastrarSensor(sensores, &total);
                break;
            case 2:
                atualizarSensor(sensores, total);
                break;
            case 3:
                exibirTodos(sensores, total);
                break;
            case 4:
                exibirCriticos(sensores, total);
                break;
            case 5:
                calcularMediaTipo(sensores, total);
                break;
            case 6:
                ordenarSensores(sensores, total);
                break;
            case 7:
                removerSensor(sensores, &total);
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

void cadastrarSensor(Sensor sensores[], int *total){
    if(*total >= 10){
        printf("\nLimite de sensores atingido!\n\n");
        return;
    }
    Sensor novoSensor;
    printf("Informe o ID do sensor: ");
    scanf("%d", &novoSensor.id);
    for(int i = 0; i < *total; i++){
        if(sensores[i].id == novoSensor.id){
            printf("\nID já existe! Tente novamente.\n\n");
            return;
        }
    }
    printf("Informe o tipo do sensor: ");
    scanf("%s", novoSensor.tipo);
    printf("Informe o limite máximo do sensor: ");
    scanf("%f", &novoSensor.limiteMax);
    printf("Informe o limite mínimo do sensor: ");
    scanf("%f", &novoSensor.limiteMin);

    novoSensor.valorAtual = 0.0;
    novoSensor.status = 0;

    FILE *arquivo = fopen("sensores.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    fprintf(arquivo, "%d %s %.2f %.2f %.2f\n", novoSensor.id, novoSensor.tipo, novoSensor.valorAtual, novoSensor.limiteMax, novoSensor.limiteMin);
    fclose(arquivo);

    sensores[*total] = novoSensor;
    (*total)++;
}

void atualizarSensor(Sensor sensores[], int total){
    if(total == 0){
        printf("\nNenhum sensor cadastrado!\n\n");
        return;
    }

    int id;
    int index = -1;

    printf("Informe o ID do sensor a ser atualizado: ");
    scanf("%d", &id);
    for(int i = 0; i < total; i++){
        if(sensores[i].id == id){
            index = i;
            break;
        }
    }

    if(index == -1){
        printf("\nSensor não encontrado!\n\n");
        return;
    }

    printf("Informe o novo valor atual do sensor: ");
    scanf("%f", &sensores[index].valorAtual);

    sensores[index].status = avaliarStatus(sensores[index].valorAtual, sensores[index].limiteMax, sensores[index].limiteMin);

    FILE *arquivo = fopen("sensores.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for(int i = 0; i < total; i++){
        fprintf(arquivo, "%d %s %.2f %.2f %.2f\n", sensores[i].id, sensores[i].tipo, sensores[i].valorAtual, sensores[i].limiteMax, sensores[i].limiteMin);
    }
    fclose(arquivo);
}

void exibirTodos(Sensor sensores[], int total){
    if(total == 0){
        printf("\nNenhum sensor cadastrado!\n\n");
        return;
    }

    printf("\n");

    for(int i = 0; i < total; i++){
        const char *palavraStatus;

        if (sensores[i].status == 2) {
            palavraStatus = "CRÍTICO";
        } else if (sensores[i].status == 1) {
            palavraStatus = "ALERTA";
        } else {
            palavraStatus = "NORMAL";
        }
        
        printf("ID: %d, Tipo: %s, Valor Atual: %.2f, Limite Máximo: %.2f, Limite Mínimo: %.2f, Status: %s\n", sensores[i].id, sensores[i].tipo, sensores[i].valorAtual, sensores[i].limiteMax, sensores[i].limiteMin, palavraStatus);
    }

    printf("\n");

}

void exibirCriticos(Sensor sensores[], int total){
    if(total == 0){
        printf("\nNenhum sensor cadastrado!\n\n");
        return;
    }

    printf("\n");

    for(int i = 0; i < total; i++){
        if(sensores[i].status == 2){
            printf("ID: %d, Tipo: %s, Valor Atual: %.2f, Limite Máximo: %.2f, Limite Mínimo: %.2f\n", sensores[i].id, sensores[i].tipo, sensores[i].valorAtual, sensores[i].limiteMax, sensores[i].limiteMin);
        }
    }

    printf("\n");
}

void calcularMediaTipo(Sensor sensores[], int total){
    if(total == 0){
        printf("\nNenhum sensor cadastrado!\n\n");
        return;
    }
    
    char tipo[25];
    float soma = 0;
    float media;
    int contador = 0;

    printf("\n");

    printf("Sensores disponíveis:\n");
    for(int i = 0; i < total; i++){
        int repetido = 0;

        for(int j = 0; j < i; j++){
            if(strcmp(sensores[i].tipo, sensores[j].tipo) == 0){
                repetido = 1;
                break;
            }
        }

        if(repetido == 0){
            printf("- %s\n", sensores[i].tipo);
        }
    }

    printf("\n");

    printf("Informe o tipo de sensor para calcular a média: ");
    scanf("%s", tipo);
    for(int i = 0; i < total; i++){
        if(strcmp(sensores[i].tipo, tipo) == 0){
            soma += sensores[i].valorAtual;
            contador++;
        }
    }

    if(contador > 0){
        media = soma / contador;
        printf("\nMédia do tipo %s: %.2f\n\n", tipo, media);
    } else {
        printf("\nNenhum sensor do tipo %s encontrado!\n\n", tipo);
    }
}

void ordenarSensores(Sensor sensores[], int total){
    if(total < 2){
        printf("\nNão há sensores suficientes para ordenar!\n\n");
        return;
    }

    int opcao;

    printf("\n");

    printf("1. Crescente\n");
    printf("2. Decrescente\n");
    printf("0. Sair\n");
    printf("Escolha a ordem de ordenação: ");
    scanf("%d", &opcao);

    switch(opcao){
        case 0:
            printf("\nVoltando...\n\n");
            return;
        case 1:
            ordenarSensoresCrescente(sensores, total);
            break;
        case 2:
            ordenarSensoresDecrescente(sensores, total);
            break;
        default:
            printf("Opção inválida!\n");
            return;
    }

    FILE *arquivo = fopen("sensores.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    for(int i = 0; i < total; i++){
        fprintf(arquivo, "%d %s %.2f %.2f %.2f\n", sensores[i].id, sensores[i].tipo, sensores[i].valorAtual, sensores[i].limiteMax, sensores[i].limiteMin);
    }
    fclose(arquivo);

    printf("\nSensores ordenados com sucesso!\n\n");
}

void removerSensor(Sensor sensores[], int *total){
    if(*total == 0){
        printf("\nNenhum sensor cadastrado!\n\n");
        return;
    }

    int id;
    int index = -1;

    printf("Informe o ID do sensor a ser removido: ");
    scanf("%d", &id);
    for(int i = 0; i < *total; i++){
        if(sensores[i].id == id){
            index = i;
            break;
        }
    }

    if(index == -1){
        printf("\nSensor não encontrado!\n\n");
        return;
    }

    for(int i = index; i < *total - 1; i++){
        sensores[i] = sensores[i + 1];
    }
    (*total)--;
    printf("\nSensor com ID %d removido!\n\n", id);

    FILE *arquivo = fopen("sensores.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    for(int i = 0; i < *total; i++){
        fprintf(arquivo, "%d %s %.2f %.2f %.2f\n", sensores[i].id, sensores[i].tipo, sensores[i].valorAtual, sensores[i].limiteMax, sensores[i].limiteMin);
    }
    fclose(arquivo);
}

void carregarSensores(Sensor sensores[], int *total) {
    FILE *arquivo = fopen("sensores.txt", "r");
    
    if (arquivo == NULL) {
        printf("Nenhum arquivo de sensores encontrado. Iniciando com lista vazia.\n");
        return; 
    }

    while (fscanf(arquivo, "%d %s %f %f %f\n", 
           &sensores[*total].id, 
           sensores[*total].tipo, 
           &sensores[*total].valorAtual, 
           &sensores[*total].limiteMax, 
           &sensores[*total].limiteMin) == 5) {
        
        sensores[*total].status = avaliarStatus(sensores[*total].valorAtual, sensores[*total].limiteMax, sensores[*total].limiteMin);
        
        (*total)++;
        
        if (*total >= 10) break;
    }

    fclose(arquivo);
}

int avaliarStatus(float valorAtual, float limiteMax, float limiteMin) {
    if (valorAtual > limiteMax * 1.2 || valorAtual < limiteMin * 0.8) {
        return 2;
    } else if (valorAtual > limiteMax || valorAtual < limiteMin) {
        return 1;
    } else {
        return 0;
    }
}

void ordenarSensoresDecrescente(Sensor sensores[], int total){
    for(int i = 0; i < total - 1; i++){
        for(int j = 0; j < total - i -1; j++){
            if(sensores[j].valorAtual < sensores[j + 1].valorAtual){
                Sensor temp = sensores[j];
                sensores[j] = sensores[j + 1];
                sensores[j + 1] = temp;
            }
        }
    }
}

void ordenarSensoresCrescente(Sensor sensores[], int total){
    for(int i = 0; i < total - 1; i++){
        for(int j = 0; j < total - i -1; j++){
            if(sensores[j].valorAtual > sensores[j + 1].valorAtual){
                Sensor temp = sensores[j];
                sensores[j] = sensores[j + 1];
                sensores[j + 1] = temp;
            }
        }
    }
}