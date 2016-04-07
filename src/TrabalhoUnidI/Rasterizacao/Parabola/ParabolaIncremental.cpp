/*
 * ParabolaIncremental.cpp
 *
 *  Created on: 16/03/2016
 *      Author: hugo
 */

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#include <iostream>
using namespace std;

#define LARGURA_JANELA 250
#define ALTURA_JANELA 250
#define XMAXIMO (LARGURA_JANELA/2)
#define YMAXIMO	(ALTURA_JANELA/2)

void displayParabolaIncremental(void) {
	float a = 1, b = 0, c = 0;
	float x0 = -124, y0 = 1, x1 = 120, y1 = 50, x, y, m, yinc;

	x0 = x0 / XMAXIMO;
	y0 = y0 / YMAXIMO;
	x1 = x1 / XMAXIMO;
	y1 = y1 / YMAXIMO;
	m = (y1 - y0) / (x1 - x0);

	/*
	 * Limpar todos os pixels
	 */
	glClear(GL_COLOR_BUFFER_BIT);

	/*
	 * c) Implemente a rasterização de uma parábola da forma y = a*x*x + b*x + c, em que a, b e c são
	 parâmetros reais (dados um x inicial e um x final).
	 - Utilizando o algoritmo incremental criado em sala
	 */
	x = x0;
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 1.0, 0.0);
	do {
		y = a * x * x + b * x + c;
		yinc = floor(y * YMAXIMO + 0.2) / YMAXIMO;
		glVertex3f(x, yinc, 0.0);
		cout << x << ", " << yinc << endl;
		x = x + 0.01f / XMAXIMO;
	} while (x <= x1);
	glEnd();

	x = x0;
	a = 2;
	b = -2;
	c = -.5;
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	glColor3f(0.0, 1.0, 1.0);
	do {
		y = a * x * x + b * x + c;
		yinc = floor(y * YMAXIMO + 0.2) / YMAXIMO;
		glVertex3f(x, yinc, 0.0);
		cout << x << ", " << yinc << endl;
		x = x + 0.01f / XMAXIMO;
	} while (x <= x1);
	glEnd();

	x = x0;
	a = .5;
	b = .25;
	c = 0;
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 1.0);
	do {
		y = a * x * x + b * x + c;
		yinc = floor(y * YMAXIMO + 0.2) / YMAXIMO;
		glVertex3f(x, yinc, 0.0);
		cout << x << ", " << yinc << endl;
		x = x + 0.01f / XMAXIMO;
	} while (x <= x1);
	glEnd();
	/*
	 * Sem pausa!
	 * Iniciar processo com rotinas OpenGL de buffer
	 */
	glutSwapBuffers();
}

void initParabolaIncremental(void) {
	/* selecionar cor de limpeza (fundo)
	 *
	 */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* Inicializar valores de visualização
	 *
	 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
}

/*
 * Declarar tamanho de janela inicial, posição, e modo de tela
 * (buffer simples e RGBA). Abrir janela com "Linha Simples"
 * nesta barra de título. Chamar rotinas de inicialização.
 * Registrar função de chamada de retorno para gráficos na tela.
 * Entrar como laço principal e eventos d processo.
 */
int mainParabolaIncremental(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Parábola Incremental");
	initParabolaIncremental();
	glutDisplayFunc(displayParabolaIncremental);
	glutMainLoop();
	return 0; /* ISO C requer "main" para retornar int */
}
