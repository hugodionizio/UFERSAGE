/*
 * RasterizacaoSimples.cpp
 *
 *  Created on: 15/03/2016
 *      Author: hugo
 */

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

void displayParabolaEquacao(void) {
	float a = 1;
	float x0 = -1;
	float x1 = 1;
	float x = x0;
	float b = 0;
	float c = 0;

	/*
	 * Limpar todos os pixels
	 */
	glClear(GL_COLOR_BUFFER_BIT);

	/*
	 * c) Implemente a rasterização de uma parábola da forma y = a*x*x + b*x + c, em que a, b e c são
	 parâmetros reais (dados um x inicial e um x final).
	 - Utilizando a equação da parábola
	 */
	glColor3f(1.0, 0.0, 0.0); // Vermelho
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 0.0);
	for (x = x0; x <= x1; x += 0.0001) {
		glVertex3f(x, a * x * x + b * x + c, 0.0);
	}
	glEnd();

	a = 2;
	b = -2;
	c = -.5;
	glColor3f(0.0, 1.0, 0.0); // Verde
	glBegin(GL_POINTS);
	glColor3f(0.0, 1.0, 0.0);
	for (x = x0; x <= x1; x += 0.0001) {
		glVertex3f(x, a * x * x + b * x + c, 0.0);
	}
	glEnd();

	a = .5;
	b = .25;
	c = 0;
	glColor3f(0.0, 0.0, 1.0); // Azul
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 1.0);
	for (x = x0; x <= x1; x += 0.0001) {
		glVertex3f(x, a * x * x + b * x + c, 0.0);
	}
	glEnd();
	/*
	 * Sem pausa!
	 * Iniciar processo com rotinas OpenGL de buffer
	 */
	glutSwapBuffers();
}

void initParabolaEquacao(void) {
	/* selecionar cor de limpeza (fundo)
	 *
	 */
	glClearColor(1.0, 1.0, 1.0, 0.0);

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
int mainParabolaEquacao(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Equação da Parábola");
	initParabolaEquacao();
	glutDisplayFunc(displayParabolaEquacao);
	glutMainLoop();
	return 0; /* ISO C requer "main" para retornar int */
}
