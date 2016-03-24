/*
 * ProtecaoTela.cpp
 *
 *  Created on: 17/03/2016
 *      Author: hugo
 */


/*
 * 4. Implementar uma proteção de tela em OpenGL onde a figura
 * geométrica animada fique passeando pela tela e
 * mude a direção do movimento quando colidir com uma das bordas
 *  da janela gráfica (utlize a tranformação de translação);
 *  - Adicionar interação com teclado para aumentar ou diminuir a velocidade de movimentação;
 *	- Adicionar interação com o Mouse afim de abrir menu que permite modificar o objeto animado
 *	 e a cor do mesmo.
 */

#ifdef WINDOWS
# include <windows.h>
# include <gl/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

// Tamanho e posi��o inicial do quadrado
GLfloat x1ProtecaoTela = 100.0f;
GLfloat y1ProtecaoTela = 150.0f;
GLsizei rsizeProtecaoTela = 50;

// Tamanho do incremento nas dire��es x e y
// (n�mero de pixels para se mover a cada
// intervalo de tempo)
GLfloat xstepProtecaoTela = 1.0f;
GLfloat ystepProtecaoTela = 1.0f;

// Largura e altura da janela
GLfloat windowWidthProtecaoTela;
GLfloat windowHeightProtecaoTela;

// Fun��o callback chamada para fazer o desenho
void DesenhaProtecaoTela(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Limpa a janela de visualiza��o com a cor de fundo especificada
	glClear(GL_COLOR_BUFFER_BIT);

	// Especifica que a cor corrente � vermelha
	//         R     G     B
	glColor3f(1.0f, 0.0f, 0.0f);

	// Desenha um quadrado preenchido com a cor corrente
	glBegin(GL_QUADS);
		glVertex2i(x1ProtecaoTela, y1ProtecaoTela + rsizeProtecaoTela);
		glVertex2i(x1ProtecaoTela, y1ProtecaoTela);

		// Especifica que a cor corrente � azul
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2i(x1ProtecaoTela + rsizeProtecaoTela, y1ProtecaoTela);
		glVertex2i(x1ProtecaoTela + rsizeProtecaoTela, y1ProtecaoTela + rsizeProtecaoTela);
	glEnd();

	// Executa os comandos OpenGL
	glutSwapBuffers();
}

// Fun��o callback chamada pela GLUT a cada intervalo de tempo
// (a window n�o est� sendo redimensionada ou movida)
void TimerProtecaoTela(int value) {
	// Muda a dire��o quando chega na borda esquerda ou direita
	if (x1ProtecaoTela > windowWidthProtecaoTela - rsizeProtecaoTela || x1ProtecaoTela < 0)
		xstepProtecaoTela = -xstepProtecaoTela;

	// Muda a dire��o quando chega na borda superior ou inferior
	if (y1ProtecaoTela > windowHeightProtecaoTela - rsizeProtecaoTela || y1ProtecaoTela < 0)
		ystepProtecaoTela = -ystepProtecaoTela;

	// Verifica as bordas.  Se a window for menor e o
	// quadrado sair do volume de visualiza��o
	if (x1ProtecaoTela > windowWidthProtecaoTela - rsizeProtecaoTela)
		x1ProtecaoTela = windowWidthProtecaoTela - rsizeProtecaoTela - 1;

	if (y1ProtecaoTela > windowHeightProtecaoTela - rsizeProtecaoTela)
		y1ProtecaoTela = windowHeightProtecaoTela - rsizeProtecaoTela - 1;

	// Move o quadrado
	x1ProtecaoTela += xstepProtecaoTela;
	y1ProtecaoTela += ystepProtecaoTela;

	// Redesenha o quadrado com as novas coordenadas
	glutPostRedisplay();
	glutTimerFunc(33, TimerProtecaoTela, 1);
}

// Inicializa par�metros de rendering
void InicializaProtecaoTela(void) {
	// Define a cor de fundo da janela de visualiza��o como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Fun��o callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanelaProtecaoTela(GLsizei w, GLsizei h) {
	// Evita a divisao por zero
	if (h == 0)
		h = 1;

	// Especifica as dimens�es da Viewport
	glViewport(0, 0, w, h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de sele��o (left, right, bottom, top)
	if (w <= h) {
		windowHeightProtecaoTela = 250.0f * h / w;
		windowWidthProtecaoTela = 250.0f;
	} else {
		windowWidthProtecaoTela = 250.0f * w / h;
		windowHeightProtecaoTela = 250.0f;
	}

	gluOrtho2D(0.0f, windowWidthProtecaoTela, 0.0f, windowHeightProtecaoTela);
}

// Programa Principal
int mainProtecaoTela(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 350);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Proteção de Tela");
	glutDisplayFunc(DesenhaProtecaoTela);
	glutReshapeFunc(AlteraTamanhoJanelaProtecaoTela);
	glutTimerFunc(33, TimerProtecaoTela, 1);
	InicializaProtecaoTela();
	glutMainLoop();
}
