#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *buffer = NULL;
  size_t size = 0;
  char *token;
  char *saveptr;

  while (1) {

    printf("Enter programs to run.\n>");

    getline(&buffer, &size, stdin);

    token = strtok_r(buffer, "\n", &saveptr);

    pid_t pid = fork();

    if (pid == 0) {
      // child process
      execlp(token, token, NULL);
      printf("Exec failure\n");
      exit(1);
    }

    else {
      // parent process
      waitpid(pid, NULL, 0);
    }
  }
  free(buffer);
  return 0;
}
