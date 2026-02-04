#pragma once

typedef struct {
  int *fields, *tips, *mask, *resp;
  int size;
} Board;

Board newBoard(int size);

void destroyBoard(Board *self);

void setField(Board *self, int row, int col, int value);

int getField(Board *self, int row, int col);

void setResp(Board *self, int row, int col, int active);

int getResp(Board *self, int row, int col);

void generateTips(Board *self);

void markAddPos(Board *self, int row, int col);

void markRemPos(Board *self, int row, int col);

int getMask(Board *self, int row, int col);

void printBoard(Board *self);
