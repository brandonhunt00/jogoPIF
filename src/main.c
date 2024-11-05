#include <string.h>
#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define ALTURA_DAS_RAQUETES 5
#define CORRECAO_RAQUETE 1  

typedef struct {
    int x, y;
} Raquete;

typedef struct {
    int x, y;
    int dx, dy;
} Bola;

void printPontuacao(int pontuacao1, int pontuacao2);
void printRaquete(Raquete *raquete);
void clearRaquete(Raquete *raquete);
void printBola(Bola *bola);
void moverBola(Bola *bola, Raquete *raquete1, Raquete *raquete2, int *pontuacao1, int *pontuacao2);

int main() {
    int ch = 0;
    int pontuacao1 = 0, pontuacao2 = 0;

    Raquete *raquete1 = (Raquete *)malloc(sizeof(Raquete));
    Raquete *raquete2 = (Raquete *)malloc(sizeof(Raquete));
    Bola *bola = (Bola *)malloc(sizeof(Bola));

    if (raquete1 == NULL || raquete2 == NULL || bola == NULL) {
        fprintf(stderr, "Erro de alocação de memória\n");
        return 1;
    }

    raquete1->x = 1;
    raquete1->y = 10;
    raquete2->x = 78;
    raquete2->y = 10;
    bola->x = 10;
    bola->y = 5;
    bola->dx = 1;
    bola->dy = 1;

    screenInit(1);
    keyboardInit();
    timerInit(50);

    printPontuacao(pontuacao1, pontuacao2);
    printRaquete(raquete1);
    printRaquete(raquete2);
    screenUpdate();

    while (ch != 10) {
        if (keyhit()) {
            ch = readch();
            if (ch == 'w' && raquete1->y > 1) {
                clearRaquete(raquete1);
                raquete1->y -= CORRECAO_RAQUETE;
            } else if (ch == 's' && raquete1->y < SCRENDY - ALTURA_DAS_RAQUETES) {
                clearRaquete(raquete1);
                raquete1->y += CORRECAO_RAQUETE;
            } else if (ch == 'i' && raquete2->y > 1) {
                clearRaquete(raquete2);
                raquete2->y -= CORRECAO_RAQUETE;
            } else if (ch == 'k' && raquete2->y < SCRENDY - ALTURA_DAS_RAQUETES) {
                clearRaquete(raquete2);
                raquete2->y += CORRECAO_RAQUETE;
            }
            screenUpdate();
        }

        if (timerTimeOver() == 1) {
            moverBola(bola, raquete1, raquete2, &pontuacao1, &pontuacao2);
            printPontuacao(pontuacao1, pontuacao2);
            printRaquete(raquete1);
            printRaquete(raquete2);
            screenUpdate();
        }
    }
    free(raquete1);
    free(raquete2);
    free(bola);

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}

void printPontuacao(int pontuacao1, int pontuacao2) {
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(0, 0);
    printf("Jogador 1: %d | Jogador 2: %d", pontuacao1, pontuacao2);
}

void printRaquete(Raquete *raquete) {
    screenSetColor(GREEN, DARKGRAY);
    for (int i = 0; i < ALTURA_DAS_RAQUETES; i++) {
        screenGotoxy(raquete->x, raquete->y + i);
        printf("|");
    }
}

void clearRaquete(Raquete *raquete) {
    for (int i = 0; i < ALTURA_DAS_RAQUETES; i++) {
        screenGotoxy(raquete->x, raquete->y + i);
        printf(" ");
    }
}

void printBola(Bola *bola) {
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(bola->x, bola->y);
    printf("O");
}

void moverBola(Bola *bola, Raquete *raquete1, Raquete *raquete2, int *pontuacao1, int *pontuacao2) {
    int novaBolaX = bola->x + bola->dx;
    int novaBolaY = bola->y + bola->dy;

    if (novaBolaY <= 1 || novaBolaY >= SCRENDY - 1) bola->dy = -bola->dy;

    if ((novaBolaX == raquete1->x + 1 && novaBolaY >= raquete1->y && novaBolaY < raquete1->y + ALTURA_DAS_RAQUETES) ||
        (novaBolaX == raquete2->x - 1 && novaBolaY >= raquete2->y && novaBolaY < raquete2->y + ALTURA_DAS_RAQUETES)) {
        bola->dx = -bola->dx;
    }

    if (novaBolaX <= 0) {
        (*pontuacao2)++;
        novaBolaX = SCRENDX / 2;
        novaBolaY = SCRENDY / 2;
        bola->dx = -bola->dx;
    } else if (novaBolaX >= SCRENDX) {
        (*pontuacao1)++;
        novaBolaX = SCRENDX / 2;
        novaBolaY = SCRENDY / 2;
        bola->dx = -bola->dx;
    }

    screenGotoxy(bola->x, bola->y);
    printf(" ");
    
    bola->x = novaBolaX;
    bola->y = novaBolaY;
    
    printBola(bola);
}
