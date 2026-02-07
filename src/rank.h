#pragma once

typedef struct {
  char name[27];
  int duration;
} Player;

typedef struct {
  Player ranking[10];
  int count;
} Rank;

void printRank();

void tryInsertPlayerRank(const char *name, int duration);
