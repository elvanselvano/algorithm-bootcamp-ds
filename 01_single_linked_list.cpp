#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  Node *next; // node's next pointer
} *head, *tail; // global head and tail

Node *createNode(int value) {
  // allocate memory with size of Node and cast it to Node*
  Node *newNode = (Node*)malloc(sizeof(Node)); 
  newNode->value = value; // fill in the value
  newNode->next = NULL; // next node is null
  return newNode;
}

void pushHead(int value) {
  Node *temp = createNode(value); // create new node

  if(!head) { // if there's no head (0 node)
    head = tail = temp; // node is the first and last
  } else { // >= 1 node
    temp->next = head; // node points to head
    head = temp; // node becomes head
  }
}

void pushTail(int value) {
  Node *temp = createNode(value);

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
    printf("%d -> ", curr->value);
    curr = curr->next; // move to the next node
  }
  puts("NULL");
  getchar();
}

void visualizeList(int N, int values[], int randomizer) {
  for(int i = 0; i < N; i++) {
    if(i % randomizer) {
      pushHead(values[i]);
      printf("Inserted %d to the head.\n", values[i]);
    } else {
      pushTail(values[i]);
      printf("Inserted %d to the tail.\n", values[i]);
    }

    printLinkedList();
  }

  for(int i = 0; i < N; i++) {
    if(i % randomizer) {
      popTail();
      puts("Removed the tail.");
    } else {
      popHead();
      puts("Removed the head.");
    }

    printLinkedList();
  }
}

int main() {
  int N = 8;
  int values[] = {10, 9, 13, 12, 5, 11, 8, 15};
  visualizeList(N, values, 2);
  visualizeList(N, values, 1);
  visualizeList(N, values, 3);

  return 0;
}