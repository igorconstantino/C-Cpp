#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da struct
typedef struct aluno {
	char nome[61];
	char curso[60];
	int nro_UNESP;
} Aluno;

/*
OBS: 
1 - Não utilizar espaços no nome e curso(não consegui fazer ler espaços e funcionar)
2 - Feche o programa antes de buscar os alunos(se não ele sempre vai buscar o primeiro)
*/

int main() {
	// Variaveis
	FILE *arq, *ind;
	Aluno aluno;
	int op, ra_pedido, ind_buscado, vetorRA[5], vetorIND[5];
	long int posicao;
  char strAux[121];
  char *token;

	// Abertura dos arquivos
	arq = fopen("turma.txt", "a+");
	ind = fopen("index.txt", "a+");

	// Teste se arquivos foram abertos
	if (arq == NULL)
		printf("Nao foi possivel abrir o arquivo da turma!");
	if (ind == NULL)
		printf("Nao foi possivel abrir o arquivo de indice!");

	do {
		// Menu
		printf("\n(1) - Gravar aluno\n"
			     "(2) - Buscar aluno\n"
			     "(3) - Fechar\n\n");

		printf("Digite a opcao desejada: ");
		scanf("%d", &op);

		// Gravar aluno
		if (op == 1) {
			posicao = ftell(arq); // Pegando a posição de cada registro inserido

			printf("\nDigite o nome do aluno: \n");
			scanf("%s", aluno.nome); 
			fprintf(arq, "%s|", aluno.nome);

			printf("Digite o curso do aluno: \n");
			scanf("%s", aluno.curso); 
			fprintf(arq, "%s|", aluno.curso);

			printf("Digite o numero(RA) do aluno(4 digitos): \n");
			scanf("%d", &aluno.nro_UNESP);
			fprintf(arq, "%d|", aluno.nro_UNESP);
      
      // Gravando os RAs e indices no index.txt
      fprintf(ind, "\n");
			fprintf(ind, "%d ", aluno.nro_UNESP);
			fprintf(ind, "%ld", posicao);

      long int posicaoFinal = ftell(arq); // Pegando posição final do registro

      // Preenchendo com #
      for(long int i = posicaoFinal; i < posicao + 128; i++) // Laço começando onde termina o registro e terminando na posição inicial do novo registro + 128 (tamanho do registro)
        fprintf(arq, "#");
      
		}// Fim opção 1 -----------------------------------


		// Buscar aluno
		if (op == 2) {
      // Armazenando os valores do RA e indice em vetores
      for(int i = 0; i < 5; i++){
        fscanf(ind, "\n%d %d\n", &vetorRA[i], &vetorIND[i]);
      }

			printf("Digite o RA do aluno: ");
			scanf("%d", &ra_pedido);

      // For para buscar o RA pedido e pegar seu respectivo índice
      for(int i = 0; i < 5;i++){
        if(ra_pedido == vetorRA[i]){
          ind_buscado = vetorIND[i];
        }
      }

      // Deslocando até o índice buscado
      fseek(arq, ind_buscado, SEEK_SET);
      // Lendo os proximos caracteres
      fgets(strAux, 124, arq);  
      
      token = strtok(strAux, "|"); 

      printf("\nDados do aluno:");
      while(token != NULL){
        printf("%s, ", token);
        token = strtok(NULL, "|#");
      }
      
		}// Fim opção 2 -----------------------------------

	} while (op != 3);

	// Fechamento dos arquivos
	fclose(arq);
	fclose(ind);

	return 0;
}