#ifndef NINJA_H
#define NINJA_H

void freeMemoryNinja(Ninja* ninja);
void freeMemoryTree(nodeNinja* treeNinja);

void insertList(list* list, Ninja* ninja, int positionIndex);
void freeList(list* list);

void removeElementList(list *list, int positionIndex);
void nodeTree(node* root, list* list);

void printTreePreOrderAlgorithm(nodeNinja* rootNinja);
void printLevelOrder(node* root);
void printGivenLevel(node* root, int level);
void printLogger(void);
void printNinjaElementIndex(Ninja* ninja, int index);
void printNinja(Ninja* ninja);

void cleanLogger(void);
void logger(Ninja *firstNinja, Ninja *secondNinja, int attribute);
void matchLogger(char *nameNinja);
void printLoser(Ninja* firstNinja,Ninja* secondNinja, int attribute);
void printWinner(Ninja* firstNinja, Ninja* secondNinja, int attribute);
void menu(void);

int keep(void);
int getValue(int reset);
int getAttribute(Ninja *, int);
int leafTree(node* root, Ninja* ninja);
int heightNode(node* root);
int IsEmptyList(list* list);

char* getAttName(int);

#endif
