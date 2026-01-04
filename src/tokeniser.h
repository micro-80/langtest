#include <stdio.h>

#define TOKENS                                                                 \
  X(TOKEN_KEYWORD_FUNCTION)                                                    \
  X(TOKEN_FUNCTION_DECLARATION_RETURN_INDICATOR)                               \
  X(TOKEN_CURLY_BRACKET_OPEN)                                                  \
  X(TOKEN_CURLY_BRACKET_CLOSE)                                                 \
  X(TOKEN_CURLY_BRACE_OPEN)                                                    \
  X(TOKEN_CURLY_BRACE_CLOSE)                                                   \
  X(TOKEN_KEYWORD_DEF)                                                         \
  X(TOKEN_STRING_LITERAL)                                                      \
  X(TOKEN_COLON)                                                               \
  X(TOKEN_EQUALS)                                                              \
  X(TOKEN_SEMI_COLON)                                                          \
  X(TOKEN_IDENTIFIER)                                                          \
  X(TOKEN_KEYWORD_RETURN)                                                      \
  X(TOKEN_NUMERIC_LITERAL)

typedef enum TokenType {
#define X(value) value,
  TOKENS
#undef X
} TokenType;

const char* to_string(TokenType token);

TokenType *parse_tokens_for_file(FILE *sourceFile);
