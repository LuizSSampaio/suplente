#include <time.h>

#include "board.h"
#include "game.h"

Game newGame(enum Dificult dificult, char *player) {
  Game self;

  self.dificult = dificult;
  self.board = newBoard(self.dificult);
  self.player = player;
  self.startTime = time(NULL);

  return self;
}

void destroyGame(Game *self) { destroyBoard(&self->board); }
