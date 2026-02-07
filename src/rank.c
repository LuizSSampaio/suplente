#include <stdio.h>
#include <string.h>

#include "rank.h"

Rank loadRank() {
  const char *path = "sumplete.rnk";
  FILE *file = fopen(path, "r");
  Rank rank;
  if (file == NULL) {
    rank.count = 0;
    return rank;
  }

  for (int i = 0; i < 10; i++) {
    Player player;
    if (fscanf(file, "%s%d", player.name, &player.duration) == -1) {
      rank.count = i;
      fclose(file);
      return rank;
    }
    rank.ranking[i] = player;
  }

  fclose(file);
  rank.count = 10;
  return rank;
}

void printRank() {
  Rank rank = loadRank();
  printf("%28s | %28s\n", "Nome", "Tempo");
  for (int i = 0; i < rank.count; i++) {
    printf("%28s | %28d\n", rank.ranking[i].name, rank.ranking[i].duration);
  }
}

void tryInsertPlayerRank(const char *name, int duration) {
  Rank rank = loadRank();

  if (rank.count == 10 && duration >= rank.ranking[rank.count - 1].duration) {
    return;
  }

  int insertPos = rank.count;
  for (int i = 0; i < rank.count; i++) {
    if (duration < rank.ranking[i].duration) {
      insertPos = i;
      break;
    }
  }

  for (int i = (rank.count < 10 ? rank.count : 9); i > insertPos; i--) {
    rank.ranking[i] = rank.ranking[i - 1];
  }

  strcpy(rank.ranking[insertPos].name, name);
  rank.ranking[insertPos].duration = duration;

  if (rank.count < 10) {
    rank.count++;
  }

  const char *path = "sumplete.rnk";
  FILE *file = fopen(path, "w");
  if (file == NULL) {
    printf("Falha ao salvar o ranking.");
    return;
  }

  for (int i = 0; i < rank.count; i++) {
    fprintf(file, "%s %d\n", rank.ranking[i].name, rank.ranking[i].duration);
  }

  fclose(file);
}
