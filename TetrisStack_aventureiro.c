#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//1. Estruturas de dados
//Vou precisar de duas estruturas principais:

//Peça (Peca)

typedef struct {
    char nome;  // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;     // Identificador único
}Peca;

// Protótipo da função
Peca gerarPeca(int id);

//2. Fila circular de peças futuras

#define TAM_FILA 5

typedef struct {
    Peca elementos[TAM_FILA];
    int frente;
    int tras;
    int tamanho;
}Fila;


//3. Pilha de reserva

#define TAM_PILHA 3

typedef struct {
    Peca elementos[TAM_PILHA];
    int topo;
}Pilha;

//2. Funções principais
//a) Gerar peça aleatória
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

//b) Operações da fila circular
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = 0;
    f->tamanho = 0;
}

int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

int filaCheia(Fila *f) {
    return f->tamanho == TAM_FILA;
}

void enfileirar(Fila *f, Peca p) {
    if (!filaCheia(f)) {
        f->elementos[f->tras] = p;
        f->tras = (f->tras + 1) % TAM_FILA;
        f->tamanho++;
    }
}

Peca desenfileirar(Fila *f) {
    Peca p = f->elementos[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->tamanho--;
    return p;
}

//c) Operações da pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

void empilhar(Pilha *p, Peca x) {
    if (!pilhaCheia(p)) {
        p->topo++;
        p->elementos[p->topo] = x;
    }
}

Peca desempilhar(Pilha *p) {
    Peca x = p->elementos[p->topo];
    p->topo--;
    return x;
}

//3. Exibir estado atual
void exibirEstado(Fila *f, Pilha *p) {
    printf("\nFila de peças:\t");
    for (int i = 0, idx = f->frente; i < f->tamanho; i++) {
        printf("[%c %d] ", f->elementos[idx].nome, f->elementos[idx].id);
        idx = (idx + 1) % TAM_FILA;
    }
    
    printf("\nPilha de reserva\t(Topo -> Base): ");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->elementos[i].nome, p->elementos[i].id);
    }
    printf("\n");
}

//4. Menu e lógica principal
//Jogar peça → remove da fila e adiciona nova peça.
//Reservar peça → remove da fila e empilha na pilha.
//Usar peça da reserva → remove do topo da pilha.
//Sempre gerar uma nova peça para a fila após cada ação.

int main() {
    srand(time(NULL));
    Fila fila;
    Pilha pilha;
    int idAtual = 0, opcao;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Preenche a fila inicial
    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(&fila, gerarPeca(idAtual++));
    }

    do {
        exibirEstado(&fila, &pilha);
        printf("\nOpções:\n1 Jogar peça\n2 Reservar peça\n3 Usar peça reservada\n0 Sair\nOpção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: // Jogar peça
                if (!filaVazia(&fila)) {
                    Peca jogada = desenfileirar(&fila);
                    printf("Jogou a peça [%c %d]\n", jogada.nome, jogada.id);
                    enfileirar(&fila, gerarPeca(idAtual++));
                }
                break;
            case 2: // Reservar peça
                if (!filaVazia(&fila) && !pilhaCheia(&pilha)) {
                    Peca reservada = desenfileirar(&fila);
                    empilhar(&pilha, reservada);
                    enfileirar(&fila, gerarPeca(idAtual++));
                    printf("Reservou a peça [%c %d]\n", reservada.nome, reservada.id);
                } else {
                    printf("Não foi possível reservar a peça.\n");
                }
                break;
            case 3: // Usar peça reservada
                if (!pilhaVazia(&pilha)) {
                    Peca usada = desempilhar(&pilha);
                    printf("Usou a peça reservada [%c %d]\n", usada.nome, usada.id);
                } else {
                    printf("Pilha de reserva vazia.\n");
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
