#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "log.h"

/*
Funçoes com respeito a lista
*/

//Cria um elemento, que eh o time

t_elemento* create_element(Ninja* ninja){       

    t_elemento* ptr = (t_elemento*) malloc(sizeof(t_elemento));    
    if(ptr != NULL){
        ptr->ninja = ninja;
        ptr->proximo = NULL;
        ptr->anterior = NULL;
    }
    return ptr;
}
//Funcao que verifica se eh vazia
int IsEmpty(t_list* list){
    return (list->primeiro == NULL && list->ultimo == NULL);
}

//Cria uma lista, inicializando
t_list* creat_list(){
        t_list* lista = (t_list*) malloc(sizeof(t_list));
        if(lista != NULL){
            lista->primeiro = NULL;
            lista->ultimo = NULL;
            lista->much_ninja = 0;
        }
        return lista;
}
//Insere um time na lista
void insert_list(t_list* lista, Ninja* ninja, int posicao){
    t_elemento* ptr = create_element(ninja);
    //printf("%s\n",team->much_team);
    if(IsEmpty(lista)){
        lista->ultimo = ptr;
        lista->primeiro = ptr;
    }else{
        if(posicao >= lista->much_ninja){
            ptr->anterior = lista->ultimo;
            lista->ultimo->proximo = ptr;
            lista->ultimo = ptr;
        }else{

        t_elemento* aux = lista->primeiro;

        for(int i = 0; i < posicao - 1; i++){
            if(aux->proximo != NULL){
                aux = aux->proximo;
            }
        }

            ptr->anterior = aux->anterior;
            ptr->proximo = aux;
            aux->anterior = ptr;
        if(ptr->anterior != NULL){
            aux->anterior->proximo = ptr;
        }else{
            lista->primeiro = ptr;
        }
    }  
    }
    (lista->much_ninja)++;
}

//Remove um time da lista
void lista_remover(t_list *lista, int posicao){

    if(IsEmpty(lista)){
        liberar_lista(lista);
        exit(-1);
    }else{
        t_elemento* aux = lista->primeiro;
        for(int i =0;i< posicao - 1; i++){
            if(aux->proximo != NULL){
                aux = aux->proximo;
            }
        }
        if(aux->proximo != NULL){
            aux->proximo->anterior = aux->anterior;
        }else{
            lista->ultimo = aux->anterior;
        }

        if(aux->anterior != NULL){
            aux->anterior->proximo = aux->proximo;
        }else{
            lista->primeiro = aux->proximo;
        }
        
        ninja_free(aux->ninja);
        free(aux);
    }
    (lista->much_ninja)--;

}

//libera memoria da lista

void liberar_lista(t_list* lista){
    while(!IsEmpty(lista)){
        lista_remover(lista, 0);
    }
    free(lista);
}

//imprime a lista

Ninja* list_position(t_list* lista, int posicao){
    
    t_elemento* element = lista->primeiro;
    for(int i = 0;i <= posicao - 1; i++){
        if(element->proximo != NULL){
            element = element->proximo;
        }
    }
    return element->ninja;
}

t_list* ler_ninjas(FILE *ninjas){
    char name[20];
    char elemento[20];	
    char a[20];
    int ninjutso, genjutso , taijutso, defesa;
    int posicao;
    
    t_list* lista = creat_list();

    Ninja* ler;

    while(fscanf(ninjas, "%[^,]s", name) == 1){
        fscanf(ninjas, "%2[ ,]s", a);
        fscanf(ninjas, "%[^,]s", elemento);
        fscanf(ninjas, "%s", a);
        fscanf(ninjas, "%d, %d, %d, %d\n", &ninjutso, &genjutso, &taijutso, &defesa);

        ler = ninja_create(name, elemento, ninjutso, genjutso, taijutso, defesa);
        insert_list(lista, ler, posicao);
        rando(ler, lista, posicao);
    }
    return lista;
}


//Quantidade na lista
Ninja* how(t_list* lista){
    printf("\n%d\n", lista->much_ninja);
}

//Imprimir uma lista
Ninja* print(t_list* lista){
    for(int i = 0; i < lista->much_ninja;i++){
        Ninja* Japa = list_position(lista, i);
        printf("\n%s  -> %s  -> %d -> %d -> %d -> %d\n", Japa->nome, Japa->elemento, Japa->ninjutso, Japa->genjutso, Japa->taijutso, Japa->defesa);
        
    }
}
//Remover da lista de maneira aleatoria é notavel que 17 = 16

t_list* rando(Ninja* ninja, t_list* lista, int posicao){
        while(lista->much_ninja == 17){
            //srand(time(NULL));
            posicao = rand()%32;
            ninja = list_position(lista, posicao);
            if(ninja != NULL){
                lista_remover(lista, posicao);
            }
        }    
}


//Imprime time
void imprime_ninja(Ninja* ninja, int usado){ 
    if(ninja != NULL){
        if(ninja->nome != NULL)
            //printf("Seu personagem:|%s|\n", ninja->nome); 
						switch(usado){
							case 1:
            		printf("Elemento:|%s|\n\e[1;35m1)\e[0m Ninjutso: XX\n\e[1;35m2)\e[0m Genjustso: %d\n\e[1;35m3)\e[0m Taijutso: %d\n\e[1;35m4)\e[0m Defesa: %d\n\n",ninja->elemento, ninja->genjutso, ninja->taijutso, ninja->defesa);
								break;
							case 2:
            		printf("Elemento:|%s|\n\e[1;35m1)\e[0m Ninjutso: %d\n\e[1;35m2)\e[0m Genjustso: XX\n\e[1;35m3)\e[0m Taijutso: %d\n\e[1;35m4)\e[0m Defesa: %d\n\n",ninja->elemento, ninja->ninjutso, ninja->taijutso, ninja->defesa);
								break;
							case 3:
            		printf("Elemento:|%s|\n\e[1;35m1)\e[0m Ninjutso: %d\n\e[1;35m2)\e[0m Genjustso: %d\n\e[1;35m3)\e[0m Taijutso: XX\n\e[1;35m4)\e[0m Defesa: %d\n\n",ninja->elemento, ninja->ninjutso, ninja->genjutso, ninja->defesa);
								break;
							case 4:
            		printf("Elemento:|%s|\n\e[1;35m1)\e[0m Ninjutso: %d\n\e[1;35m2)\e[0m Genjustso: %d\n\e[1;35m3)\e[0m Taijutso: %d\n\e[1;35m4)\e[0m Defesa: XX\n\n",ninja->elemento, ninja->ninjutso, ninja->genjutso, ninja->taijutso);
								break;
							default:
            		printf("Elemento:|%s|\n\e[1;35m1)\e[0m Ninjutso: %d\n\e[1;35m2)\e[0m Genjustso: %d\n\e[1;35m3)\e[0m Taijutso: %d\n\e[1;35m4)\e[0m Defesa: %d\n\n",ninja->elemento, ninja->ninjutso, ninja->genjutso, ninja->taijutso, ninja->defesa);
								break;
						}	
    }
}//end imprime time

void print_ninja(Ninja* ninja){
    if(ninja != NULL){
        if(ninja->nome != NULL)
            printf("Ninja:|%s|\n", ninja->nome);
        
    }
}//end imprime time


Ninja* atributos(t_list* lista){
    for(int i = 0; i < lista->much_ninja;i++){

        Ninja* Japa = list_position(lista, i);
        int x = rand()%4;

        printf("Ninja %d:\n", i);
        switch(x){
            case 0:
                printf("Ninjutso: %d Genjutso: ?? Taijutso: ?? Defesa: ??\n\n", Japa->ninjutso);
            break;

            case 1:
                printf("Ninjutso: ?? Genjutso: %d Taijutso: ?? Defesa: ??\n\n", Japa->genjutso);
                
            break;

            case 2:
                printf("Ninjutso: ?? Genjutso: ?? Taijutso: %d Defesa: ??\n\n", Japa->taijutso);
                
            break;
            case 3:
               printf("Ninjutso: ?? Genjutso: ?? Taijutso: ?? Defesa: %d \n\n", Japa->defesa);
                
            break;
            default:
                printf("Null\n");
            break;
        }
    }
}
