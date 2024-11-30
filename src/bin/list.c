#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "tree.h"
#include "log.h"

/*
    Utils for List<Ninja>
*/

elementNinja* createElement(Ninja* ninja){
    elementNinja* element = (elementNinja*) malloc(sizeof(elementNinja));

    if(element != NULL){
        element->ninja = ninja;
        element->next = NULL;
        element->before = NULL;
    }
    return element;
}

bool isListEmpty(list* list){
    return (list->first == NULL && list->last == NULL);
}

list* createList(){
        list* list = (list*) malloc(sizeof(list));
        if(list != NULL){
            list->first = NULL;
            list->last = NULL;
            list->countNinja = 0;
        }
        return list;
}

void insertList(list* list, Ninja* ninja, int position) {
    elementNinja* element = createElement(ninja);

    if (isListEmpty(list)) {
        // Case: Empty list
        list->first = element;
        list->last = element;
    } else if (position >= list->countNinja) {
        // Case: Insert at the end
        element->previous = list->last;
        list->last->next = element;
        list->last = element;
    } else {
        // Case: Insert in the middle or at the start
        elementNinja* current = list->first;

        // Navigate to the desired position
        for (int i = 0; i < position; i++) {
            if (current->next != NULL) {
                current = current->next;
            }
        }

        // Update pointers for insertion
        element->next = current;
        element->previous = current->previous;
        current->previous = element;

        if (element->previous != NULL) {
            element->previous->next = element;
        } else {
            // Update `first` if inserted at the start
            list->first = element;
        }
    }

    // Increment the element count
    list->countNinja++;
}

void removeList(list* list, int position) {
    // Check for empty list
    if (isListEmpty(list)) {
        printf("Error: Cannot remove from an empty list.\n");
        return;
    }

    // Check for invalid position
    if (position < 0 || position >= list->countNinja) {
        printf("Error: Invalid position.\n");
        return;
    }

    elementNinja* elementNinjaAux = list->first;

    // Navigate to the desired position
    for (int i = 0; i < position; i++) {
        elementNinjaAux = elementNinjaAux->next;
    }

    // Update links to remove `aux` from the list
    if (elementNinjaAux->next != NULL) {
        elementNinjaAux->next->previous = elementNinjaAux->previous;
    } else {
        // Update last if the removed element is the last one
        list->last = elementNinjaAux->previous;
    }

    if (elementNinjaAux->previous != NULL) {
        elementNinjaAux->previous->next = elementNinjaAux->next;
    } else {
        // Update first if the removed element is the first one
        list->first = elementNinjaAux->next;
    }

    // Free the element and its associated data
    freeNinja(elementNinjaAux->ninja); // Free the `Ninja` structure
    free(elementNinjaAux);

    // Decrement the count
    list->countNinja--;
}


//libera memoria da lista

void freeMemoryList(list* lista) {
    if (lista == NULL) return; // Handle null pointer gracefully

    // Free each element in the list
    elementNinja* current = lista->first;
    while (current != NULL) {
        elementNinja* next = current->next; // Store the next element
        ninja_free(current->ninja);        // Free the Ninja data
        free(current);                     // Free the element itself
        current = next;                    // Move to the next element
    }

    // Free the list structure
    free(lista);
}


//imprime a lista

Ninja* getElementFromList(list* list, int position) {
    // Check for invalid position or empty list
    if (list == NULL || list->first == NULL || position < 0 || position >= list->countNinja) {
        printf("Error: Invalid position or empty list.\n");
        return NULL;
    }

    // Traverse the list to the desired position
    elementNinja* element = list->first;
    for (int i = 0; i < position; i++) {
        element = element->next; // Move to the next element
    }

    // Return the Ninja at the desired position
    return element->ninja;
}


list* getFileNinjaList(FILE* ninjas) {
    // Check if file is valid
    if (ninjas == NULL) {
        printf("Error: File not found or cannot be opened.\n");
        return NULL;
    }

    char name[20];
    char element[20];
    char description[20];
    int ninjutsu, genjutsu, taijutsu, block;

    list* list = createList();
    if (list == NULL) {
        printf("Error: Unable to create list.\n");
        return NULL;
    }

    // Read ninjas from file and populate the list
    while (fscanf(ninjas, "%19[^,], %19[^,], %19[^,], %d, %d, %d, %d\n",
                  name, element, description, &ninjutsu, &genjutsu, &taijutsu, &block) == 7) {
        Ninja* ninjaElement = createNinja(name, element, ninjutsu, genjutsu, taijutsu, block);
        if (ninjaElement == NULL) {
            printf("Error: Unable to create ninja.\n");
            freeMemoryList(list);
            return NULL;
        }
        insertList(list, ninjaElement, list->countNinja); // Insert at the end
    }

    return list;
}

void printListCount(list* list) {
    if (list == NULL) {
        printf("The list is empty or uninitialized.\n");
        return;
    }
    printf("Number of ninjas: %d\n", list->countNinja);
}

void printNinjaList(list* ninjaList) {
    // Check if the list is null or empty
    if (ninjaList == NULL || ninjaList->countNinja == 0) {
        printf("The list is empty or uninitialized.\n");
        return;
    }

    // Iterate through the list and print each Ninja's details
    for (int i = 0; i < ninjaList->countNinja; i++) {
        Ninja* currentNinja = getElementFromList(ninjaList, i);
        printf("\nName: %s\nElement: %s\nNinjutsu: %d\nGenjutsu: %d\nTaijutsu: %d\nBlock: %d\n",
               currentNinja->name, currentNinja->element,
               currentNinja->ninjutsu, currentNinja->genjutsu,
               currentNinja->taijutsu, currentNinja->block);
    }
}

list* randomizeNinjaList(list* ninjaList) {
    if (ninjaList == NULL) {
        printf("Error: List is null.\n");
        return NULL;
    }

    // Ensure the list has more than 17 ninjas before proceeding
    while (ninjaList->countNinja > 17) {
        int position = rand() % ninjaList->countNinja; // Generate a random position
        Ninja* targetNinja = positionList(ninjaList, position); // Get the Ninja at the random position
        if (targetNinja != NULL) {
            removeList(ninjaList, position); // Remove the Ninja at the random position
        }
    }

    return ninjaList; // Return the modified list
}

void printNinja(Ninja* ninja, int highlightedStat) {
    if (ninja == NULL) {
        printf("Error: Ninja is NULL.\n");
        return;
    }

    if (ninja->name == NULL || ninja->element == NULL) {
        printf("Error: Ninja has incomplete data.\n");
        return;
    }

    // Placeholder for stats, replacing the highlighted one with "XX"
    char ninjutsu[10], genjutsu[10], taijutsu[10], block[10];
    snprintf(ninjutsu, sizeof(ninjutsu), "%d", ninja->ninjutsu);
    snprintf(genjutsu, sizeof(genjutsu), "%d", ninja->genjutsu);
    snprintf(taijutsu, sizeof(taijutsu), "%d", ninja->taijutsu);
    snprintf(block, sizeof(block), "%d", ninja->block);

    switch (highlightedStat) {
        case 1: snprintf(ninjutsu, sizeof(ninjutsu), "XX"); break;
        case 2: snprintf(genjutsu, sizeof(genjutsu), "XX"); break;
        case 3: snprintf(taijutsu, sizeof(taijutsu), "XX"); break;
        case 4: snprintf(block, sizeof(block), "XX"); break;
        default: break;
    }

    // Print Ninja details with color formatting
    printf("\e[1;34mElemento: %s\n"
           "\e[1;35m1)\e[0m Ninjutsu: %s\n"
           "\e[1;35m2)\e[0m Genjutsu: %s\n"
           "\e[1;35m3)\e[0m Taijutsu: %s\n"
           "\e[1;35m4)\e[0m block: %s\n\n",
           ninja->elemento, ninjutsu, genjutsu, taijutsu, block);
}


void printNinja(Ninja* ninja) {
    // Validate that the Ninja object is not NULL
    if (ninja == NULL) {
        printf("Error: Ninja is NULL.\n");
        return;
    }

    // Validate that the Ninja has a name
    if (ninja->nome == NULL) {
        printf("Error: Ninja has no name.\n");
        return;
    }

    // Print Ninja details
    printf("Ninja Details:\n");
    printf("Name: %s\n", ninja->nome);

    // Check and print optional attributes
    if (ninja->elemento != NULL) {
        printf("Element: %s\n", ninja->elemento);
    }

    printf("Ninjutsu: %d\n", ninja->ninjutsu);
    printf("Genjutsu: %d\n", ninja->genjutsu);
    printf("Taijutsu: %d\n", ninja->taijutsu);
    printf("Defense: %d\n", ninja->block);
    printf("\n");
}

Ninja* getElementFromList(list* list, int index) {
    elementNinja* current = list->first;
    for (int i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }
    if (current != NULL) {
        return current->ninja;
    }
    return NULL;  // Return NULL if index is out of bounds
}

void attributes(list* list) {
    // Ensure random number generator is seeded
    srand((unsigned int)time(NULL));

    // Loop through the list of ninjas
    for (int i = 0; i < list->countNinja; i++) {
        // Get the ninja at the current index
        Ninja* ninjaElement = getElementFromList(list, i);

        if (ninjaElement == NULL) {
            printf("Error: Ninja at index %d is NULL.\n", i);
            continue;  // Skip if the ninja is NULL
        }

        // Generate a random number between 0 and 3
        int x = rand() % 4;

        printf("Ninja %d:\n", i);

        // Print one random attribute of the ninja based on the random number
        switch(x) {
            case 0:
                printf("ninjutsu: %d | genjutsu: ?? | taijutsu: ?? | block: ??\n\n", ninjaElement->ninjutsu);
                break;

            case 1:
                printf("ninjutsu: ?? | genjutsu: %d | taijutsu: ?? | block: ??\n\n", ninjaElement->genjutsu);
                break;

            case 2:
                printf("ninjutsu: ?? | genjutsu: ?? | taijutsu: %d | block: ??\n\n", ninjaElement->taijutsu);
                break;

            case 3:
                printf("ninjutsu: ?? | genjutsu: ?? | taijutsu: ?? | block: %d\n\n", ninjaElement->block);
                break;

            default:
                // This case should never happen with rand() % 4
                printf("Null\n");
                break;
        }
    }
}
