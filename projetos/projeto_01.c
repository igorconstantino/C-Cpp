#include <stdio.h> //Inclusão de bibliotecas

int main(){ //Início do programa principal

  FILE *figura, *cinza;                                                 //Declaração dos arquivos de entrada e saída do programa
  int largura, altura, n, k, pixel_01, pixel_02, pixel_03, pixel_cinza; //Declaração de variáveis utilizadas ao longo da execução

  figura= fopen("figura.dat", "r"); //Abrindo para ler o arquivo de entrada "figura" 
  cinza= fopen("cinza.dat", "w");   //Abrindo para escrever no arquivo de saída "cinza"

  if ((figura==NULL)||(cinza==NULL)) {                   //Validando existência dos arquivos
    printf("Nao foi possivel abrir um dos arquivos.");
    return 0;                                            //Finalizando o programa caso não existam 
  }else
    printf("Arquivos abertos com sucesso.");   

  fscanf(figura, "%d %d", &largura, &altura); //Lendo os valores de larura e altura
    
  if ((largura<12)||(largura>1024)||(altura<12)||(altura>1024)) //Validando dimensões da imagem 
    printf("As dimensoes da imagem sao invalidas.");
  else
    fprintf(cinza, "%d %d\n", largura, altura);                 //Escrevendo no arquivo "cinza" os valores de largura e altura

  for (k=0; k<altura; k++) {    //Laço para percorrer a as linhas 
    for (n=0; n<largura; n++) { //Laço para percorrer as colunas
      pixel_cinza=0;            //Inicializando a variável sempre com o valor 0
      fscanf(figura, "%d %d %d ", &pixel_01, &pixel_02, &pixel_03); //Lendo os 3 valores dos pixeis(R,G,B)
      pixel_cinza=(pixel_01 + pixel_02 + pixel_03)/3;               //Calculando sua media para um pixel cinza
      fprintf(cinza, "%d ", pixel_cinza);                           //Escrevendo o valor do pixel cinza no arquivo "cinza"
    }
    fprintf(cinza, "\n");       //Pulando para a próxima linha após ler uma linha
  }

  //Fechando ambos arquivos
  fclose(figura); 
  fclose(cinza);

  //Fim do programa
  return 0;
}