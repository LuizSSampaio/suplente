#pragma once

typedef struct {
  int *fields, *tips, *mask;
  int size;
} Board;

Board newBoard(int size);

void destroyBoard(Board *self);

void setField(Board *self, int row, int col, int value);

void setRowTip(Board *self, int row, int value);

void setColumnTip(Board *self, int col, int value);

void markAddPos(Board *self, int row, int col);

void markRemPos(Board *self, int row, int col);
