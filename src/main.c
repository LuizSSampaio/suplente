#include <stdio.h>
#include <string.h>

#include "board.h"
#include "game.h"

#define clearBuffer                                                            \
  do {                                                                         \
    int c;                                                                     \
    while ((c = getchar()) != '\n' && c != EOF) {                              \
    }                                                                          \
  } while (0)

void repl();
void helpCommand();
Game newGameCommand();

int main() {
  printf("Bem vindo ao Jogo SUMPLETE\n\n");

  helpCommand();
  repl();

  return 0;
}

void repl() {
  char command[17];
  int hasGame = 0;
  Game save;
  while (1) {
    printf("> ");
    if (fgets(command, 16, stdin) == NULL || strcmp(command, "sair\n") == 0)
      break;

    if (strcmp(command, "ajuda\n") == 0) {
      helpCommand();
      continue;
    }

    if (strcmp(command, "novo\n") == 0) {
      save = newGameCommand();
      hasGame = 1;
      printBoard(&save.board);
      continue;
    }
  }
}

void helpCommand() {
  printf("Comandos do jogo\n");
  printf("\e[1majuda:\e[m Exibe os comandos do jogo\n");
  printf("\e[1msair:\e[m Sair do Jogo\n");
  printf("\e[1mnovo:\e[m Começar um novo jogo\n");
  printf("\e[1mcarregar:\e[m Carregar um jogo salvo em arquivo\n");
  printf("\e[1mranking:\e[m Exibir o ranking\n");
  printf("\e[1msalvar:\e[m Salva o jogo atual\n");
  printf("\e[1mdica:\e[m Marca uma posição no jogo\n");
  printf("\e[1mresolver:\e[m Resolve o jogo atual\n");
  printf("\e[1madicionar <lin> <col>:\e[m marca a posição <lin> <col> para "
         "entrar na "
         "soma\n");
  printf("\e[1mremover <lin> <col>:\e[m remove a posição da soma\n");
}

Game newGameCommand() {
  char name[27] = "Guest";
  printf("Digite o nome do jogador: ");
  if (scanf("%s", name) == -1)
    printf("Falha ao inserir o nome, usando nome padrão\n");
  clearBuffer;

  Difficult difficult = Easy;
  while (1) {
    char choice;
    printf("Digite a dificuldade(F/M/D): ");
    if (scanf("%c", &choice) == -1)
      continue;

    clearBuffer;

    if (choice == 'F') {
      difficult = Easy;
      break;
    }

    if (choice == 'M') {
      difficult = Medium;
      break;
    }

    if (choice == 'D') {
      difficult = Hard;
      break;
    }
  }

  return newGame(difficult, name);
}
