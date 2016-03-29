/*
 * CirculoCoordPolar.cpp
 *
 *  Created on: 16/03/2016
 *      Author: hugo
 */

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

void displayCirculoCoordPolar(void) {
	float i = 0;
	float R = 1;
	float theta = 0;
	/*
	 * Limpar todos os pixels
	 */
	glClear(GL_COLOR_BUFFER_BIT);

	/*
	 * b) Rasterização de cículos, dado o raio de entrada.
	 * - Utilizando coordenadas polares.
	 */
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 1.0, 0.0);
	// x = xc + R*cos(theta)
	// y1 = yc + R*sin(theta)
	// y2 = -(yc + R*sin(theta))
	for (theta = 180; theta >= 0; theta-=.005) {
		glVertex3f(R*cos(theta), R*sin(theta), 0.0);
		glVertex3f(R*cos(theta), -R*sin(theta), 0.0);
		cout << "[" << R*cos(theta) << ", " << R*sin(theta) << "] [";
		cout << R*cos(theta) << ", " << -R*sin(theta) << "]" << endl;
	}
	glEnd();

	/*
	 * Sem pausa!
	 * Iniciar processo com rotinas OpenGL de buffer
	 */
	glutSwapBuffers();
}

void initCirculoCoordPolar(void) {
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
 * (buffer simples e RGBA). Abrir janela com "hello"
 * nesta barra de título. Chamar rotinas de inicialização.
 * Registrar função de chamada de retorno para gráficos na tela.
 * Entrar como laço principal e eventos d processo.
 */
int mainCirculoCoordPolar(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(LARGURA_JANELA, ALTURA_JANELA);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Círculo com Coordenadas Polares");
	initCirculoCoordPolar();
	glutDisplayFunc(displayCirculoCoordPolar);
	glutMainLoop();
	return 0; /* ISO C requer "main" para retornar int */
}
