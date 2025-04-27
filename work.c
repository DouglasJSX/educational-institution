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
    // Salvar os ponteiros next e prev originais do aluno
    Student *nextOriginal = auxStudent->next;
    Student *prevOriginal = auxStudent->prev;
    
    // Procurar o último aluno do grupo
    Student *lastStudent = auxGroup->startStudent;
    while (lastStudent->next != NULL) {
      lastStudent = lastStudent->next;
    }
    
    // Reestabelecer os ponteiros originais do aluno
    auxStudent->next = nextOriginal;
    auxStudent->prev = prevOriginal;
  }
}

void removeStudent(int studentCode, int classCode) {
  Class *currentClass = startClass;
  
  // Encontrar a turma do aluno
  while (currentClass != NULL) {
    if (currentClass->code == classCode) {
      break;
    }
    currentClass = currentClass->next;
  }
  
  if (currentClass == NULL) {
    printf("Turma não encontrada\n");
    return;
  }
  
  Student *currentStudent = currentClass->startStudent;
  Student *previousStudent = NULL;
  
  // Buscar o aluno na lista de alunos da turma
  while (currentStudent != NULL) {
    if (currentStudent->code == studentCode) {
      // Remover das listas duplamente encadeadas
      if (previousStudent != NULL) {
        previousStudent->next = currentStudent->next;
      } else {
        currentClass->startStudent = currentStudent->next;
      }
      
      if (currentStudent->next != NULL) {
        currentStudent->next->prev = previousStudent;
      }
      
      // Se o aluno está em um grupo, atualizar o contador do grupo
      if (currentStudent->groupValue > 0) {
        Group *group = currentClass->startGroup;
        while (group != NULL) {
          if (group->groupValue == currentStudent->groupValue) {
            group->qtdStudents--;
            
            // Se este aluno era o primeiro do grupo, atualizar o ponteiro
            if (group->startStudent == currentStudent) {
              group->startStudent = currentStudent->next;
            }
            break;
          }
          group = group->next;
        }
      }
      
      // Atualizar contadores
      currentClass->qtdStudents--;
      header.qtdStudents--;
      
      // Liberar memória
      free(currentStudent);
      return;
    }
    
    previousStudent = currentStudent;
    currentStudent = currentStudent->next;
  }
  
  printf("Aluno não encontrado\n");
}

void removeGroup(Group *groupToRemove, Class *parentClass) {
  if (groupToRemove == NULL || parentClass == NULL) {
    return;
  }
  
  // Remover todos os alunos do grupo (modificar apenas o campo groupValue)
  Student *currentStudent = parentClass->startStudent;
  while (currentStudent != NULL) {
    if (currentStudent->groupValue == groupToRemove->groupValue) {
      currentStudent->groupValue = 0; // Aluno não pertence mais a nenhum grupo
    }
    currentStudent = currentStudent->next;
  }
  
  // Remover o grupo da lista
  Group *previousGroup = NULL;
  Group *currentGroup = parentClass->startGroup;
  
  while (currentGroup != NULL) {
    if (currentGroup == groupToRemove) {
      if (previousGroup == NULL) {
        parentClass->startGroup = currentGroup->next;
      } else {
        previousGroup->next = currentGroup->next;
      }
      
      if (currentGroup->next != NULL) {
        currentGroup->next->prev = previousGroup;
      }
      
      // Atualizar contadores
      parentClass->qtdGroups--;
      header.qtdGroups--;
      
      // Liberar memória
      free(groupToRemove);
      return;
    }
    
    previousGroup = currentGroup;
    currentGroup = currentGroup->next;
  }
}

void removeClassAndDescendants(int classCode) {
  Class *currentClass = startClass;
  Class *previousClass = NULL;
  
  while (currentClass != NULL) {
    if (currentClass->code == classCode) {
      // Remover todos os grupos da turma
      Group *currentGroup = currentClass->startGroup;
      while (currentGroup != NULL) {
        Group *nextGroup = currentGroup->next;
        removeGroup(currentGroup, currentClass);
        currentGroup = nextGroup;
      }
      
      // Remover todos os alunos da turma
      Student *currentStudent = currentClass->startStudent;
      while (currentStudent != NULL) {
        Student *nextStudent = currentStudent->next;
        // Não precisamos chamar removeStudent aqui para evitar modificações na lista durante a iteração
        free(currentStudent);
        header.qtdStudents--;
        currentStudent = nextStudent;
      }
      
      // Remover a turma da lista
      if (previousClass == NULL) {
        startClass = currentClass->next;
      } else {
        previousClass->next = currentClass->next;
      }
      
      if (currentClass->next != NULL) {
        currentClass->next->prev = previousClass;
      }
      
      // Atualizar contador
      header.qtdClasses--;
      
      // Liberar memória
      free(currentClass);
      return;
    }
    
    previousClass = currentClass;
    currentClass = currentClass->next;
  }
  
  printf("Turma não encontrada\n");
}

// SOMENTE PARA TESTE DAS INCLUSÕES
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
      printf("Alunos: Nobody\n");
    } else {
      printf("Alunos: \n");
      Student *auxStudent = auxClass->startStudent;
      while (auxStudent != NULL) {
        printf("Cod.%d - %s\n", auxStudent->code, auxStudent->name);
        auxStudent = auxStudent->next;
      }
    }
    
    // Listar grupos e seus alunos
    if (auxClass->startGroup == NULL) {
      printf("Grupo: Nobody\n");
    } else {
      printf("Grupo(s): \n");
      Group *auxGroup = auxClass->startGroup;
      
      while (auxGroup != NULL) {
        printf("Gropo: %d\n", auxGroup->groupValue);
        
        if (auxGroup->startStudent == NULL) {
          printf("  Alunos: Nobody\n");
        } else {
          printf("  Alunos: \n");
          Student *auxStudent = auxClass->startStudent;
          while (auxStudent != NULL) {
            if (auxStudent->groupValue == auxGroup->groupValue) {
              printf("    Cod.%d - %s\n", auxStudent->code, auxStudent->name);
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

void consultClass(){
  Class *aux = startClass;
  int count = 0;

  if (startClass == NULL) {
    printf("\nNenhuma turma cadastrada\n");
    return;
  }

  printf("\n\nTurmas cadastradas:\n");

  while (aux != NULL) {
    printf("Turma %d: %d\n", ++count, aux->code);
    aux = aux->next;
  }
}

void consultStudents(int classCode){
  Class *auxClass = startClass;
  int found = 0;

  while (auxClass != NULL) {
    if (auxClass->code == classCode) {
      found = 1;
      break;
    }
    auxClass = auxClass->next;
  }

  if (found == 0) {
    printf("\nTurma nao encontrada\n");
    return;
  }

  if (auxClass->startStudent == NULL) {
    printf("\nNenhum aluno cadastrado\n");
    return;
  }

  printf("\n\nAlunos da turma %d:\n", auxClass->code);

  Student *aux = auxClass->startStudent;
  int count = 0;

  while (aux != NULL) {
    printf("Aluno %d: %s\n", ++count, aux->name);
    aux = aux->next;
  }
}

void consultStudentsPerGroup(int classCode){
  Class *auxClass = startClass;
  int found = 0;

  while (auxClass != NULL) {
    if (auxClass->code == classCode) {
      found = 1;
      break;
    }
    auxClass = auxClass->next;
  }

  if (found == 0) {
    printf("\nTurma nao encontrada\n");
    return;
  }

  if (auxClass->startGroup == NULL) {
    printf("\nNenhum grupo cadastrado\n");
    return;
  }

  printf("\n\nGrupos da turma %d:\n", auxClass->code);

  Group *auxGroup = auxClass->startGroup;
      
  while (auxGroup != NULL) {
    printf("Gropo: %d\n", auxGroup->groupValue);
    
    if (auxGroup->startStudent == NULL) {
      printf("  Alunos: Nobody\n");
    } else {
      printf("  Alunos: \n");
      Student *auxStudent = auxClass->startStudent;
      while (auxStudent != NULL) {
        if (auxStudent->groupValue == auxGroup->groupValue) {
          printf("    Cod.%d - %s\n", auxStudent->code, auxStudent->name);
        }
        auxStudent = auxStudent->next;
      }
    }
    auxGroup = auxGroup->next;
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
  insertOrderedStudent("Matheus", 1, 204);
  insertOrderedStudent("Ana", 2, 204);
  insertOrderedStudent("Douglas", 3, 204);
  insertOrderedStudent("Giovanna", 4, 204);
  insertOrderedStudent("Cleusas", 5, 204);
  insertStudentToGroup(1, 204, 128);
  insertStudentToGroup(2, 204, 128);
  insertStudentToGroup(4, 204, 125);
  insertOrderedClass(308);
  insertOrderedClass(238);
  insertOrderedClass(128);
  // write();
  // consultClass();
  consultStudentsPerGroup(204);

  return 0;
}