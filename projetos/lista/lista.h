#define MAX 100
#define TRUE 1
#define FALSE 0
#define boolean int

//Tipo chave
typedef int tipo_chave;

//Tipo registro
typedef struct{
	char nome[30];
	//mais campos...
}tipo_dado; 

//Tipo elemento
typedef struct{
	tipo_chave chave;
	tipo_dado info;
}tipo_elem;

//Tipo lista
typedef struct{
	int nelem; 
	tipo_elem A[MAX + 1];
}lista;

//Operações:
//------------------------
boolean Vazia(lista*);

boolean Cheia(lista*);

void Definir(lista*);

void Apagar(lista*);

boolean Inserir_posic(tipo_elem, lista*);

boolean Buscar(tipo_chave, lista*, int*);

void Remover_posic(int, lista*);

void Impr_elem(tipo_elem);

void Imprimir(lista*);

int Tamanho(lista*);

//Lista Ordenada--------------------------------
boolean Inserir_ord(tipo_elem, lista*);

boolean Buscar_ord(tipo_chave, lista*, int*);

boolean Busca_bin(tipo_chave, lista*, int*);

boolean Remover_ch(tipo_chave, lista*);