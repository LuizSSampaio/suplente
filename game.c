#include "game.h"
#include "board.h"

Game newGame(enum Dificult dificult, char *player) {
  Game self;

  self.dificult = dificult;
  self.board = newBoard(self.dificult);
  self.player = player;
  self.turns = 0;

  return self;
}

void destroyGame(Game *self) { destroyBoard(&self->board); }
