#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value; 
  Node *next, *prev;
} *first, *last; // first (highest priority), last (lowest priority)

Node *createNode(int value) {
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->value = value;
  newNode->next = newNode->prev = NULL;
  return newNode;
}

void pushPriority(int value) { // similar to popMid()
  Node *newNode = createNode(value);

  if(!first) {
    first = last = newNode;
  } else if(value > first->value) { // pushHead()
    newNode->next = first; // D -> A (first) B C
    first->prev = newNode; // D -> <-  A (first) B C
    first = newNode; // D (first) -> <-  A B C
  } else if(value < last->value) { // pushTail()
    last->next = newNode; // A B C (last) -> D
    newNode->prev = last; // A B C (last) -> <- D
    last = newNode; // A B C D (last)
  } else { // pushMid()
    Node *curr = first;
    // 50 40 30 20, insert 35
    while(value < curr->value) {
      curr = curr->next; // 50 40 30 (curr) 20
    }

    newNode->next = curr; // 35->next = 30
    newNode->prev = curr->prev; // 35->prev = 40
    curr->prev->next = newNode; // 40->next = 35
    curr->prev = newNode; // 30->prev = 35
  }
}

void printQueue() {
  Node *curr = first;

  printf("Queue: ");
  while(curr) {
    printf("%d -> ", curr->value);
    curr = curr->next;
  }
  puts("NULL");
}

void removePriority() { // similar to popHead()
  if(!first) {
    return;
  } else if(first == last) {
    free(first);
    first = last = NULL;
  } else {
    Node *candidateFirst = first->next;
    first->next = candidateFirst->prev = NULL;
    first = candidateFirst;
  }

}

void visualizePriority(int N, int values[]) {
  for(int i = 0; i < N; i++) {
    pushPriority(values[i]);
    printf("Inserted %d to the list.\n", values[i]);
    printQueue();
    getchar();
  }

  for(int i = 0; i < N; i++) {
    removePriority();
    printf("Removed the first element from the list.\n");
    printQueue();
    getchar();
  }
}

int main() {
  int N = 8;
  int values[] = {10, 9, 13, 12, 5, 11, 8, 15};
  visualizePriority(N, values); 

  return 0;
}