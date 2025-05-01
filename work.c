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

struct studentInfo {
  int code;
  char name[100];
  int count;
  char classNames[10][100]; // até 10 turmas por aluno
  struct studentInfo *next;
};
typedef struct studentInfo StudentInfo;

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

void removeStudentFromClass(int classCode, int studentCode) {
  Class *currentClass = startClass;

  // Procurar a turma pelo código
  while (currentClass != NULL && currentClass->code != classCode) {
    currentClass = currentClass->next;
  }

  if (currentClass == NULL) {
    printf("Turma com código %d não encontrada.\n", classCode);
    return;
  }

  // Remover o aluno da lista de alunos da turma
  Student *prevStudent = NULL;
  Student *currStudent = currentClass->startStudent;

  while (currStudent != NULL && currStudent->code != studentCode) {
    prevStudent = currStudent;
    currStudent = currStudent->next;
  }

  if (currStudent == NULL) {
    printf("Aluno com código %d não encontrado na turma %d.\n", studentCode, classCode);
    return;
  }

  // Remove o aluno da lista
  if (prevStudent == NULL) {
    currentClass->startStudent = currStudent->next;
  } else {
    prevStudent->next = currStudent->next;
  }

  // Atualiza contadores
  currentClass->qtdStudents--;
  header.qtdStudents--;

  // Remover o aluno de todos os grupos da turma
  Group *group = currentClass->startGroup;
  while (group != NULL) {
    Student *prevInGroup = NULL;
    Student *currInGroup = group->startStudent;

    while (currInGroup != NULL) {
      if (currInGroup->code == studentCode) {
        if (prevInGroup == NULL) {
          group->startStudent = currInGroup->next;
        } else {
          prevInGroup->next = currInGroup->next;
        }
        free(currInGroup);
        group->qtdStudents--;
        break; // O aluno não pode estar mais de uma vez no mesmo grupo
      }
      prevInGroup = currInGroup;
      currInGroup = currInGroup->next;
    }

    group = group->next;
  }

  // Por fim, libera a memória do aluno da turma
  free(currStudent);

  printf("Aluno %d removido da turma %d e de qualquer grupo associado.\n", studentCode, classCode);
}


void removeStudentFromGroup(int classCode, int groupValue, int studentCode) {
  Class *currentClass = startClass;

  // Procurar a turma pelo código
  while (currentClass != NULL && currentClass->code != classCode) {
      currentClass = currentClass->next;
  }

  if (currentClass == NULL) {
      printf("Turma com código %d não encontrada.\n", classCode);
      return;
  }

  // Procurar o grupo pelo valor do grupo (groupValue)
  Group *currentGroup = currentClass->startGroup;
  while (currentGroup != NULL && currentGroup->groupValue != groupValue) {
      currentGroup = currentGroup->next;
  }

  if (currentGroup == NULL) {
      printf("Grupo com valor %d não encontrado na turma %d.\n", groupValue, classCode);
      return;
  }

  // Procurar o aluno no grupo
  Student *prevStudent = NULL;
  Student *currStudent = currentGroup->startStudent;

  while (currStudent != NULL && currStudent->code != studentCode) {
      prevStudent = currStudent;
      currStudent = currStudent->next;
  }

  if (currStudent == NULL) {
      printf("Aluno com código %d não está no grupo %d da turma %d.\n", studentCode, groupValue, classCode);
      return;
  }

  // Remover o aluno do grupo
  if (prevStudent == NULL) {
      currentGroup->startStudent = currStudent->next;
  } else {
      prevStudent->next = currStudent->next;
  }

  free(currStudent);
  currentGroup->qtdStudents--;

  printf("Aluno %d removido do grupo %d da turma %d.\n", studentCode, groupValue, classCode);
}

void listStudentsWithoutGroup(int classCode) {
  Class *currentClass = startClass;

  // Procurar a turma pelo código
  while (currentClass != NULL && currentClass->code != classCode) {
      currentClass = currentClass->next;
  }

  if (currentClass == NULL) {
      printf("Turma com código %d não encontrada.\n", classCode);
      return;
  }

  Student *student = currentClass->startStudent;
  int found = 0;

  while (student != NULL) {
      int inGroup = 0;

      // Verificar se o aluno está em algum grupo da turma
      Group *group = currentClass->startGroup;
      while (group != NULL) {
          Student *groupStudent = group->startStudent;
          while (groupStudent != NULL) {
              if (groupStudent->code == student->code) {
                  inGroup = 1;
                  break;
              }
              groupStudent = groupStudent->next;
          }
          if (inGroup) break;
          group = group->next;
      }

      if (!inGroup) {
          printf("Aluno sem grupo: %s (código %d)\n", student->name, student->code);
          found = 1;
      }

      student = student->next;
  }

  if (!found) {
      printf("Todos os alunos da turma %d estão em grupos.\n", classCode);
  }
}

void listStudentsInMultipleClasses() {
  StudentInfo *studentList = NULL;
  Class *currentClass = startClass;
  int foundAny = 0;

  // Primeiro passagem: coletar informações de todos os alunos
  while (currentClass != NULL) {
      Student *currentStudent = currentClass->startStudent;
      
      while (currentStudent != NULL) {
          // Verificar se o aluno já está na nossa lista de informações
          StudentInfo *info = studentList;
          StudentInfo *prevInfo = NULL;
          
          while (info != NULL && info->code != currentStudent->code) {
              prevInfo = info;
              info = info->next;
          }
          
          if (info == NULL) {
              // Aluno não encontrado na lista, adicionar novo
              info = (StudentInfo*) malloc(sizeof(StudentInfo));
              info->code = currentStudent->code;
              strcpy(info->name, currentStudent->name);
              info->count = 1;
              strcpy(info->classNames[0], ""); // Inicializa o primeiro elemento
              sprintf(info->classNames[0], "Turma %d", currentClass->code);
              info->next = studentList;
              studentList = info;
          } else {
              // Aluno já existe na lista, incrementar contador
              info->count++;
              if (info->count <= 10) { // Só armazena até 10 turmas
                  sprintf(info->classNames[info->count-1], "Turma %d", currentClass->code);
              }
          }
          
          currentStudent = currentStudent->next;
      }
      
      currentClass = currentClass->next;
  }

  // Segunda passagem: imprimir alunos em mais de uma turma
  printf("\nAlunos em mais de uma turma:\n");
  printf("----------------------------\n");
  
  StudentInfo *info = studentList;
  while (info != NULL) {
      if (info->count > 1) {
          foundAny = 1;
          printf("Aluno: %s (Código: %d)\n", info->name, info->code);
          printf("Quantidade de turmas: %d\n", info->count);
          printf("Turmas: ");
          
          int maxClassesToShow = info->count > 10 ? 10 : info->count;
          for (int i = 0; i < maxClassesToShow; i++) {
              printf("%s", info->classNames[i]);
              if (i < maxClassesToShow - 1) printf(", ");
          }
          
          if (info->count > 10) {
              printf(" e mais %d turmas", info->count - 10);
          }
          
          printf("\n----------------------------\n");
      }
      
      StudentInfo *temp = info;
      info = info->next;
      free(temp); // Liberar memória da lista temporária
  }

  if (!foundAny) {
      printf("Nenhum aluno está em mais de uma turma.\n");
  }
}

void listStudentsInSingleClass() {
  StudentInfo *studentList = NULL;
  Class *currentClass = startClass;
  int foundAny = 0;

  // Primeira passagem: coletar informações de todos os alunos
  while (currentClass != NULL) {
      Student *currentStudent = currentClass->startStudent;
      
      while (currentStudent != NULL) {
          // Verificar se o aluno já está na nossa lista de informações
          StudentInfo *info = studentList;
          StudentInfo *prevInfo = NULL;
          
          while (info != NULL && info->code != currentStudent->code) {
              prevInfo = info;
              info = info->next;
          }
          
          if (info == NULL) {
              // Aluno não encontrado na lista, adicionar novo
              info = (StudentInfo*) malloc(sizeof(StudentInfo));
              info->code = currentStudent->code;
              strcpy(info->name, currentStudent->name);
              info->count = 1;
              strcpy(info->classNames[0], ""); // Inicializa o primeiro elemento
              sprintf(info->classNames[0], "Turma %d", currentClass->code);
              info->next = studentList;
              studentList = info;
          } else {
              // Aluno já existe na lista, incrementar contador
              info->count++;
              if (info->count <= 10) { // Só armazena até 10 turmas
                  sprintf(info->classNames[info->count-1], "Turma %d", currentClass->code);
              }
          }
          
          currentStudent = currentStudent->next;
      }
      
      currentClass = currentClass->next;
  }

  // Segunda passagem: imprimir alunos em apenas uma turma
  printf("\nAlunos em apenas uma turma:\n");
  printf("----------------------------\n");
  
  StudentInfo *info = studentList;
  while (info != NULL) {
      if (info->count == 1) {
          foundAny = 1;
          printf("Aluno: %s (Código: %d)\n", info->name, info->code);
          printf("Turma: %s\n", info->classNames[0]);
          printf("----------------------------\n");
      }
      
      StudentInfo *temp = info;
      info = info->next;
      free(temp); // Liberar memória da lista temporária
  }

  if (!foundAny) {
      printf("Nenhum aluno está em apenas uma turma (ou não há alunos cadastrados).\n");
  }
}

void showMenu() {
  int option;
  char name[100];
  int code, classCode, groupValue;
  
  do {
      printf("\n\n=== MENU PRINCIPAL ===\n");
      printf("1) Incluir nova turma\n");
      printf("2) Remover turma\n");
      printf("3) Consultar turmas\n");
      printf("4) Incluir aluno na lista de alunos de uma turma\n");
      printf("5) Remover aluno da lista de alunos de uma turma\n");
      printf("6) Consultar alunos de uma turma\n");
      printf("7) Incluir aluno no grupo de uma turma\n");
      printf("8) Remover aluno do grupo de uma turma\n");
      printf("9) Consultar alunos dos grupos de uma turma\n");
      printf("10) Alunos sem grupo em uma turma\n");
      printf("11) Alunos em mais de uma turma\n");
      printf("12) Alunos em apenas uma turma\n");
      printf("0) Sair\n");
      printf("\nDigite sua opcao: ");
      scanf("%d", &option);
      
      switch(option) {
          case 1: // Incluir nova turma
              printf("\n=== INCLUIR NOVA TURMA ===\n");
              printf("Digite o codigo da turma: ");
              scanf("%d", &code);
              insertOrderedClass(code);
              break;
              
          case 2: // Remover turma
              printf("\n=== REMOVER TURMA ===\n");
              printf("Digite o codigo da turma a ser removida: ");
              scanf("%d", &code);
              removeClassAndDescendants(code);
              break;
              
          case 3: // Consultar turmas
              printf("\n=== TURMAS CADASTRADAS ===\n");
              consultClass();
              break;
              
          case 4: // Incluir aluno na turma
              printf("\n=== INCLUIR ALUNO NA TURMA ===\n");
              printf("Digite o nome do aluno: ");
              scanf(" %[^\n]s", name);
              printf("Digite o codigo do aluno: ");
              scanf("%d", &code);
              printf("Digite o codigo da turma: ");
              scanf("%d", &classCode);
              insertOrderedStudent(name, code, classCode);
              break;
              
          case 5: // Remover aluno da turma
              printf("\n=== REMOVER ALUNO DA TURMA ===\n");
              printf("Digite o codigo do aluno: ");
              scanf("%d", &code);
              printf("Digite o codigo da turma: ");
              scanf("%d", &classCode);
              removeStudentFromClass(classCode, code);
              break;
              
          case 6: // Consultar alunos da turma
              printf("\n=== CONSULTAR ALUNOS DA TURMA ===\n");
              printf("Digite o codigo da turma: ");
              scanf("%d", &classCode);
              consultStudents(classCode);
              break;
              
          case 7: // Incluir aluno no grupo
              printf("\n=== INCLUIR ALUNO NO GRUPO ===\n");
              printf("Digite o codigo do aluno: ");
              scanf("%d", &code);
              printf("Digite o codigo da turma: ");
              scanf("%d", &classCode);
              printf("Digite o valor do grupo: ");
              scanf("%d", &groupValue);
              insertStudentToGroup(code, classCode, groupValue);
              break;
              
          case 8: // Remover aluno do grupo
              printf("\n=== REMOVER ALUNO DO GRUPO ===\n");
              printf("Digite o codigo do aluno: ");
              scanf("%d", &code);
              printf("Digite o codigo da turma: ");
              scanf("%d", &classCode);
              printf("Digite o valor do grupo: ");
              scanf("%d", &groupValue);
              removeStudentFromGroup(classCode, groupValue, code);
              break;
              
          case 9: // Consultar alunos dos grupos
              printf("\n=== CONSULTAR GRUPOS DA TURMA ===\n");
              printf("Digite o codigo da turma: ");
              scanf("%d", &classCode);
              consultStudentsPerGroup(classCode);
              break;
              
          case 10: // Alunos sem grupo
              printf("\n=== ALUNOS SEM GRUPO ===\n");
              printf("Digite o codigo da turma: ");
              scanf("%d", &classCode);
              listStudentsWithoutGroup(classCode);
              break;
              
          case 11: // Alunos em mais de uma turma
              printf("\n=== ALUNOS EM MAIS DE UMA TURMA ===\n");
              listStudentsInMultipleClasses();
              break;
              
          case 12: // Alunos em apenas uma turma
              printf("\n=== ALUNOS EM APENAS UMA TURMA ===\n");
              listStudentsInSingleClass();
              break;
              
          case 0: // Sair
              printf("\nSaindo do sistema...\n");
              break;
              
          default:
              printf("\nOpcao invalida! Tente novamente.\n");
      }
      
      if (option != 0) {
          printf("\nPressione Enter para continuar...");
          getchar(); // Limpa o buffer
          getchar(); // Espera o Enter
      }
      
  } while (option != 0);
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

  showMenu();

  return 0;
}