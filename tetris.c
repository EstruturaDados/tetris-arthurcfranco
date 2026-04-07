#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5

// Struct da peça
typedef struct {
    char tipo;
    int id;
} Peca;

// Struct da fila circular
typedef struct {
    Peca dados[TAM];
    int inicio;
    int fim;
    int tamanho;
} Fila;

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
}

// Verifica se está cheia
int filaCheia(Fila *f) {
    return f->tamanho == TAM;
}

// Verifica se está vazia
int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

// Gera tipo aleatório de peça
char gerarTipo() {
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    return tipos[rand() % 7];
}

// Enfileirar
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia!\n");
        return;
    }

    f->dados[f->fim] = p;
    f->fim = (f->fim + 1) % TAM;
    f->tamanho++;
}

// Desenfileirar
Peca dequeue(Fila *f) {
    Peca p = {'X', -1};

    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return p;
    }

    p = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % TAM;
    f->tamanho--;

    return p;
}

// Mostrar fila
void mostrarFila(Fila *f) {
    printf("\nFila de Pecas:\n");

    int i = f->inicio;

    for (int count = 0; count < f->tamanho; count++) {
        printf("[Tipo: %c | ID: %d] ", f->dados[i].tipo, f->dados[i].id);
        i = (i + 1) % TAM;
    }

    printf("\n");
}

int main() {
    srand(time(NULL));

    Fila fila;
    inicializarFila(&fila);

    int idAtual = 1;

    // Preenche a fila inicialmente
    for (int i = 0; i < TAM; i++) {
        Peca p;
        p.tipo = gerarTipo();
        p.id = idAtual++;
        enqueue(&fila, p);
    }

    int opcao;

    do {
        mostrarFila(&fila);

        printf("\n1 - Jogar peça (dequeue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            // Remove peça da frente
            Peca removida = dequeue(&fila);

            if (removida.id != -1) {
                printf("Peca jogada: Tipo %c | ID %d\n", removida.tipo, removida.id);

                // Adiciona nova peça automaticamente
                Peca nova;
                nova.tipo = gerarTipo();
                nova.id = idAtual++;

                enqueue(&fila, nova);
            }
        }

    } while (opcao != 0);

    return 0;
}
