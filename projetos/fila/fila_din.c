#include "fila.h"
//Tipo registro
typedef struct{
	char nome[30];
	//mais tipos...
}tipo_dado;

//Tipo elemento
typedef struct elem{
	tipo_dado info;
	struct elem *lig;
}tipo_elem;

//Tipo fila
typedef struct{
	tipo_elem *inicio, *fim;
}fila;


//Operações----------------------

void Definir(fila *q){
	q->inicio = NULL;
	q->fim = NULL;
}

boolean Vazia(fila *q){
	return (q->inicio == NULL);
}

void Tornar_vazia(fila *q){
	tipo_elem *ndel, *nextno;
	
	if(!Vazia(q)){
		nextno = q->inicio;
		
		while(nextno != NULL){
			ndel = nextno;
			nextno = nextno->lig;
			free(ndel);
		}
	}
	
	Definir(q);
}

boolean Inserir(fila *q, tipo_dado info){
	tipo_elem *p;
	p = malloc(sizeof(tipo_elem));
	
	if(p == NULL)
		return FALSE;
		
	p->info = info;
	p->lig = NULL;
	
	if(Vazia(q))
		q->inicio = p;
	else
		q->fim->lig = p;
		
	q->fim = p;
	
	return TRUE;		
}

boolean Remover(fila *q, tipo_dado *info){
	tipo_elem *p;
	
	if(Vazio(q))
		return FALSE;
		
	p = q->inicio;
	*info = p->info;
	q->inicio = p->lig;
	
	if(q->inicio = NULL)
		q->fim = NULL;
		
	free(p);
	
	return TRUE;		
}

int Tamanho(fila *q){
	tipo_elem *p;
	int count = 0;
	
	p = q->inicio;
	
	while(p != NULL){
		count++;
		p = p->lig;
	}
	
	return count;
}

boolean Inicio_fila(fila *q, tipo_dado *elem){
	if(Vazia(q))
		return FALSE;
		
	*elem = q->inicio->info;
	
	return TRUE;	
}