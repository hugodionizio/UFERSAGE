/*
 * helo.cpp
 *
 *  Created on: 20/03/2016
 *      Author: hugo
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

void displayHello(void) {
	/*
	 * Limpar todos os pixels
	 */
	glClear(GL_COLOR_BUFFER_BIT);

	/*
	 * Desenhar polígono em branco (retângulo) com cantos em
	 *  (0.25, 0.25, 0.0) e (0.75, 0.75, 0.0)
	 */
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex3f(.25, .25, 0.0);
		glVertex3f(.75, .25, 0.0);
		glVertex3f(.75, .75, 0.0);
		glVertex3f(.25, .75, 0.0);
	glEnd();

	/*
	 * Sem pausa!
	 * Iniciar processo com rotinas OpenGL de buffer
	 */
	glFlush();
}

void initHello(void) {
	/*
	 * selecionar cor de limpeza (fundo)
	 */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*
	 * Inicializar valores de visualização
	 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);
}

/*
 * Declarar tamanho de janela inicial, posição, e modo de tela
 * (buffer simples e RGBA). Abrir janela com "hello"
 * nesta barra de título. Chamar rotinas de inicialização.
 * Registrar função de chamada de retorno para gráficos na tela.
 * Entrar como laço principal e eventos d processo.
 */
int mainHello(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("hello");
	initHello();
	glutDisplayFunc(displayHello);
	glutMainLoop();
	return 0; /* ISO C requer "main" para retornar int */
}



