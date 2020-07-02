#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"
#define MAX 1000


int compareStrings(const char *temp1, const char *temp2) {
  while (*temp1 && *temp2) {
    if(*temp1 == *temp2) {
      temp1++;
      temp2++;
    }
    else {
      if (*temp1 < *temp2) {
	return -1; //returning a negative value
      }
      else {
	return 1; //returing a positive value
      }
    }
  }
  return 0; //return 0 if the strings are the same
}

/*void tests() {
  char str1[] = " I love ice cream" ;
  char **tokens = tokenize(str1);

  print_tokens(tokens);
}
*/


int main(void) {
  char buffer[2041];
  int condition = 1;

  List* test_history = init_history();
  printf("%s\n", get_history(test_history, 1)); //should print list is empty, list has no entries
  add_history(test_history, "happy");
  add_history(test_history, "joy");

  printf("%s\n", get_history(test_history, 0)); //should print not found
  printf("%s\n", get_history(test_history, 1)); //should print happy

  List* list = init_history();
  
  while (condition == 1) {
    printf("$ "); //ready for input
    fgets(buffer, MAX, stdin);
    char** tokens = tokenize(buffer);
    print_tokens(tokens);

    if (compareStrings(tokens[0], "history") == 0) {
      print_history(list);
    } else if (tokens[0][0] - '1' == 0) {
      int x = tokens[0][1] - '0';
      if (x >= 1) {
	printf("%s\n", get_history(list, x));
      }
    } else {
      add_history(list, buffer);
    }
  }
  return 0;
}
 
