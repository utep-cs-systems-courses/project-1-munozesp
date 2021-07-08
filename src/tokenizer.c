#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#define false 0
#define true 1

/*Return true(non-zero) if c is a whitespace character 
  ('\t' or ' ').
  Zero terminators are not printable (therefore false) */

int space_char(char c) {
  if (c == ' ' || c == '\t'){
    return true;
  } else {
    return false;
  }
}

/*Return true (non-zero) if c is a non-whitespace 
  character (not tab or space).
  Zero terminators are not printable (therefore false) */
int non_space_char(char c) {
  if (c != ' ' && c!= '\t') {
    return true;
  } else {
    return false;
  }
}

/*Returns a pointer to the first character of the next
  space-separated word in zero-terminated str. 
  Return a zero pointer if str does not contain any words. */
char *word_start(char *str) {
  char* tmp = str;
  while (*tmp != '\0') {
    if ((non_space_char(tmp[0])) == 1) {
      return tmp;
    }
    tmp++;
  }
  return tmp;
  }

/* Returns a pointer terminator char following *word */
char *word_terminator(char *word) {
  while (non_space_char((*word))) {
    word++;
    if (space_char(*word)) {
      return word;
    }
  }
  return "0";
}

/*Counts the number of words in the string argument. */
int count_words(char *str) {
  int count = 0; // store number of words

  int OUT = 0; // out of word
  int IN = 1; //in a word
  int state = OUT; //whether we are in a word or not

  //traverse char pointer
  while (*str) {
    if (*str == ' ' || *str == '\t' || *str == '\n') {
      state = OUT;
    } else if (state == OUT) {
      state = IN;
      count++;
    }
    str++;
  }
  return count;
}

/*Returns a freshly allocateed new zero-terminated string
  containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len) {
  char* helper = inStr; //storing original string
  char* copyStr = NULL; // storing copy of string

  // "hello world"
  // \0 terminator escape character
  // "hello world\0" (len) +1
  copyStr = (char*) malloc(sizeof(char) * (len +1));

  //mandatory to add '\0' at the end of the string
  copyStr[len] = '\0';

  int index = 0;

  //Copy the contents from the helper pointer (which has the same address as the original string)
  //to copyStr until you reach the end of the string

  while (*helper != '\0') {
    copyStr[index++] = *helper++;
  }
  return copyStr;
}

char **tokenize(char* str) {
  int size = count_words(str); //how many words are in the string

  //allocate memory
  char** tokens = (char**) malloc(sizeof(char*) * (size +1));

  char* start = word_start(str);
  char* terminator = word_terminator(start);

  int i;
  for (i = 0; i < size; i++){
    if(i > 0) {
      start = word_start(terminator);
      terminator = word_terminator(start);
    }
    int size2 = terminator - start;
    tokens[i] = malloc(size2 * sizeof(char));

    for(int j =0; j < size2; j++) {
      tokens[i][j] = start[j];
    }
  }
  return tokens;
}

/*Prints all tokens*/
void print_tokens(char **tokens) {
  int i= 0;
  while (tokens[i] != NULL) {
    printf("tokens[%d] = %s\n", i, tokens [i]);
    i++;
  }

}
/*Frees all tokens and the vector containing them */
void free_tokens(char **tokens) {
  while (*tokens) {
    free(*tokens);
    tokens++;
  }
  free(tokens);
}
 
