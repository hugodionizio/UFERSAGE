/*
 * TrabalhoUnidII.h
 *
 *  Created on: Mar 30, 2016
 *      Author: hugo
 */

#ifndef TRABALHOUNIDII_H_
#define TRABALHOUNIDII_H_

#include "../Examples/examples_II.h" // Para incrementar MALHA_PLY com NUM_EXAMPLES

enum Trabalho_Unidade_II {
#ifdef __linux__
	// Unidade II
	// Examples (redbook)

	// Fim da Unidade II

	// Trabalho 2 - Unidade II
	PLY = EXAMPLES_II,
#endif

	MALHA_PLY,
	MALHA = MALHA_PLY,
	FIM_QUESTOES_TRABALHO_II
};

int mainMalha(int, char **);
int mainPly(int, char **);

// Funções
void desenharMalha(void);
void desenhaCubo(void);

#endif /* TRABALHOUNIDII_H_ */
