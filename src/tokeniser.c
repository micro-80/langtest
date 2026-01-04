#include "tokeniser.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_TOKENS_ALLOCATION 8
#define READ_FILE_BUFFER_SIZE 256

const char *to_string(TokenType token) {
  switch (token) {
#define X(token_type)                                                          \
  case token_type:                                                             \
    return #token_type;
    TOKENS
#undef X
  }
}

// TODO: make -> a delimiter
bool is_char_delimiter(const char c) {
  const char *delimiters = " (){}:=;\t\n";
  // quite a lot of O(n) searches here
  return strchr(delimiters, c) != NULL;
}

TokenType tokenise(const char *token) {
  if (strcmp(token, "def") == 0) return TOKEN_KEYWORD_DEF;
  else if (strcmp(token, "function") == 0) return TOKEN_KEYWORD_FUNCTION;
  else if (strcmp(token, "return") == 0) return TOKEN_KEYWORD_RETURN;
  else if (strcmp(token, "->") == 0) return TOKEN_FUNCTION_DECLARATION_RETURN_INDICATOR;
  else if (strcmp(token, "{") == 0) return TOKEN_CURLY_BRACE_OPEN;
  else if (strcmp(token, "}") == 0) return TOKEN_CURLY_BRACE_CLOSE;
  else if (strcmp(token, "(") == 0) return TOKEN_CURLY_BRACKET_OPEN;
  else if (strcmp(token, ")") == 0) return TOKEN_CURLY_BRACKET_CLOSE;
  else if (strcmp(token, ":") == 0) return TOKEN_COLON;
  else if (strcmp(token, "=") == 0) return TOKEN_EQUALS;
  else if (strcmp(token, ";") == 0) return TOKEN_SEMI_COLON;
  else if (isdigit(token[0])) return TOKEN_NUMERIC_LITERAL;
  else if (token[0] == '"' && token[strlen(token) - 1] == '"') return TOKEN_STRING_LITERAL;
  else return TOKEN_IDENTIFIER;
}

TokenType tokenise_delimiter(const char delimiter) {
  const char *tokenised_delimiters = "(){}:=;";
  
  if (strchr(tokenised_delimiters, delimiter) != NULL) {
    const char delimiter_string[2] = { delimiter, '\0' };
    return tokenise(delimiter_string);
  }
  return -1;
}

TokenType *parse_tokens_for_file(FILE *source_file) {
  TokenType *tokens = malloc(INITIAL_TOKENS_ALLOCATION * sizeof(TokenType));

  // FIXME: this should probably support arbitrarily long lines
  char buf[READ_FILE_BUFFER_SIZE];
  int line_count = 0;

  while (fgets(buf, sizeof(buf), source_file) != NULL) {
    line_count++;

    // sanity check for above FIXME
    size_t line_length = strlen(buf);
    char last_char = buf[line_length - 1];
    if (last_char != '\n' && !feof(source_file)) {
      fprintf(stderr, "Line %i exceeded maximum capacity of %i characters.",
              line_count, READ_FILE_BUFFER_SIZE);
      exit(1);
    }

    int cursor = 0;
    while (buf[cursor] != '\n' && cursor < line_length) {
      while (is_char_delimiter(buf[cursor]) && cursor < line_length) {
        TokenType tokenised_delimiter = tokenise_delimiter(buf[cursor]);
        if (tokenised_delimiter != -1) {
	  printf("%s ", to_string(tokenised_delimiter));
	}
        cursor++;
      }
      int token_start_cursor = cursor;

      while (!is_char_delimiter(buf[cursor]) && cursor < line_length) {
        cursor++;
      }

      char token[READ_FILE_BUFFER_SIZE];
      int token_length = cursor - token_start_cursor;
      if (token_length == 0) {
        continue;
      }

      memcpy(token, &buf[token_start_cursor], token_length);
      token[token_length] = '\0';

      // TODO: handle //blah style comments
      if (strcmp(token, "//") == 0) {
        break;
      }

      if (token[0] == '"') {
        while (buf[cursor++] != '"') {
          if (buf[cursor] == '\n') {
            fprintf(stderr, "Line %i: unterminated string literal", line_count);
	    exit(1);
	  }
	  continue;
        }
	// TODO: extract into own function
	int token_length = cursor - token_start_cursor;
	memcpy(token, &buf[token_start_cursor], token_length);
	token[token_length] = '\0';
      }

      const TokenType token_type = tokenise(token);
      const char *token_str = to_string(token_type);
      switch (token_type) {
      case TOKEN_IDENTIFIER:
      case TOKEN_STRING_LITERAL:
        printf("%s(%s) ", to_string(tokenise(token)), token);
	break;
      default:
	printf("%s ", to_string(tokenise(token)));	
	break;
      }
    }
    printf("\n");
  };

  return tokens;
}
