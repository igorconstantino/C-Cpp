#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

#define MAX 100
#define TRUE 1
#define FALSE 0
#define boolean int

//Lista sequencial----------------
boolean Vazia(lista *L){
	return (L->nelem == 0);		
}

boolean Cheia(lista *L){
	return (L->nelem == MAX);
}

void Definir(lista *L){
	L->nelem = 0;
	L->A[0].chave = 0;
}

void Apagar(lista *L){
	L->nelem = 0;
}

boolean Inserir_posic(tipo_elem x, int p, lista *L){
	int q;
	
	if(Cheia(L) || p > L->nelem+1 || p < 1){
		return FAlSE;
	}else{
		for(q = L->nelem; q >= p; q--)
			L->A[q + 1] = L->A[q];
		
		L->A[p] = x;
		L->nelem++;
		
		return TRUE;
	}
}

boolean Buscar(tipo_chave x, lista *L, int *p){
	if(!Vazia(L)){
		int i = 1;
		
		while(i <= L->nelem){
			
			if(L->A[i].chave == x.chave){
				*p = i;
				
				return TRUE;
			}else{
				i++;
			}
		}
	}
	
	return FALSE;
}

void Remover_posic(int p, lista *L){
	int i;
	
	for(i = p+1; i < L->nelem; i++)
		L->A[i - 1] = L->A[i];
		
	L->nelem--;
}

void Impr_elem(tipo_elem t){
	printf("chave: %d", t.chave);
	printf("info: %s", t.info.nome);
}

void Imprimir(lista *L){
	int i;
	
	if(!Vazia(L))
		for(i = 1; i < L->nelem; i++)
			Impr_elem(L->A[i]);	
}

int Tamanho(lista *L){
	return L->nelem;
}

//Lista ordenada
//----------------------------

boolean Inserir_ord(tipo_elem x, lista *L){
	int i = 1;
	
	if(Vazia(L)){
		return Inserir_posic(x, i, L);
	}else{
		
		while(i <= L->nelem){
			
			if(x.chave < L->A[i].chave)
				return Inserir_posic(x, i, L);
			else
				i++;	
		}
		
		return Inserir_posic(x, i, L);
	}
}

//Busca simples
boolean Buscar_ord(tipo_chave x, lista *L, int *p){
	if(!Vazia(L)){
		int i = 1;
		
		while(i <= L->nelem){
			if(L->A[i].chave >= x){
				if(L->A[i].chave == x){
					*p = i;
					
					return TRUE;
				}
			}else{
				i++;
			}
		}
	}
	return FALSE;//Não encontrou
}

//busca binária
boolean Busca_bin(tipo_chave x, lista *L, int *p){
	int inf = 1;
	int sup = L->nelem;
	int meio;
	
	while(sup >= inf){
		meio = (inf + sup) / 2;
		
		if(L->A[meio].chave == x){
			*p = meio;
			
			return TRUE;
		}else{
			if(L->A[meio].chave < x){
				inf = meio + 1; 
			}else{
				sup = meio - 1;
			}	
		}
	}
	return FALSE;
}

boolean Remover_ch(tipo_chave x, lista *L){
	int *p;
	boolean removeu = FALSE;
	
	if(Busca_bin(x, L, p)){
		Remover_posic(p, L);
		removeu = TRUE;
	}
	return removeu;
}