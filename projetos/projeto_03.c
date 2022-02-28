#include <stdio.h>
#include <stdlib.h>

int j=0;		                              //Variável global para escrever respostas no vetor solução

int balanceRec(int, int, int, int*, int*);//Função recursiva da balança
int rem_first(int*, int*);					      //Função que exclui o primeiro elemento do vetor  
void add_vet(int*, int);				          //Adiciona um peso ao vetor solução e adiciona 1 a j
void reset(int*);						              //Zera o vetor e o j

//Início da função principal
int main(){
  
  //Quantidade de produtos, quantidade de pesos, soma de todos os pesos
  int N, M, soma=0;		

  //Vetor de pesos, vetor com pesos da solução, vetor dos pesos dos produtos
  int Vpesos[M], Vsol[M], Vpro[N];

  //Input de N e M com suas validações
  do{																	
    printf("\n\tEntre com a quantidade de produtos [1-100]: ");		
    scanf("%d", &N);
  }while(N<1 || N>100);							
  
  //Input da quantidade de pesos
  do{														
    printf("\n\tEntre com a quantidade de pesos[5-20]: ");		
    scanf("%d", &M);
  }while(M<5 || M>20);	

  //Input dos pesos e soma total dos pesos
  printf("\n\tEntre com os valores dos %d pesos: ", M);				
  for(int i=0;i<M;i++){
	  do{
	    scanf("%d", Vpesos+i);
    }while(Vpesos[i]>1000000 || Vpesos[i]<1);
	soma+=Vpesos[i];
  }

  //Input dos pesos dos produtos
  printf("\n\tEntre com os pesos dos %d produtos: ", N);			
  for(int i=0;i<N;i++)
    do
      scanf("%d", Vpro+i);
    while(Vpro[i]<0);

  for(int i=0; i<N; i++){  
    if(Vpro[i]==0 || Vpro[i]>soma){ 
      printf("\n\t0");                                 //Valores nao calculaveis
    }else{
      int flag=balanceRec(M, Vpro[i], 0, Vpesos, Vsol);//Chamada da função 
      j--;                                             //Ajuste do j
      //Saída das respostas:
      if(flag){												                 
        printf("\n\tPesos para o produto de peso %d: ", Vpro[i]);
    
        for(int i=j;i>=0;i--) 
          if(Vsol+i>0) 
            printf("\t%d", Vsol[i]);
          
        for(int i=j;i>=0;i--) 
          if(Vsol+i<0) 
            printf("\t%d", Vsol[i]);
      }else{ 
        printf("\n\t0");
      }  
      reset(Vsol);//Zera vetor e j
    }
  }
  return 0;
}//Fim da função principal



//auxpeso= quantidade de pesos disponiveis, BE= balança da esquerda,  BD= balança da direita
int balanceRec(int auxpeso, int BE, int BD, int* Vpesos, int *Vsol){

  int Vaux[auxpeso];						//Vetor auxiliar para não mudar os valores de Vpesos
  for(int i=0; i<auxpeso; i++) 
    Vaux[auxpeso-i-1]=Vpesos[i];//Vetor auxiliar é o inverso de Vpesos

  //Pesos iguais
  if(BD==BE) 
    return 1;		

  //caso 0
  if(auxpeso==0) 
    return 0;	

  int n=rem_first(Vaux, &auxpeso);//n é o primeiro valor do vetor, o maior peso disponivel no momento

  if(balanceRec(auxpeso, BE, BD, Vpesos, Vsol)) 
    return 1; 								    //n > peso do produto

  //n colocado na balança da direita
  if(balanceRec(auxpeso, BE, BD+n, Vpesos, Vsol)){ 
    add_vet(Vsol, n); 
    return 1;
  }			

  //n colocado na balança da esquerda
  if(balanceRec(auxpeso, BE+n, BD, Vpesos, Vsol)){ 
    add_vet(Vsol, (-1*n)); 
    return 1;
  }	
  return 0;
}//Fim da funcão balanceRec



//V é um vetor, N é um ponteiro
int rem_first(int *V,int *N){		
  int primeiro = *(V);  //primeiro valor do vetor, que será retornado
  for(int i=0;i<(*N);i++)
   *(V+i) = *(V+i+1);		//exclusao do primeiro peso
  
  *N =(*N)-1;	  				//"diminuição" do tamanho do vetor
  
  return primeiro;
}//Fim da função rem_first



//V é um vetor, num é o numero que será adicionado ao vetor
void add_vet(int* V, int num){	
  for(int i=0; i<j+1; i++)
    if(V[i]==num) //verifica se o numero já está no vetor
      return;	

  V[j]=num;       //adiciona o numero no vetor
  j++;            //soma 1 a j
  return;
}//Fim da função add_vet



//V é um vetor
void reset(int* V){			
	int i=0;
	do{	
		V[i]=0;	//Zera V
		i++;
  }while(i<=j); 
  j=0;      //Zera j
  return;	
}//Fim da função reset