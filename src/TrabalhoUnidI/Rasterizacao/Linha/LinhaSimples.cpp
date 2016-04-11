/*
 * LinhaSimples.cpp
 *
 *  Created on: 15/03/2016
 *      Author: hugo
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

void displayLinhaSimples(void) {
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
	 *	- Algoritmo Simples
	 */
	cout << "Algoritmo Simples da Reta (vermelho):" << endl;
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 0.0);
	for (x = x0; x < x1; x += 0.4f / XMAXIMO) {
		y = y0
				+ floor(((XMAXIMO + YMAXIMO) / 2) * m * (x - x0) + .5)
						/ ((XMAXIMO + YMAXIMO) / 2);
		// cout << x << ", " << y << endl;
		glVertex3f(x, y, 0.0);
	}
	glEnd();

	/*
	 * Sem pausa!
	 * Iniciar processo com rotinas OpenGL de buffer
	 */
	glutSwapBuffers();
}

void initLinhaSimples(void) {
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
int mainLinhaSimples(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(LARGURA_JANELA, ALTURA_JANELA);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Linha Simples ou Imediato");
	initLinhaSimples();
	glutDisplayFunc(displayLinhaSimples);
	glutMainLoop();
	return 0; /* ISO C requer "main" para retornar int */
}
