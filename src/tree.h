#ifndef __TREE__
#define __TREE__

#include <stdio.h>
#include <stdlib.h>

// Declaration of struct

// Type struct of the ninja
typedef struct {
    char* nome;
    char* elemento;
    int ninjutsu;
    int genjutsu;
    int taijutsu;
    int defesa;
} Ninja;

// Struct of node (tree)

typedef struct node{
    Ninja* ninja;
    struct node* left;
    struct node* right;
}t_node;

t_node* node_create();

Ninja* ninja_create(char* _nome, char* _elemento, int _ninjutsu, int _genjutsu, int _taijutsu, int _defesa);

void ninja_free(Ninja* ninja);

t_node* tree_create();

void tree_free(t_node* tree);

Ninja* fight(Ninja* ninja_one, Ninja* ninja_two, int attribute);

void tree_print_preorder(t_node* root);


//Input from txt: nome, elemento, ninjutsu , genjusto , taijutsu, defesa

// Store in double linked list in memory

// Struct of ninja with double linked list
typedef struct ninja{
    Ninja* ninja;
    struct ninja* proximo;
    struct ninja* anterior;
 } t_elemento;

// Aux list struct
typedef struct aux_lista{
    t_elemento* primeiro; //Referencia para o primeiro elemento da lista
    t_elemento* ultimo;   //Referencia para o ultimo elemento da lista
    int much_ninja;    //Contador de times
}t_list; 

t_elemento* create_element(Ninja* ninja);

int IsEmpty(t_list* list);

void insert_list(t_list* lista, Ninja* ninja, int posicao);
void print_ninja(Ninja* ninja);
void lista_remover(t_list *lista, int posicao);

void liberar_lista(t_list* lista);

Ninja* list_position(t_list* lista, int posicao);

t_list* creat_list();

t_list* ler_ninjas(FILE *teams);

Ninja* how(t_list* lista);

Ninja* print(t_list* lista);

t_list* rando(Ninja* ninja, t_list* lista, int posicao);

void imprime_ninja(Ninja* ninja, int usado);

void tree_no(t_node* root, t_list* lista);

int tree_leaf(t_node* root, Ninja* ninja);

Ninja* atributos(t_list* lista);

void printLevelOrder(t_node* raiz);

void printGivenLevel(t_node* root, int level); 

int height(t_node* root); 

#endif