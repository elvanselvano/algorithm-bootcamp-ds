#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  Node *next, *prev; // point to the left and right
} *head, *tail; // point to the leftmost and rightmost node

Node *createNode(int value) {
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->value = value;
  newNode->next = newNode->prev = NULL;
  return newNode;
}

void pushHead(int value) {
  Node *temp = createNode(value);

  if(!head) { // empty list
    head = tail = temp; // temp (head and tail)
  } else { // A (head), insert B
    head->prev = temp; // B (temp) <- A (head)
    temp->next = head; // B (temp) -><- A (head)
    head = temp; // B (temp, head) -><- A
  }
}

void pushTail(int value) {
  Node *temp = createNode(value);

  if(!head) { // empty list
    head = tail = temp; // temp (head dan tail)
  } else { // A (tail), insert B
    tail->next = temp; // A (tail) -> B (temp)
    temp->prev = tail; // A (tail) -><- B (temp)
    tail = temp;  // A -><- B (temp, tail)
  }
}

void pushMid(int value) {
  if(!head) { // empty list
    Node *temp = createNode(value);
    head = tail = temp;
  } else if(value < head->value) { // add to the leftmost
    pushHead(value);
  } else if(value > tail->value) { // add to the rightmost
    pushTail(value);
  } else { // value is between head and tail
    Node *temp = createNode(value); // 9 (temp)
    Node *curr = head; // 1 (head, curr) -><- 8 -><- 12 -><- 15, insert 9

    while(curr->value < value) {
      curr = curr->next; // traverse until curr->value > value
    }

    // 1 -><- 8 -><- 12 (curr) -><- 15 || 9 (temp)
    temp->prev = curr->prev; // 9->prev = 8
    temp->next = curr; // 9->next = 12
    
    // 1 -><- 8 ->      <- 12 (curr) -><- 15
    //        \(prev)   /(next)
    //               9 (temp)

    curr->prev->next = temp; // 8->next = 9
    curr->prev = temp; // 12->prev = 9
    // 1 -><- 8                           12 (curr) -><- 15
    //       \(prev)\(next)     /(next)/(prev)
    //                   9 (temp)
  }
}

void popHead() {
  if(!head) { // empty list
    return;
  } else if(head == tail) { // 1 node
    free(head);
    head = tail = NULL;
  } else { // >= 1 node
    Node *newHead = head->next; // A (head) -><- B (newHead) -><- C
    head->next = newHead->prev = NULL; // A (head) || B (newHead) -><- C
    free(head); // B (newHead) -><- C
    head = newHead; // B (head, newHead) -><- C
  }
}

void popTail() {
  if(!head) { // empty list
    return; 
  } else if(head == tail) { // 1 node
    free(head);
    head = tail = NULL;
  } else { // >= 1 node
    Node *newTail = tail->prev; // A -><- B (newTail) -><- C (tail)
    tail->prev = newTail->next = NULL; // A -><- B (newTail) || C (tail)
    free(tail); // A -><- B (newTail)
    tail = newTail; // A -><- B (tail, newTail)
  }
}

void popMid(int value) {
  if(!head) { // empty list
    return;
  } else if(head->value == value) {
    popHead(); 
  } else if(tail->value == value) {
    popTail(); 
  } else { // value is between head and tail
    Node *curr = head; // 10 (curr) 20 30 40 50, remove 30

    while(curr && curr->value != value) {
      curr = curr->next; // traverse until we find the value
    }

    // 10 -><- 20 -><- 30 (curr) -><- 40 -><- 50, remove 30
    curr->prev->next = curr->next; // 20->next = 40
    curr->next->prev = curr->prev; // 40->prev = 20

    // 10 -><- 20      -><-     40 -><- 50, mau hapus 30
    //          \<- 30 (curr) ->/ 

    curr->prev = curr->next = NULL; // set pointers to NULL
    free(curr); // free assigned memory
    curr = NULL; // remove value
  }
}

void printLinkedList() {
  Node *curr = head;
  printf("Linked List: ");

  while(curr) {
    printf("%d -> ", curr->value);
    curr = curr->next;
  }
  puts("NULL");
}

void visualizeList(int N, int values[]) {
  for(int i = 0; i < N; i++) {
    pushMid(values[i]);
    printf("Inserted %d to the list.\n", values[i]);
    printLinkedList();
    getchar();
  }

  for(int i = 0; i < N; i++) {
    popMid(values[i]);
    printf("Removed %d from the list.\n", values[i]);
    printLinkedList();
    getchar();
  }
}

int main() {
  int N = 8;
  int values[] = {10, 9, 13, 12, 5, 11, 8, 15};
  visualizeList(N, values);

  return 0;
}