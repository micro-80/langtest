#include <stdio.h>

const char* FILE_NAME = "test.lt";

int main() {
  FILE *testSrc = fopen(FILE_NAME, "r");
  if (!testSrc) {
    perror(FILE_NAME);
    return 1;
  }

  int character;
  do {
    character = getc(testSrc);
    printf("%c\n", character);
  } while (character != EOF);

  if (fclose(testSrc) == EOF) {
    printf("Error while closing file.");
  }
  
  return 0;
}
