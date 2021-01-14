#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
  char name[255];
  int score;
  Node *next; // node's next pointer
} *head, *tail; // global head and tail

Node *createNode(const char *name, int score) {
  Node *newNode = (Node*)malloc(sizeof(Node)); // allocate memory
  strcpy(newNode->name, name);
  newNode->score = score;
  newNode->next = NULL; // next node is null
  return newNode;
}

void pushHead(const char *name, int score) {
  Node *temp = createNode(name, score); // create new node

  if(!head) { // if there's no head (0 node)
    head = tail = temp;
  } else { // >= 1 node
    temp->next = head; // node points to head
    head = temp; // node becomes head
  }
}

void pushTail(const char *name, int score) {
  Node *temp = createNode(name, score);

  if(!head) { // empty list
    head = tail = temp; // temp (head dan tail)
  } else { // A (tail), insert B
    tail->next = temp; // A (tail) -> B (temp)
    tail = temp; // A -> B (tail, temp)
  }
}

void popHead() {
  if(!head) { // empty list
    return;
  } else if(head == tail) { // 1 node
    free(head); // free allocated memory
    head = tail = NULL; // remove value
  } else { // >= 1 node
    Node *temp = head->next; // A (head) -> B (newHead) -> C
    head->next = NULL; // A (head) || B (newHead) -> C
    free(head); // free allocated memory
    head = temp; // B (head, newHead) -> C
  }
}

void popTail() {
  if(!head) { // empty list
    return;
  } else if(head == tail) { // 1 node
    free(head); // free allocated memory
    head = tail = NULL; // remove value
  } else {
    Node *curr = head; // 50 (head, curr) -> 54 -> 36 (tail) -> NULL

    while(curr->next != tail) {
      curr = curr->next; // loop until one node behind tail
    }

    // 50 (head) -> 54 (curr) -> 36 (tail) -> NULL
    curr->next = NULL; // 50 (head) -> 54 (curr) -> NULL || 36 (tail) -> NULL
    free(tail); // 50 (head) -> 54 (curr) -> NULL
    tail = curr; // 50 (head) -> 54 (tail, curr) -> NULL
  }
}

void printLinkedList() {
  Node *curr = head; // set current node to head
                                          
  while(curr) { // while there is still curr
    printf("%s -> ", curr->name);
    curr = curr->next; // move to the next node
  }
  puts("NULL");
  getchar();
}

int main() {
  pushHead("Darnell", 95); // 95 (head, tail) -> NULL
  printLinkedList();
  pushTail("whisper0", 97); // 95 (head) -> 97 (tail) -> NULL
  printLinkedList();
  pushHead("pai", 100); // 100 (head) -> 95 -> 97 (tail) -> NULL
  printLinkedList();
  pushHead("romario", 98); // 98 (head) -> 100 -> 95 -> 97 (tail) -> NULL
  printLinkedList();
  popHead(); // 100 (head) -> 95 -> 97 (tail) -> NULL
  printLinkedList();
  popTail(); // 100 (head) -> 95 (tail) -> NULL
  printLinkedList();
  popTail(); // 100 (head, tail) -> NULL
  printLinkedList();
  popHead(); // NULL
  printLinkedList();
  return 0;
}