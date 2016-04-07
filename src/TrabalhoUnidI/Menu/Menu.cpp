/*
 * Menu.cpp
 *
 *  Created on: 16/03/2016
 *      Author: hugo
 */

/*
 * 2. Construa um menu contendo opções para objetos e cores.
 * A opção objetos possibilita a exibição de um determinado
 * objejo na cena.
 * As opções são:
 * 		triângulo,
 * 		quadrado,
 * 		pentágono e
 * 		hexágono.
 * Na opção cores deve ser possível escolher uma cor para o
 *  objeto mostrado.
 * */

#ifdef WINDOWS
# include <windows.h>
# include <gl/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif
#include <string.h>
#include <stdio.h>
#include <ft2build.h>
#include <freetype2/freetype.h>
#include <config/ftheader.h>
#include <FTGL/ftgl.h>
#include <FTGL/FTGLPixmapFont.h>
#include "Menu.h"

// Constantes
enum {
	QUADRADO = 1, TRIANGULO, LOSANGO, PENTAGONO, HEXAGONO
};

// Variáveis
char textoQuestaoMenu[30];
GLfloat win_questao_menu, rQuestaoMenu, gQuestaoMenu, bQuestaoMenu;
GLint view_w_questao_menu, view_h_questao_menu, primitivaQuestaoMenu;

int testeFTGL() {
	// Create a pixmap font from a TrueType file.
	FTGLPixmapFont font("/home/user/Arial.ttf");

	// If something went wrong, bail out.
	if (font.Error())
		return -1;

	// Set the font size and render a small text.
	font.FaceSize(72);
	font.Render("Hello World!");

	return 0;
}

// Função que desenha um losango
void DesenhaLosangoQuestaoMenu(void) {
	glBegin (GL_POLYGON);
	glVertex2f(-25.0f, 0.0f);
	glVertex2f(0.0f, 25.0f);
	glVertex2f(25.0f, 0.0f);
	glVertex2f(0.0f, -25.0f);
	glEnd();
}

// Desenha um texto na janela GLUT
void DesenhaTextoQuestaoMenu(char *string) {
	glPushMatrix();
	// Posição no universo onde o texto será colocado
	glRasterPos2f(-win_questao_menu,
			win_questao_menu - (win_questao_menu * 0.08));
	// Exibe caracter a caracter
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *string++);
	glPopMatrix();
}

// Função callback chamada para fazer o desenho
void DesenhaQuestaoMenu(void) {
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

	glClear (GL_COLOR_BUFFER_BIT);

	// Define a cor corrente
	glColor3f(rQuestaoMenu, gQuestaoMenu, bQuestaoMenu);

	testeFTGL();

	// Desenha uma primitiva
	switch (primitivaQuestaoMenu) {
	case QUADRADO:
		DesenhaQuadradoQuestaoMenu();
		break;
	case TRIANGULO:
		DesenhaTrianguloQuestaoMenu();
		break;
	case LOSANGO:
		DesenhaLosangoQuestaoMenu();
		break;
	case PENTAGONO:
		DesenhaPentagonoQuestaoMenu();
		break;
	case HEXAGONO:
		DesenhaHexagonoQuestaoMenu();
		break;
	}

	// Exibe a posição do mouse na janela
	glColor3f(1.0f, 1.0f, 1.0f);
	DesenhaTextoQuestaoMenu(textoQuestaoMenu);

	glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void InicializaQuestaoMenu(void) {
	// Define a cor de fundo da janela de visualização como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	win_questao_menu = 150.0f;
	primitivaQuestaoMenu = QUADRADO;
	rQuestaoMenu = 0.0f;
	gQuestaoMenu = 0.0f;
	bQuestaoMenu = 1.0f;
	strcpy(textoQuestaoMenu, "(0,0)");
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamJanQuestaoMenu(GLsizei w, GLsizei h) {
	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);
	view_w_questao_menu = w;
	view_h_questao_menu = h;

	// Inicializa o sistema de coordenadas
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-win_questao_menu, win_questao_menu, -win_questao_menu,
			win_questao_menu);
}

// Função callback chamada sempre que o mouse é movimentado
// sobre a janela GLUT com um botão pressionado
void MovMouseBotaoPressQuestMenu(int x, int y) {
	sprintf(textoQuestaoMenu, "Botao pressionado (%d,%d)", x, y);
	glutPostRedisplay();
}

// Função callback chamada sempre que o mouse é movimentado
// sobre a janela GLUT
void MoveMouseQuestaoMenu(int x, int y) {
	sprintf(textoQuestaoMenu, "(%d,%d)", x, y);
	glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos do teclado
// para teclas especiais, tais como F1, PgDn e Home
void TeclasEspeciaisQuestaoMenu(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		win_questao_menu -= 10;
		if (win_questao_menu < 10)
			win_questao_menu = 10;
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-win_questao_menu, win_questao_menu, -win_questao_menu,
				win_questao_menu);
	}
	if (key == GLUT_KEY_DOWN) {
		win_questao_menu += 10;
		if (win_questao_menu > 500)
			win_questao_menu = 500;
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-win_questao_menu, win_questao_menu, -win_questao_menu,
				win_questao_menu);
	}
	glutPostRedisplay();
}

// Gerenciamento do menu com as opções de cores
void QuestaoMenuCor(int op) {
	switch (op) {
	case 0:
		rQuestaoMenu = 1.0f;
		gQuestaoMenu = 0.0f;
		bQuestaoMenu = 0.0f;
		break;
	case 1:
		rQuestaoMenu = 0.0f;
		gQuestaoMenu = 1.0f;
		bQuestaoMenu = 0.0f;
		break;
	case 2:
		rQuestaoMenu = 0.0f;
		gQuestaoMenu = 0.0f;
		bQuestaoMenu = 1.0f;
		break;
	}
	glutPostRedisplay();
}

// Gerenciamento do menu com as opções de cores
void QuestaoMenuPrimitiva(int op) {
	switch (op) {
	case 0:
		primitivaQuestaoMenu = QUADRADO;
		break;
	case 1:
		primitivaQuestaoMenu = TRIANGULO;
		break;
	case 2:
		primitivaQuestaoMenu = LOSANGO;
		break;
	case 3:
		primitivaQuestaoMenu = PENTAGONO;
		break;
	case 4:
		primitivaQuestaoMenu = HEXAGONO;
	}
	glutPostRedisplay();
}

// Gerenciamento do menu principal
void QuestaoMenuPrincipal(int op) {
}

// Criacao do Menu
void CriaQuestaoMenu() {
	int menu, submenu1, submenu2;

	submenu1 = glutCreateMenu(QuestaoMenuCor);
	glutAddMenuEntry("Vermelho", 0);
	glutAddMenuEntry("Verde", 1);
	glutAddMenuEntry("Azul", 2);

	submenu2 = glutCreateMenu(QuestaoMenuPrimitiva);
	glutAddMenuEntry("Quadrado", 0);
	glutAddMenuEntry("Triangulo", 1);
	glutAddMenuEntry("Losango", 2);
	glutAddMenuEntry("Penta'gono", 3);
	glutAddMenuEntry("Hexagono", 4);

	menu = glutCreateMenu(QuestaoMenuPrincipal);
	glutAddSubMenu("Cor", submenu1);
	glutAddSubMenu("Primitivas", submenu2);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouseQuestaoMenu(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN)
			CriaQuestaoMenu();

	glutPostRedisplay();
}

// Programa Principal
int mainQuestaoMenu(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(350, 300);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Menu de Geometrias");
	glutDisplayFunc(DesenhaQuestaoMenu);
	glutReshapeFunc(AlteraTamJanQuestaoMenu);
	glutMotionFunc(MovMouseBotaoPressQuestMenu);
	glutPassiveMotionFunc(MoveMouseQuestaoMenu);
	glutMouseFunc(GerenciaMouseQuestaoMenu);
	glutSpecialFunc(TeclasEspeciaisQuestaoMenu);
	InicializaQuestaoMenu();
	glutMainLoop();

	return (0);
}
