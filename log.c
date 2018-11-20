#include <stdio.h>
#include "tree.h"
#include <string.h>
#include <stdlib.h>

void printLoggi(void){
	FILE *loggi = fopen(".log", "r");

	char linha[1000];

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
	char match[500] = "";
	FILE *logger = fopen(".log", "a");
	// Armazena o vencedor
	Ninja *winner = fight(one, two, attribute);
	// Imprime no arquivo ".log" o resultado de UMA luta
	fprintf(logger, "%s x %s\n\tAtributo usado: %d\n", one->nome, two->nome, attribute);
	fprintf(logger, "\tVencedor: %s\n", winner->nome);
	// Configura o matchLoggi
	char att_str[2] = "";
	itoa(attribute, att_str, 10);
	strcat(match, one->nome), strcat(match, " x "), strcat(match, two->nome), strcat(match, "\n\tAtributo usado: ");
	strcat(match, att_str), strcat(match, "\n\tVencedor: "), strcat(match, winner->nome), strcat(match, "\n");
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