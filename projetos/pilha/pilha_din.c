#include "pilha.h"
//Estruturas e tipos empregados ----------------
//Tipo chave
typedef int tipo_chave;

//Tipo registro
typedef struct{
	char nome[10];
}tipo_dado;

//Tipo elemento
typedef struct elem{
	tipo_dado info;
	struct elem *lig;
}tipo_elem; 

//Tipo pilha
typedef struct{
	tipo_elem *topo;
}pilha;

//Cria uma pilha vazia 
void Define(pilha *p){
	p->topo = NULL;
}

//Inserir x no topo da pilha
boolean Push(tipo_dado x, pilha *p){
	tipo_elem *q = malloc(sizeof(tipo_elem));
	
	if(q == NULL)
		return FALSE;
	
	q->info = x;
	q->lig = p->topo;
	p->topo = q;
	
	return TRUE;
} 

//Testa se a pilha está vazia
boolean Vazia(pilha *p){
	return (p->topo == NULL);
}

//Acessa o topo sem remove-lo
tipo_elem *Topo(pilha *p){
	return p->topo;
}

//Remove o elemneto do topo sem retornar o valor
void Pop_up(pilha *p){
	tipo_elem *q = p->topo;
	p->topo = p->topo->lig;
	free(q);
}

//Remove e retorna o elemento
tipo_elem *Pop(pilha *p){
	tipo_elem *q = p->topo;
	p->topo = p->topo->lig;
	
	return q;
}

