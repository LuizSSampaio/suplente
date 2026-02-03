#include <stdio.h>
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

void printRowSeparator(char *separator, int repeat) {
  for (int i = 0; i <= repeat; i++) {
    printf("%s", separator);
  }
  printf("\n");
}

void printBoard(Board *self) {
  printRowSeparator("|---|", self->size + 1);
  // Column index
  printf("|   |");
  for (int i = 0; i < self->size; i++) {
    printf("| %d |", i + 1);
  }
  printf("|   |\n");

  printRowSeparator("|---|", self->size + 1);

  for (int i = 0; i < self->size; i++) {
    // Row Index
    printf("| %d |", i + 1);

    // Row Fields
    for (int j = 0; j < self->size; j++) {
      printf("| %d |", self->fields[(i) + ((j)*self->size)]);
    }

    // Row Tip
    printf("| %d |\n", self->tips[i + self->size + 1]);

    printRowSeparator("|---|", self->size + 1);
  }

  // Column Tip
  printf("|   |");
  for (int i = 0; i < self->size; i++) {
    printf("| %d |", self->tips[i]);
  }
  printf("|   |\n");

  printRowSeparator("|---|", self->size + 1);
}
