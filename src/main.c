#include <stdio.h>
#include <string.h>

#include "board.h"
#include "game.h"

void repl();
void helpCommand();

int main() {
  printf("Bem vindo ao Jogo SUMPLETE\n\n");

  helpCommand();
  repl();

  return 0;
}

void helpCommand() {
  printf("Comandos do jogo\n");
  printf("ajuda: Exibe os comandos do jogo\n");
  printf("sair: Sair do Jogo\n");
  printf("novo: Começar um novo jogo\n");
  printf("carregar: Carregar um jogo salvo em arquivo\n");
  printf("ranking: Exibir o ranking\n");
  printf("salvar: Salva o jogo atual\n");
  printf("dica: Marca uma posição no jogo\n");
  printf("resolver: Resolve o jogo atual\n");
  printf("adicionar <lin> <col>: marca a posição <lin> <col> para entrar na "
         "soma\n");
  printf("remover <lin> <col>: remove a posição da soma\n");
}

void repl() {
  char command[17];
  while (1) {
    printf("> ");
    if (fgets(command, 16, stdin) == NULL || strcmp(command, "sair\n") == 0)
      break;

    if (strcmp(command, "ajuda\n") == 0) {
      helpCommand();
      continue;
    }
  }
}
