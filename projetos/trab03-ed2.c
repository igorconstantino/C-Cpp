#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORDEM 5
#define MAX_CHARS_NOME 30
#define MAX_CHARS_CURSO 30
#define RRN_NULL -1
#define DELIMITER "#"
#define DATA_FILENAME "turma.dat"
#define INDEX_FILENAME "ibtree.idx"
#define REG_SIZE 128

typedef struct {
  char nome[MAX_CHARS_NOME];
  char curso[MAX_CHARS_CURSO];
  int RA_UNESP;
} Aluno;

typedef struct {
  int RA;
  int RRN;
} Chave;

typedef struct {
  int num_chaves;
  Chave chaves[ORDEM-1];
  int descendentes[ORDEM];
  int folha;
} Pagina;

// Função para ler um aluno do teclado
Aluno ler_aluno() {
  Aluno aluno;
  printf("Nome: ");
  scanf("%s", aluno.nome);
  printf("Curso: ");
  scanf("%s", aluno.curso);
  printf("RA da UNESP: ");
  scanf("%d", &aluno.RA_UNESP);
  return aluno;
}

void inserir_aluno(Aluno aluno) {
  // Abre o arquivo de dados em modo de append
  FILE* data_file = fopen(DATA_FILENAME, "a");
  // Calcula o RRN do novo aluno como o tamanho atual do arquivo de dados
  int RRN = ftell(data_file);
  // Escreve o aluno no final do arquivo
  fwrite(&aluno, sizeof(Aluno), 1, data_file);
  // Preenche o espaço restante do registro com o caractere '#'
  int i;
  for (i = 0; i < REG_SIZE - sizeof(Aluno); i++) {
    fputc('#', data_file);
  }
  fclose(data_file);
}

int inserir_chave_pagina(int RA, int RRN, int RRN_pagina, FILE* index_file) {
  // Lê a página do arquivo de índice
  Pagina pagina;
  fseek(index_file, RRN_pagina, SEEK_SET);
  fread(&pagina, sizeof(Pagina), 1, index_file);
  // Verifica se a página é uma folha
  if (pagina.folha) {
    // Insere a chave na página folha
    int i = ORDEM - 2;
    while (i >= 0 && RA < pagina.chaves[i].RA) {
      pagina.chaves[i + 1] = pagina.chaves[i];
      pagina.descendentes[i + 1] = pagina.descendentes[i];
      i--;
    }
    pagina.chaves[i + 1].RA = RA;
    pagina.chaves[i + 1].RRN = RRN;
    pagina.num_chaves++;
    // Escreve a página atualizada no arquivo de índice
    fseek(index_file, RRN_pagina, SEEK_SET);
    fwrite(&pagina, sizeof(Pagina), 1, index_file);
    // Retorna o RRN da página
    return RRN_pagina;
  } else {
    // Encontra o descendente apropriado
    int i = ORDEM - 2;
    while (i >= 0 && RA < pagina.chaves[i].RA) {
      i--;
    }
    i++;
    // Insere a chave no descendente
    int novo_RRN = inserir_chave_pagina(RA, RRN, pagina.descendentes[i], index_file);
  }
}



void inserir_chave(int RA, int RRN) {
  // Abre o arquivo de índice em modo de leitura e escrita
  FILE* index_file = fopen(INDEX_FILENAME, "r+");
  // Lê o RRN da página raiz do cabeçalho do arquivo
  int raiz;
  fread(&raiz, sizeof(int), 1, index_file);
  // Insere a chave na árvore a partir da página raiz
  int nova_raiz = inserir_chave_pagina(RA, RRN, raiz, index_file);
  // Verifica se a página raiz foi dividida
  if (nova_raiz != raiz) {
    // Escreve a nova raiz no cabeçalho do arquivo de índice
    fseek(index_file, 0, SEEK_SET);
    fwrite(&nova_raiz, sizeof(int), 1, index_file);
  }
  fclose(index_file);
}

// Função recursiva para buscar uma chave em uma página da árvore-B
Aluno buscar_chave(int RA, int rrn_pagina, FILE* index_file) {
  // Lê a página do arquivo
  Pagina pagina;
  fseek(index_file, rrn_pagina, SEEK_SET);
  fread(&pagina, sizeof(Pagina), 1, index_file);
  // Procura a chave na página
  int i;
  for (i = 0; i < pagina.num_chaves; i++) {
    if (pagina.chaves[i].RA == RA) {
      // Se achou a chave, lê o aluno do arquivo de dados
      Aluno aluno;
      FILE* data_file = fopen(DATA_FILENAME, "r");
      fseek(data_file, pagina.chaves[i].RRN, SEEK_SET);
      fread(&aluno, sizeof(Aluno), 1, data_file);
      fclose(data_file);
      return aluno;
    } else if (RA < pagina.chaves[i].RA) {
      // Se a chave é menor, busca na página descendente à esquerda
      break;
    }
  }
  // Se a chave não foi encontrada e não há mais descendentes, retorna aluno vazio
  if (pagina.descendentes[i] == RRN_NULL) {
    Aluno aluno_vazio;
    return aluno_vazio;
  }
  // Senão, busca recursivemente na página descendente
  return buscar_chave(RA, pagina.descendentes[i], index_file);
}

// Função para buscar um aluno pelo RA
Aluno buscar_aluno(int RA) {
  // Abre o arquivo de índice
  FILE* index_file = fopen(INDEX_FILENAME, "r");
  // Lê o RRN da página raiz do cabeçalho do arquivo
  int rrn_raiz;
  fread(&rrn_raiz, sizeof(int), 1, index_file);
  // Se a árvore estiver vazia, retorna aluno vazio
  if (rrn_raiz == RRN_NULL) {
    Aluno aluno_vazio;
    return aluno_vazio;
  }
  // Senão, busca a chave recursivamente na árvore
  return buscar_chave(RA, rrn_raiz, index_file);
}

// Função para excluir um aluno pelo RA
void excluir_aluno(int RA) {
  // Abre o arquivo de índice
  FILE* index_file = fopen(INDEX_FILENAME, "r+");
  // Lê o RRN da página raiz do cabeçalho do arquivo
  int rrn_raiz;
  fread(&rrn_raiz, sizeof(int), 1, index_file);
  // Se a árvore não estiver vazia, exclui a chave recursivamente
  if (rrn_raiz != RRN_NULL) {
    rrn_raiz = excluir_chave(RA, rrn_raiz, index_file);
  }
  // Atualiza o RRN da página raiz no cabeçalho do arquivo
  fseek(index_file, 0, SEEK_SET);
  fwrite(&rrn_raiz, sizeof(int), 1, index_file);
  fclose(index_file);
}

// Função recursiva para excluir uma chave de uma página da árvore-B
int excluir_chave(int RA, int rrn_pagina, FILE* index_file) {
  // Lê a página do arquivo
  Pagina pagina;
  fseek(index_file, rrn_pagina, SEEK_SET);
  fread(&pagina, sizeof(Pagina), 1, index_file);
  // Procura a chave na página
  int i;
  for (i = 0; i < pagina.num_chaves; i++) {
    if (pagina.chaves[i].RA == RA) {
      // Se achou a chave, remove-a da página e retorna o RRN da página alterada
      pagina.num_chaves--;
      for (; i < pagina.num_chaves; i++) {
        pagina.chaves[i] = pagina.chaves[i+1];
      }
      fseek(index_file, rrn_pagina, SEEK_SET);
      fwrite(&pagina, sizeof(Pagina), 1, index_file);
      return rrn_pagina;
    } else if (RA < pagina.chaves[i].RA) {
      // Se a chave é menor, exclui recursivamente da página descendente à esquerda
      break;
    }
  }
  // Se a chave não foi encontrada e não há mais descendentes, retorna RRN nulo
  if (pagina.descendentes[i] == RRN_NULL) {
    return RRN_NULL;
  }
  // Senão, exclui recursivamente da página descendente
  int rrn_filho = excluir_chave(RA, pagina.descendentes[i], index_file);
  // Se o filho não foi alterado, retorna o RRN da página atual
  if (rrn_filho == pagina.descendentes[i]) {
    return rrn_pagina;
  }
  // Senão, atualiza o RRN do filho na página atual e retorna o RRN alterado
  pagina.descendentes[i] = rrn_filho;
  fseek(index_file, rrn_pagina, SEEK_SET);
  fwrite(&pagina, sizeof(Pagina), 1, index_file);
  return rrn_pagina;
}

int main() {
  int opcao;
  do {
    printf("\nMenu:\n");
    printf("1. Inserir aluno\n");
    printf("2. Buscar aluno\n");
    printf("3. Excluir aluno\n");
    printf("0. Sair\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    switch (opcao) {
      case 1: {
        Aluno aluno = ler_aluno();
        inserir_aluno(aluno);
        inserir_chave(aluno.RA_UNESP, ftell(DATA_FILENAME));
        break;
      }
      case 2: {
        int RA;
        printf("RA da UNESP: ");
        scanf("%d", &RA);
        Aluno aluno = buscar_aluno(RA);
        if (aluno.RA_UNESP == 0) {
          printf("Aluno não encontrado\n");
        } else {
          printf("Nome: %s\n", aluno.nome);
          printf("Curso: %s\n", aluno.curso);
          printf("RA da UNESP: %d\n", aluno.RA_UNESP);
        }
        break;
      }
      case 3: {
        int RA;
        printf("RA da UNESP: ");
        scanf("%d", &RA);
        excluir_aluno(RA);
        break;
      }
    }
  } while (opcao != 0);
  return 0;
}