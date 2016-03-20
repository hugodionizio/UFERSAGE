// Menu.c - Isabel H. Manssour
// Um programa OpenGL simples que exemplifica
// como exibir textos e utilizar menus e fun��es 
// callback para verificar a movimenta��o do 
// mouse na janela GLUT.
// Este c�digo est� baseado nos exemplos 
// dispon�veis no livro "OpenGL SuperBible", 
// 2nd Edition, de Richard S. e Wright Jr.

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

// Constantes
#define QUADRADO 1
#define TRIANGULO 2
#define LOSANGO   3

// Vari�veis
char texto[30];
GLfloat win_menu, r, g, b;
GLint view_w_menu, view_h_menu, primitiva;

// Fun��o que desenha um quadrado
void DesenhaQuadradoMenu(void) {
	glBegin(GL_QUADS);
	glVertex2f(-25.0f, -25.0f);
	glVertex2f(-25.0f, 25.0f);
	glVertex2f(25.0f, 25.0f);
	glVertex2f(25.0f, -25.0f);
	glEnd();
}

// Fun��o que desenha um tri�ngulo
void DesenhaTrianguloMenu(void) {
	glBegin(GL_TRIANGLES);
	glVertex2f(-25.0f, -25.0f);
	glVertex2f(0.0f, 25.0f);
	glVertex2f(25.0f, -25.0f);
	glEnd();
}

// Fun��o que desenha um losango
void DesenhaLosangoMenu(void) {
	glBegin(GL_POLYGON);
	glVertex2f(-25.0f, 0.0f);
	glVertex2f(0.0f, 25.0f);
	glVertex2f(25.0f, 0.0f);
	glVertex2f(0.0f, -25.0f);
	glEnd();
}

// Desenha um texto na janela GLUT
void DesenhaTextoMenu(char *string) {
	glPushMatrix();
	// Posi��o no universo onde o texto ser� colocado
	glRasterPos2f(-win_menu, win_menu - (win_menu * 0.08));
	// Exibe caracter a caracter
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *string++);
	glPopMatrix();
}

// Fun��o callback chamada para fazer o desenho
void DesenhaMenu(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);

	// Define a cor corrente
	glColor3f(r, g, b);

	// Desenha uma primitiva
	switch (primitiva) {
	case QUADRADO:
		DesenhaQuadradoMenu();
		break;
	case TRIANGULO:
		DesenhaTrianguloMenu();
		break;
	case LOSANGO:
		DesenhaLosangoMenu();
		break;
	}

	// Exibe a posi��o do mouse na janela
	glColor3f(1.0f, 1.0f, 1.0f);
	DesenhaTextoMenu(texto);

	glutSwapBuffers();
}

// Inicializa par�metros de rendering
void InicializaMenu(void) {
	// Define a cor de fundo da janela de visualiza��o como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	win_menu = 150.0f;
	primitiva = QUADRADO;
	r = 0.0f;
	g = 0.0f;
	b = 1.0f;
	strcpy(texto, "(0,0)");
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanelaMenu(GLsizei w, GLsizei h) {
	// Especifica as dimens�es da Viewport
	glViewport(0, 0, w, h);
	view_w_menu = w;
	view_h_menu = h;

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-win_menu, win_menu, -win_menu, win_menu);
}

// Fun��o callback chamada sempre que o mouse � movimentado
// sobre a janela GLUT com um bot�o pressionado
void MoveMouseBotaoPressionadoMenu(int x, int y) {
	sprintf(texto, "Botao pressionado (%d,%d)", x, y);
	glutPostRedisplay();
}

// Fun��o callback chamada sempre que o mouse � movimentado
// sobre a janela GLUT 
void MoveMouseMenu(int x, int y) {
	sprintf(texto, "(%d,%d)", x, y);
	glutPostRedisplay();
}

// Fun��o callback chamada para gerenciar eventos do teclado   
// para teclas especiais, tais como F1, PgDn e Home
void TeclasEspeciaisMenu(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		win_menu -= 10;
		if (win_menu < 10)
			win_menu = 10;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-win_menu, win_menu, -win_menu, win_menu);
	}
	if (key == GLUT_KEY_DOWN) {
		win_menu += 10;
		if (win_menu > 500)
			win_menu = 500;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-win_menu, win_menu, -win_menu, win_menu);
	}
	glutPostRedisplay();
}

// Gerenciamento do menu com as op��es de cores           
void MenuCor(int op) {
	switch (op) {
	case 0:
		r = 1.0f;
		g = 0.0f;
		b = 0.0f;
		break;
	case 1:
		r = 0.0f;
		g = 1.0f;
		b = 0.0f;
		break;
	case 2:
		r = 0.0f;
		g = 0.0f;
		b = 1.0f;
		break;
	}
	glutPostRedisplay();
}

// Gerenciamento do menu com as op��es de cores           
void MenuPrimitiva(int op) {
	switch (op) {
	case 0:
		primitiva = QUADRADO;
		break;
	case 1:
		primitiva = TRIANGULO;
		break;
	case 2:
		primitiva = LOSANGO;
		break;
	}
	glutPostRedisplay();
}

// Gerenciamento do menu principal           
void MenuPrincipal(int op) {
}

// Criacao do Menu
void CriaMenu() {
	int menu, submenu1, submenu2;

	submenu1 = glutCreateMenu(MenuCor);
	glutAddMenuEntry("Vermelho", 0);
	glutAddMenuEntry("Verde", 1);
	glutAddMenuEntry("Azul", 2);

	submenu2 = glutCreateMenu(MenuPrimitiva);
	glutAddMenuEntry("Quadrado", 0);
	glutAddMenuEntry("Tri�ngulo", 1);
	glutAddMenuEntry("Losango", 2);

	menu = glutCreateMenu(MenuPrincipal);
	glutAddSubMenu("Cor", submenu1);
	glutAddSubMenu("Primitivas", submenu2);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Fun��o callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN)
			CriaMenu();

	glutPostRedisplay();
}

// Programa Principal 
int mainMenu(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(350, 300);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Exemplo de Menu e Exibi��o de Caracteres");
	glutDisplayFunc(DesenhaMenu);
	glutReshapeFunc(AlteraTamanhoJanelaMenu);
	glutMotionFunc(MoveMouseBotaoPressionadoMenu);
	glutPassiveMotionFunc(MoveMouseMenu);
	glutMouseFunc(GerenciaMouse);
	glutSpecialFunc(TeclasEspeciaisMenu);
	InicializaMenu();
	glutMainLoop();
}
