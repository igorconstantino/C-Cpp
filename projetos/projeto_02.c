//Inclusão de bibliotecas
#include <stdio.h>
#include <math.h>

//Prototipação das funções
//n é o expoente
long double funcao_01(int, long double);	     //(1/2 x 3/4 x 5/6 x ... x (n-2)/(n-1))
long double funcao_02(int);	                   //(1/n)
long double funcao_03(int);	                   //(1/2)^n
int verificacao(long double, long double, int);//Verificação da precisão

//Início da função principal
int main(){

  int p, aux=1, i=1;             //Precisão de pi, teste de precisao, quantidade de parcelas da sequencia
  long double pi=0, pi_aux=0, primeiro_termo;//Pi, teste para pi e primeiro termo

  printf("\nInforme a precisão de pi, insira um número de 1 a 15: ");
  
  do{ //Entrada de dados e validação de entrada
    scanf("%d", &p); 
    if(p<1)
      printf("\nValor menor que 1.\nDigite novamente: ");
    else if(p>15)
      printf("\nValor maior que 15.\nDigite novamente: ");
  }while((p<1)||(p>15));

  do{
    primeiro_termo=funcao_01(i,primeiro_termo);
    
    pi+=(primeiro_termo*funcao_02(i)*funcao_03(i))*6;//Cálculo de pi
    
    aux=verificacao(pi, pi_aux, aux);                //Verificação de precisão
    
    pi_aux=pi;          //Pi anterior recebe o valor agora do atual pi(atualização do pi_aux)
    i+=2;	              //Quantidade de parcelas aumenta em 2 para continuar ímpar
  }while(aux-1!=p);     //Precisão desejada alcançada

  printf("\nValor de pi: %.20Lf", pi);

}//Fim da função principal	

//Função 01
long double funcao_01(int n, long double primeiro_termo){
  if(n==1)
    return(1);
  primeiro_termo*=(long double)(n-2)/(n-1);
return(primeiro_termo);
}//(1/2 x 3/4 x 5/6 x ... x (n-2)/(n-1))

//Função 02
long double funcao_02(int n){
  return((double)(1)/(n));
}//(1/n)

//Função 03
long double funcao_03(int n){
  return(pow(0.5,n));
}//(1/2)^n

//Verificação
int verificacao(long double pi, long double pi_aux, int aux){
  long int testepi;         //Auxiliares para para verificação da precisão de mais de uma casa com o mesmo cálculo
  long int testeaux;    
  
  testepi= pi*pow(10, aux);      //Teste de pi atual(aux é o número de casas verificadas)
  testeaux= pi_aux*pow(10, aux); //Teste de pi anterior(aux é o número de casas verificadas)
  if(testepi==testeaux)
    aux++;                       //Se forem iguais o aux aumenta 1 

  return(aux);   
}//Verificação da precisão