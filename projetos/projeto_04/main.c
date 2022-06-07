#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main(int argc, char *argv[]) {
	
    int op;

    lista *minhaLista;
    tipo_elem novo_elem = {12 , {"Igor"}};
    tipo_chave chave = 12;
    int posic = 1;

    Definir(minhaLista);

	do{
        printf("---------------OPCOES--------------\n");
        printf( "0 - Sair                           \n"
                "1 - Verificar se esta vazia        \n"
                "2 - Verificar se esta cheia        \n"
                "3 - Definir a lista                \n"     
                "4 - Apagar a lista                 \n"
                "5 - Inserir na lista               \n"
                "6 - Buscar elemento                \n"
                "7 - Remover elemento               \n"
                "8 - Imprimir elemento              \n"
                "9 - Imprimir lista                 \n"
                "10 - Mostrar tamanho               \n"
                "11 - Inserir ordenando             \n"
                "12 - Buscar ordenado               \n"
                "13 - Busca binaria                 \n"
                "14 - Remover pela chave            \n");
        printf("\nDigite uma opcao: \n");
        scanf("%d", &op);

        switch(op){
            case 1:
                Vazia(minhaLista);
                break;
            case 2:
                Cheia(minhaLista);
                break;
            case 3:
                Definir(minhaLista);
                break;
            case 4:
                Apagar(minhaLista);
                break;
            case 5:
                Inserir_posic(novo_elem, minhaLista);
                break;
            case 6:
                Buscar(chave, minhaLista, posic);
                break;
            case 7:
                Remover_posic(posic, minhaLista);
                break;
            case 8:
                Impr_elem(novo_elem);
                break;
            case 9:
                Imprimir(minhaLista);
                break;
            case 10:
                Tamanho(minhaLista);
                break;
            case 11:
                Inserir_ord(novo_elem, minhaLista);
                break;
            case 12:
                Buscar_ord(chave, minhaLista, posic);
                break;
            case 13:
                Busca_bin(chave, minhaLista, posic);
                break;
            case 14:
                Remover_ch(chave, minhaLista);
                break;               
        }

    }while(op != 0);
	
	return 0;
}