/*
 * hello.c
 *
 * Programa em OpenGL simples usando GLUT
 *
 *  Created on: 16/02/2016
 *      Author: hugo
 */
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

using namespace std;

void displayMouse(void) {
	float i = 0;
	float R = 1;
	/*
	 * Limpar todos os pixels
	 */
	glClear(GL_COLOR_BUFFER_BIT);

	/*
	 * Desenhar polígono em branco (retângulo) com cantos em
	 *  (0.25, 0.25, 0.0) e (0.75, 0.75, 0.0)
	 */
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 1.0);

	// y1 = sqrt(R^2-x^2)
	// y2 = -sqrt(R^2-x^2)

	for (i = -1; i < 1; i+=0.0001) {
		glVertex3f(i, sqrt(R*R-i*i), 0.0);
		glVertex3f(i, -sqrt(R*R-i*i), 0.0);
	}
	glColor3f(0.0, 1.0, 0.0);
	glEnd();

	/*
	 * Sem pausa!
	 * Iniciar processo com rotinas OpenGL de buffer
	 */
	glutSwapBuffers();
}

void newDisplayMouse(void) {
	float i = 0;
	float R = 1;
	/*
	 * Limpar todos os pixels
	 */
	glClear(GL_COLOR_BUFFER_BIT);

	/*
	 * Desenhar polígono em branco (retângulo) com cantos em
	 *  (0.25, 0.25, 0.0) e (0.75, 0.75, 0.0)
	 */
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);

	// y1 = sqrt(R^2-x^2)
	// y2 = -sqrt(R^2-x^2)

	for (i = -1; i < 1; i+=0.0001) {
		glVertex3f(i, sqrt(R*R-i*i), 0.0);
		glVertex3f(i, -sqrt(R*R-i*i), 0.0);
	}
	glColor3f(1.0, 1.0, 1.0);
	glEnd();

	/*
	 * Sem pausa!
	 * Iniciar processo com rotinas OpenGL de buffer
	 */
	glutSwapBuffers();
}

void initMouse(void) {
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

// glutKeyboardFunc

void testeMouse(int button, int state, int x, int y) {

	if (button == GLUT_RIGHT_BUTTON)
//		cout << "Testando botões do mouse..." << endl;
		if(state == GLUT_UP) {
			newDisplayMouse();
			glutPostRedisplay();
		}
}

/*
 * Declarar tamanho de janela inicial, posição, e modo de tela
 * (buffer simples e RGBA). Abrir janela com "hello"
 * nesta barra de título. Chamar rotinas de inicialização.
 * Registrar função de chamada de retorno para gráficos na tela.
 * Entrar como laço principal e eventos d processo.
 */
int mainMouse(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Olá OpenGL");
	initMouse();
	glutMouseFunc(testeMouse);
	glutDisplayFunc(displayMouse);
	glutMainLoop();
	return 0; /* ISO C requer "main" para retornar int */
}
