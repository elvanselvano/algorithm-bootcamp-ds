#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  Node *next, *prev;
} *head, *tail, *curr;

Node *createNode(int value) {
  Node *temp = (Node*)malloc(sizeof(Node));
  temp->value = value;
  temp->next = temp->prev = NULL;
  return temp;
}

void pushHead(int value) {
  Node *temp = createNode(value);

  if(!head) { // 0 node
    head = tail = temp; // Linked List: temp (head dan tail)
  } else { // Linked List: A (head), mau insert B
    head->prev = temp; // B (temp) <- A (head)
    temp->next = head; // B (temp) -><- A (head)
    head = temp; // B (temp, head) -><- A
  }
}

void pushTail(int value) {
  Node *temp = createNode(value);

  if(!head) { // 0 node
    head = tail = temp; // Linked List: temp (head dan tail)
  } else { // Linked List: A (tail), mau insert B
    tail->next = temp; // A (tail) -> B (temp)
    temp->prev = tail; // A (tail) -><- B (temp)
    tail = temp;  // A -><- B (temp, tail)
  }
}

void pushMid(int value) {
  if(!head) { // tidak ada node
    Node *temp = createNode(value);
    head = tail = temp;
  } else if(value < head->value) { // nilai kurang dari head
    pushHead(value);
  } else if(value > tail->value) { // nilai lebih dari tail
    pushTail(value);
  } else { // nilai di antara head dan tail
    // 1 (curr) -> 8 -> 12 -> 15, mau insert 9
    Node *temp = createNode(value);
    Node *curr = head;

    // selama nilainya kurang dari value
    while(curr->value < value) {
      curr = curr->next;
    }
    // 1 -><- 8 -><- 12 (curr) -><- 15, mau insert 9
    // 1 -><- 8 -><- 9 -><- 12 (curr) -><- 15

    temp->prev = curr->prev; // temp->prev = 8
    temp->next = curr; // temp->next = 12
    // Hasilnya: 1 -><- 8 ->      <- 12 (curr) -><- 15
    //                   \(prev)   /(next)
    //                         temp

    curr->prev->next = temp; // 8->next = temp
    curr->prev = temp; // 12->prev = temp
    // Hasilnya: 1 -><- 8                           12 (curr) -><- 15
    //                   \(prev)\(next)     /(next)/(prev)
    //                                 temp
  }
}

void popHead() {
  if(!head) { // 0 node
    return;
  } else if(head == tail) { // 1 node
    free(head);
    head = tail = NULL;
  } else { // >= 1 node
    Node *temp = head->next; // A (head) -><- B (temp) -><- C
    head->next = temp->prev = NULL; // A (head) B (temp) -><- C
    free(head); // B (temp) -><- C
    head = temp; // B (head, temp) -><- C
  }
}

void popTail() {
  if(head && head == tail) { // jika hanya 1 node
    head = tail = NULL;
    free(head);
  } else { // jika > 1 node // A -><- B -><- C (tail)
    Node *newTail = tail->prev; // A -><- B (newTail) -><- C (tail)
    tail->prev = newTail->next = NULL; // A -><- B (newTail) C (tail)
    free(tail); // A -><- B (newTail)
    tail = newTail; // A -><- B (tail)
  }
}

void popMid(int value) {
  if(!head) {
    return;
  } else if(head->value == value) {
    popHead(); // jika nilai head adalah yang mau kita hapus
  } else if(tail->value == value) {
    popTail(); // jika nilai tail adalah yang mau kita hapus
  } else { // jika nilai yang mau kita hapus ada di tengah2
    curr = head; // 10 (curr) 20 30 40 50, mau hapus 30

    while(curr && curr->value != value) {
      curr = curr->next;
    }
    // 10 -><- 20 -><- 30 (curr) -><- 40 -><- 50, mau hapus 30

    curr->prev->next = curr->next; // 20->next = 40
    curr->next->prev = curr->prev; // 40->prev = 20
    // 10 -><- 20      -><-     40 -><- 50, mau hapus 30
    //          \<- 30 (curr) ->/ 

    curr->prev = curr->next = NULL; // set pointers to NULL
    free(curr); // free assigned memory
    curr = NULL; // remove value
  }
}

bool search(int value) {
  curr = head;

  while(curr) {
    if(curr->value == value) {
      return true;
    }
    curr = curr->next;
  }

  return false;
}

void printLinkedList() {
  curr = head;

  while(curr) {
    printf("%d ", curr->value);
    curr = curr->next;
  }
  puts("");
}

int main() {
  pushMid(15);
  pushMid(10);
  pushMid(20);
  pushMid(25);
  printLinkedList();
  popHead();
  printLinkedList();
  popMid(20);
  printLinkedList();
  popMid(15);
  printLinkedList();
  popMid(25);
  printLinkedList();

  return 0;
}