#define tam_fila 1000
#define indice int
#define boolean int
#define TRUE 1
#define FALSE 0

//tipo resgistro
typedef struct{
	char nome[30];
	//dados...
}tipo_dado;

typedef struct{
	int A[tam_fila];
	indice inicio, fim;
}fila;

//operações------------------
void Definir(fila*);

boolean Vazia(fila*);

boolean Cheia(fila*);

boolean Inserir(fila*, int);

boolean Remover(fila*, int*);

int Tamanho(fila*);

boolean Inicio_fila(fila*, int);