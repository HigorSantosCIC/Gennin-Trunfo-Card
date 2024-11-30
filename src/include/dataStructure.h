#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* name;
    char* element;
    int ninjutsu;
    int genjutsu;
    int taijutsu;
    int block;
} Ninja;

Ninja* createNinja(char* name, char* element, int ninjutsu, int genjutsu, int taijutsu, int block);

typedef struct elementNinja{
    Ninja* ninja;
    struct elementNinja* next;
    struct elementNinja* previous;
} elementNinja;

elementNinja* createElementNinja(Ninja* ninja);


typedef struct nodeNinja{
    Ninja* ninja;
    struct nodeNinja* left;
    struct nodeNinja* right;
} nodeNinja;

nodeNinja* createNode();
nodeNinja* createTree();

typedef struct countList {
    elementNinja* first;
    elementNinja* last;
    int countNinja;
} list;

list* createList();
list* randomizeNinjaList(Ninja* ninja, list* list, int positionIndex);
void readNinjasInput(FILE *teams);
int countList(list* list);  // Should return an int, not a Ninja*
void printList(list* list);  // Print the whole list of ninjas
Ninja* fightNinja(Ninja* firstNinja, Ninja* secondNinja, int paramInput);
void attributes(list* list);  // Print ninja attributes
elementNinja* listPositionIndex(list* list, int positionIndex);  // Correct return type to elementNinja*

#endif
