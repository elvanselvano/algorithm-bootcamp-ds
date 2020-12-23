#include <stdio.h> // i/o
#include <string.h> // strcpy
#include <stdlib.h> // dynamic memory allocation

struct Course {
  char ID[10];
  int score;
};

struct Student {
  char name[255];
  double GPA;
  Course c;
};

// createStudent return pointer that points to the newly created Student
Student *createStudent(const char *name, int age, double GPA, const char *ID, int score) {
  // allocate memory with size of Student, cast void* to Student*
  Student *newStudent = (Student*)malloc(sizeof(Student));
  strcpy(newStudent->name, name); // strcpy untuk string
  newStudent->GPA = GPA; // (*newStudent).GPA = GPA;
  strcpy(newStudent->c.ID, ID); // strcpy((*newStudent).c.ID, ID)
  newStudent->c.score = score; // (*newStudent).c.score = score;
  return newStudent;
}

void displayStudent(Student *s) {
  printf("Name: %s\n", s->name);
  printf("GPA: %lf\n", s->GPA);
  printf("Course ID: %s\n", s->c.ID);
  printf("Score: %d\n", s->c.score);
}

void removeStudent(Student *s) {
  free(s); // free allocated memory from malloc
  s = NULL; // protect against dangling pointer
}

int main() {
  Student *s = createStudent("Mang Oleh", 23, 3.90, "COMP6048", 95);
  displayStudent(s);
  removeStudent(s);

  // might still show some data due to undefined behavior (accessing illegal memory)
  // displayStudent(s);

  return 0;
}