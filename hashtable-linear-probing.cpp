#include <stdio.h>
#include <string.h>

const int MAX_ELEMENT = 10; // maksimal elemen dalam hashtable
const int MAX_LENGTH = 255; // panjang maksimal setiap elemen
char HASHTABLES[MAX_ELEMENT][MAX_LENGTH]; // bisa menampung elemen sebanyak MAX_ELEMENT dengan tiap elemen memiliki panjang maksimal MAX_LENGTH

void view() {
  for(int i = 0; i < MAX_ELEMENT; i++) {
    printf("%d -> %s\n", i, HASHTABLES[i]);
  }
}

int hash(const char *str) {
  // hash function ascii sum
  int sum = 0;
  for(int i = 0; str[i] != '\0'; i++) {
    sum += str[i] - '0'; // sum ditambahkan ascii karakter sekarang
  }

  return sum % MAX_ELEMENT; // dimodulo agar tidak out of bounds
}

int linearProbing(int index) {
  // loop dari index+1 karena index sudah full
  // untuk tiap iterasi, i = (i+1) % MAX ELEMENT
  // untuk memastikan i tidak melewati MAX_ELEMENT
  // pas sebelum dia nyentuh MAX_ELEMENT,
  // i akan menjadi 0 karena modulo
  // kemudian i akan loop dari 0 sampai index-1

  for(int i = index+1; i != index; i = (i+1) % MAX_ELEMENT) {
    if(HASHTABLES[i][0] == '\0') { // jika table di index i kosong
      return i; // return index kosongnya
    }
  }

  return -1; // tidak ketemu index kosong
}

void insert(const char *str) {
  int index = hash(str); // dapatkan index melalui hash function

  if(HASHTABLES[index][0] == '\0') { // jika index masih kosong
    strcpy(HASHTABLES[index], str); // masukkan string di hashtable
  } else { // jika index sudah terisi
    index = linearProbing(index); // cari index baru
    if(index == -1) {
      puts("Sudah penuh");
      return;
    }
    strcpy(HASHTABLES[index], str); // masukkan string di index baru
  }
}

int main() {
  insert("romario");
  insert("admiralspoon");
  insert("kesya");
  insert("nich");
  insert("valencia");
  insert("laffpai");
  insert("kevice");
  view();
  return 0;
}