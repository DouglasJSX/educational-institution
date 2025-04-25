#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct student {
  char name[20];
  int code;
  struct student *next, *prev;
};

typedef struct student Student;

struct group {
  int classCode;
  int groupValue;
  Student *startStudent;
  struct group *next, *prev;
};

typedef struct group Group;

struct class {
  int code;
  Group *startGroup;
  Student *startStudent;
  struct class *next, *prev;
};

typedef struct class Class;

Class *startClass;
Group *startGroup;
Student *startStudent;

void insertOrderedClass(int code) {
  Class *new, *aux = startClass;

  new = (Class*) malloc(sizeof(Class));

  new -> code = code;
  new -> startGroup = NULL;
  new -> startStudent = NULL;
  new -> next = NULL;
  new -> prev = NULL;

  if (startClass == NULL) {
    startClass = new;
  } else {
    while (aux -> next != NULL && aux -> code < code) {
      aux = aux -> next;
    }
    if (aux == startClass && aux -> code < code) {
      new -> prev = aux;
      aux -> next = new;
    } else if (aux == startClass && aux -> code > code) {
      new -> next = aux;
        aux -> prev = new;
        startClass = new;
    } else if (aux -> next == NULL && aux -> code < code) {
      new -> prev = aux;
      aux -> next = new;
    } else {
      new -> prev = aux -> prev;
      new -> next = aux;
      (aux -> prev) -> next = new;
      aux -> prev = new;
    } 
  }
}

void writeOrderedClass() {
  Class *aux = startClass;

  if (startClass == NULL) {
    printf("Nenhuma turma cadastrada\n");
    return;
  }

  while (aux != NULL) {
    printf("%d\n", aux -> code);
    aux = aux -> next;
  }
}

int main(){
  startClass = NULL;
  startGroup = NULL;
  startStudent = NULL;

  insertOrderedClass(204);
  insertOrderedClass(305);
  insertOrderedClass(238);
  insertOrderedClass(128);
  insertOrderedClass(402);
  writeOrderedClass();

  return 0;
}