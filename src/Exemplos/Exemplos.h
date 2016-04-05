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
	// Exemplos (Manssour)
	PRIMEIRO_PROGRAMA,
	ANIMA,
	INTERACAO,
	NUM_PRIM_EXEMPLOS,
	QUADRADO,
	TRIANGULO,
	LOSANGO,
	PRIMITIVAS,
	TEAPOT3D,
	ILUMINACAO,
	NUM_EXEMPLOS
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
