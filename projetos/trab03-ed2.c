#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tamanho fixo do registro do aluno
#define TAM_REG 128

#define TAM_PAGINA 5

// Ordem da arvore-B
#define ORDEM 5

// Estrutura para representar um registro do aluno
typedef struct
{
    char *nome;
    char *curso;
    int RA_UNESP;
} Aluno;

// Estrutura para representar uma chave do indice
typedef struct
{
    int RA_UNESP;
    int RRN;
} Chave;

// Estrutura para representar uma pagina da arvore-B
typedef struct
{
    int num_chaves;
    Chave chaves[ORDEM - 1];
    int filhos[ORDEM];
} Pagina;

int obter_RRN_nova_pagina() {
  // Abre o arquivo de indice em modo de leitura
  FILE *arq_indice = fopen("ibtree.idx", "rb");

  // Move o ponteiro para o final do arquivo
  fseek(arq_indice, 0, SEEK_END);

  // Calcula o tamanho do arquivo em bytes
  int tamanho_arq = ftell(arq_indice);

  // Calcula o RRN da nova pagina
  int RRN_nova_pagina = tamanho_arq / TAM_PAGINA;

  // Fecha o arquivo de indice
  fclose(arq_indice);

  return RRN_nova_pagina;
}


// Funcao para ler um aluno do arquivo de dados
Aluno *ler_aluno(int RRN)
{
    // Abre o arquivo de dados
    FILE *arq_dados = fopen("turma.dat", "rb");
    if (arq_dados == NULL)
    {
        printf("Erro ao abrir o arquivo de dados\n");
        return NULL;
    }

    // Posiciona o ponteiro de leitura no inicio do registro do aluno
    fseek(arq_dados, RRN * TAM_REG, SEEK_SET);

    // Aloca memoria para o aluno
    Aluno *aluno = (Aluno *)malloc(sizeof(Aluno));

    // Le os campos do aluno
    fread(aluno->nome, sizeof(char), 50, arq_dados);
    fread(aluno->curso, sizeof(char), 50, arq_dados);
    fread(&aluno->RA_UNESP, sizeof(int), 1, arq_dados);

    // Fecha o arquivo de dados
    fclose(arq_dados);

    return aluno;
}

// Funcao para escrever um aluno no arquivo de dados
void escrever_aluno(Aluno *aluno, int RRN)
{
    // Abre o arquivo de dados
    FILE *arq_dados = fopen("turma.dat", "rb+");
    if (arq_dados == NULL)
    {
        printf("Erro ao abrir o arquivo de dados\n");
        return;
    }

    // Posiciona o ponteiro de escrita no inicio do registro do aluno
    fseek(arq_dados, RRN * TAM_REG, SEEK_SET);

    // Escreve os campos do aluno
    fwrite(aluno->nome, sizeof(char), 50, arq_dados);
    fwrite(aluno->curso, sizeof(char), 50, arq_dados);
    // fwrite(&

    // Funcao para ler uma pagina da arvore-B do arquivo de indice
    Pagina *ler_pagina(int RRN){
        // Abre o arquivo de indice
        FILE *arq_indice = fopen("ibtree.idx", "rb");
        if (arq_indice == NULL)
        {
            printf("Erro ao abrir o arquivo de indice\n");
            return NULL;
        }

        // Posiciona o ponteiro de leitura no inicio da pagina
        fseek(arq_indice, RRN * (ORDEM - 1) * sizeof(Chave) + sizeof(int), SEEK_SET);

        // Aloca memoria para a pagina
        Pagina *pagina = (Pagina *)malloc(sizeof(Pagina));

        // Le o numero de chaves na pagina
        fread(&pagina->num_chaves, sizeof(int), 1, arq_indice);

        // Le as chaves da pagina
        fread(pagina->chaves, sizeof(Chave), ORDEM - 1, arq_indice);

        // Le os filhos da pagina
        fread(pagina->filhos, sizeof(int), ORDEM, arq_indice);

        // Fecha o arquivo de indice
        fclose(arq_indice);

        return pagina;
    }

    // Funcao para escrever uma pagina da arvore-B no arquivo de indice
    void escrever_pagina(Pagina * pagina, int RRN)
    {
        // Abre o arquivo de indice
        FILE *arq_indice = fopen("ibtree.idx", "rb+");
        if (arq_indice == NULL)
        {
            printf("Erro ao abrir o arquivo de indice\n");
            return;
        }

        // Posiciona o ponteiro de escrita no inicio da pagina
        fseek(arq_indice, RRN * (ORDEM - 1) * sizeof(Chave) + sizeof(int), SEEK_SET);

        // Escreve o numero de chaves na pagina
        fwrite(&pagina->num_chaves, sizeof(int), 1, arq_indice);

        // Escreve as chaves da pagina
        fwrite(pagina->chaves, sizeof(Chave), ORDEM - 1, arq_indice);

        // Escreve os filhos da pagina
        fwrite(pagina->filhos, sizeof(int), ORDEM, arq_indice);

        // Fecha o arquivo de indice
        fclose(arq_indice);
    }

    // Funcao para inserir um novo aluno no arquivo de dados e atualizar o arquivo de indice
    void inserir_aluno(Aluno * aluno)
    {
        // Escreve o aluno no final do arquivo de dados

        // Obtem o tamanho atual do arquivo de dados
        FILE *arq_dados = fopen("turma.dat", "rb");
        fseek(arq_dados, 0, SEEK_END);
        int tam_arq_dados = ftell(arq_dados);
        fclose(arq_dados);

        // Calcula o RRN do novo aluno
        int RRN_novo_aluno = tam_arq_dados / TAM_REG;

        // Abre o arquivo de dados em modo de escrita
        arq_dados = fopen("turma.dat", "rb+");
        if (arq_dados == NULL)
        {
            printf("Erro ao abrir o arquivo de dados\n");
            return;
        }

        // Escreve o aluno no final do arquivo de dados
        fseek(arq_dados, RRN_novo_aluno * TAM_REG, SEEK_SET);
        fwrite(aluno->nome, sizeof(char), 50, arq_dados);
        fwrite(aluno->curso, sizeof(char), 50, arq_dados);
        fwrite(&aluno->RA_UNESP, sizeof(int), 1, arq_dados);
        fwrite("#", sizeof(char), TAM_REG - 3 * sizeof(char) - sizeof(int), arq_dados);
        fclose(arq_dados);

        // Le o RRN da raiz da arvore-B do arquivo de indice
        int RRN_raiz;
        FILE *arq_indice = fopen("ibtree.idx", "rb");
        if (arq_indice == NULL)
        {
            printf("Erro ao abrir o arquivo de indice\n");
            return;
        }
        fread(&RRN_raiz, sizeof(int), 1, arq_indice);
        fclose(arq_indice);

        // Se a arvore estiver vazia, cria uma nova pagina raiz
        if (RRN_raiz == -1)
        {
            Pagina *pagina_raiz = (Pagina *)malloc(sizeof(Pagina));
            pagina_raiz->num_chaves = 1;
            pagina_raiz->chaves[0].RA_UNESP = aluno->RA_UNESP;
            pagina_raiz->chaves[0].RRN = RRN_novo_aluno;
            for (int i = 0; i < ORDEM; i++)
            {
                pagina_raiz->filhos[i] = -1;
            }
            escrever_pagina(pagina_raiz, 0);

            // Atualiza o RRN da raiz no arquivo de indice
            arq_indice = fopen("ibtree.idx", "rb+");
            fwrite(&RRN_raiz, sizeof(int), 1, arq_indice);

            fclose(arq_indice);
        }
        else
        {
            // A arvore ja possui pelo menos uma pagina, entao busca a pagina onde o novo aluno deve ser inserido
            int RRN_atual = RRN_raiz;
            Pagina *pagina_atual = ler_pagina(RRN_atual);
            while (pagina_atual->filhos[0] != -1)
            {
                // A pagina atual possui pelo menos um filho, entao busca o filho correspondente
                int i;
                for (i = 0; i < pagina_atual->num_chaves; i++)
                {
                    if (aluno->RA_UNESP < pagina_atual->chaves[i].RA_UNESP)
                    {
                        break;
                    }
                }
                RRN_atual = pagina_atual->filhos[i];
                free(pagina_atual);
                pagina_atual = ler_pagina(RRN_atual);
            }

            // A pagina atual e a folha onde o novo aluno deve ser inserido
            if (pagina_atual->num_chaves < ORDEM - 1)
            {
                // A pagina ainda possui espaco, entao insere o novo aluno na pagina atual
                int i;
                for (i = 0; i < pagina_atual->num_chaves; i++)
                {
                    if (aluno->RA_UNESP < pagina_atual->chaves[i].RA_UNESP)
                    {
                        break;
                    }
                }
                for (int j = pagina_atual->num_chaves; j > i; j--)
                {
                    pagina_atual->chaves[j] = pagina_atual->chaves[j - 1];
                }
                pagina_atual->chaves[i].RA_UNESP = aluno->RA_UNESP;
                pagina_atual->chaves[i].RRN = RRN_novo_aluno;
                pagina_atual->num_chaves++;
                escrever_pagina(pagina_atual, RRN_atual);
            }
            else
            {
                // A pagina esta che

                // Aloca memoria para a nova pagina e inicializa seus campos
                Pagina *nova_pagina = (Pagina *)malloc(sizeof(Pagina));
                nova_pagina->num_chaves = 0;
                for (int i = 0; i < ORDEM; i++)
                {
                    nova_pagina->filhos[i] = -1;
                }

                // Divide as chaves da pagina atual entre a pagina atual e a nova pagina
                int i;
                for (i = 0; i < ORDEM - 1; i++)
                {
                    if (aluno->RA_UNESP < pagina_atual->chaves[i].RA_UNESP)
                    {
                        break;
                    }
                }
                int j;
                for (j = 0; j < i; j++)
                {
                    nova_pagina->chaves[j] = pagina_atual->chaves[ORDEM - 1 + j];
                    nova_pagina->num_chaves++;
                }
                nova_pagina->chaves[j].RA_UNESP = aluno->RA_UNESP;
                nova_pagina->chaves[j].RRN = RRN_novo_aluno;
                nova_pagina->num_chaves++;
                j++;
                for (; j < ORDEM; j++)
                {
                    nova_pagina->chaves[j] = pagina_atual->chaves[ORDEM - 1 + j - 1];
                    nova_pagina->num_chaves++;
                }

                // Atualiza o numero de chaves da pagina atual
                pagina_atual->num_chaves = ORDEM - 1;

                // Calcula o RRN da nova pagina
                int RRN_nova_pagina = obter_RRN_nova_pagina();

                // Atualiza os filhos da nova pagina
                for (int k = 0; k < ORDEM; k++)
                {
                    nova_pagina->filhos[k] = pagina_atual->filhos[k + ORDEM - 1];
                    pagina_atual->filhos[k + ORDEM - 1] = -1;
                }

                // Escreve as paginas no arquivo de indice
                escrever_pagina(pagina_atual, RRN_atual);
                escrever_pagina(nova_pagina, RRN_nova_pagina);

                // Libera a memoria das paginas
                free(pagina_atual);
                free(nova_pagina);

                // Verifica se a pagina atual e a raiz da arvore-B
                if (RRN_atual == RRN_raiz)
                {
                    // A pagina atual e a raiz da arvore-B, ent

                    // Aloca memoria para a nova raiz
                    Pagina *nova_raiz = (Pagina *)malloc(sizeof(Pagina));
                    nova_raiz->num_chaves = 1;
                    nova_raiz->chaves[0] = nova_pagina->chaves[0];
                    nova_raiz->filhos[0] = RRN_atual;
                    nova_raiz->filhos[1] = RRN_nova_pagina;

                    // Atualiza o RRN da raiz no arquivo de indice
                    arq_indice = fopen("ibtree.idx", "rb+");
                    fwrite(&RRN_nova_pagina, sizeof(int), 1, arq_indice);
                    fclose(arq_indice);

                    // Escreve a nova raiz no arquivo de indice
                    escrever_pagina(nova_raiz, RRN_nova_pagina);

                    // Libera a memoria da nova raiz
                    free(nova_raiz);
                }
            }
        }
    }
}