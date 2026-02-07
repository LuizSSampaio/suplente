#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "board.h"
#include "game.h"
#include "rank.h"

#define clearBuffer                                                            \
  do {                                                                         \
    int c;                                                                     \
    while ((c = getchar()) != '\n' && c != EOF) {                              \
    }                                                                          \
  } while (0)

void repl();
void playerVictory(Game *game);
int validatePosition(Game *game, int row, int col);
void helpCommand();
Game newGameCommand();
Game loadGameCommand();
void tipCommand(Game *game);
void solveGameCommand(Game *game);
void saveGameCommand(Game *save);

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
    if (scanf("%s", command) == -1 || strcmp(command, "sair") == 0)
      break;

    if (strcmp(command, "adicionar") == 0) {
      if (hasGame != 1) {
        printf("Não existe um jogo ativo. Use o comando ajuda\n");
        continue;
      }

      int row, col;
      scanf("%d%d", &row, &col);
      if (!validatePosition(&save, row, col)) {
        printf("A posição %d %d é inválida\n", row, col);
        continue;
      }
      markAddPos(&save.board, row, col);
      printBoard(&save.board);
      if (checkVictory(&save)) {
        playerVictory(&save);
        printBoard(&save.board);
        hasGame = 0;
      }
      continue;
    }

    if (strcmp(command, "remover") == 0) {
      if (hasGame != 1) {
        printf("Não existe um jogo ativo. Use o comando ajuda\n");
        continue;
      }

      int row, col;
      scanf("%d%d", &row, &col);
      if (!validatePosition(&save, row, col)) {
        printf("A posição %d %d é inválida\n", row, col);
        continue;
      }
      markRemPos(&save.board, row, col);
      printBoard(&save.board);
      if (checkVictory(&save)) {
        playerVictory(&save);
        hasGame = 0;
      }
      continue;
    }

    clearBuffer;

    if (strcmp(command, "novo") == 0) {
      save = newGameCommand();
      hasGame = 1;
      printBoard(&save.board);
      continue;
    }

    if (strcmp(command, "carregar") == 0) {
      save = loadGameCommand();
      hasGame = 1;
      printBoard(&save.board);
      continue;
    }

    if (strcmp(command, "ranking") == 0) {
      printRank();
      continue;
    }

    if (strcmp(command, "dica") == 0) {
      if (hasGame != 1) {
        printf("Não existe um jogo ativo. Use o comando ajuda\n");
        continue;
      }
      tipCommand(&save);
      printBoard(&save.board);
      continue;
    }

    if (strcmp(command, "resolver") == 0) {
      if (hasGame != 1) {
        printf("Não existe um jogo ativo. Use o comando ajuda\n");
        continue;
      }

      solveGameCommand(&save);
      printBoard(&save.board);
      hasGame = 0;
      continue;
    }

    if (strcmp(command, "salvar") == 0) {
      if (hasGame != 1) {
        printf("Não existe um jogo ativo para salvar\n");
        continue;
      }
      saveGameCommand(&save);
      continue;
    }

    if (strcmp(command, "ajuda") != 0) {
      printf("Comando \e[1m%s\e[m não existe:\n", command);
    }

    helpCommand();
  }
}

void playerVictory(Game *game) {
  const int duration = time(NULL) - game->startTime;
  printf("Parabens! %s você gastou %d segundos para completar o jogo.\n",
         game->player, duration);
  tryInsertPlayerRank(game->player, duration);
}

int validatePosition(Game *game, int row, int col) {
  return !(row > game->board.size || row < 1 || col > game->board.size ||
           col < 1);
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

Game loadGameCommand() {
  char file[21];
  printf("Digite o nome do jogo salvo: ");
  scanf("%s", file);
  clearBuffer;
  return loadGame(file);
}

void tipCommand(Game *game) {
  srand(time(NULL));
  const int boardArea = game->board.size * game->board.size;
  const int offset = rand() % boardArea;
  for (int i = offset; i < boardArea + offset; i++) {
    int index = i;
    if (index >= boardArea) {
      index -= boardArea;
    }

    if (game->board.resp[index] == 1 && game->board.mask[index] != 1) {
      game->board.mask[index] = 1;
      return;
    }
  }
  printf("Não existe mais dicas disponíveis\n");
}

void solveGameCommand(Game *game) {
  const int boardArea = game->board.size * game->board.size;
  for (int i = 0; i < boardArea; i++) {
    game->board.mask[i] = game->board.resp[i];
  }
}

void saveGameCommand(Game *save) {
  char file[21];
  printf("Digite o nome do jogo salvo: ");
  scanf("%s", file);
  clearBuffer;
  saveGame(save, file);
}
