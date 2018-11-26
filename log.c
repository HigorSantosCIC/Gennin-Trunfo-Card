#include <stdio.h>
#include "tree.h"
#include "log.h"
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "ninja.h"
#include "time.h"
#include "log.h"

void printLoggi(void){
	FILE *loggi = fopen(".log", "r");

	char linha[1000];
	printf("\e[1;33mHistorico de luta\n\n\e[0m");

	while(fscanf(loggi, "%[^\n]s", linha) != EOF){
		fscanf(loggi, "%*c");
		printf("%s\n", linha);
	}

	fclose(loggi);
	return;
}

void cleanLoggi(void){
	// Limpa o arquivo ".log"
	fclose(fopen(".log", "w"));
	return;
}

void loggi(Ninja *one, Ninja *two, int attribute){
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

void loserLoggi(Ninja* ninja, Ninja* ninja2, int atributo){
	system("clear");
	matchLoggi(NULL);
	printf("\e[1;33mResultado: %s (%d) X (%d) %s\n", ninja->nome, getAtt(ninja, atributo), getAtt(ninja2, atributo), ninja2->nome);
	printf("Ninja vencedor = %s\nAtributo usado = %s\e[0m\n", ninja->nome, getAttName(atributo));
	//printf("\e[1;33m Resultado: %s X %s\n", ninja->nome, ninja2->nome);
	//printf("Ninja vencedor = %s\nAtributo usado = %d\e[0m\n", ninja->nome, atributo);

	printf("\e[1;33m   ___   ___   ___   ___    ___   _   _\n");   
    printf("  | _ \\ | __| | _ \\ |   \\  | __| | | | | \n");  
    printf("  |  _/ | _|  |   / | |) | | _|  | |_| | \n");  
    printf("  |_|   |___| |_|_\\ |___/  |___|  \\___/  \n\e[0m");  
	printf("\n") ;
	printf("Pressione qualquer tecla para continuar\n");
	
	char pause[300];
	scanf("%s", pause);
	system("clear");
}

void winnerLoggi(Ninja* ninja,Ninja* ninja2, int atributo){
	system("clear");
	matchLoggi(NULL);
	printf("\e[1;33mResultado: %s (%d) X (%d) %s\n", ninja->nome, getAtt(ninja, atributo), getAtt(ninja2, atributo), ninja2->nome);
	printf("Ninja vencedor = %s\nAtributo usado = %s\e[0m\n", ninja->nome, getAttName(atributo));

	printf("\e[1;33m     __   _____ _  _  ___ ___ _   _\n"); 
	printf("     \\ \\ / / __| \\| |/ __| __| | | |\n");
	printf("      \\ V /| _|| .` | (__| _|| |_| |\n");
	printf("       \\_/ |___|_|\\_|\\___|___|\\___/\n\e[0m");
	printf("\n");
	printf("Pressione qualquer tecla para continuar\n");
	char pause[300];
	scanf("%s", pause);
	system("clear");
}

void menuLoggi(){
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

int keepLoggi(){

	srand(time(NULL));
	cleanLoggi();
    FILE *ninjas;
    ninjas = fopen ("ninjas.txt", "r");
    t_list* lista;
    if(ninjas == NULL){
        printf("Arquivo Invalido\n");
        return 0;  
    }else{
        printf("\n");
    }
    

    lista = ler_ninjas(ninjas); 
    printf("Escolha um ninja: \n");
    atributos(lista);

    int x;
    do{     
        scanf("%d", &x);
    }while(x < 0 || x >= 16);

    Ninja* aux = list_position(lista, x);   
    t_node* arvore = tree_create();
    
    tree_no(arvore, lista);
	
    for(int i = 1;i < height(arvore); i++){
        printf("\033[1;33m\n\nETAPA %d\n\033[0m", i);
        if(tree_leaf(arvore, aux) == 1)
		    break;
    }

	//system("clear");
    printLoggi();
	printf("\033[1;33m\nJogar Novamente (?)\n\033[0m");
	menuLoggi();
    printf("\n\n");
    fclose(ninjas);

    tree_free(arvore);
}