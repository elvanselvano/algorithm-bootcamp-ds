#include <stdio.h>
#include <string.h>

const int MAX_ELEMENT = 6;
char HASHTABLES[MAX_ELEMENT][255];

void view() {
  for(int i = 0; i < MAX_ELEMENT; i++) {
    printf("%d -> %s\n", i, HASHTABLES[i]);
  }
}

int hash(const char *str) {
  return (str[0] - 'a') % MAX_ELEMENT;
}

int linearProbing(int index) {
  // loop from index+1
  // for each iteration, i = (i+1) % MAX ELEMENT
  // in order to make sure i won't pass MAX_ELEMENT
  // just before it reach MAX_ELEMENT,
  // i will become 0 because of modulo
  // it will then loop from 0 to index
  for(int i = index+1; i != index; i = (i+1) % MAX_ELEMENT) {
    if(HASHTABLES[i][0] == '\0') { // jika table di index i kosong
      return i;
    }
  }

  return -1;
}

void insert(const char *str) {
  int index = hash(str); // get index

  if(HASHTABLES[index][0] != '\0') { // if index is already full
    index = linearProbing(index); // find new index
  }

  if(index != -1) { // if we can still insert to table
    strcpy(HASHTABLES[index], str); // insert the value
  } else {
    puts("Table is full!");
  }
}

int main() {
  insert("budi");
  insert("asep");
  insert("david");
  insert("cecep");
  insert("elsa");
  view();
  return 0;
}