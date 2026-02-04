#include <stdio.h>
#include <stdlib.h>

#include "board.h"

Board newBoard(int size) {
  Board self;

  const int boardArea = size * size;

  self.fields = malloc(boardArea * sizeof(int));
  self.tips = malloc(size * 2 * sizeof(int));
  self.mask = malloc(boardArea * sizeof(int));
  self.resp = malloc(boardArea * sizeof(int));
  self.size = size;

  for (int i = 0; i < boardArea; i++) {
    self.fields[i] = 0;
    self.mask[i] = 0;
    self.resp[i] = 0;
  }

  for (int i = 0; i < self.size * 2; i++) {
    self.tips[i] = 0;
  }

  return self;
}

void destroyBoard(Board *self) {
  free(self->fields);
  free(self->tips);
  free(self->mask);
  free(self->resp);
}

void setField(Board *self, int row, int col, int value) {
  self->fields[(row - 1) + ((col - 1) * self->size)] = value;
}

int getField(Board *self, int row, int col) {
  return self->fields[(row - 1) + ((col - 1) * self->size)];
}

void setResp(Board *self, int row, int col, int active) {
  self->fields[(row - 1) + ((col - 1) * self->size)] = (active != 0) ? 1 : 0;
}

int getResp(Board *self, int row, int col) {
  return self->fields[(row - 1) + ((col - 1) * self->size)];
}

void generateTips(Board *self) {
  for (int row = 0; row < self->size; row++) {
    for (int col = 0; col < self->size; col++) {
      const int pos = row + (col * self->size);
      if (self->resp[pos]) {
        self->tips[row + self->size] += self->fields[pos];
        self->tips[col] += self->fields[pos];
      }
    }
  }
}

void markAddPos(Board *self, int row, int col) {
  self->mask[(row - 1) + ((col - 1) * self->size)] = 1;
}

void markRemPos(Board *self, int row, int col) {
  self->mask[(row - 1) + ((col - 1) * self->size)] = -1;
}

int getMask(Board *self, int row, int col) {
  return self->mask[(row - 1) + ((col - 1) * self->size)];
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
