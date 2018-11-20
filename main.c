#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include <locale.h>
#include "time.h"
#include "log.h"

int main () {
    srand(time(NULL));
	cleanLoggi();
    setlocale(LC_CTYPE,"pt_BR.UTF-8");
    FILE *ninjas;
    ninjas = fopen ("ninjas.txt", "r");
    t_list* lista;
    if(ninjas == NULL){
        printf("Arquivo Invalido\n");
        return 0;  
    }else{
        printf("Arquivo aberto com sucesso");
    }
    
    lista = ler_ninjas(ninjas); 

    printf("Escolha um ninja: \n");
    atributos(lista);

    int x;
    do{     
        scanf("%d", &x);
    }while(x < 0 || x >= 16);

    Ninja* aux = list_position(lista, x);   

    t_node* arvore = tree_create();

    tree_no(arvore, lista);

    for(int i = 1;i < height(arvore); i++){
        system("clear");
        printf("\033[1;33m\n\nETAPA %d\n\033[0m", i);
		printf("\n");
        
        if(tree_leaf(arvore, aux) == 1)
			break;
    }
	
    printLoggi();
    
    printf("\n\n");

    fclose(ninjas);

    return 0;
}
