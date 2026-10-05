#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function that adds to the array and clears the 5th entry
void history(char *array[], int *count, char *line);

int main() {

  char *line = NULL;
  size_t size = 0;
  int count = 0;
  char *array[5];

  printf("Enter input: ");

  while (getline(&line, &size, stdin) != -1) {
    history(array, &count, line);
    // check if the user typed "print"
    // strcmp compares two strings, returns 0 when the same
    if (strcmp(line, "print\n") == 0) {
      for (int i = 0; i < count; i++) {
        printf("%s", array[i]);
      }
    }

    line = NULL; // reset
    size = 0;
    printf("Enter input: ");
  }

  for (int i = 0; i < count; i++) {
    free(array[i]);
  }

  free(line);
}

void history(char *array[], int *count, char *line) {
  // counter is pointer bc orginal count var is in main()
  if (*count < 5) {
    array[*count] = line;
    (*count)++;
  } else {
    free(array[0]);
    for (int i = 0; i < 4; i++) {
      array[i] = array[i + 1];
    }

    // array starts at 0 ** so 4 is techincally 5th spot
    array[4] = line;
  }
}
