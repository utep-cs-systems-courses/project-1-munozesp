#include <stdio.h>
#include <stdlib.h>
#include "history.h"
#include "tokenizer.h"


/*Initialize linked list to keep history. */
List* init_history () {
  List *history = (List*) malloc(sizeof(List) * 300);
  return history;
}

/* Add a history item to the end of the list.
   List* list- the linked list
   char* str- the string to store.
*/

void add_history(List *list, char *str) {
  Item* addItem = (Item*) malloc(sizeof(Item)*300);
  addItem->str = str;
  if (list->root == NULL) {
    addItem->id = 1;
    list->root = addItem;
  }
  else {
    Item* history_item = list->root;
    addItem->id=1;
    while (history_item->next != NULL) {
      addItem->id++;
      history_item = history_item->next;
    }
    history_item->next=addItem;
    addItem->str = str;
    addItem->id++;
  }
}
/* Retrieve string stored in the node where Item->id == id.
   List* list - the linked list
   int id- the id of the Item to find
*/
char *get_history(List *list, int id) {
  if (list->root == NULL) {
    return "List is empty";
  }
  else {
    Item* temp = list->root;
    while (temp != NULL) {
      if (temp->id == id) {
	return temp->str;
      }
      temp = temp->next;
    }
    return "Sorry item ID not found";
  }
}

/*Print entire contents of the list*/
void print_history(List *list) {
  int i= 0;
  Item *tmp = list->root;
  while (tmp != NULL) {
    printf("Item [%d]: %s\n", tmp->id, tmp->str);
    tmp = tmp->next;
    
  }
}

/*Free history list and the strings it references. */
void free_history(List *list) {
  Item* tmp;
  Item* tmp2 = list->root;
  while (tmp2 != NULL) {
    tmp = tmp2;
    tmp2 = tmp2->next;
    free(tmp);
    free(tmp->str);
  }
  free(list);
}

