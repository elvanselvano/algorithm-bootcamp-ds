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
  Node *temp = createNode(name, score); // buat node baru

  if(!head) { // linked list kosong (0 node)
    head = tail = temp; // temp akan menjadi head dan tail
  } else { // >= 1 node
    temp->next = head; // node setelah temp adalah head
    head = temp; // head baru adalah temp
  }
}

void pushTail(const char *name, int score) {
  // Kita mau pushTail D10 di linked list berikut:
  // A2 (head) -> B3 -> C4 (tail) 

  // D10 (temp) -> NULL || Node *temp = createNode(name, score)
  // A2 (head) -> B3 -> C4 (tail) -> D10 (temp) -> NULL || tail->next = temp
  // A2 (head) -> B3 -> C4 -> D10 (tail) -> NULL || tail = temp

  Node *temp = createNode(name, score); // buat nodenya

  if(!head) { // linked list kosong (0 node)
    head = tail = temp; // temp akan menjadi head dan tail
  } else { // >= 1 node
    tail->next = temp; // tail lama -> next adalah node baru
    tail = temp; // temp akan menjadi tail (node terakhir)
  }
}

void popHead() {
  if(!head) { // jika tidak ada node
    return; // return (tidak ngapa2in)
  } else if(head == tail) { // untuk kasus 1 node di pophead bsa diabaikan
    free(head); // free allocated memory
    head = tail = NULL;
  } else {
    // INITIAL: 98 (head) -> 100 -> 95 -> 97 (tail) -> NULL
    Node *temp = head; // 98 (head, temp) -> 100 -> 95 -> 97 (tail) -> NULL
    head = temp->next; // 98 (temp) -> 100 (head) -> 95 -> 97 (tail) -> NULL
    temp->next = NULL; // 98 (temp) -> NULL || 100 (head) -> 95 -> 97 (tail) -> NULL
    free(temp); // 100 (head) -> 95 -> 97 (tail) -> NULL
  }
}

void popTail() {
  if(!head) { // jika tidak ada node
    return; // return (tidak ngapa2in)
  } else if(head == tail) { // 50 (head, tail) -> NULL
    free(head); // free allocated memory
    head = tail = NULL; // kosongkan nilainya
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
  Node *curr = head; // curr adalah index yang akan berjalan
  // 30 (head) -> 20 -> 15 -> 40 (tail) -> NULL
  //  curr
                                          
  while(curr) { // selama curr bukan NULL
    printf("%s -> ", curr->name); // print data
    curr = curr->next; // curr akan berjalan ke node selanjutnya
  }
  printf("NULL\n");
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