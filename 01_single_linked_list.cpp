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
  // Kita mau pushTail D10 di linked list berikut:
  // A2 (head) -> B3 -> C4 (tail) 

  // D10 (temp) -> NULL || Node *temp = createNode(name, score)
  // A2 (head) -> B3 -> C4 (tail) -> D10 (temp) -> NULL || tail->next = temp
  // A2 (head) -> B3 -> C4 -> D10 (tail) -> NULL || tail = temp

  Node *temp = createNode(name, score); // create new node

  if(!head) { // if there's no head (0 node)
    head = tail = temp;
  } else { // >= 1 node
    tail->next = temp; // tail points to node
    tail = temp; // node becomes tail
  }
}

void popHead() {
  if(!head) { // 0 node
    return;
  } else if(head == tail) { // only 1 node
    free(head); // free allocated memory
    head = tail = NULL; // remove value
  } else { // >= 1 node
    Node *temp = head->next; // 98 (head) -> 100 (temp) -> 95 -> 97 (tail) -> NULL
    head->next = NULL; // 98 (head) -> N || 100 (temp) -> 95 -> 97 (tail) -> NULL
    free(head); // free allocated memory
    head = temp; // set new head
  }
}

void popTail() {
  if(!head) { // 0 node
    return;
  } else if(head == tail) { // only 1 node
    free(head); // free allocated memory
    head = tail = NULL; // remove value
  } else {
    // INITIAL: 50 (head) -> 54 -> 73 -> 36 (tail) -> NULL
    Node *temp = head; // 50 (head, temp) -> 54 -> 73 -> 36 (tail) -> NULL

    while(temp->next != tail) { // selama node selanjutnya bukan tail
      temp = temp->next; // loop terus
    }

    // 50 (head) -> 54 -> 73 (temp) -> 36 (tail) -> NULL
    temp->next = NULL; // 50 (head) -> 54 -> 73 (temp) -> NULL || 36 (tail) -> NULL
    free(tail); // 50 (head) -> 54 -> 73 (temp) -> NULL
    tail = temp; // 50 (head) -> 54 -> 73 (tail, temp) -> NULL
  }
}

void printLinkedList() {
  Node *curr = head; // set current node to head
                                          
  while(curr) { // while there is still curr
    printf("%s -> ", curr->name);
    curr = curr->next; // move to the next node
  }
  puts("NULL");
}

int main() {
  pushHead("Darnell", 95); // 95 (head, tail) -> NULL
  pushTail("whisper0", 97); // 95 (head) -> 97 (tail) -> NULL
  pushHead("pai", 100); // 100 (head) -> 95 -> 97 (tail) -> NULL
  pushHead("romario", 98); // 98 (head) -> 100 -> 95 -> 97 (tail) -> NULL
  popHead(); // 100 (head) -> 95 -> 97 (tail) -> NULL
  popTail(); // 100 (head) -> 95 (tail) -> NULL
  popTail(); // 100 (head, tail) -> NULL
  popHead(); // NULL
  printLinkedList();
  return 0;
}