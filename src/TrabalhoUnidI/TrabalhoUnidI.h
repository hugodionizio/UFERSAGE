/*
 * TrabalhoUnidI.h
 *
 *  Created on: 24/03/2016
 *      Author: hugo
 */

//#ifndef SRC_TRABALHOUNIDI_TRABALHOUNIDI_H_
#pragma once
#define SRC_TRABALHOUNIDI_TRABALHOUNIDI_H_

#include "../Examples/examples.h"

enum Trabalho_Unidade_I {
#ifdef __linux__
	// Trabalho I - Unidade I
	// Questão do Quadrado (Questão 2 - Parte 1)
	QUESTAOQUADRADO = EXAMPLES_I,

	// Questão da Rasterização (Questão 1 - Parte 2)
	LINHASIMPLES,
	LINHAINCREMENTAL,
	LINHABRESENHAM,
	CIRCULOEQUACAO,
	CIRCULOCOORDPOLAR,
	CIRCULOBRESENHAM,
	PARABOLAEQUACAO,
	PARABOLAINCREMENTAL,
	EXPOENTEINCREMENTAL,

	// Questão do Menu (Questão 2 - Parte 2)
	QUESTAOMENU,

	// Questão das Transformações (Questão 3 - Parte 2)
	TRANSFORMACOES,

	// Questão do Quadrado (Questão 4 - Parte 2)
	PROTECAOTELA,
	FIM_QUESTOES_TRABALHO_I
	// Fim da Unidade I
};

// Questão do Quadrado (Questão 2 - Parte 1)
int mainQuestaoQuadrado(int, char **);

// Questão da Rasterização (Questão 1 - Parte 2)
int mainLinhaSimples(int, char **);
int mainLinhaIncremental(int, char **);
int mainLinhaBresenham(int, char **);
int mainCirculoEquacao(int, char **);
int mainCirculoCoordPolar(int, char **);
int mainCirculoBresenham(int, char **);
int mainParabolaEquacao(int, char **);
int mainParabolaIncremental(int, char **);
int mainExpoenteIncremental(int, char **);

// Questão do Menu (Questão 2 - Parte 2)
int mainQuestaoMenu(int, char **);

// Questão das Transformações (Questão 3 - Parte 2)
int mainTransformacoes(int, char **);

// Questão do Quadrado (Questão 4 - Parte 2)
int mainProtecaoTela(int, char **);

#endif /* SRC_TRABALHOUNIDI_TRABALHOUNIDI_H_ */
