#pragma once

#include "board.h"

enum Difficult { Easy = 3, Medium = 5, Hard = 7 };

typedef struct {
  Board board;
  enum Difficult dificult;

  char player[27];
  int startTime;
} Game;

Game newGame(enum Difficult dificult, const char *player);

void destroyGame(Game *self);

void saveGame(Game *self, const char name[21]);

Game loadGame(const char name[21]);
