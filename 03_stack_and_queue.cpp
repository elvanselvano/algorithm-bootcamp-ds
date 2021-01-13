#include <stdio.h>
#include <stdlib.h>

/*
STACK (First in Last Out)
prev = up, next = down
3 -> top
8
5 
*/

/*
QUEUE (First in First Out)
prev = left, next = right
3 (first), 8, 5, 10, 15 (last)
*/

struct Node {
  int value;
  Node *next, *prev;
};

Node *top; // top of the stack
Node *first, *last; // first and last node in queue

Node *createNode(int value) {
  Node *temp = (Node*)malloc(sizeof(Node));
  temp->value = value;
  temp->next = temp->prev = NULL;
  return temp;
}

void pushStack(int value) { // similar to pushHead
  Node *temp = createNode(value);
 
  if(!top) { // 0 node
    top = temp;
  } else { // >= 1 node
    top->prev = temp;
    temp->next = top;
    top = temp;
  }
}

void removeStack() { // similar to popHead
  if(!top) { // 0 node
    return;
  } else if(top->next == NULL) { // 1 node
    free(top); // free allocated memory
    top = NULL; // remove value
  } else { // > 1 node
    Node *newTop = top->next;
    top->next = newTop->prev = NULL;
    free(top);
    top = newTop;
  } 
}

void pushQueue(int value) { // similar to pushTail
  Node *temp = createNode(value);

  if(!first) { // 0 node
    first = last = temp;
  } else {
    last->next = temp;
    temp->prev = last;
    last = temp;
  }
}

void removeQueue() { // similar to popHead
  if(!first) { // 0 node
    return;
  } else if(first == last) { // 1 node
    free(first); // free allocated memory
    first = last = NULL; // remove value
  } else { // > 1 node
    Node *newFirst = first->next;
    first->next = newFirst->prev = NULL;
    free(first);
    first = newFirst;
  } 
}

void printStack() {
  Node *curr = top;

  puts("Stack: ");
  while(curr) {
    printf("%d\n", curr->value);
    curr = curr->next; // traverse down
  }
  puts("NULL");
}

void printQueue() {
  Node *curr = first;

  printf("Queue: ");
  while(curr) {
    printf("%d -> ", curr->value);
    curr = curr->next; // traverse right
  }
  puts("NULL");
}

void visualizeStack(int N, int values[]) {
  for(int i = 0; i < N; i++) {
    pushStack(values[i]);
    printf("Inserted %d to the top of the stack.\n", values[i]);
    printStack();
    getchar();
  }

  for(int i = 0; i < N; i++) {
    removeStack();
    puts("Removed the top of the stack.");
    printStack();
    getchar();
  }
}

void visualizeQueue(int N, int values[]) {
  for(int i = 0; i < N; i++) {
    pushQueue(values[i]);
    printf("Inserted %d to the queue.\n", values[i]);
    printQueue();
    getchar();
  }

  for(int i = 0; i < N; i++) {
    removeQueue();
    puts("Removed the first element from the queue.");
    printQueue();
    getchar();
  }
}

int main() {
  int N = 8;
  int values[] = {10, 9, 13, 12, 5, 11, 8, 15};
  // visualizeStack(N, values);
  // visualizeQueue(N, values);

  return 0;
}
