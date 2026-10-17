/* TODO: Provide implementations of your tokenize function here */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../vector/vect.h"
#include "tokens.h"

/** Is c one of the special single-character tokens? */
static int is_special(char c) {
  return c == '(' || c == ')' || c == '<' || c == '>' || c == ';' || c == '|';
}

/** Is c a whitespace character that separates tokens? */
static int is_whitespace(char c) {
  return c == ' ' || c == '\t' || c == '\n';
}

/** Add the len characters starting at start to the vector as one token. */
static void add_token(vect_t *tokens, const char *start, size_t len) {
  assert(tokens != NULL);
  assert(start != NULL);

  char *token = (char *) malloc(len + 1);
  assert(token != NULL);
  memcpy(token, start, len);
  token[len] = '\0';

  vect_add(tokens, token);  /* the vector stores its own copy */
  free(token);
}

/** Split the input string into a vector of tokens. */
vect_t *tokenize(const char *input) {
  assert(input != NULL);

  vect_t *tokens = vect_new();
  assert(tokens != NULL);

  size_t i = 0;
  while (input[i] != '\0') {
    char c = input[i];

    if (is_whitespace(c)) {
      /* Whitespace outside quotes only separates tokens. */
      i++;
    } else if (is_special(c)) {
      /* Special characters are tokens on their own. */
      add_token(tokens, &input[i], 1);
      i++;
    } else if (c == '"') {
      /* Quoted string: everything up to the closing quote is one token,
       * without the quotes. If the quote is never closed, the token runs
       * to the end of the line. */
      size_t start = i + 1;
      size_t end = start;
      while (input[end] != '\0' && input[end] != '"' && input[end] != '\n') {
        end++;
      }
      add_token(tokens, &input[start], end - start);
      i = (input[end] == '"') ? end + 1 : end;
    } else {
      /* Word: runs until whitespace, a special character, a quote, or
       * the end of the input. */
      size_t start = i;
      while (input[i] != '\0' && !is_whitespace(input[i]) &&
             !is_special(input[i]) && input[i] != '"') {
        i++;
      }
      add_token(tokens, &input[start], i - start);
    }
  }

  return tokens;
}