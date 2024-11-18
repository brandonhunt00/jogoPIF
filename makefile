# Variáveis
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
SRC = src
INCLUDE = include
OBJ = main.o screen.o keyboard.o timer.o
EXEC = pong

# Regra padrão
all: $(EXEC)

# Regra para criar o executável
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Regras para compilar os arquivos objeto
main.o: $(SRC)/main.c $(INCLUDE)/screen.h $(INCLUDE)/keyboard.h $(INCLUDE)/timer.h
	$(CC) $(CFLAGS) -c $(SRC)/main.c

screen.o: $(SRC)/screen.c $(INCLUDE)/screen.h
	$(CC) $(CFLAGS) -c $(SRC)/screen.c

keyboard.o: $(SRC)/keyboard.c $(INCLUDE)/keyboard.h
	$(CC) $(CFLAGS) -c $(SRC)/keyboard.c

timer.o: $(SRC)/timer.c $(INCLUDE)/timer.h
	$(CC) $(CFLAGS) -c $(SRC)/timer.c

# Limpar arquivos objeto e executável
clean:
	rm -f $(OBJ) $(EXEC)
