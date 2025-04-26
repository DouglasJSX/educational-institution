#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct student {
  char name[20];
  int code, classCode, groupValue;
  struct student *next, *prev;
};

typedef struct student Student;

struct group {
  int classCode, groupValue, qtdStudents;
  Student *startStudent;
  struct group *next, *prev;
};

typedef struct group Group;

struct class {
  int code, qtdGroups, qtdStudents;
  Group *startGroup;
  Student *startStudent;
  struct class *next, *prev;
};

typedef struct class Class;

struct header {
  int qtdClasses, qtdGroups, qtdStudents;
} header;

Class *startClass;
Group *startGroup;
Student *startStudent;

void insertOrderedClass(int code) {
  Class *new, *aux = startClass, *ant = NULL;

  // Verificar se a turma já existe
  while (aux != NULL) {
    if (aux->code == code) {
      printf("Turma ja cadastrada\n");
      return;
    }
    aux = aux->next;
  }

  // Criar nova turma
  new = (Class*) malloc(sizeof(Class));
  new->code = code;
  new->startGroup = NULL;
  new->startStudent = NULL;
  new->qtdGroups = 0;
  new->qtdStudents = 0;
  new->next = NULL;
  new->prev = NULL;
  header.qtdClasses++;

  // Inserir de forma ordenada
  if (startClass == NULL) {
    // Lista vazia
    startClass = new;
  } else {
    // Reiniciar aux para inserção ordenada
    aux = startClass;
    
    // Verificar se deve inserir no início
    if (code < aux->code) {
      new->next = startClass;
      startClass->prev = new;
      startClass = new;
    } else {
      // Procurar posição de inserção
      while (aux != NULL && aux->code < code) {
        ant = aux;
        aux = aux->next;
      }
      
      // Inserir no meio ou fim
      new->next = aux;
      if (aux != NULL) {
        aux->prev = new;
      }
      new->prev = ant;
      ant->next = new;
    }
  }
}

void insertOrderedGroup(int classCode, int groupValue) {
  Class *auxClass = startClass;
  Group *new, *aux = NULL, *ant = NULL;
  int found = 0;

  // Procurar a turma
  while (auxClass != NULL) {
    if (auxClass->code == classCode) {
      found = 1;
      break;
    }
    auxClass = auxClass->next;
  }

  if (!found) {
    printf("Turma nao encontrada\n");
    return;
  }

  // Inicializar aux com o início da lista de grupos da turma
  aux = auxClass->startGroup;

  // Verificar se o grupo já existe
  while (aux != NULL) {
    if (aux->groupValue == groupValue) {
      printf("Grupo ja cadastrado\n");
      return;
    }
    aux = aux->next;
  }

  // Criar novo grupo
  new = (Group*) malloc(sizeof(Group));
  new->groupValue = groupValue;
  new->classCode = classCode;
  new->startStudent = NULL;
  new->qtdStudents = 0;
  new->next = NULL;
  new->prev = NULL;
  header.qtdGroups++;
  auxClass->qtdGroups++;

  // Inserir de forma ordenada na lista de grupos da turma
  if (auxClass->startGroup == NULL) {
    // Lista vazia
    auxClass->startGroup = new;
  } else {
    // Reiniciar aux para inserção ordenada
    aux = auxClass->startGroup;
    
    // Verificar se deve inserir no início
    if (groupValue < aux->groupValue) {
      new->next = auxClass->startGroup;
      auxClass->startGroup->prev = new;
      auxClass->startGroup = new;
    } else {
      // Procurar posição de inserção
      while (aux != NULL && aux->groupValue < groupValue) {
        ant = aux;
        aux = aux->next;
      }
      
      // Inserir no meio ou fim
      new->next = aux;
      if (aux != NULL) {
        aux->prev = new;
      }
      new->prev = ant;
      ant->next = new;
    }
  }
}

void insertOrderedStudent(char name[], int code, int classCode) {
  Class *auxClass = startClass;
  Student *new, *aux = NULL, *ant = NULL;
  int found = 0;

  // Procurar a turma
  while (auxClass != NULL) {
    if (auxClass->code == classCode) {
      found = 1;
      break;
    }
    auxClass = auxClass->next;
  }

  if (!found) {
    printf("Turma nao encontrada\n");
    return;
  }

  // Inicializar aux com o início da lista de alunos da turma
  aux = auxClass->startStudent;

  // Verificar se o aluno já existe
  while (aux != NULL) {
    if (aux->code == code) {
      printf("Aluno ja cadastrado\n");
      return;
    }
    aux = aux->next;
  }

  // Criar novo aluno
  new = (Student*) malloc(sizeof(Student));
  strcpy(new->name, name);
  new->code = code;
  new->classCode = classCode;
  new->groupValue = 0;
  new->next = NULL;
  new->prev = NULL;
  header.qtdStudents++;
  auxClass->qtdStudents++;

  // Inserir de forma ordenada na lista de alunos da turma
  if (auxClass->startStudent == NULL) {
    // Lista vazia
    auxClass->startStudent = new;
  } else {
    // Reiniciar aux para inserção ordenada
    aux = auxClass->startStudent;
    
    // Verificar se deve inserir no início
    if (strcmp(name, aux->name) < 0) {
      new->next = auxClass->startStudent;
      auxClass->startStudent->prev = new;
      auxClass->startStudent = new;
    } else {
      // Procurar posição de inserção
      while (aux != NULL && strcmp(aux->name, name) < 0) {
        ant = aux;
        aux = aux->next;
      }
      
      // Inserir no meio ou fim
      new->next = aux;
      if (aux != NULL) {
        aux->prev = new;
      }
      new->prev = ant;
      ant->next = new;
    }
  }
}

void insertStudentToGroup(int code, int classCode, int groupValue) {
  Class *auxClass = startClass;
  Group *auxGroup = NULL;
  Student *auxStudent = NULL;
  int foundClass = 0, foundStudent = 0, foundGroup = 0;

  // Procurar a turma
  while (auxClass != NULL) {
    if (auxClass->code == classCode) {
      foundClass = 1;
      break;
    }
    auxClass = auxClass->next;
  }

  if (!foundClass) {
    printf("Turma nao encontrada\n");
    return;
  }

  // Procurar o aluno na turma
  auxStudent = auxClass->startStudent;
  while (auxStudent != NULL) {
    if (auxStudent->code == code) {
      foundStudent = 1;
      break;
    }
    auxStudent = auxStudent->next;
  }

  if (!foundStudent) {
    printf("Aluno nao encontrado\n");
    return;
  }

  // Procurar o grupo na turma
  auxGroup = auxClass->startGroup;
  while (auxGroup != NULL) {
    if (auxGroup->groupValue == groupValue) {
      foundGroup = 1;
      break;
    }
    auxGroup = auxGroup->next;
  }

  // Se o grupo não existe, criar
  if (!foundGroup) {
    insertOrderedGroup(classCode, groupValue);
    // Buscar o grupo recém criado
    auxGroup = auxClass->startGroup;
    while (auxGroup != NULL) {
      if (auxGroup->groupValue == groupValue) {
        break;
      }
      auxGroup = auxGroup->next;
    }
  } else if (auxGroup->qtdStudents >= 2) {
    printf("Grupo cheio\n");
    return;
  }

  // Adicionar aluno ao grupo
  if (auxStudent->groupValue != 0) {
    printf("Aluno ja pertence a um grupo\n");
    return;
  }

  // Atualizar a informação do grupo no aluno
  auxStudent->groupValue = groupValue;
  
  // Atualizar contador de alunos no grupo
  auxGroup->qtdStudents++;
  
  // Se é o primeiro aluno no grupo
  if (auxGroup->startStudent == NULL) {
    auxGroup->startStudent = auxStudent;
  } else {
    // Procurar o último aluno do grupo
    Student *lastStudent = auxGroup->startStudent;
    while (lastStudent->next != NULL && lastStudent->groupValue == groupValue) {
      lastStudent = lastStudent->next;
    }
    // Adicionar o novo aluno ao final
    lastStudent->next = auxStudent;
    auxStudent->prev = lastStudent;
  }
}

void write() {
  Class *auxClass = startClass;

  if (startClass == NULL) {
    printf("Nenhuma turma cadastrada\n");
    return;
  }

  while (auxClass != NULL) {
    printf("\nTurma: %d\n", auxClass->code);
    
    // Listar alunos da turma
    if (auxClass->startStudent == NULL) {
      printf("Students: Nobody\n");
    } else {
      printf("Students: \n");
      Student *auxStudent = auxClass->startStudent;
      while (auxStudent != NULL) {
        printf("Cod.%d - %s\n", auxStudent->code, auxStudent->name);
        auxStudent = auxStudent->next;
      }
    }
    
    // Listar grupos e seus alunos
    if (auxClass->startGroup == NULL) {
      printf("Groups: Nobody\n");
    } else {
      printf("Groups: \n");
      Group *auxGroup = auxClass->startGroup;
      
      while (auxGroup != NULL) {
        printf("Group: %d\n", auxGroup->groupValue);
        
        if (auxGroup->startStudent == NULL) {
          printf("  Students: Nobody\n");
        } else {
          printf("  Students: \n");
          Student *auxStudent = auxClass->startStudent;
          while (auxStudent != NULL) {
            if (auxStudent->groupValue == auxGroup->groupValue) {
              printf("  Cod.%d - %s\n", auxStudent->code, auxStudent->name);
            }
            auxStudent = auxStudent->next;
          }
        }
        auxGroup = auxGroup->next;
      }
    }
    
    auxClass = auxClass->next;
  }
}

int main() {
  startClass = NULL;
  startGroup = NULL;
  startStudent = NULL;
  header.qtdClasses = 0;
  header.qtdGroups = 0;
  header.qtdStudents = 0;

  insertOrderedClass(204);
  insertOrderedClass(305);
  insertOrderedStudent("Matheus", 1, 204);
  insertOrderedStudent("Ana", 2, 204);
  insertStudentToGroup(1, 204, 1);
  write();

  return 0;
}