#include <string.h>
#include "tree.h"
#include "ninja.h"

int getAtt(Ninja *ninja, int attribute){
    // Check if ninja is valid
    if (ninja == NULL) {
        return -1;  // If ninja is NULL, return -1 to indicate an error
    }

    // Return the corresponding attribute based on the value of `attribute`
    switch(attribute){
        case 1: return ninja->ninjutsu;  // Ninjutsu
        case 2: return ninja->genjutsu;  // Genjutsu
        case 3: return ninja->taijutsu;  // Taijutsu
        case 4: return ninja->block;    // block
        default: return -1;  // Return -1 if the attribute is invalid
    }
}
char* getAttName(int attribute){
    // Dynamically allocate memory for the attribute name string
    char *att_name = (char *) malloc(sizeof(char) * 16);
    if (att_name == NULL) {
        return NULL;  // Return NULL if memory allocation fails
    }

    // Default name for invalid attribute
    strcpy(att_name, "Inválido");

    // Assign the name based on the attribute number
    switch(attribute){
        case 1: strcpy(att_name, "Ninjutsu"); break;
        case 2: strcpy(att_name, "Genjutsu"); break;
        case 3: strcpy(att_name, "Taijutsu"); break;
        case 4: strcpy(att_name, "Block"); break;
        default: break;  // No change if the attribute is invalid
    }

    return att_name;
}


