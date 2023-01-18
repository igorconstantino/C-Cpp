#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ORDEM 5
#define MIN 2

// Tipo Aluno
typedef struct Aluno{
    char *nome;
    char *curso;
    int RA_UNESP;
    int rrn;
}Aluno;

// Tipo Arvore
typedef struct Arvore{
    Aluno key[ORDEM+1];
    struct Arvore *filho[ORDEM+1];
    int numKeys;
} Arvore;

Arvore *raiz=NULL; //Raiz nula para inserir na folha depois

void declareArvore(Aluno aluno, FILE *arq);
Arvore *newNo(Aluno keys, Arvore *filho);
void insertNo(Aluno keys, int pos, Arvore *no,  Arvore *filho);
void split(Aluno keys, Aluno *pointer, int pos,  Arvore *no,  Arvore *filho,  Arvore **new);
int insertLeaf(Aluno keys, Aluno *pointer, Arvore *no, Arvore **filho);
void verifyToInsert(Aluno keys);
int search(Arvore *no, int val, FILE *arq);
void indice(Arvore *treeB, FILE *arq);
void writeArq(Aluno *aluno, FILE *arq);



//Funcoes para arvore B
void declareArvore(Aluno aluno, FILE *arq){
    while (!feof(arq)){
        fscanf(arq, "%d %d\n", &aluno.RA_UNESP, &aluno.rrn);
        verifyToInsert(aluno);
    }
}
// Criar um novo nó da árvore
Arvore *newNo(Aluno keys, Arvore *filho){
    Arvore *new;
    new = (Arvore *)malloc(sizeof(Arvore));
    new->key[1].RA_UNESP = keys.RA_UNESP;
    new->key[1].rrn = keys.rrn;
    new->numKeys = 1;
    new->filho[0] = raiz;
    new->filho[1] = filho;
    return new;
}

// Inserir a nova chave em um nó da árvore
void insertNo(Aluno keys, int pos, Arvore *no,  Arvore *filho) {
    int j = no->numKeys;
    while (j > pos) {
      no->key[j + 1] = no->key[j];
      no->filho[j + 1] = no->filho[j];
      j--;
    }
    no->key[j + 1].RA_UNESP = keys.RA_UNESP;
    no->key[j + 1].rrn = keys.rrn;
    no->filho[j + 1] = filho;
    no->numKeys++;
}

// Função de split
void split(Aluno keys, Aluno *pointer, int pos,  Arvore *no,  Arvore *filho,  Arvore **new) {
    int meio, j;

    if (pos > MIN)
      meio = MIN + 1;
    else
      meio = MIN;

    *new = (Arvore *)malloc(sizeof(Arvore));
    j = meio + 1;
    while (j <= ORDEM) {
      (*new)->key[j - meio] = no->key[j];
      (*new)->filho[j - meio] = no->filho[j];
      j++;
    }
    no->numKeys = meio;
    (*new)->numKeys = ORDEM - meio;

    if (pos <= MIN)
      insertNo(keys, pos, no, filho);

    else
      insertNo(keys, pos - meio, *new, filho);

    pointer->RA_UNESP = no->key[no->numKeys].RA_UNESP;
    pointer->rrn = no->key[no->numKeys].rrn;
    (*new)->filho[0] = no->filho[no->numKeys];
    no->numKeys--;
}

// Função para auxiliar na verificação para saber se é preciso criar um nó
int insertLeaf(Aluno keys, Aluno *pointer, Arvore *no, Arvore **filho){
    int pos;
    // Verifica se nó não existe
    if(!no){
        *pointer = keys;
        *filho = NULL; //Nulo para inserir na folha
        return 1;
    }
    // Verificando se o RA passado é menor que o do nó da árvore
    if(keys.RA_UNESP < no->key[1].RA_UNESP)
        pos = 0;
    else{
        for (pos = no->numKeys; (keys.RA_UNESP < no->key[pos].RA_UNESP && pos > 1 ); pos--);{
            if(keys.RA_UNESP == no->key[pos].RA_UNESP)
                printf("\nRA JA INSERIDO!");
        }
    }
    // Verificando recursivamente na árvore
    if(insertLeaf(keys, pointer, no->filho[pos], filho)){
        if (no->numKeys < ORDEM)
            insertNo(*pointer, pos, no, *filho);
        else{
            split(*pointer, pointer, pos, no, *filho, filho);
            return 1; // Vai ser necessário criar um novo nó
        }   
    }
    return 0;
}

// Função que verifica se será necessário criar um novo nó
void verifyToInsert(Aluno keys){
    Arvore *filho;
    int retorno;
    Aluno pointer;
    
    if(insertLeaf(keys, &pointer, raiz, &filho))
        raiz = newNo(pointer, filho);
}

// Função para buscar um item na arvore
int search(Arvore *no, int val, FILE *arq){
    fseek(arq, 0, SEEK_SET);
    Aluno aluno;
    int i;

    if(no){ 
        for(i = 0; i < no->numKeys; i++){
            if(search(no->filho[i], val, arq))
                return 1;
              
            if(no->key[i + 1].RA_UNESP == val){ // Se o RA da proxima posição for igual ao buscado
                char c[1];
                
                fseek(arq, no->key[i +1].rrn + 1, SEEK_SET); // Movendo ate a posição do RRN
                fscanf(arq, "%d|", &aluno.RA_UNESP); // Lendo o RA do aluno
                
                aluno.nome = (char*)malloc(sizeof(70));
                c[0] = fgetc(arq);

                do{
                    strcat(aluno.nome, c);
                    c[0] = fgetc(arq);
                }while(c[0] != '|'); // Lendo e formando a string "nome" ate o '|'

                aluno.curso = (char*)malloc(sizeof(70));
                c[0] = fgetc(arq);

                do{
                    strcat(aluno.curso, c);
                    c[0] = fgetc(arq);
                }while(c[0] != '|'); // Lendo e formando a string "curso" ate o '|'                
                printf("Encontrado!\n%s|%s|%d\n", aluno.nome, aluno.curso, aluno.RA_UNESP);

                return 1;
            }        
        }       
        if(search(no->filho[i], val, arq))
            return 1;
    }

    return 0;
}

//FUNCOES EXTRAS
// Função que atualiza o índice da árvore
void indice(Arvore *treeB, FILE *arq){
    int i;
    if(treeB){
        for(i = 0; i < treeB->numKeys; i++){
            indice(treeB->filho[i], arq);
            fprintf(arq, "%d\n", treeB->key[i+1].RA_UNESP);
            fprintf(arq, "%d\n", treeB->key[i+1].rrn);
        }
        indice(treeB->filho[i], arq);// chama recursivamente
    }
}

// Função que escreve os dados dos alunos no arquivo e completa com '#'
void writeArq(Aluno *aluno, FILE *arq){
    int start, end;
    fseek(arq, 0, SEEK_END);
    start = ftell(arq);
    fprintf(arq, "|%d|%s|%s|", aluno->RA_UNESP, aluno->nome, aluno->curso);
    end = ftell(arq);

    for(int i=0; i < 128 - (end-start); i++)
        fprintf(arq, "#");
    aluno->rrn = start;
}

// Função principal
int main(){

    int key, ch;
    int op=0;
    Aluno aluno;
    Arvore arvore;
    FILE *data;
    FILE *index;
    char nome[60];
    char curso[60];

    data = fopen("turma.dat", "a+");
    index = fopen("ibtree.idx", "a+");
    
    do
    {
        printf("\nDigite a opcao que deseja: ");
        printf("\n 1 - Inserir aluno");
        printf("\n 2 - Buscar aluno");
        printf("\n 3 - Sair\n");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            printf("\nNome do aluno a inserir: ");
            scanf(" %[^\n]c", nome);
            aluno.nome = (char *)malloc(sizeof(strlen(nome)+1));
            strcpy(aluno.nome, nome);

            printf("\nCurso do aluno a inserir: ");
            scanf(" %[^\n]c", curso);
            aluno.curso = (char *)malloc(sizeof(strlen(curso)+1));
            strcpy(aluno.curso, curso);
            int tamanho;
            
            do{
                printf("\nDigite o RA: ");
                scanf("%d", &aluno.RA_UNESP);
               
            } while (aluno.RA_UNESP > 100000000 && aluno.RA_UNESP < 99999999);

            writeArq(&aluno, data);
            verifyToInsert(aluno);
            fseek(index, 0, SEEK_END);
            indice(raiz, index);
            break;
        case 2:
            printf("\nDigite o RA a ser buscado: ");
            scanf("%d", &key);
            search(raiz, key, data);
            break;
        
        default:
            break;
        }
    } while (op!=3);

    fclose(index);
    fclose(data);
    return 0;
}