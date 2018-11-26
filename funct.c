#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "log.h"

//Funçoes com respeito a arvore e elemento


//cria e inicializa um no
t_node* node_create(){
    t_node* ptr = (t_node*) malloc(sizeof(t_node));
    if(ptr != NULL){
        ptr->ninja = NULL;
        ptr->left = NULL;
        ptr->right = NULL;
    }
    return ptr;
}

//cria um elemento ninja
Ninja* ninja_create(char* _nome, char* _elemento, int _ninjutsu, int _genjutsu, int _taijutsu, int _defesa){
    
    Ninja* ptr = (Ninja*) malloc(sizeof(Ninja));

    if(ptr != NULL){
        ptr->nome = (char*) malloc(sizeof(strlen(_nome)+1 ));
        ptr->elemento = (char*) malloc(sizeof(strlen(_elemento)+1 ));
            if(ptr->nome != NULL && ptr->elemento != NULL){
                strcpy(ptr->nome, _nome);
                strcpy(ptr->elemento, _elemento);
                ptr->ninjutsu = _ninjutsu;
                ptr->genjutsu = _genjutsu;
                ptr->taijutsu =_taijutsu;
                ptr->defesa = _defesa;
            }
    }
    return ptr;
}


//limpa memoria do elemento ninja

void ninja_free(Ninja* ninja){
    if(!ninja)
        free(ninja->nome);
        free(ninja->elemento);
        free(ninja);
}

//Adiciona nó de maneira recursiva

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

//de fato cria a arvore

t_node* tree_create(){
    t_node* raiz = node_create();
    for(int i =0;i < 4;i++){
        adicionar_no(raiz);
    }
    return raiz;    
}


//libera memoria da arvore 

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

//insere da lista na arvore

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

//TORNEIO
 
int tree_leaf(t_node* root, Ninja* ninja){    
    
    static int choose = 0;
    static int chosen = 0;

    if(root != NULL && root->left != NULL && root->right != NULL) {
        //no folha
        if(root->left->ninja != NULL && root->right->ninja != NULL){
            Ninja* one = root->left->ninja;
            Ninja* two = root->right->ninja;        
            //localizar o ninja escolhido
            if(ninja == root->left->ninja || ninja == root->right->ninja){
				    chosen = choose;
                    //atribuir ninja para one se for igual ao escolhido
					Ninja *eu = ninja == one ? one : two, *tu = ninja == one ? two : one;
					printf("\n\033[1;34mSeu ninja: %s\033[0m\n", eu->nome);
                    //imprime o ninja com XX
                    imprime_ninja(ninja, chosen);
                    printf("\n\033[1;34mSeu Adversário: %s\033[0m\n",tu->nome);
                        do{
        	                printf("\nSelecione um atributo = \n");
                            scanf("%d", &choose);
                        } while(choose == chosen || choose <= 0 || choose > 4);
                
                    root->ninja = fight(one, two, choose);
                    system("clear");
                    if(root->ninja == ninja)
                        winnerLoggi(one, two, choose);
                    else
                        loserLoggi(one, two, choose);

                    loggi(one, two, choose);
                    if(root->ninja != ninja)
				        return 1;
            }else{
            	int atributo_rand = (rand()%4) + 1;
                loggi(one, two, atributo_rand);
            	root->ninja = fight(one, two, atributo_rand);
			}           
            root->left->ninja = NULL;
            root->right->ninja = NULL;
        }
        
       	    if(tree_leaf(root->left,ninja) != 0) return 1;
        	if(tree_leaf(root->right,ninja) != 0) return 1;
  }
    return 0;
}


// Luta entre os integrantes

Ninja* fight(Ninja* ninja_one, Ninja* ninja_two, int attribute){
    switch(attribute){
        case 1: 
            if(ninja_one->ninjutsu >= ninja_two->ninjutsu){
                return ninja_one;
            }else{
                return ninja_two;
            }
            break;
        case 2: 
            if(ninja_one->genjutsu >= ninja_two->genjutsu){
                return ninja_one;
            }else{
                return ninja_two;
            }
            break;
        case 3: 
            if(ninja_one->taijutsu >= ninja_two->taijutsu){
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

//printa a arvore em pre ordem

void tree_print_preorder(t_node* root){
    if(root == NULL){
        return;
    }
    print_ninja(root->ninja);
    tree_print_preorder(root->left);
    tree_print_preorder(root->right);
}//end print arvore()

void printGivenLevel(t_node* raiz, int level){
    static int nivel_atual = -1;
		nivel_atual++;
    if(raiz != NULL)
    	if(level == nivel_atual && raiz->ninja != NULL){
      	  printf("%s [%d] \n", raiz->ninja->nome, raiz->ninja->ninjutsu);
    	}
    	else{
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
