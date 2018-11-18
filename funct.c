#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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

Ninja* largura(t_node* raiz, Ninja* ninja){
    if(raiz == NULL){
        return 0;
    }
    else if(raiz->ninja == ninja)
        return 1;

    else if (largura(raiz->left, ninja))
        return 1;
    else
    return (largura(raiz->right, ninja));
}



Ninja* tree_leaf(t_node* root, int x){    
        Ninja* one;
        Ninja* two;
    if(root != NULL) {
        if(root->left->ninja != NULL && root->right->ninja != NULL){
            one = root->left->ninja;
            two = root->right->ninja;
            root->ninja = fight(one, two, x);
            return root->ninja;
        }
        tree_leaf(root->left, x);
        tree_leaf(root->right, x);
  }
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
void imprime_ninja(Ninja* ninja){
    if(ninja != NULL){
        if(ninja->nome != NULL)
            printf("Seu personagem: |%s|\n", ninja->nome);
            printf("Elemento: |%s|\n1) Ninjutso: %d\n2) Genjustso: %d\n3) Taijutso: %d\n4) Defesa: %d\n\n",ninja->elemento, ninja->ninjutso, ninja->genjutso, ninja->taijutso, ninja->defesa);
    }
}//end imprime time

void print_ninja(Ninja* ninja){
    if(ninja != NULL){
        if(ninja->nome != NULL)
            printf("Ninja: |%s|\n", ninja->nome);
        
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
        fscanf(ninjas, "%s", a);
        fscanf(ninjas, "%[^,]", elemento);
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
            srand(time(NULL));
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
        int x = rand()%3;

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
