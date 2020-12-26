#include <stdio.h>
#include <stdlib.h>

/*
prev = atas, next = bawah
  8
  3 -> top
  5 
*/

struct Node {
  int value;
  Node *next, *prev;
} *top;

Node *createNode(int value) {
  Node *temp = (Node*)malloc(sizeof(Node));
  temp->value = value;
  temp->next = temp->prev = NULL;
  return temp;
}

void push(int value) {
  Node *temp = createNode(value);
 
  if(!top) { // kasus 0 node
    top = temp;
  } else { // kasus >= 1 node
    top->prev = temp;
    temp->next = top;
    top = temp;
  }
}

void remove() {
  if(!top) { // 0 node
    return;
  } else if(top && top->next == NULL) { // 1 node
    free(top); // free allocated memory
    top = NULL; // remove value
  } else { // > 1 node
    Node *temp = top->next;
    top->next = temp->prev = NULL;
    free(top);
    top = temp;
  } 
}

void printStack() {
  Node *curr = top;

  puts("Stack: ");
  while(curr) {
    printf("%d\n", curr->value);
    curr = curr->next; // traverse down
  }
  puts("");
}

int main() {
  push(8); 
  push(4);
  remove();
  remove();
  printStack();

  return 0;
}
