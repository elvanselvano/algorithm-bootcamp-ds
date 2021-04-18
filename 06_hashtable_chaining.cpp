#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_BUCKETS = 6; // 6 linked lists

struct Node {
  char name[255];
  Node *next;
} *head[MAX_BUCKETS], *tail[MAX_BUCKETS];

Node *createNode(const char *name) {
  Node *temp = (Node*)malloc(sizeof(Node));
  strcpy(temp->name, name);
  temp->next = NULL;
  return temp;
}

// https://stackoverflow.com/questions/1579721/why-are-5381-and-33-so-important-in-the-djb2-algorithm
unsigned long djb2(const char *str) {
  unsigned long hash = 5381;

  for(int i = 0; str[i] != '\0'; i++) {
    int c = int(str[i]);
    hash = ((hash << 5) + hash) + c;
  }
    
  return hash % MAX_BUCKETS;
}

void insert(const char *str) { // similar to pushTail()
  Node *temp = createNode(str);
  int index = djb2(str); // use djb2 hashing algorithm

  if(!head[index]) { // if head is empty
    head[index] = tail[index] = temp;
  } else { // else push tail
    tail[index]->next = temp;
    tail[index] = temp;
  }
}

void traverseLinkedList(int i) {
  Node *curr = head[i];

  while(curr) {
    printf("%s -> ", curr->name);
    curr = curr->next;
  }
}

void view() {
  for(int i = 0; i < MAX_BUCKETS; i++) {
    printf("Index %d: ", i);
    if(head[i]) { // if head exists
      traverseLinkedList(i);
    } 
    puts("NULL");
  }
}

int main() {
  char names[][255] = {
    {"romario"}, {"admiralspoon"}, {"kesya"}, 
    {"nich"}, {"valencia"}, {"laffpai"},
    {"kevice"}, {"darnell"}, {"doctorneuron"},
    {"ashborne"}, {"hans"}, {"whisper"}
  };

  for(int i = 0; i < 12; i++) {
    insert(names[i]);
  }

  view();
  return 0;
}