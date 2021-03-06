/*
 *   Copyright (C) 2008, 2008 Rafael Siqueira Telles Vieira
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *   See the GNU General Public License for more details.
 *
 *   License: http://www.lia.ufc.br/~rafaelstv/licenca_GPL_pt.txt
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software Foundation,
 *   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 *
 */

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define LARGURA 500
#define ALTURA 500

float pBezier[4][2];
int indiceBezier;

// Função callback chamada para gerenciar eventos do mouse
void Inicia() {

	pBezier[0][0] = -1.0f; //ponto 1 x
	pBezier[0][1] = 0.0f; //ponto 1 y

	pBezier[1][0] = -0.5f;
	pBezier[1][1] = -0.5f;

	pBezier[2][0] = 0.5f;
	pBezier[2][1] = 0.5f;

	pBezier[3][0] = 1.0f;
	pBezier[3][1] = 0.0f;
}

void atualiza(int x, int y) {
	float cx, cy;

	cx = ((float) (2.0f * x) / (float) LARGURA) - 1.0f;
	cy = ((float) (2.0f * y) / (float) ALTURA) - 1.0f;
	cy *= -1.0f;

	pBezier[indiceBezier][0] = cx;
	pBezier[indiceBezier][1] = cy;
	glutPostRedisplay();
}

void escolha(int botao, int estado, int x, int y) {
	if ((botao == GLUT_LEFT_BUTTON) && (estado == GLUT_DOWN))
		indiceBezier = 1;

	if ((botao == GLUT_RIGHT_BUTTON) && (estado == GLUT_DOWN))
		indiceBezier = 2;

	atualiza(x, y);
}

void captura(int x, int y) {
	atualiza(x, y);
}

float fatorial(int a) {
	int i;
	float produto;

	produto = 1.0f;
	for (i = a; i > 0; i--)
		produto *= (float) i;
	return produto;
}

float combinacao(int a, int b) {
	return fatorial(b) / (fatorial(a) * fatorial(b - a));
}

float binomio(int n, int k) {
	return fatorial(n) / (fatorial(k) * fatorial(n - k));
}

void exibe(void) {
	GLint i;
	GLfloat u, x, y;

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < 4; i++)
		glVertex2f(pBezier[i][0], pBezier[i][1]);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS);
	for (u = 0.0f; u <= 1.0f; u += 0.001f) {
		x = 0.0f;
		y = 0.0f;
		for (i = 0; i < 4; i++) {
			x += combinacao(i, 3) * pow(u, i) * pow(1.0f - u, 3 - i)
					* pBezier[i][0];
			y += combinacao(i, 3) * pow(u, i) * pow(1.0f - u, 3 - i)
					* pBezier[i][1];
		}
		glVertex2f(x, y);
	}
	glEnd();

	glFlush();
}

int mainBezier(int argc, char** argv) {
	Inicia();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ALTURA, LARGURA);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("Desenhando uma curva de Bézier");
	glutDisplayFunc(exibe);
	glutMouseFunc(escolha);
	glutMotionFunc(captura);
	glutMainLoop();

	return 0;
}
