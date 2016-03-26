/*
 * LinhaIncremental.cpp
 *
 *  Created on: 16/03/2016
 *      Author: hugo
 */

/*
 * a) Rasterização de linhas dados os pontos inicial e final
 *	- Algoritmo Incremental
 */

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

#define LARGURA_JANELA 250
#define ALTURA_JANELA 250
#define XMAXIMO (LARGURA_JANELA/2)
#define YMAXIMO	(ALTURA_JANELA/2)

using namespace std;

void displayLinhaIncremental(void) {
	float x0 = 1, y0 = 1, x1 = 120, y1 = 50, x, y, m;

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
	 * a) Rasterização de linhas dados os pontos inicial e final
	 *	- Algoritmo Incremental
	 */
	cout << "Algoritmo Incremental da Reta (verde):" << endl;
	x = x0;
	y = y0;
	float yinc;
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS);
		glColor3f(0.0, 1.0, 0.0);
		do {
			yinc = floor(0.4f *(y + 0.5)) / YMAXIMO;
			glVertex3f(x, yinc, 0.0);
			cout << x << ", " << yinc << endl;
			x = x + 0.4f / XMAXIMO;
			y = y + m;
		} while (x <= x1);
	glEnd();

	/*
	 * Sem pausa!
	 * Iniciar processo com rotinas OpenGL de buffer
	 */
	glutSwapBuffers();
}

void initLinhaIncremental(void) {
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
 * (buffer simples e RGBA). Abrir janela com "Linha Incremental"
 * nesta barra de título. Chamar rotinas de inicialização.
 * Registrar função de chamada de retorno para gráficos na tela.
 * Entrar como laço principal e eventos d processo.
 */
int mainLinhaIncremental(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Linha Incremental");
	initLinhaIncremental();
	glutDisplayFunc(displayLinhaIncremental);
	glutMainLoop();
	return 0; /* ISO C requer "main" para retornar int */
}
