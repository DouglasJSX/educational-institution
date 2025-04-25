Sistema de Gerenciamento de Turmas e Grupos
Descrição
Este projeto implementa um sistema para gerenciar turmas, alunos e grupos em uma instituição de ensino superior. O sistema permite que professores organizem seus alunos em grupos de trabalho, mantendo um controle eficiente das relações entre turmas, alunos e grupos.
Estrutura de Dados
O sistema utiliza listas encadeadas para implementar as seguintes estruturas:

Lista de turmas
Lista de alunos por turma
Lista de grupos por turma

Cada estrutura foi implementada manualmente sem o uso de funções ou classes prontas de listas encadeadas disponíveis na linguagem.
Funcionalidades
O sistema oferece as seguintes operações:

Gerenciamento de Turmas

Incluir nova turma
Remover turma (com todos seus alunos e grupos)
Consultar turmas existentes


Gerenciamento de Alunos

Incluir aluno em uma turma
Remover aluno de uma turma
Consultar alunos de uma turma
Listar alunos sem grupo em uma turma
Listar alunos presentes em mais de uma turma
Listar alunos presentes em apenas uma turma


Gerenciamento de Grupos

Incluir aluno em um grupo
Remover aluno de um grupo
Consultar grupos e seus integrantes
Divisão automática de alunos em grupos por tamanho definido



Regras de Negócio

Cada aluno só pode pertencer a um grupo dentro da mesma turma
Um aluno pode estar em múltiplas turmas (e consequentemente em grupos diferentes de turmas diferentes)
Somente alunos matriculados em uma turma podem ser adicionados aos grupos daquela turma

Como Executar

Clone o repositório:

git clone https://github.com/seu-usuario/sistema-gerenciamento-turmas.git

Navegue até o diretório do projeto:

cd sistema-gerenciamento-turmas

Compile e execute o programa (exemplo para C/C++):

gcc main.c -o sistema
./sistema
Interface
O sistema utiliza uma interface textual simples com um menu de opções numeradas para acessar cada funcionalidade.
Tecnologias Utilizadas

C
Implementação manual de listas encadeadas
Manipulação explícita de ponteiros e referências entre nodos
