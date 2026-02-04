#pragma once

#include "board.h"

enum Dificult { Easy = 3, Medium = 5, Hard = 7 };

typedef struct {
  Board board;
  enum Dificult dificult;

  char player[27];
  int startTime;
} Game;

Game newGame(enum Dificult dificult, const char *player);

void destroyGame(Game *self);

void saveGame(Game *self, const char name[21]);

Game loadGame();
