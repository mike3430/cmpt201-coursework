#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>

int main() {

  char *buffer = NULL; // intialize to null then will automatically allocate memory to size of text
  size_t size = 0;
  char *token;
  char *saveptr;

  printf("Please enter some text: ");
  getline(&buffer, &size, stdin);

  // now need to loop

  token = strtok_r(buffer, " ", &saveptr);

  while (token != NULL) {

    printf("%s\n", token);
    token = strtok_r(NULL, " ", &saveptr);
  }
}
