#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int x = 34, y = 12;
int incX = 1, incY = 1;
int bolaX = 10, bolaY = 5;
int direcaoX = 1, direcaoY = 1;
int paddleX = 40;  // Posição inicial da raquete no eixo X
int paddleY = 20;  // Posição inicial no eixo Y
int paddleWidth = 6;  // Largura da raquete
int pontuacao = 0;

void printPontuacao() {
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(0, 0);  // Exibe a pontuação no canto superior esquerdo
    printf("Pontuação: %d", pontuacao);
}

void printPaddle(int nextPaddleX) {
    screenSetColor(GREEN, DARKGRAY);
    screenGotoxy(paddleX, paddleY);
    printf("      ");  // Apaga a raquete anterior (espaços vazios do tamanho da raquete)

    paddleX = nextPaddleX;

    screenGotoxy(paddleX, paddleY);
    printf("======");  // Desenha a raquete na nova posição
}

void printBall(int nextBolaX, int nextBolaY) {
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(bolaX, bolaY);
    printf(" ");  // Apaga a bola anterior

    bolaX = nextBolaX;
    bolaY = nextBolaY;

    screenGotoxy(bolaX, bolaY);
    printf("O");  // Imprime a bola na nova posição
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
    printPaddle(paddleX);  // Imprime a raquete no início do jogo
    screenUpdate();

    while (ch != 10) {
        // Handle user input
        if (keyhit()) {
            ch = readch();
            printKey(ch);
            
            // Controle da raquete
            if (ch == 'a' && paddleX > MINX+1)  // Move para a esquerda
            {
                printPaddle(paddleX - 2);  // Mova a raquete 2 espaços à esquerda
            }
            else if (ch == 'd' && paddleX < MAXX - paddleWidth - 1)  // Move para a direita
            {
                printPaddle(paddleX + 2);  // Mova a raquete 2 espaços à direita
            }

            screenUpdate();
        }

        // Update game state (move elements, verify collision, etc)
        if (timerTimeOver() == 1) {
            // Movimento da bola
            int novaBolaX = bolaX + direcaoX;
            if (novaBolaX >= MAXX-1 || novaBolaX <= MINX+1) direcaoX = -direcaoX;

            int novaBolaY = bolaY + direcaoY;
            
            // Verifica se a bola atingiu a raquete
            if (novaBolaY == paddleY && novaBolaX >= paddleX && novaBolaX <= (paddleX + paddleWidth))
            {
                direcaoY = -direcaoY;  // A bola quica na raquete
                pontuacao++;  // Incrementa a pontuação
                printPontuacao();  // Atualiza a pontuação na tela
            }
            else if (novaBolaY >= MAXY-1 || novaBolaY <= MINY+1)
            {
                direcaoY = -direcaoY;  // A bola quica nas bordas superior/inferior
            }

            printBall(novaBolaX, novaBolaY);  // Atualiza a posição da bola

            // Movimento da string "Hello World"
            int novaPosX = x + incX;
            if (novaPosX >= (MAXX - strlen("Hello World") - 1) || novaPosX <= MINX + 1) incX = -incX;

            int novaPosY = y + incY;
            if (novaPosY >= MAXY - 1 || novaPosY <= 1) incY = -incY;

            printHello(novaPosX, novaPosY);
            printPaddle(paddleX);  // Sempre imprime a raquete a cada atualização
            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}