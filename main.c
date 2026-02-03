#include <stdio.h>
#include <string.h>

#include "board.h"

void repl();

int main() {
  printf("Bem vindo ao Jogo SUMPLETE\n");

  Board board = newBoard(3);
  printBoard(&board);
  destroyBoard(&board);

  // repl();

  return 0;
}

void repl() {
  char command[17];
  while (1) {
    printf("> ");
    if (fgets(command, 16, stdin) == NULL)
      break;

    if (strcmp(command, "sair\n") == 0)
      break;
  }
}
