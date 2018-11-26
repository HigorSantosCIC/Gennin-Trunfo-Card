#include <string.h>
#include "tree.h"
#include "ninja.h"

int getAtt(Ninja *ninja, int attribute){
	switch(attribute){
		case 1: return ninja->ninjutsu;
		case 2: return ninja->genjutsu;
		case 3: return ninja->taijutsu;
		case 4: return ninja->defesa;
		default:;
	}
	return -1;
}

char * getAttName(int attribute){
	char *att_name = (char *) malloc(sizeof(char) * 16);
	strcpy(att_name, "Inválido");
	switch(attribute){
		case 1: strcpy(att_name, "ninjutsu");
			break;
		case 2: strcpy(att_name, "genjutsu");
			break;
		case 3: strcpy(att_name, "taijutsu");
			break;
		case 4: strcpy(att_name, "defesa");
			break;
		default:;
	}
	return att_name;
}

int getValue(int reset){
	static int value = 0;
	if(reset){
		value = 0;
		return -1;
	}else{
		value++;
	}
	return value;
}