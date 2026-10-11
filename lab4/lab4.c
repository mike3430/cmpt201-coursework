#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 256

struct header {
  uint64_t size;
  struct header *next;
};

void handle_error(const char *msg) {
  perror(msg);
  exit(1);
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);

  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

int main() {

  // increase the heap by 256 bytes
  void *start = sbrk(256);

  if (start == (void *)-1) {
    return 1;
  }

  // split the 256-byte region into two 128 bytes
  void *first_block = start;
  void *second_block = (char *)start + 128; // needs to add (char*)

  // Begginning of each block is a struct header
  struct header *first_header = (struct header *)first_block;
  struct header *second_header = (struct header *)second_block;

  // First block's header
  first_header->size = 128;
  first_header->next = NULL;

  // Second block header
  second_header->size = 128;
  second_header->next = first_header;

  // point to the data region which starts after the blocks header
  char *first_data = (char *)first_block + sizeof(struct header);
  char *second_data = (char *)second_block + sizeof(struct header);

  // memset to put first block to 0 and second block to 1
  memset(first_data, 0, 128 - sizeof(struct header));
  memset(second_data, 1, 128 - sizeof(struct header));

  // print
  print_out("first block: %p\n", &first_block, sizeof(first_block));
  print_out("Second block: %p\n", &second_block, sizeof(second_block));
  print_out("First block size: %lu\n", &first_header->size, sizeof(first_header->size));
  print_out("First block next: %p\n", &first_header->next, sizeof(first_header->next));
  print_out("Second block size: %lu\n", &second_header->size, sizeof(second_header->size));
  print_out("Second block next: %p\n", &second_header->next, sizeof(second_header->next));

  size_t data_size = 128 - sizeof(struct header);

  for (size_t i = 0; i < data_size; i++) {
    uint64_t value = (uint8_t)first_data[i];
    print_out("%lu\n", &value, sizeof(value));
  }

  for (size_t i = 0; i < data_size; i++) {
    uint64_t value = (uint8_t)second_data[i];
    print_out("%lu\n", &value, sizeof(value));
  }

  return 0;
}
