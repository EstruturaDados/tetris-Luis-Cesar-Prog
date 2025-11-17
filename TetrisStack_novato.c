#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5   // Tamanho total da fila

// ----------------------------
// Struct que representa uma peça
// ----------------------------
typedef struct {
    char nome;  // Tipo da peça ('I', 'O', 'T', 'L')
    int id;     // Identificador único
} Peca;

// ----------------------------
// Variáveis globais da fila circular
// ----------------------------
Peca fila[MAX_FILA];
int inicio = 0;   // Índice do primeiro elemento
int fim = 0;      // Índice onde o próximo elemento será inserido
int quantidade = 0; // Quantidade atual de peças

int proximoID = 0; // Controle para gerar IDs únicos

// ----------------------------
// Gera automaticamente uma peça
// ----------------------------
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4]; // Escolhe um dos 4 tipos
    nova.id = proximoID++;
    return nova;
}

// ----------------------------
// Insere uma peça no fim da fila (enqueue)
// ----------------------------
void enqueue() {
    if (quantidade == MAX_FILA) {
        printf("\n❌ A fila está cheia! Não é possível inserir nova peça.\n");
        return;
    }

    fila[fim] = gerarPeca();
    fim = (fim + 1) % MAX_FILA;
    quantidade++;

    printf("\n✔ Peça inserida com sucesso!\n");
}

// ----------------------------
// Remove uma peça da frente da fila (dequeue)
// ----------------------------
void dequeue() {
    if (quantidade == 0) {
        printf("\n❌ Não há peças para jogar! A fila está vazia.\n");
        return;
    }

    Peca removida = fila[inicio];
    inicio = (inicio + 1) % MAX_FILA;
    quantidade--;

    printf("\n✔ Peça jogada: [%c %d]\n", removida.nome, removida.id);
}

// ----------------------------
// Exibe o estado atual da fila
// ----------------------------
void exibirFila() {
    printf("\n===== Fila de Peças =====\n");

    if (quantidade == 0) {
        printf("(vazia)\n");
        return;
    }

    int i = inicio;

    for (int c = 0; c < quantidade; c++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % MAX_FILA;
    }
    printf("\n--------------------------\n");
}

// ----------------------------
// Função principal
// ----------------------------
int main() {
    srand(time(NULL)); // Semente aleatória

    // Inicializar fila com 5 elementos
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue();
    }

    int opcao;

    do {
        exibirFila();

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue();
                break;

            case 2:
                enqueue();
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\n❌ Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}