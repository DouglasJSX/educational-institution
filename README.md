# Sistema de Gerenciamento de Turmas e Grupos

### Descrição:
Este projeto implementa um sistema para gerenciar turmas, alunos e grupos em uma instituição de ensino superior. O sistema permite que professores organizem seus alunos em grupos de trabalho, mantendo um controle eficiente das relações entre turmas, alunos e grupos.

### Estrutura de Dados
O sistema utiliza listas encadeadas para implementar as seguintes estruturas:

<ul>
  <li>Lista de turmas</li>
  <li>Lista de alunos por turma</li>
  <li>Lista de grupos por turma</li>
</ul>

Cada estrutura foi implementada manualmente sem o uso de funções ou classes prontas de listas encadeadas disponíveis na linguagem.

### Funcionalidades
O sistema oferece as seguintes operações:

<ol>
    <li>
      <strong>Gerenciamento de Turmas</strong>
    <ul>
      <li>Incluir nova turma</li>
      <li>Remover turma (com todos seus alunos e grupos)</li>
      <li>Consultar turmas existentes</li>
    </ul>
    </li>
    <li>
    <strong>Gerenciamento de Alunos</strong>
    <ul>
    <li>Incluir aluno em uma turma</li>
    <li>Remover aluno de uma turma</li>
    <li>Consultar alunos de uma turma</li>
    <li>Listar alunos sem grupo em uma turma</li>
    <li>Listar alunos presentes em mais de uma turma</li>
    <li>Listar alunos presentes em apenas uma turma</li>
  </ul>
  </li>
    <li>
    <strong>Gerenciamento de Grupos</strong>
    <ul>
    <li>Incluir aluno em um grupo</li>
    <li>Remover aluno de um grupo</li>
    <li>Consultar grupos e seus integrantes</li>
    <li>Divisão automática de alunos em grupos por tamanho definido</li>
  </ul>
  </li>
</ol>

### Regras de Negócio

<ul>
  <li>
    Cada aluno só pode pertencer a um grupo dentro da mesma turma
  </li>
  <li>
    Um aluno pode estar em múltiplas turmas (e consequentemente em grupos diferentes de turmas diferentes)
  </li>
  <li>
    Somente alunos matriculados em uma turma podem ser adicionados aos grupos daquela turma
  </li>
</ul>

### Como Executar

<ol>
  <li>Clone o repositório:<br />
    
    git clone https://github.com/DouglasJSX/educational-institution.git
    
  </li>
  <li>Navegue até o diretório do projeto:<br />
    
    cd educational-institution
    
  </li>
  <li>Navegue até o diretório do projeto:<br />
    
    cd educational-institution
    
  </li>
  <li>Compile e execute o programa:<br />
    
    F6
    
  </li>
</ol>

### Interface
O sistema utiliza uma interface textual simples com um menu de opções numeradas para acessar cada funcionalidade.

### Tecnologias Utilizadas

<ul>
  <li>
    C
  </li>
  <li>
    Implementação manual de listas encadeadas
  </li>
  <li>
    Manipulação explícita de ponteiros e referências entre nodos
  </li>
</ul>
