/*
 * ExpoenteIncremental.cpp
 *
 *  Created on: 16/03/2016
 *      Author: hugo
 */

/*
 * d) Crie um algoritmo incremental para curvas dadas pela
 * 		equação y = a exp(b*x), em que a e b são
 * 		parâmetros reais (dados um x inicial e um x final).
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

void displayExpoenteIncremental(void) {
	float a = .067, b = 2.7172, c = 0;
	float x0 = -125, y0, x1 = 125, y1 = 50, x, y, m, yinc;

	x0 = x0 / XMAXIMO;
	x1 = x1 / XMAXIMO;
	/*
	 * Limpar todos os pixels
	 */
	glClear(GL_COLOR_BUFFER_BIT);

	/*
	 * d) Crie um algoritmo incremental para curvas dadas pela
	 * 		equação y = a exp(b*x), em que a e b são
	 * 		parâmetros reais (dados um x inicial e um x final).
	 */
	x = x0;
	glColor3f(1.0, 1.0, 0.0); // Vermelho
	glBegin(GL_POINTS);
	glColor3f(1.0, 1.0, 0.0);
		do {
			y = a*exp(b*x);
			yinc = floor(y*YMAXIMO+0.5)/YMAXIMO;
			glVertex3f(x, yinc, 0.0);
			cout << x << ", " << yinc << endl;
			x = x + 0.01f / XMAXIMO;
		} while (x <= x1);
	glEnd();

	x = x0;
	a = -.067;
	b = 2.7172;
	glColor3f(0.0, 1.0, 0.0); // Verde
	glBegin(GL_POINTS);
	glColor3f(0.0, 1.0, 0.0);
		do {
			y = a*exp(b*x);
			yinc = floor(y*YMAXIMO+0.5)/YMAXIMO;
			glVertex3f(x, yinc, 0.0);
//			cout << x << ", " << yinc << endl;
			x = x + 0.01f / XMAXIMO;
		} while (x <= x1);
	glEnd();

	x = x0;
	a = .067;
	b = -2.7172;
	glColor3f(0.0, 0.0, 1.0); // Azul
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 1.0);
		do {
			y = a*exp(b*x);
			yinc = floor(y*YMAXIMO)/YMAXIMO;
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

void initExpoenteIncremental(void) {
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
int mainExpoenteIncremental(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Expoente Incremental");
	initExpoenteIncremental();
	glutDisplayFunc(displayExpoenteIncremental);
	glutMainLoop();
	return 0; /* ISO C requer "main" para retornar int */
}
