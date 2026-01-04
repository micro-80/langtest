#include "tokeniser.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr,
            "You need to supply exactly 1 argument - the file to be parsed.\n");
    return 1;
  }

  const char *file_name = argv[1];

  FILE *source_file = fopen(file_name, "r");
  if (!source_file) {
    fprintf(stderr, "Error opening file %s: %s\n", file_name, strerror(errno));
    return 1;
  }

  TokenType *ast = parse_tokens_for_file(source_file);

  free(ast);

  if (fclose(source_file) == EOF) {
    perror("Error closing file");
    return 1;
  }

  return 0;
}
