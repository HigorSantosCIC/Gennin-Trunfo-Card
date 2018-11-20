#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "log.h"

t_node* node_create(){
    t_node* ptr = (t_node*) malloc(sizeof(t_node));
    if(ptr != NULL){
        ptr->ninja = NULL;
        ptr->left = NULL;
        ptr->right = NULL;
    }
    return ptr;
}

Ninja* ninja_create(char* _nome, char* _elemento, int _ninjutso, int _genjutso, int _taijutso, int _defesa){
    
    Ninja* ptr = (Ninja*) malloc(sizeof(Ninja));

    if(ptr != NULL){
        ptr->nome = (char*) malloc(sizeof(strlen(_nome)+1 ));
        ptr->elemento = (char*) malloc(sizeof(strlen(_elemento)+1 ));
            if(ptr->nome != NULL && ptr->elemento != NULL){
                strcpy(ptr->nome, _nome);
                strcpy(ptr->elemento, _elemento);
                ptr->ninjutso = _ninjutso;
                ptr->genjutso = _genjutso;
                ptr->taijutso =_taijutso;
                ptr->defesa = _defesa;
            }
    }
    return ptr;
}

void ninja_free(Ninja* ninja){
    free(ninja->nome);
    free(ninja->elemento);
    free(ninja);
}
//Recursivamento
void adicionar_no(t_node* raiz){
    if(raiz->left != NULL){
        adicionar_no(raiz->left);
    }else{
        raiz->left = node_create();
    }
    if(raiz->right != NULL){
        adicionar_no(raiz->right);
    }else{
        raiz->right = node_create();
    }
    return;
}

t_node* tree_create(){
    t_node* raiz = node_create();
    for(int i =0;i < 4;i++){
        adicionar_no(raiz);
    }
    return raiz;    
}

void tree_free(t_node* tree){
    if(tree->left != NULL){
        tree_free(tree->left);
    }
    if(tree->right != NULL){
        tree_free(tree->right);
    }
    free(tree);
    return;
}

void tree_no(t_node* root, t_list* lista){
    if(root != NULL){
        if(root->left == NULL && root->right == NULL){
            root->ninja = lista->primeiro->ninja;
            lista->primeiro = lista->primeiro->proximo;
        }
        tree_no(root->left, lista);
        tree_no(root->right, lista);
    }
}

int tree_leaf(t_node* root, Ninja* ninja){    
    static int choose = 0;
    static int chosen = 0;
    if(root != NULL && root->left != NULL && root->right != NULL) {
        if(root->left->ninja != NULL && root->right->ninja != NULL){
    			Ninja* one = root->left->ninja;
    			Ninja* two = root->right->ninja;
            if(ninja == root->left->ninja || ninja == root->right->ninja){
				    chosen = choose;
					Ninja *eu = ninja == one ? one : two, *tu = ninja == one ? two : one;
                    //system("clear");
					printf("\n\033[1;34mSeu ninja: %s\nAdversário: %s\033[0m\n", eu->nome, tu->nome);
                    imprime_ninja(ninja, chosen);
            do{
        	        printf("\nEscolha o seu atributo (%d usado)\n", chosen);
                    scanf("%d", &choose);
            }while(choose == chosen || (choose <= 0 || choose > 4));
                root->ninja = fight(one, two, choose);
				loggi(one, two, choose);

                if(root->ninja != ninja)
					return 1;
            }else{
            	int atributo_rand = (rand()%4) + 1;
                loggi(one, two, atributo_rand);
            	root->ninja = fight(one, two, atributo_rand);
						}
        }
       	    if(tree_leaf(root->left,ninja) != 0) return 1;
        	if(tree_leaf(root->right,ninja) != 0) return 1;
  }
    return 0;
}

Ninja* fight(Ninja* ninja_one, Ninja* ninja_two, int attribute){
    switch(attribute){
        case 1: 
            if(ninja_one->ninjutso >= ninja_two->ninjutso){
                return ninja_one;
            }else{
                return ninja_two;
            }
            break;
        case 2: 
            if(ninja_one->genjutso >= ninja_two->genjutso){
                return ninja_one;
            }else{
                return ninja_two;
            }
            break;
        case 3: 
            if(ninja_one->taijutso >= ninja_two->taijutso){
                return ninja_one;
            }else{
                return ninja_two;
            }
            break;
        case 4: 
            if(ninja_one->defesa >= ninja_two->defesa){
                return ninja_one;
            }else{
                return ninja_two;
            }
            break;
        default:
            printf("a");
            break;
    }
}


void tree_print_preorder(t_node* root){
    if(root == NULL){
       //printf("RAIZ NULA\n");        
        return;
    }
    print_ninja(root->ninja);
    tree_print_preorder(root->left);
    tree_print_preorder(root->right);
}//end print arvore()

//Imprime time
void imprime_ninja(Ninja* ninja, int usado){ 
    if(ninja != NULL){
        if(ninja->nome != NULL)
            printf("Seu personagem:|%s|\n", ninja->nome); 
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



void printGivenLevel(t_node* raiz, int level){
    static int nivel_atual = -1;
		nivel_atual++;
    if(raiz != NULL)
    	if(level == nivel_atual && raiz->ninja != NULL){
      	  printf("%s [%d] \n", raiz->ninja->nome, raiz->ninja->ninjutso);
    	}
    	else
    	{
      	  printGivenLevel(raiz->left, level);
        	printGivenLevel(raiz->right, level);
    	}
		nivel_atual--;
}

int height(t_node* no){ 
    if (no==NULL) 
        return 0; 
    else
    { 
        int lheight = height(no->left); 
        int rheight = height(no->right); 
  
        if (lheight > rheight) 
            return(lheight+1); 
        else return(rheight+1); 
    } 
} 

void printLevelOrder(t_node* raiz){
    int h = height(raiz);
    for(int i = 0; i < h; i++){
        printGivenLevel(raiz, i);
				printf("\n");
    }

}


/* void whoaiam(t_node* raiz){
    int h
} */
