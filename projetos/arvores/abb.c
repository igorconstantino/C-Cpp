#include <stdlib.h>     //Para usar malloc, free, exit ...
#include <stdio.h>      //Para usar printf ,... 
#include "ABB.h"

//Operações
//------------------------------------------------------
//Cria uma árvore binária vazia
void Definir(tree t)
{
   t = NULL;
}

//Verifica se a AB é uma árvore vazia
int Vazia(tree t)
{ 
   return (t == NULL);
}

//Define nó raiz
void Criar_raiz(tree t, tipo_dado elem)
{
   //o tipo 'tree' é um ponteiro de nó!
   tree raiz = malloc(sizeof(no)); 
   if (!raiz)
   {
      printf( "Memoria insuficiente!\n" );
      return;
   }
   
   raiz->esq = NULL;
   raiz->dir = NULL;
   raiz->info = elem;
   t = raiz;
}

//Retorna a altura (profundidade) da AB
int Altura(tree t)
{	
   if (t == NULL)
      return 0;
   
   int altE = Altura(t->esq);
   int altD = Altura(t->dir);
   
   if (altE > altD)
      return (altE + 1);

   return(altD + 1); //altura = max(altE,altD) + 1
}

//Função recursiva para verificar se uma AB é balanceada
boolean Balanceada(tree t)
{
   if (t == NULL)
      return TRUE;
   else if (t->esq == NULL && t->dir == NULL) //t não tem filhos
      return TRUE;
   else if (t->esq != NULL && t->dir != NULL) //t tem ambas subárvores não-nulas
      return (Balanceada(t->esq) && Balanceada(t->dir)); //recursão
   else if (t->esq != NULL) //t tem um único filho – na esquerda
      return (Altura(t->esq) == 1);
   else 					  //t tem um único filho – na direita
      return (Altura(t->esq) == 1);
}

//Função (recursida) para calcular o número de nós da AB
int Numero_nos(tree t)
{
   if (t == NULL)
      return 0;
   
   int nE = Numero_nos(t->esq);
   int nD = Numero_nos(t->dir);
   
   return(nE + nD + 1);
}

//Função (recursiva) para verificar se 
//uma AB é perfeitamente balanceada
boolean Perf_balanceada(tree t)
{
   if (t == NULL)
      return TRUE;
   else if (t->esq == NULL && t->dir == NULL)  //t não tem filhos
      return TRUE;
   else if(t->esq != NULL && t->dir != NULL)  //t tem ambas subárvores não-nulas
 	  return (Perf_balanceada(t->esq) && Perf_balanceada(t->dir)); //recursão
   else if(t->esq != NULL)                 //t tem um único filho – na  esquerda 
      return (Numero_nos(t->esq) == 1);
   else                                      //t tem um único filho – na direita
      return (Numero_nos(t->esq) == 1);
}

//Função p/ adicionar um filho à direita de um nó, cujo ponteiro é dado (pai). 
//Se o nó não possui filho à direita, então cria esse filho com conteúdo "elem"
boolean Insere_dir(tree pai, tipo_dado elem)
{
   if (pai == NULL)
      return FALSE;
   
   if (pai->dir != NULL)
   {
      printf("Ja tem filho a direita\n");
      return FALSE;
   }

   //Jeito #1
   Criar_raiz(pai->dir, elem);
   
   //Jeito #2 ('na mão')
   //tree no = malloc(sizeof(no));
   //no->esq = NULL;
   //no->dir = NULL;
   //no->info = item;
   //pai->dir = no;
   
   return TRUE;
}

//Função p/ adicionar um filho à esquerda de um nó, cujo ponteiro é dado (pai). 
//Se o nó não possui filho à esquerda, então cria esse filho com conteúdo "elem"
boolean Insere_esq(tree pai, tipo_dado elem)
{
   if (pai == NULL)
      return FALSE;
   
   if (pai->esq != NULL)
   {
      printf("Ja tem filho a esquerda\n");
      return FALSE;
   }

   Criar_raiz(pai->esq, elem);
   
   return TRUE;
}


//Percorre a árvore em pré-ordem
void Pre_ordem(tree t)
{
   if(t != NULL)
   {
      Visita(t);
      Pre_ordem(t->esq);
      Pre_ordem(t->dir);
   }
}

//Percorre a árvore no esquema in-ordem
void In_ordem(tree t)
{
   if(t != NULL) 
   {
      In_ordem(t->esq);
      Visita(t);
      In_ordem(t->dir);
   }
}

//Percorre a árvore em pós-ordem
void Pos_ordem(tree t)
{
   if(t != NULL)
   {
      Pos_ordem(t->esq);
	  Pos_ordem(t->dir);
      Visita(t);
   }
}

//Função "Visita" na forma de impressão de dado
void Visita(tree t)
{
   printf("Valor: %d\n", t->info.valor);
}

//Função (recursiva) de busca para ABB
pno Busca_r(tree raiz, tipo_dado elem)
{
	if(raiz == NULL)
		return NULL;
		
	if(elem.valor == raiz->info.valor)
		return raiz;
		
	if(elem.valor < raiz->info.valor)
		return Busca_r(raiz->esq, elem);
	else
		return Busca_r(raiz->dir, elem);	
				
}

//Função (não-recursiva) de busca para ABB
pno Busca_nr(tree raiz, tipo_dado elem)
{
   pno p = raiz;
   
   while (p != NULL)
   {
      if (p->info.valor == elem.valor) 
         return p;
      else if (elem.valor > p->info.valor) 
         p = p->dir;
      else 
         p = p->esq;
   }
   
   return p;
}

//Função (recursiva) para inserir um elemento com um 
//valor x em uma ABB, caso ele ainda não esteja lá. 
//Retorna o ponteiro para o nó que contém o elem. c/ valor x 
pno Busca_insere(tree raiz, tipo_dado elem)
{
	//Insere elemento como raiz da árvore
	if(raiz == NULL){
		raiz = malloc(sizeof(tree));
		raiz->info = elem;
		raiz->esq = NULL;
		raiz->dir = NULL;
		
		return raiz;
	}
	
	if(elem.valor < raiz->info.valor)
		return Busca_insere(raiz->esq, elem);
		
	if(elem.valor > raiz->info.valor)
		return Busca_insere(raiz->dir, elem);
		
	return raiz;	
}


//Função (recursiva) para buscar e remover um elemento com um
//valor x. Retorna true se removeu o elemento; false, se o 
//elemento de valor x não estava na árvore
//Implementacao 3 da aula
boolean Busca_remove(tree raiz, tipo_dado elem)
{
   //Árvore vazia; x não está na árvore
   if (raiz == NULL)
      return FALSE;
   
   //Encontrou exatamente x: eliminar
   if (raiz->info.valor == elem.valor) 
   { 
      Remove_no(raiz);
      //Caso altere a raiz no procedimento, altera aqui
      return TRUE;
   }
   
   if (raiz->info.valor < elem.valor)
   {
	  //Buscar e remover na sub-árvore direita
      return Busca_remove(raiz->dir, elem);
   }
   else
   {
      //Buscar e remover na sub-árvore esquerda
      return Busca_remove(raiz->esq, elem);
   }
}

//Função de remoção dado um nó p
//p é o ponteiro para o nó a ser removido. 
//Retorna em p o ponteiro para o nó que o substituiu
//Implementacao 3 da aula
void Remove_no(pno p)
{
   pno q;
   
   if (p->esq == NULL)
   {
      //Substitui pelo filho à direita
      q = p; 
	  p = p->dir; 
	  free(q);	  
   } 
   else if (p->dir == NULL) 
   {
      //Substitui pelo filho à esquerda
      q = p; 
	  p = p->esq; 
	  free(q);
   } 
   else
      Substitui_menor_a_direita(p, p->dir);
      //Alternativamente: Substituir_maior_a_esquerda(p, p->esq)
}

//Encontra o sucessor de p, isto é, o descendente mais 
//à esquerda da sub-arvore à direita de p. É um nó
//terminal: seu conteúdo é copiado em q e ele será removido
//Implementacao 3 da aula
void Substitui_menor_a_direita(pno p, pno suc)
{
   pno q;
   
   if (suc->esq == NULL)
   {
      p->info = suc->info;
      
	  //Remover sucessor
      q = suc;
      suc = suc->dir;
      free(q);
   } 
   else
      Substitui_menor_a_direita(p, suc->esq);
}
