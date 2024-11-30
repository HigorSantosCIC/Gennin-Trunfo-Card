#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dataStructure.h>
#include <utilsMethods.h>

I want to include utilsMethods.h

nodeNinja* createNode(){
    nodeNinja* ptrNode = (nodeNinja*) malloc(sizeof(nodeNinja));

    if(ptrNode != NULL){
        ptrNode->ninja = NULL;
        ptrNode->left = NULL;
        ptrNode->right = NULL;
    } else {
        fprintf(stderr, "Error: Memory allocation for nodeNinja failed.\n");
        return NULL;
    }

    printf("Created node at address: %p\n", (void*) ptrNode);
    return ptrNode;
}

Ninja* createNinja(char* name, char* element, int ninjutsu, int genjutsu, int taijutsu, int block) {
    // Allocate memory for the Ninja structure
    Ninja* elementNinja = (Ninja*) malloc(sizeof(Ninja));

    if (elementNinja == NULL) {
        fprintf(stderr, "Error: Memory allocation for Ninja failed.\n");
        return NULL;
    }

    // Allocate memory for name
    elementNinja->name = (char*) malloc(strlen(name) + 1); // +1 for null terminator
    if (elementNinja->name == NULL) {
        fprintf(stderr, "Error: Memory allocation for Ninja name failed.\n");
        free(elementNinja);
        return NULL;
    }

    // Allocate memory for element
    elementNinja->element = (char*) malloc(strlen(element) + 1); // +1 for null terminator
    if (elementNinja->element == NULL) {
        fprintf(stderr, "Error: Memory allocation for Ninja element failed.\n");
        free(elementNinja->name);
        free(elementNinja);
        return NULL;
    }

    // Copy strings and assign other fields
    strcpy(elementNinja->name, name);
    strcpy(elementNinja->element, element);
    elementNinja->ninjutsu = ninjutsu;
    elementNinja->genjutsu = genjutsu;
    elementNinja->taijutsu = taijutsu;
    elementNinja->block = block;

    return elementNinja;
}

void freeMemoryNinja(Ninja* ninja) {
    if (ninja) {
        free(ninja->name);
        free(ninja->element);
        free(ninja);
    }
}

void addNode(nodeNinja* root) {
    if (root == NULL) {
        fprintf(stderr, "Error: Root node is NULL.\n");
        return;
    }

    // Traverse and add to the left branch
    if (root->left != NULL) {
        addNode(root->left);
    } else {
        root->left = createNode();
    }

    // Traverse and add to the right branch
    if (root->right != NULL) {
        addNode(root->right);
    } else {
        root->right = createNode();
    }
}

nodeNinja* createTree(){
    nodeNinja* root = createNode();

    for(int i = 0;i < 4;i++){
        addNode(root);
    }

    return root;
}

void freeMemoryTree(nodeNinja* treeNinja){
    if(tree == NULL){
        return;
    }

    freeMemoryTree(tree->left);
    freeMemoryTree(tree->right);
    free(tree);

}

void nodeTree(nodeNinja* root, list* list) {
    if (root == NULL || list == NULL || list->first == NULL) {
        return; // Base case: stop if tree or list is empty
    }

    // If the current node is a leaf
    if (root->left == NULL && root->right == NULL) {
        if (list->first != NULL) {
            root->ninja = list->first->ninja; // Assign Ninja to the leaf node
            list->first = list->first->next;  // Move to the next element in the list
            list->countNinja--;               // Decrement the ninja count
        } else {
            fprintf(stderr, "Error: List exhausted before filling all leaf nodes.\n");
        }
        return; // Leaf nodes do not require further recursion
    }

    // Recursively traverse the left and right subtrees
    nodeTree(root->left, list);
    nodeTree(root->right, list);
}

int leafTree(nodeNinja* root, elementNinja* ninja) {
    if (root != NULL && root->left != NULL && root->right != NULL) {
        static int choose = 0;
        static int chosen = 0;

        // Only proceed if both left and right nodes have valid ninjas
        if (root->left->ninja != NULL && root->right->ninja != NULL) {
            Ninja* first = root->left->ninja;
            Ninja* second = root->right->ninja;

            // Find the chosen ninja
            if (ninja == root->left->ninja || ninja == root->right->ninja) {
                chosen = choose;

                Ninja *firstNinja = (ninja == one ? one : two), *secondNinja = ninja == one ? two : one;
                printf("\n\033[1;34mYour Ninja: %s\033[0m\n", firstNinja->name);
                printNinjaElementIndex(ninja, chosen);
                printf("\n\033[1;34mYour Opponent: %s\033[0m\n", secondNinja->nome);

                // User selects an attribute
                do {
                    printf("\nSelect an attribute (1-4): ");
                    if (scanf("%d", &choose) != 1) {
                        while(getchar() != '\n');  // Clear invalid input
                        printf("Invalid input! Please enter a number between 1 and 4.\n");
                    }
                } while (choose == chosen || choose <= 0 || choose > 4);

                // Run the fight
                root->ninja = fight(one, two, choose);
                system("clear");

                logger(one, two, choose);

                // Log the result
                if (root->ninja == ninja)
                    printWinner(one, two, choose);
                else
                    printLoser(one, two, choose);

                // If the user lost, return 1
                if (root->ninja != ninja)
                    return 1;
            } else {
                // Random battle if ninja is not chosen
                int randomAttribute = (rand() % 4) + 1;
                logger(one, two, randomAttribute);
                root->ninja = fight(one, two, randomAttribute);
            }

            // Reset ninjas in both left and right children
            root->left->ninja = NULL;
            root->right->ninja = NULL;
        }

        // Continue recursive traversal of left and right subtrees
        if (leafTree(root->left, ninja) != 0) return 1;
        if (leafTree(root->right, ninja) != 0) return 1;
    }
    return 0;
}


Ninja* fightNinja(Ninja* firstNinja, Ninja* secondNinja, int attribute) {
    // Ensure we have valid ninjas
    if (firstNinja == NULL || secondNinja == NULL) {
        printf("Error: Invalid ninja.\n");
        return NULL; // Return NULL if either ninja is invalid
    }

    switch(attribute) {
        case 1: // Ninjutsu
            return (firstNinja->ninjutsu >= secondNinja->ninjutsu) ? firstNinja : secondNinja;
        case 2: // Genjutsu
            return (firstNinja->genjutsu >= secondNinja->genjutsu) ? firstNinja : secondNinja;
        case 3: // Taijutsu
            return (firstNinja->taijutsu >= secondNinja->taijutsu) ? firstNinja : secondNinja;
        case 4: // Defesa
            return (firstNinja->defesa >= secondNinja->defesa) ? firstNinja : secondNinja;
        default:
            printf("Error: Invalid attribute.\n");
            return NULL; // Return NULL on invalid attribute
    }
}

void printTreePreOrderAlgorithm(nodeNinja* root){
    if(root == NULL){
        return;
    }

   if (root->ninja != NULL) {
           printNinja(root->ninja);
       } else {
           printf("No ninja at this node.\n");
       }

    printTreePreOrderAlgorithm(root->left);
    printTreePreOrderAlgorithm(root->right);
}

void printGivenLevel(nodeNinja* root, int level, int updatedLevel) {
    if (root == NULL) {
        return; // Return if the node is NULL
    }

    // Check if we are at the correct level
    if (level == updatedLevel && root->ninja != NULL) {
        // Print ninja information at the given level
        printf("%s [%d]\n", root->ninja->nome, root->ninja->ninjutsu);
    } else {
        // Recursively print left and right children at the next level
        printGivenLevel(root->left, level, updatedLevel + 1);
        printGivenLevel(root->right, level, updatedLevel + 1);
    }
}

int height(nodeNinja* node) {
    if (node == NULL) {
        return 0;  // Base case: The height of an empty tree is 0
    } else {
        // Recursively compute the height of the left and right subtrees
        int lheight = height(node->left);
        int rheight = height(node->right);

        // Return the larger of the two heights, plus 1 for the current node
        return (lheight > rheight) ? lheight + 1 : rheight + 1;
    }
}

void printLevelOrder(nodeNinja* root) {
    int h = height(root);  // Get the height of the tree
    // If the tree is empty, h will be 0, and the loop won't execute.
    for (int i = 0; i < h; i++) {
        printGivenLevel(root, i);  // Print all nodes at level 'i'
        printf("\n");  // Print a newline after each level
    }
}
