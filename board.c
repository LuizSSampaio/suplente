#include <stdlib.h>

#include "board.h"

Board newBoard(int size) {
  Board self;

  self.fields = malloc(size * size * sizeof(int));
  self.tips = malloc(size * 2 * sizeof(int));
  self.mask = malloc(size * size * sizeof(int));
  self.size = size;

  return self;
}

void destroyBoard(Board *self) {
  free(self->fields);
  free(self->tips);
  free(self->mask);
}

void setField(Board *self, int row, int col, int value) {
  self->fields[(row - 1) + ((col - 1) * self->size)] = value;
}

void setRowTip(Board *self, int row, int value) {
  self->tips[row + self->size] = value;
}

void setColumnTip(Board *self, int col, int value) {
  self->tips[col - 1] = value;
}

void markAddPos(Board *self, int row, int col) {
  self->mask[(row - 1) + ((col - 1) * self->size)] = 1;
}

void markRemPos(Board *self, int row, int col) {
  self->mask[(row - 1) + ((col - 1) * self->size)] = -1;
}
