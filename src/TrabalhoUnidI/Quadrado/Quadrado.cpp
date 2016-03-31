// Quadrado.cpp - Isabel H. Manssour
// Um programa OpenGL simples que desenha um
// quadrado em  uma janela GLUT.
// Este código está baseado no GLRect.c, exemplo
// disponível no livro "OpenGL SuperBible",
// 2nd Edition, de Richard S. e Wright Jr.

/*
 *
 (a) altere, de forma aleatória, a cor de fundo, quando o botão esquerdo do mouse é clicado.
 (b) altere, de forma aletória, a cor do objeto quando o botão direito do mouse é clicado.
 (c) aplique a alteração de cor do objeto através do teclado:
 - apertando 'r' o objeto fica vermelho
 - apertando 'g' o objeto fica verde
 - apertando 'b' o objeto fica azul
 - apertando 'c' o objeto fica ciano
 - apertando 'm' o objeto fica magenta
 - apertando 'y o objeto fica amarelo
 *
 */

#include <GL/freeglut_std.h>

#ifdef WINDOWS
# include <windows.h>
# include <gl/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

#include <random>
#include <iostream>
#include "../../Exemplos/Exemplos.h"

using namespace std;

// Função callback chamada para fazer o desenho
void DesenhaQuadradoInterativo(void) {
//	float v[] = { 1.0f, 0.0f, 0.0f };
//	Desenha(v);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

	// Limpa a janela de visualização com a cor de fundo especificada
	glClear (GL_COLOR_BUFFER_BIT);

	// Especifica que a cor corrente é vermelha
	//         R     G     B
	//glColor3f(1.0, 0.0, 0.0);

	// Desenha um quadrado preenchido com a cor corrente
	glBegin (GL_QUADS);
	glVertex2i(100, 150);
	glVertex2i(100, 100);
	// Especifica que a cor corrente é azul
	//glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2i(150, 100);
	glVertex2i(150, 150);
	glEnd();

	// Executa os comandos OpenGL
	glFlush();

}

// Verifica qual botão do mouse é pressionado
void testeBotaoMouse(int button, int state, int x, int y) {

	if (state == GLUT_UP) {
		random_device rd;
		mt19937 mt(rd());
		uniform_real_distribution<double> dist(0, 1);
		if (button == GLUT_LEFT_BUTTON) {
			// (a) altere, de forma aleatória, a cor de fundo, quando o botão esquerdo do mouse é clicado.
			glClearColor(dist(mt), dist(mt), dist(mt), dist(mt));
		} else if (button == GLUT_RIGHT_BUTTON) {
			// (b) altere, de forma aletória, a cor do objeto quando o botão direito do mouse é clicado.
			glColor3f(dist(mt), dist(mt), dist(mt));
		}
	}
	glutPostRedisplay();
}

// (c) aplique a alteração de cor do objeto através do teclado:
void alteraCorObjetoTeclado(unsigned char key, int x, int y) {

	switch (key) {
		// - apertando 'r' o objeto fica vermelho
	case 'R':
	case 'r':
		glColor3f(1.0f, 0.0f, 0.0f);
		break;

		// - apertando 'g' o objeto fica verde
	case 'G':
	case 'g':
		glColor3f(0.0f, 1.0f, 0.0f);
		break;

		// - apertando 'b' o objeto fica azul
	case 'B':
	case 'b':
		glColor3f(0.0f, 0.0f, 1.0f);
		break;

		// - apertando 'c' o objeto fica ciano
	case 'C':
	case 'c':
		glColor3f(0.0f, 1.0f, 1.0f);
		break;

		// - apertando 'm' o objeto fica magenta
	case 'M':
	case 'm':
		glColor3f(1.0f, 0.0f, 1.0f);
		break;

		// - apertando 'y o objeto fica amarelo
	case 'Y':
	case 'y':
		glColor3f(1.0f, 1.0f, 0.0f);
		break;
	}

	glutPostRedisplay();
}

// Inicializa parâmetros de rendering
void Inicializa(void) {
// Define a cor de fundo da janela de visualização como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h) {
// Evita a divisao por zero
	if (h == 0)
		h = 1;

// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);

// Inicializa o sistema de coordenadas
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

// Estabelece a janela de seleção (left, right, bottom, top)
	if (w <= h)
		gluOrtho2D(0.0f, 250.0f, 0.0f, 250.0f * h / w);
	else
		gluOrtho2D(0.0f, 250.0f * w / h, 0.0f, 250.0f);
}

// Programa Principal
int mainQuestaoQuadrado(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 350);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Quadrado Interativo");
	glutDisplayFunc(DesenhaQuadradoInterativo);
	glutReshapeFunc(AlteraTamanhoJanela);
	glutKeyboardFunc(alteraCorObjetoTeclado);
	glutMouseFunc(testeBotaoMouse);
	Inicializa();
	glutMainLoop();

	return (0);
}
