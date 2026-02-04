#include <stdio.h>
#include <string.h>
#include <time.h>

#include "board.h"
#include "game.h"

Game newGame(enum Difficult dificult, const char *player) {
  Game self;

  self.dificult = dificult;
  self.board = newBoard(self.dificult);
  self.startTime = time(NULL);

  strcat(self.player, player);

  return self;
}

void destroyGame(Game *self) { destroyBoard(&self->board); }

int fileExists(const char *path) {
  FILE *f = fopen(path, "r");
  if (f) {
    fclose(f);
    return 1;
  }
  return 0;
}

void saveGame(Game *self, const char name[21]) {
  char path[32] = "";
  strcat(path, "saves/");
  strcat(path, name);
  strcat(path, ".sum");

  if (fileExists(path)) {
    char choice = ' ';
    while (choice != 's') {
      printf("Já existe um jogo salvo com o nome %s, deseja continuar(s/n)? ",
             name);

      if (scanf("%c ", &choice) == -1 || choice == 'n')
        return;
    }
  }

  FILE *save = fopen(path, "w");
  if (save == NULL) {
    printf("Falha ao criar o arquivo de salvamento!\n");
    return;
  }

  // Board
  fprintf(save, "%d\n", self->dificult);
  for (int i = 0; i < self->board.size; i++) {
    for (int j = 0; j < self->board.size; j++) {
      fprintf(save, "%d", getField(&self->board, i + 1, j + 1));
      if (j + 1 < self->board.size)
        fprintf(save, " ");
    }
    fprintf(save, "\n");
  }

  // Response
  int respCount = 0;
  for (int i = 0; i < self->board.size; i++) {
    if (self->board.resp[i])
      respCount++;
  }
  fprintf(save, "%d\n", respCount);
  for (int i = 0; i < self->board.size; i++) {
    for (int j = 0; j < self->board.size; j++) {
      if (getResp(&self->board, i + 1, j + 1))
        fprintf(save, "%d %d\n", i + 1, j + 1);
    }
  }

  // Mask
  int maskCount = 0;
  for (int i = 0; i < self->board.size; i++) {
    if (self->board.mask[i] != 0)
      maskCount++;
  }
  fprintf(save, "%d\n", maskCount);
  for (int i = 0; i < self->board.size; i++) {
    for (int j = 0; j < self->board.size; j++) {
      int maskVal = getMask(&self->board, i + 1, j + 1);
      if (maskVal == 0)
        continue;

      char operation = maskVal == 1 ? 'a' : 'r';
      fprintf(save, "%c %d %d\n", operation, i + 1, j + 1);
    }
  }

  // Player
  fprintf(save, "%s\n%d\n", self->player,
          ((int)time(NULL) - self->startTime) / 1000);

  fclose(save);
}

// TODO: Remove error handling boilerplate
Game loadGame(const char name[21]) {
  char path[32] = "";
  strcat(path, "saves/");
  strcat(path, name);
  strcat(path, ".sum");

  FILE *save = fopen(path, "r");
  if (save == NULL) {
    printf("Falha ao carregar o arquivo %s.\nCriando um novo jogo...", path);
    return newGame(Easy, "None");
  }

  Game self;

  // Difficult
  int size;
  if (fscanf(save, "%d", &size) == -1) {
    fclose(save);
    printf("Falha ao carregar o arquivo %s.\nCriando um novo jogo...", path);
    return newGame(Easy, "None");
  }
  self.dificult = size;
  self.board = newBoard(self.dificult);

  // Fields
  for (int i = 0; i < self.board.size; i++) {
    for (int j = 0; j < self.board.size; j++) {
      int value;
      if (fscanf(save, "%d", &value) == -1) {
        fclose(save);
        printf("Falha ao carregar o arquivo %s.\nCriando um novo jogo...",
               path);
        return newGame(Easy, "None");
      }
      setField(&self.board, i + 1, j + 1, value);
    }
  }

  // Response
  int respCount;
  if (fscanf(save, "%d", &respCount) == -1) {
    fclose(save);
    printf("Falha ao carregar o arquivo %s.\nCriando um novo jogo...", path);
    return newGame(Easy, "None");
  }
  for (int i = 0; i < respCount; i++) {
    int row, col;
    if (fscanf(save, "%d%d", &row, &col) == -1) {
      fclose(save);
      printf("Falha ao carregar o arquivo %s.\nCriando um novo jogo...", path);
      return newGame(Easy, "None");
    }
    setResp(&self.board, row, col, 1);
  }

  // Mask
  int maskCount;
  if (fscanf(save, "%d", &maskCount) == -1) {
    fclose(save);
    printf("Falha ao carregar o arquivo %s.\nCriando um novo jogo...", path);
    return newGame(Easy, "None");
  }
  for (int i = 0; i < maskCount; i++) {
    char operation;
    int row, col;
    if (fscanf(save, " %c%d%d", &operation, &row, &col) == -1) {
      fclose(save);
      printf("Falha ao carregar o arquivo %s.\nCriando um novo jogo...", path);
      return newGame(Easy, "None");
    }
    if (operation == 'a') {
      markAddPos(&self.board, row, col);
      continue;
    }
    markRemPos(&self.board, row, col);
  }

  // Player
  if (fscanf(save, " %s", self.player) == -1) {
    fclose(save);
    printf("Falha ao carregar o arquivo %s.\nCriando um novo jogo...", path);
    return newGame(Easy, "None");
  }
  int duration;
  if (fscanf(save, "%d", &duration) == -1) {
    fclose(save);
    printf("Falha ao carregar o arquivo %s.\nCriando um novo jogo...", path);
    return newGame(Easy, "None");
  }
  self.startTime = time(NULL) - duration * 1000;

  fclose(save);
  return self;
}
