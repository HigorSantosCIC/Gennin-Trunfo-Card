#ifndef NINJA
#define NINJA

typedef struct node {
    Ninja* ninja;
    struct node* left;
    struct node* right;
}t_node;

typedef struct ninja {
    char* nome;
    char* elemento;
    int ninjutsu;
    int genjutsu;
    int taijutsu;
    int defesa;
} Ninja;

//Nin, gen, tai, def = 0 a 100//

//Assinaturas

t_node* node_create;

Ninja* ninja_create(char* _nome, char* _elemento,int _ninjutsu, int _genjutsu,int _taijutsu, int _defesa);

void ninja_free(Ninja* ninja);

t_node* tree_create();

void tree_free(t_node* tree);

Ninja* fight(Ninja* ninja_one, Ninja* ninja_two, int attribute);

void tree_print_preorder(t_node* root);

#endif
