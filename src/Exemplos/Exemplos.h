/*
 * Mouse.h
 *
 *  Created on: 28/02/2016
 *      Author: hugo
 */

#ifndef EXEMPLOS_MOUSE_H_
#define EXEMPLOS_MOUSE_H_

enum Exemplo {
	// Unidade I
	// Exercícios
	AULA01,
	MOUSE,

	// Exemplo (Professor Leandro Souza)
	EXEMPLOCALLBACKS,

	// Exemplos (Manssour)
	PRIMEIRO_PROGRAMA,
	QUADRADO_COLORIDO,
	ANIMA,
	INTERACAO,
	MENU,
	TEAPOT3D,
	ILUMINACAO,
	NUM_PRIM_EXEMPLOS,
	NUM_EXEMPLOS = NUM_PRIM_EXEMPLOS
};

enum {
	QUADRADO, TRIANGULO, LOSANGO, PENTAGONO, HEXAGONO, PRIMITIVAS
};


// Exercícios
int mainAula01(int, char**);
int mainMouse(int, char **);

// Exemplo (Professor Leandro Souza)
int mainExemploCallbacks(int, char**);

// Exemplos (Manssour)
int mainPrimeiroPrograma(int, char **);
int mainQuadrado(int, char **);
int mainAnima(int, char **);
int mainInteracao(int, char **);
int mainMenu(int, char **);
int mainTeaPot3D(int, char **);
int mainIluminacao(int, char **);

// Funções
void DesenhaPrimeiroPrograma(void);
void DesenhaAnima(void);
void DesenhaInteracao(void);
void Timer(int);
//void AlteraTamanhoJanelaAnima(GLsizei w, GLsizei h);
void DesenhaTeaPot3D(void);
void DesenhaIluminacao(void);

#endif /* EXEMPLOS_MOUSE_H_ */
