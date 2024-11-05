#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int bolaX = 10, bolaY = 5;
int direcaoX = 1, direcaoY = 1;
int paddleX = 40; 
int paddleY = 20; 
int paddleWidth = 6;  
int pontuacao = 0;

void printPontuacao() {
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(0, 0);  
    printf("Pontuação: %d", pontuacao);
}

void printRaquete(int nextPaddleX) {
    screenSetColor(GREEN, DARKGRAY);
    screenGotoxy(paddleX, paddleY);
    printf("      ");  

    paddleX = nextPaddleX;

    screenGotoxy(paddleX, paddleY);
    printf("======"); 
}

void printBola(int nextBolaX, int nextBolaY) {
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(bolaX, bolaY);
    printf(" ");  

    bolaX = nextBolaX;
    bolaY = nextBolaY;

    screenGotoxy(bolaX, bolaY);
    printf("O"); 
}

void printKey(int ch) {
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(35, 22);
    printf("Key code: ");

    screenGotoxy(34, 23);
    printf("            ");
    
    if (ch == 27) screenGotoxy(36, 23);
    else screenGotoxy(39, 23);

    printf("%d ", ch);
    while (keyhit())
    {
        printf("%d ", readch());
    }
}

int main() {

    int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);
    printRaquete(paddleX); 
    printPontuacao();
    screenUpdate();

    while (ch != 10) {
        if (keyhit()) {
            ch = readch();
            printKey(ch);
            
            if (ch == 'a' && paddleX > MINX+1) {
                printRaquete(paddleX - 2);  
            }
            else if (ch == 'd' && paddleX < MAXX - paddleWidth - 1) {
                printRaquete(paddleX + 2); 
            }
            screenUpdate();
        }
        if (timerTimeOver() == 1) {
            int novaBolaX = bolaX + direcaoX;
            if (novaBolaX >= MAXX-1 || novaBolaX <= MINX+1) direcaoX = -direcaoX;

            int novaBolaY = bolaY + direcaoY;
            
            if (novaBolaY == paddleY && novaBolaX >= paddleX && novaBolaX <= (paddleX + paddleWidth)) {
                direcaoY = -direcaoY; 
                pontuacao++; 
                printPontuacao();  
            }
            else if (novaBolaY >= MAXY-1 || novaBolaY <= MINY+1) {
                direcaoY = -direcaoY;  
            }

            printBola(novaBolaX, novaBolaY);  

            printRaquete(paddleX);  
            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
