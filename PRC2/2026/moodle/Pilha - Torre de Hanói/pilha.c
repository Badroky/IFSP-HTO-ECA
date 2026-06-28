#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mantendo o seu padrao de cores para o terminal
#define COR_NORMAL "\033[32m"
#define COR_ALERTA "\033[33m"
#define COR_CRITICO "\033[31m"
#define COR_RESET "\033[0m"

typedef struct {
   int *discos;
   int topo;
   int capacidade;
   char id_pino; // Serve para identificar se é A, B ou C
} pilha;

// TODAS as funções do sistema
void inicializar_pilha(pilha *p, int capacidade, char id_pino);
int pilha_vazia(const pilha *p); // 'const' para somente leitura (assim da pra garantir que ele n muda nada e ferra todo o fluxo eu acho :D )
int pilha_cheia(const pilha *p); // 'const' para somente leitura
void empilhar(pilha *p, int disco);
int desempilhar(pilha *p);
void mover_disco(pilha *origem, pilha *destino);
void exibir_estado(const pilha *a, const pilha *b, const pilha *c, int total_discos); // 'const' para somente leitura
void resolver_hanoi(int n, pilha *origem, pilha *destino, pilha *auxiliar, const pilha *A, const pilha *B, const pilha *C, int total_discos, int *passos);
void liberar_pilhas(pilha *a, pilha *b, pilha *c);
void limpar_buffer(void);
void pausar(void);
void limpar_tela(void); // para ficar bonitinho

void inicializar_pilha(pilha *p, int capacidade, char id_pino) {
   p->discos = (int *)malloc(capacidade * sizeof(int));
   if (!p->discos) {
       printf("%s[ERRO CRITICO] Falha ao iniciar a memoria da pilha %c.%s\n", COR_CRITICO, id_pino, COR_RESET);
       exit(1);
   }
   p->topo = -1; // Começa zerado (-1 na verdade, pq é índice de array)
   p->capacidade = capacidade;
   p->id_pino = id_pino;
}

int pilha_vazia(const pilha *p) {
   return p->topo == -1;
}

int pilha_cheia(const pilha *p) {
   return p->topo == p->capacidade - 1;
}

void empilhar(pilha *p, int disco) {
   if (pilha_cheia(p)) {
       printf("[ERRO] A pilha %c esta cheia!\n", p->id_pino);
       return;
   }
   
   // ----  REGRA FÍSICA PEDIDA NO EXERCÍCIO !!!  ----
   if (!pilha_vazia(p) && p->discos[p->topo] < disco) {
       printf("%s[ERRO CRITICO] Quebra de regra! Tentativa de colocar disco %d sobre o disco menor %d no pino %c.%s\n", 
              COR_CRITICO, disco, p->discos[p->topo], p->id_pino, COR_RESET);
       return;
   }
   // ------------------------------------------------

   p->topo++;
   p->discos[p->topo] = disco;
}

int desempilhar(pilha *p) {
   if (pilha_vazia(p)) {
       printf("[ERRO] A pilha %c ja esta vazia!\n", p->id_pino);
       return -1;
   }
   
   int valor = p->discos[p->topo];
   p->topo--;
   return valor;
}

void mover_disco(pilha *origem, pilha *destino) {
   if (pilha_vazia(origem)) {
       printf("[ERRO] Pino origem (%c) vazio!\n", origem->id_pino);
       return;
   }

   if (pilha_cheia(destino)) {
       printf("[ERRO] Pino destino (%c) esta cheio!\n", destino->id_pino);
       return;
   }

   int disco = origem->discos[origem->topo];
   if (!pilha_vazia(destino) && destino->discos[destino->topo] < disco) {
       printf("%s[ERRO CRITICO] Quebra de regra! Tentativa de mover disco %d para cima do disco menor %d no pino %c.%s\n",
              COR_CRITICO, disco, destino->discos[destino->topo], destino->id_pino, COR_RESET);
       return;
   }

   disco = desempilhar(origem);
   empilhar(destino, disco); // A validação física já é feita no empilhar()
}

void exibir_estado(const pilha *a, const pilha *b, const pilha *c, int total_discos) {
   const pilha *lista[] = {a, b, c};
   
   printf("---------------- ESTADO DAS PILHAS -----------------\n\n");
   for (int i = 0; i < 3; i++) {
       printf(" Pino %c: Base [ ", lista[i]->id_pino);
       
       for (int j = 0; j <= lista[i]->topo; j++) {
           printf("%s%d%s ", COR_NORMAL, lista[i]->discos[j], COR_RESET);
       }
       
       // Preeche o espaço vazio com tracinhos pra ficar sempre alinhado
       for (int j = lista[i]->topo + 1; j < total_discos; j++) {
           printf("- ");
       }
       printf("] Topo\n");
   }
   printf("\n----------------------------------------------------\n");
}

void resolver_hanoi(int n, pilha *origem, pilha *destino, pilha *auxiliar, const pilha *A, const pilha *B, const pilha *C, int total_discos, int *passos) {
   if (n == 0) return;
   
   if (n == 1) {
       mover_disco(origem, destino);
       (*passos)++;
       
       limpar_tela();
       printf("\n====================================================\n");
       printf(" Passo %-4d | Movendo disco do Pino %c para o Pino %c\n", *passos, origem->id_pino, destino->id_pino);
       printf("====================================================\n");
       exibir_estado(A, B, C, total_discos);
       pausar();
       return;
   }
   
   resolver_hanoi(n - 1, origem, auxiliar, destino, A, B, C, total_discos, passos);
   
   mover_disco(origem, destino);
   (*passos)++;
   
   limpar_tela();
   printf("\n====================================================\n");
   printf(" Passo %-4d | Movendo disco do Pino %c para o Pino %c\n", *passos, origem->id_pino, destino->id_pino);
   printf("====================================================\n");
   exibir_estado(A, B, C, total_discos);
   pausar();
   
   resolver_hanoi(n - 1, auxiliar, destino, origem, A, B, C, total_discos, passos);
}

void liberar_pilhas(pilha *a, pilha *b, pilha *c) {
   free(a->discos);
   free(b->discos);
   free(c->discos);
}

void limpar_buffer(void) {
   int c;
   while ((c = getchar()) != '\n' && c != EOF);
}

void pausar(void) {
   printf("\n[SISTEMA] Pressione ENTER para continuar...");
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
   int opcao;
   int n_discos = 0;
   int inicializado = 0;
   
   pilha A, B, C;

   do {
       limpar_tela();

       printf("\n====================================================\n");
       printf("        TORRE DE HANOI - SISTEMA DE PILHAS        \n");
       printf("====================================================\n");
       printf("  1. Definir quantidade N de discos (Atual: %d)\n", n_discos);
       printf("  2. Simular resolucao passo a passo\n");
       printf("  3. Sair do sistema\n");
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
           case 1:
               if (inicializado) {
                   liberar_pilhas(&A, &B, &C); // limpa se já existia antes de redefinir
                   inicializado = 0;
               }
               
               printf("\nDigite o numero de discos N (apenas numeros maiores que 0): ");
               while (scanf("%d", &n_discos) != 1 || n_discos <= 0) {
                   printf("[ERRO] Entrada invalida. Digite novamente: ");
                   limpar_buffer();
               }
               limpar_buffer();
               
               inicializar_pilha(&A, n_discos, 'A');
               inicializar_pilha(&B, n_discos, 'B');
               inicializar_pilha(&C, n_discos, 'C');
               inicializado = 1;
               
               // Coloca todos na Origem (maior em baixo, menor em cima)
               for (int i = n_discos; i >= 1; i--) {
                   empilhar(&A, i);
               }
               
               printf("[SUCESSO] Pilhas inicializadas. %d discos alocados na Origem (Pino A).\n", n_discos);
               break;
               
           case 2:
               if (!inicializado) {
                   printf("[AVISO] Configure os discos primeiro (Opcao 1).\n");
               } else if (pilha_vazia(&A)) {
                   printf("[AVISO] A simulacao ja foi concluida! Redefina os discos na Opcao 1 para ver novamente.\n");
               } else {
                   int passos = 0;
                   
                   printf("ESTADO INICIAL:\n\n");
                   exibir_estado(&A, &B, &C, n_discos);
                   pausar();
                   
                   // Chamada da recursão: move tudo de A para C usando B como aux
                   resolver_hanoi(n_discos, &A, &C, &B, &A, &B, &C, n_discos, &passos);
                   
                   printf("\n[SUCESSO] Torre resolvida com sucesso em %d passos!\n", passos);
               }
               break;
               
           case 3:
               printf("\n[INFO] Encerrando o sistema de simulacao...\n");
               break;
               
           default: 
               printf("[AVISO] Opcao invalida.\n"); 
               break;
       }

       if (opcao != 3) {
           pausar();
       }

   } while (opcao != 3);

   if (inicializado) {
       liberar_pilhas(&A, &B, &C); // Libera a memória alocada pelo malloc/realloc (muito importante!!!!!!!!!!!!!?!!!!!!!!!!!!!!!!!!!!!!! bastante mesmo. ʕ⁠·⁠ᴥ⁠·⁠ʔ )
   }

   return 0;
}