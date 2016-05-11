/*
 * Main.h
 *
 *  Created on: 11/05/2016
 *      Author: hugo
 */

#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include "TrabalhoUnidIII/TrabalhoUnidIII.h"

enum Implementacoes {
	// Adicionais
	VORTEX = NUM_QUESTOES_TRABALHO_III,
	NUM_IMPLEMENTACOES
};

typedef int (*PFunc)(int, char**); /* O tipo PFunc é ponteiro p/ função void */

void executarPFunc(int, int, char **);
char *retornarPFunc(int pos);
bool lerPFunc(int, int, char **);

#endif /* SRC_MAIN_H_ */
