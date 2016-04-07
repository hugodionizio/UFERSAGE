/*
 * TrabalhoUnidII.h
 *
 *  Created on: Mar 30, 2016
 *      Author: hugo
 */

#ifndef TRABALHOUNIDII_H_
#define TRABALHOUNIDII_H_

#include "../Examples/examples.h" // Para incrementar MALHA_PLY com NUM_EXAMPLES

enum TrabalhoII {
	MALHA_PLY = NUM_EXAMPLES + 1, NUM_QUESTOES
};

int mainMalha(int, char **);
int mainPly(int, char **);

// Funções
void desenharMalha(void);

#endif /* TRABALHOUNIDII_H_ */
