#include <errno.h>
#include <stdio.h>
#include <string.h>

enum AST {
  KEYWORD_FUNCTION,
  FUNCTION_DECLARATION_NAME,
  FUNCTION_DECLARATION_RETURN_INDICATOR,
  FUNCTION_DECLARATION_RETURN_TYPE,
  CURLY_BRACKET_OPEN,
  CURLY_BRACKET_CLOSE,
  CURLY_BRACE_OPEN,
  CURLY_BRACE_CLOSE,
  KEYWORD_DEF,
  VARIABLE_DECLARATION_NAME,
  VARIABLE_DECLARATION_EQUALS,
  STRING_LITERAL,
  SEMI_COLON,
  CALL_FUNCTION,
  KEYWORD_RETURN,
  NUMERIC_LITERAL
};

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr,
            "You need to supply exactly 1 argument - the file to be parsed.\n");
    return 1;
  }

  const char* fileName = argv[1];
  
  FILE *testSrc = fopen(fileName, "r");
  if (!testSrc) {
    fprintf(stderr, "Error opening file %s: %s\n", fileName, strerror(errno));
    return 1;
  }

  char buf[128];
  while (fgets(buf, sizeof(buf), testSrc) != NULL) {
    printf("%s\n", buf);
  };

  if (fclose(testSrc) == EOF) {
    perror("Error closing file");
    return 1;
  }

  return 0;
}
