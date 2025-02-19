#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

#include "cut_list.h"
#include "piece_values.h"
#include "vec.h"

void get_filename(char *filename, size_t size);
int get_rod_length();

int main() {
  int rod_length = get_rod_length();

  char filename[256];
  get_filename(filename, sizeof(filename));

  Vec value_list = read_piece_values(filename);
  if (value_list == NULL) {
    fprintf(stderr, "Error in value list.\n");
    return 1;
  }

  CutList *cl = optimal_cutlist_for(value_list, rod_length);
  cutlist_print(cl, rod_length);
  cutlist_free(cl);

  return 0;
}

int get_rod_length() {
  int rod_length = 0;
  char buffer[128];

  while (1) {
    printf("Enter rod length: ");
    if (!fgets(buffer, sizeof(buffer), stdin)) {
      fprintf(stderr, "Error reading rod length.\n");
      exit(1);
    }

    if (sscanf(buffer, "%d %s", &rod_length, buffer) != 1 || rod_length < 1 ||
        strchr(buffer, '.')) {
      fprintf(stderr,
              "Invalid rod length. Must be an integer greater than 0.\n");
      continue;
    }
    return rod_length;
  }
}

void get_filename(char *filename, size_t size) {
  printf("Enter filename: ");
  if (!fgets(filename, size, stdin)) {
    fprintf(stderr, "Error reading filename.\n");
    exit(1);
  }

  filename[strcspn(filename, "\n")] = '\0';

  if (strlen(filename) == 0) {
    fprintf(stderr, "Invalid filename. Cannot be empty.\n");
    exit(1);
  }

  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Error opening file");
    exit(1);
  }

  fclose(file);
}