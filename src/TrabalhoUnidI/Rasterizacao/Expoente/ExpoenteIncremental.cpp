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

void displayExpoenteIncremental(void) {
	float a = 2;
	float x = 0;
	float b = -.3;

	/*
	 * Limpar todos os pixels
	 */
	glClear(GL_COLOR_BUFFER_BIT);

	/*
	 * a) Rasterização de linhas dados os pontos inicial e final
	 *	- Algoritmo Simples
	 */
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 1.0, 0.0);
	// y = ax + b
	for (x = -1; x < 1; x+=0.0001) {
		glVertex3f(x, a*x+b, 0.0);
	}
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	glColor3f(0.0, 1.0, 0.0);
	// y = -ax + b
	for (x = -1; x < 1; x+=0.0001) {
		glVertex3f(x, -a*x+b, 0.0);
	}
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 1.0);
	// y = ax
	for (x = -1; x < 1; x+=0.0001) {
		glVertex3f(x, a*x, 0.0);
	}
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
	glutCreateWindow("ExpoenteIncremental");
	initExpoenteIncremental();
	glutDisplayFunc(displayExpoenteIncremental);
	glutMainLoop();
	return 0; /* ISO C requer "main" para retornar int */
}
