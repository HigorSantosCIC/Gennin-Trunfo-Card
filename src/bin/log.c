#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "time.h"
#include "dataStructure.h"
#include "utilsMethods.h"


void printLogger(void){
	FILE *logger = fopen(".log", "r");

	char row[1000];
	printf("\e[1;33mHistorico de luta\n\n\e[0m");

	while(fscanf(logger, "%[^\n]s", row) != EOF){
		fscanf(loggi, "%*c");
		printf("%s\n", row);
	}

	fclose(logger);
	return;
}

void cleanLogger(void){
	fclose(fopen(".log", "w"));
	return;
}

void logger(Ninja *one, Ninja *two, int attribute){
	// Abre um arquivo pra armazenar o log
	char match[1000] = "";
	FILE *logger = fopen(".log", "a");
	FILE *match_file = fopen(".match", "w");
	// Armazena o vencedor
	Ninja *winner = fight(one, two, attribute);
	// Imprime no arquivo ".log" o resultado de UMA luta

	fprintf(match_file, "\e[1;34m%s \e[0m(\e[1;33m%d\e[0m) x (\e[1;33m%d\e[0m) \e[1;34m%s\n  Atributo usado: \e[1;33m%d \e[0m(\e[1;33m%s\e[0m)\n",
		one->nome,
		getAtt(one, attribute),
		getAtt(two, attribute),
		two->nome,
		attribute,
		getAttName(attribute)
	);
	fprintf(match_file, "  \e[1;34mVencedor: \e[1;33m%s\e[0m\n", winner->nome);
	fprintf(match_file, "$");

	fclose(match_file), fopen(".match", "r");
	fscanf(match_file, "%[^$]s", match);
	fclose(match_file);

	fprintf(logger, "%s", match);

	// Configura o matchLoggi
	matchLoggi(match);
	// Fecha o arquivo
	fclose(logger);
	return;
}


void matchLoggi(char* match){
	static char last_match[500] = "";
	if(match == NULL){
		printf("%s\n", last_match);
	}
	else	
		strcpy(last_match, match);
}

void printloser(Ninja* ninja, Ninja* ninja2, int atributo){
	system("clear");
//	printf("\e[1;33mResultado: %s (%d) X (%d) %s\n", ninja->nome, getAtt(ninja, atributo), getAtt(ninja2, atributo), ninja2->nome);
//	printf("Ninja vencedor = %s\nAtributo usado = %s\e[0m\n", ninja->nome, getAttName(atributo));

	printf("\e[1;33m   ___   ___   ___   ___    ___   _   _\n");   
    printf("  | _ \\ | __| | _ \\ |   \\  | __| | | | | \n");  
    printf("  |  _/ | _|  |   / | |) | | _|  | |_| | \n");  
    printf("  |_|   |___| |_|_\\ |___/  |___|  \\___/  \n\e[0m");  
	printf("\n") ;
	matchLoggi(NULL);
	printf("Pressione qualquer tecla para continuar\n");
	
	scanf("%*[^\n]s");
	scanf("%*c");
	scanf("%*c");
	system("clear");
}

void printWinner(Ninja* ninja,Ninja* ninja2, int atributo){
	system("clear");

	printf("\e[1;33m     __   _____ _  _  ___ ___ _   _\n"); 
	printf("     \\ \\ / / __| \\| |/ __| __| | | |\n");
	printf("      \\ V /| _|| .` | (__| _|| |_| |\n");
	printf("       \\_/ |___|_|\\_|\\___|___|\\___/\n\e[0m");
	printf("\n");
	matchLogger(NULL);
	printf("Pressione qualquer tecla para continuar\n");
	scanf("%*[^\n]s");
	scanf("%*c");
	scanf("%*c");
	system("clear");
}

void matchLogger(){
printf("\n\n");
printf("    ######## ##     ##    ###    ##     ## ########     ######  ##     ## ##     ## ##    ## ##    ## #### ##    ##\n");
printf("    ##        ##   ##    ## ##   ###   ### ##          ##    ## ##     ## ##     ## ###   ## ###   ##  ##  ###   ##\n"); 
printf("    ##         ## ##    ##   ##  #### #### ##          ##       ##     ## ##     ## ####  ## ####  ##  ##  ####  ## \n");
printf("    ######      ###    ##     ## ## ### ## ######      ##       ######### ##     ## ## ## ## ## ## ##  ##  ## ## ## \n");
printf("    ##         ## ##   ######### ##     ## ##          ##       ##     ## ##     ## ##  #### ##  ####  ##  ##  #### \n");
printf("    ##        ##   ##  ##     ## ##     ## ##          ##    ## ##     ## ##     ## ##   ### ##   ###  ##  ##   ### \n");
printf("    ######## ##     ## ##     ## ##     ## ########     ######  ##     ##  #######  ##    ## ##    ## #### ##    ## \n");
printf("\n");
 
int menu;

printf("\e[1;33m[1] Iniciar Exame\n[2] Sair\e[0m\n");

do{
	scanf("%d", &menu);
}while(menu < 0 && menu > 2);
	switch(menu){
		case 1:
		keepLoggi();
		break;
		case 2:
			exit(-1);
		break;
	}	
}

int keep() {

    srand(time(NULL));
    cleanLogger();

    FILE *ninjas = fopen("ninjas.txt", "r");
    if (ninjas == NULL) {
        printf("Arquivo Invalido\n");
        return 0;
    }

    list* list = getFileNinjaList(ninjas);
    fclose(ninjas);

    chooseNinjaAndSetUpBattle(list);

    nodeNinja* tree = tree_create();
    nodeTree(tree, list);

    for (int i = 1; i < height(arvore); i++) {
        printf("\033[1;33m\n\nETAPA %d\n\033[0m", i);
        if (tree_leaf(arvore, aux) == 1)
            break;
    }

    printLogger();
    printf("\033[1;33m\nJogar Novamente (?)\n\033[0m");

    matchLogger();
    printf("\n\n");

    treeFree(arvore);
    return 1;
}
