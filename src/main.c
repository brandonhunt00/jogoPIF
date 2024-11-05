#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int x = 34, y = 12;
int incX = 1, incY = 1;
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

void printPaddle(int nextPaddleX) {
    screenSetColor(GREEN, DARKGRAY);
    screenGotoxy(paddleX, paddleY);
    printf("      ");  

    paddleX = nextPaddleX;

    screenGotoxy(paddleX, paddleY);
    printf("======"); 
}

void printBall(int nextBolaX, int nextBolaY) {
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(bolaX, bolaY);
    printf(" ");  

    bolaX = nextBolaX;
    bolaY = nextBolaY;

    screenGotoxy(bolaX, bolaY);
    printf("O"); 
}

void printHello(int nextX, int nextY) {
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(x, y);
    printf("           ");
    x = nextX;
    y = nextY;
    screenGotoxy(x, y);
    printf("Hello World");
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

    static int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);

    printHello(x, y);
    printPaddle(paddleX); 
    screenUpdate();

    while (ch != 10) {
        if (keyhit()) {
            ch = readch();
            printKey(ch);
            
            if (ch == 'a' && paddleX > MINX+1) 
            {
                printPaddle(paddleX - 2);  
            }
            else if (ch == 'd' && paddleX < MAXX - paddleWidth - 1) 
            {
                printPaddle(paddleX + 2); 
            }

            screenUpdate();
        }

        if (timerTimeOver() == 1) {
            int novaBolaX = bolaX + direcaoX;
            if (novaBolaX >= MAXX-1 || novaBolaX <= MINX+1) direcaoX = -direcaoX;

            int novaBolaY = bolaY + direcaoY;
            
            if (novaBolaY == paddleY && novaBolaX >= paddleX && novaBolaX <= (paddleX + paddleWidth))
            {
                direcaoY = -direcaoY; 
                pontuacao++; 
                printPontuacao();  
            }
            else if (novaBolaY >= MAXY-1 || novaBolaY <= MINY+1)
            {
                direcaoY = -direcaoY;  
            }

            printBall(novaBolaX, novaBolaY);  

            int novaPosX = x + incX;
            if (novaPosX >= (MAXX - strlen("Hello World") - 1) || novaPosX <= MINX + 1) incX = -incX;

            int novaPosY = y + incY;
            if (novaPosY >= MAXY - 1 || novaPosY <= 1) incY = -incY;

            printHello(novaPosX, novaPosY);
            printPaddle(paddleX);  
            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
