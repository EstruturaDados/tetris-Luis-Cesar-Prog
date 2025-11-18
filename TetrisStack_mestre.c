#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// estrutura da peça
typedef struct {
    char nome;
    int id;
} Peca;

int idGeral = 0;
int tipoAtual = 0;

// gera peça sem usar rand (vai repetindo I, O, T, L)
Peca gerarPeca() {
    Peca p;
    char tipos[4] = {'I','O','T','L'};
    p.nome = tipos[tipoAtual];
    p.id = idGeral++;
    tipoAtual++;
    if (tipoAtual == 4) {
        tipoAtual = 0;
    }
    return p;
}

void mostrarEstado(Peca fila[], int ini, int qtde, Peca pilha[], int topo) {
    int i, pos;

    printf("\n--- Estado atual ---\n");

    printf("Fila: ");
    pos = ini;
    for (i = 0; i < qtde; i++) {
        printf("[%c %d] ", fila[pos].nome, fila[pos].id);
        pos = (pos + 1) % TAM_FILA;
    }
    printf("\n");

    printf("Pilha (topo -> base): ");
    for (i = topo; i >= 0; i--) {
        printf("[%c %d] ", pilha[i].nome, pilha[i].id);
    }
    printf("\n\n");
}

int main() {

    Peca fila[TAM_FILA];
    Peca pilha[TAM_PILHA];

    int ini = 0;
    int fim = TAM_FILA - 1;
    int qtde = TAM_FILA;
    int topo = -1;

    int op;
    int i, pos;

    // inicia a fila já cheia
    for (i = 0; i < TAM_FILA; i++) {
        fila[i] = gerarPeca();
    }

    do {

        mostrarEstado(fila, ini, qtde, pilha, topo);

        printf("1 - Jogar peça da fila\n");
        printf("2 - Reservar peça na pilha\n");
        printf("3 - Usar peça da pilha\n");
        printf("4 - Trocar peça da fila com a da pilha\n");
        printf("5 - Trocar 3 da fila com 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        if (op == 1) {
            // jogar peça
            if (qtde > 0) {
                printf("Jogou peça [%c %d]\n", fila[ini].nome, fila[ini].id);
                ini = (ini + 1) % TAM_FILA;
                qtde--;

                // repõe peça
                fim = (fim + 1) % TAM_FILA;
                fila[fim] = gerarPeca();
                qtde++;
            } else {
                printf("Fila vazia!\n");
            }

        } else if (op == 2) {
            // reservar peça
            if (qtde > 0 && topo < TAM_PILHA - 1) {

                topo++;
                pilha[topo] = fila[ini];

                printf("Reservou peça [%c %d]\n", pilha[topo].nome, pilha[topo].id);

                ini = (ini + 1) % TAM_FILA;
                qtde--;

                // repõe peça
                fim = (fim + 1) % TAM_FILA;
                fila[fim] = gerarPeca();
                qtde++;

            } else {
                printf("Não dá pra reservar!\n");
            }

        } else if (op == 3) {
            // usar peça da pilha
            if (topo >= 0) {
                printf("Usou peça [%c %d]\n", pilha[topo].nome, pilha[topo].id);
                topo--;
            } else {
                printf("Pilha vazia!\n");
            }

        } else if (op == 4) {
            // troca simples
            if (topo >= 0) {
                Peca aux = pilha[topo];
                pilha[topo] = fila[ini];
                fila[ini] = aux;
                printf("Troca simples feita!\n");
            } else {
                printf("Não dá pra trocar!\n");
            }

        } else if (op == 5) {
            // troca múltipla
            if (qtde >= 3 && topo >= 2) {

                pos = ini;
                for (i = 0; i < 3; i++) {
                    Peca aux = fila[pos];
                    fila[pos] = pilha[topo - i];
                    pilha[topo - i] = aux;

                    pos = (pos + 1) % TAM_FILA;
                }

                printf("Troca múltipla feita!\n");

            } else {
                printf("Não tem peças suficientes pra troca múltipla.\n");
            }
        }

    } while (op != 0);

    printf("Programa encerrado!\n");

    return 0;
}