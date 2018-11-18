#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include <locale.h>
#include "time.h"

int main () {

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

    how(lista);
    
    //print(lista);

    printf("Escolha um ninja: \n");
    atributos(lista);

    int x;
    do{     
    scanf("%d", &x);
    }while(x < 0 || x >= 16);

    Ninja* aux = list_position(lista, x);   
    
    imprime_ninja(aux);

    t_node* arvore = tree_create();
    
    tree_no(arvore, lista);
    
    
    int choose;
    printf("Escolha o seu atributo\n");
    scanf("%d", &choose);
    
//    tree_print_preorder(arvore);

    tree_leaf(arvore, choose);
    printf("\n\n");

    tree_print_preorder(arvore);
    


    fclose(ninjas);

    return 0;
}
